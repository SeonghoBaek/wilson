/**
*
*  @author		Seongho Baek
*  @date		2014.08.12
*/

#ifdef __cplusplus
extern "C" {
#endif

#include "Log.h"
#include "Types.h"
#include "DefaultGlobalService.h"
#include "Lock.h"
#include "Configure.h"
#include "NodePort.h"
#include "XMLTypes.h"
#include "XMLParser.h"
#include "Packet.h"
#include "ClientNode.h"
#include "BigNode.h"
#include "Normalizer.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <math.h>

char *CLIENT_STATE_TABLE[CLIENT_NONE] =
{
	(char*)"CLIENT_WAIT",
	(char*)"CLIENT_RUN",
	(char*)"CLIENT_DONE",
	(char*)"CLIENT_ERROR",
	(char*)"CLIENT_NET_ERROR",
	(char*)"CLIENT_ZOMBIE",
	(char*)"CLIENT_COMPLETE"
};

ClientNode::Router::Router(ClientNode *pClientNode)
{
	this->mpOwner = pClientNode;
	this->setThreadName((char *)"ClientNode::Router");
}

void ClientNode::Router::thread()
{
	this->mpOwner->readNode();

	//LOGE("ClientNode Router Thread Exit: %s", this->mpOwner->getName());
}

void ClientNode::exitNode()
{
	LOCK(this->mLock)
	{
		LOGD("Request Exit Node: %s", this->mClientName);
		NodeNetwork::sendNodeMessage(this->mClientNodeName, NULL, 0, KILL_MESSAGE);
		this->mExitNode = TRUE;
	}
}

ClientNode::ClientNode()
{
	LIST_INIT(this);
	mExitNode = FALSE;
	mpOwner = NULL;
	mLogVersion = 0;
	mLogSession = 0;
	mErrorId = NONE_ERROR;
	mSd = 0;
	mpRouter = NULL;
	mpBigNode = NULL;
	mpVectorList = new TermVector;
	mNumOfVectors = 0;
	mpPrevVector = NULL;
	mpTerms = NULL;
	mNumOfTerms = 0;
	mState = CLIENT_WAIT;
	mpLastRunPacket = NULL;
	mNewSession = TRUE;
	mLock = NULL;
	mRouterExit = FALSE;
	mGarbageCollecting = FALSE;
	mRes = 0;
	mSimilarity = 0;
	mGID = 0;
	mTID = 0xFFFFFFFF;
	mClientSession = 0;
}

ClientNode::ClientNode(int socket, char* pClientName, DefaultGlobalService *pOwner) : NodeAdapter(NULL, this)
{
	LIST_INIT(this);

	this->mErrorId = NONE_ERROR;
	mExitNode = FALSE;

	this->mSd = socket;

	this->mpOwner = pOwner;
	this->mpRouter = new ClientNode::Router(this);
	this->mLogVersion = 0;
	this->mLogSession = 0;
	this->mpBigNode = this->mpOwner->mpBigNode;
	this->mpVectorList = new TermVector;
	this->mNumOfVectors = 0;
	this->mpPrevVector = NULL;
	this->mState = CLIENT_WAIT;
	this->mpLastRunPacket = NULL;
	this->mpTerms = NULL;
	this->mNumOfTerms = 0;
	this->mNewSession = TRUE;
	this->mLock = Lock::createMutex();
	this->mRouterExit = FALSE;
	this->mGarbageCollecting = FALSE;
	this->mRes = 0;
	this->mSimilarity = 0;
	this->mGID = 0;
	this->mTID = 0xFFFFFFFF;
	this->mClientSession = 0;

	sprintf(this->mClientNodeName, "%s%s", DOMAIN_PREFIX, pClientName);

	this->setNodeName(this->mClientNodeName);

	strcpy(this->mClientName, pClientName);

	memset(this->mLogFileName, 0, LOG_FILE_NAME_LENGTH);

	// Find duplication
	LOGD("Find Node");
	ClientNode *pNode = this->mpBigNode->findNode(this->mClientName);
	LOGD("Complete Find Node");

	if (pNode)
	{
		LOCK(pNode->mLock)
		{
			//LOGI("DEBUG");

			if (pNode->mExitNode == TRUE)  // Node will be freed by itself.
			{
				//break;
				LOGD("Node Exiting");
			}
			else
			{
				LOGW("ClientNode Already Exist: %s", pNode->getName());

				this->mpBigNode->DelNode(pNode); // safe list del.
				NodeNetwork::sendNodeMessage(pNode->mClientNodeName, NULL, 0, KILL_MESSAGE);
				pNode->mExitNode = TRUE;

				switch (pNode->getState())
				{
					case CLIENT_RUN:
					{
						//LOGI("DEBUG");
						//LOGI("Prev Node is in Run List: %s", pNode->getName());
						if (pNode->mpPrevVector)
						{
							LIST_DEL(pNode->mpPrevVector);
							pNode->mpPrevVector->setGarbage(TRUE);

							this->mpPrevVector = pNode->mpPrevVector;
							pNode->mpPrevVector = NULL;
						}

						if (pNode->mpLastRunPacket)
						{
							this->mpLastRunPacket = pNode->mpLastRunPacket;
							pNode->mpLastRunPacket = NULL;

							this->mNewSession = FALSE;
							strcpy(this->mLogFileName, pNode->mLogFileName);
							strcpy(this->mInfoFileName, pNode->mInfoFileName);
							this->mLogVersion = pNode->mLogVersion;
						}

						this->mGID = pNode->getGID();
						this->mClientSession = pNode->getClientSession();
						this->mState = CLIENT_RUN;

						pNode->setState(CLIENT_ZOMBIE);
						this->mpBigNode->addFreeList(pNode);
					}
					break;
					default:
						pNode->setState(CLIENT_ZOMBIE);
						this->mpBigNode->addFreeList(pNode);
					break;
				}
			}
		}
	}
}

void ClientNode::loadVectorDef()
{
	char dirPath[LOG_FILE_NAME_LENGTH];

	memset(dirPath, 0, LOG_FILE_NAME_LENGTH);

	sprintf(dirPath, "%s%s", (char *)VEC_DIR, (char *)VEC_FILE_NAME);

	// Load Vector Term Definition
	FILE *frd = fopen(dirPath, "r");

	if (frd)
	{
		char line[LINE_BUFFER_LENGTH+1];

		memset(line,0,LINE_BUFFER_LENGTH+1);

		if (fgets(line, LINE_BUFFER_LENGTH, frd) == NULL)
		{
			LOGW("No Vector Definition. Set Definition in %s", dirPath);
			fclose(frd);
			return;
		}

		int numTerms = atoi(line);

		this->mpTerms = new char*[numTerms];
		this->mNumOfTerms = numTerms;

		for (int i = 0; i < numTerms; i++)
		{
			if (fgets(line, LINE_BUFFER_LENGTH, frd) == NULL)
			{
				if ( i + 1 != numTerms)
				{
					this->mNumOfTerms = i+1;
				}

				break;
			}

			this->mpTerms[i] = new char[strlen(line)];
			memset(this->mpTerms[i], 0, strlen(line));
			strncpy(this->mpTerms[i], line, strlen(line)-1);

			for (int j = 0; j < (int)strlen(this->mpTerms[i]); j++)
			{
				this->mpTerms[i][j] = toupper(this->mpTerms[i][j]);
			}
		}

		fclose(frd);
	}
	else
	{
		LOGW("No Vector Definition. Set Definition in %s", dirPath);
	}
}

void ClientNode::createLogFile(const char* pLogDirName)
{
	time_t now;
	time(&now);

	char dirPath[LOG_FILE_NAME_LENGTH];
	char curTime[LOG_FILE_NAME_LENGTH];
	char *t = ctime(&now);

	memset(dirPath, 0, LOG_FILE_NAME_LENGTH);
	memset(curTime, 0, LOG_FILE_NAME_LENGTH);

	sprintf(dirPath, "%s%s", (char *)LOG_DIR, pLogDirName);
	strncpy(curTime, t, strlen(t) - 1);

	mkdir(dirPath, 0755);

	sprintf(this->mLogFileName, "%s%s/%s%s", (char *)LOG_DIR, pLogDirName, curTime, (char *)LOG_EXT);
	sprintf(this->mInfoFileName, "%s%s/%s%s", (char *)LOG_DIR, pLogDirName, curTime, (char *)INFO_EXT);

	int fd = creat(this->mLogFileName, 0755);

	close(fd);

	fd = creat(this->mInfoFileName, 0755);

	close(fd);

	//LOGI("Log File Name: %s", this->mLogFileName);
}

void ClientNode::prepare(const char* pLogDirName)
{
	if (this->mpOwner)
	{
		LOGD("Prepare Node %s", this->mClientName);

		if (this->mNewSession == TRUE)
		{
			LOGD("Create New Log File %s", this->mClientName);
			this->createLogFile(pLogDirName);
		}

		this->loadVectorDef();

		LOGD("Run ClientNode %s", this->mClientName);
		this->run();

		LOGD("Start Router Thread %s", this->mClientName);
		this->mpRouter->startThread();

		LOGD("Join Node %s", this->mClientName);
		this->mpOwner->join(this->mClientNodeName, NODE_ENTRY_CLIENT);

		this->updateStatus();
		this->mpBigNode->addRunList(this);
	}
}

int ClientNode::normalizeLogData(char *data, int length)
{
	TermVector *tv = Normalizer::transform(data, length, this->mpTerms, this->mNumOfTerms);

	_GOODNESS(tv, -1);


	if (this->mpPrevVector)
	{
		// Calculate Distance.
		int dist = tv->getDistance(this->mpPrevVector);

		tv->setDistance(dist);

		TermVector *pMinVector = NULL;

		LIST_FOR_EACH(pMinVector, this->mpVectorList)
		{
			//LOGI("Distance: %d", pMinVector->getDistance());
			if (tv->getLogSession() == pMinVector->getLogSession())
			{
				LIST_DEL(pMinVector);
				delete pMinVector;
				this->mNumOfVectors--;

				break;
			}
		}

		if (this->mNumOfVectors >= TOP_MAINTAIN_SIZE)
		{
			pMinVector = LIST_PREV(this->mpVectorList);

			if (pMinVector->getDistance() >= tv->getDistance())
			{
				tv->setGarbage(TRUE);
			}
			else
			{
				LIST_FOR_EACH(pMinVector, this->mpVectorList)
				{
					if (tv->getDistance() > pMinVector->getDistance())
					{
						break;
					}
				}

				pMinVector = LIST_PREV(pMinVector);

				LIST_ADD(tv, pMinVector);

				pMinVector = LIST_PREV(this->mpVectorList);

				LIST_DEL(pMinVector);

				delete pMinVector;
			}
		}
		else
		{
			pMinVector = LIST_PREV(this->mpVectorList);

			LIST_FOR_EACH(pMinVector, this->mpVectorList)
			{
				if (tv->getDistance() > pMinVector->getDistance())
				{
					break;
				}
			}

			pMinVector = LIST_PREV(pMinVector);

			LIST_ADD(tv, pMinVector);

			this->mNumOfVectors++;
		}

		/*
		if (dist > 10)
		{
			Term *pTerm = NULL;

			//LOGI("Distance: %d", dist);

			char buff[1024];
			memset(buff, 0, 1024);
			sprintf(buff, "Distance: %d,", dist);
			char tmp[80];
			memset(tmp, 0, 80);

			LIST_FOR_EACH(pTerm, tv->getTermList())
			{
				//LOGI("Term %s: %d %d", pTerm->value, pTerm->freq, pTerm->pri);
				sprintf(tmp, "%s:%d ", pTerm->value, pTerm->freq);
				strcat(buff, tmp);
			}

			LOGD("Vector Summary %s:", this->mClientName);
			LOGD(buff);
		}
		*/
	}

	if (this->mpPrevVector && this->mpPrevVector->isGarbage() == TRUE) delete this->mpPrevVector;
	this->mpPrevVector = tv;

	return 0;
}

void ClientNode::processCommand(NBUSPacket *pPacket)
{
	CommandXML *pCmdXml = (CommandXML *)pPacket->getXML();

	switch (this->mState)
	{
		case CLIENT_RUN:
		{
			if (pCmdXml->getType() == CMD_TYPE_EXIT)
			{
				this->mState = CLIENT_ZOMBIE;
				this->mpBigNode->addFreeList(this);
				NodeNetwork::sendNodeMessage(this->mClientNodeName, NULL, 0, KILL_MESSAGE);
				this->mExitNode = TRUE;
				this->updateStatus();
			}
			else
			{
				if (this->mpLastRunPacket) delete this->mpLastRunPacket;
				this->mpLastRunPacket = new NBUSPacket;
				this->mpLastRunPacket->parserPacket(pPacket->getPacket(), pPacket->getPacketLength()); // Back Up.

				this->writeNode(pPacket->getPacket(), pPacket->getPacketLength());
			}
		}
		break;
		case CLIENT_DONE:
		{
			if (pCmdXml->getType() == CMD_TYPE_COMPLETE)
			{
				this->mState = CLIENT_COMPLETE;
				this->mpBigNode->addFreeList(this);
				NodeNetwork::sendNodeMessage(this->mClientNodeName, NULL, 0, KILL_MESSAGE);
				this->mExitNode = TRUE;
				this->updateStatus();
			}
			else
			{
				if (this->mpLastRunPacket) delete this->mpLastRunPacket;
				this->mpLastRunPacket = new NBUSPacket;
				this->mpLastRunPacket->parserPacket(pPacket->getPacket(), pPacket->getPacketLength()); // Back Up.

				this->writeNode(pPacket->getPacket(), pPacket->getPacketLength());

				this->mState = CLIENT_RUN;
				this->updateStatus();
			}
		}
		break;
		case CLIENT_WAIT:
		{
			if (pCmdXml->getType() == CMD_TYPE_EXIT)
			{
				this->mState = CLIENT_ZOMBIE;
				this->mpBigNode->addFreeList(this);
				NodeNetwork::sendNodeMessage(this->mClientNodeName, NULL, 0, KILL_MESSAGE);
				this->mExitNode = TRUE;
				this->updateStatus();
			}
		}
		break;
		default:
		break;
	}
}

void ClientNode::processEvent(NBUSPacket *pLPacket)
{
	EventXML *pEventXml = (EventXML *)pLPacket->getXML();

	switch(pEventXml->getType())
	{
		case EVT_TYPE_READY:
		{
			LOGD("EVENT CLIENT READY : %s", this->getName());

			EventXML* pEventXml = new EventXML;
			char* xml = NULL;

			// Register Notification
			pEventXml->setType(EVT_KEYWORD(REGOK));
			xml = pEventXml->toXML();

			NBUSPacket * pPacket = new NBUSPacket;

			pPacket->copyHeader(xml, (unsigned int)strlen(xml));

			this->writeNode(pPacket->getPacket(), pPacket->getPacketLength());

			delete pEventXml;
			delete [] xml;

			//this->mState = CLIENT_RUN;
			this->updateStatus();

			//sleep(1); // Secure DB Update

			CommandXML *pCmdXml = new CommandXML;

			pCmdXml->setType(CMD_KEYWORD(LOG)); // Start Log Send.
			xml = pCmdXml->toFullXML();

			pPacket->copyHeader(xml, (unsigned int)strlen(xml));

			LOGD("LOG Command to Client %s", this->getName());
			this->writeNode(pPacket->getPacket(), pPacket->getPacketLength());

			if (this->mpLastRunPacket == NULL) this->mpLastRunPacket = new NBUSPacket;
			this->mpLastRunPacket->parserPacket(pPacket->getPacket(), pPacket->getPacketLength()); // Back Up.

			delete [] xml;
			delete pCmdXml;
			delete pPacket;
		}
		break;
		case EVT_TYPE_LOG:
		{
			int fd = -1;
			int nWritten = 0;
			char version[80];
			int logSegment = 0;

			if (this->mState != CLIENT_RUN)
			{
				LOGI("Client %s Wait State. Trash Log.", this->getName());
				break; // WAIT, COMPLETE, ERROR: No not save log data.
			}

			if (this->mClientSession == 0) break; // Test Not Started Yet.

			fd = open(this->mLogFileName, O_RDWR | O_APPEND, 0755);
			f_offset_t offset = (f_offset_t)lseek(fd, 0, SEEK_END);
			time_t now;

			time(&now);

			char *t = ctime(&now);

			LOGD("Save Log %d bytes from %s", pLPacket->getDataLength(), this->mClientName);

			memset(version, 0, 80);
			sprintf(version, "\n<log ver %d %s\n", mLogVersion, t);

			nWritten = (int)write(fd, version, strlen(version));
			nWritten = (int)write(fd, pLPacket->getData(), pLPacket->getDataLength());

			memset(version, 0, 80);
			sprintf(version, "\n>log ver %d\n", mLogVersion);

			nWritten = (int)write(fd, version, strlen(version));

			mLogVersion++;

			logSegment = mLogVersion/LOG_SEGMENT_SIZE;

			close(fd);

			if (this->normalizeLogData((char*) pLPacket->getData(), pLPacket->getDataLength()) != -1)
			{
				char *vectorJSON = NULL;
				char *tmpJSON = NULL;

				this->mpPrevVector->setOffset(offset);
				this->mpPrevVector->setVersion(this->mLogVersion-1);
				this->mpPrevVector->setLogSession(this->mLogSession);
				this->mpBigNode->setVectorLength(this->mLogSession++, this->mpPrevVector->getLength(), this->mClientSession);

				#if (SAVE_PARTIAL_LOG == 1)
				if (this->mpPrevVector->isGarbage() != TRUE)
				{
				#endif
					tmpJSON = this->mpPrevVector->toJSON((char*)pLPacket->getData());

					vectorJSON = new char[MAX_VECTOR_LOG_LENGTH+1];
					memset(vectorJSON, 0, MAX_VECTOR_LOG_LENGTH+1);

					sprintf(vectorJSON,
							"log${\"cid\":%u,\"session\":%u,\"segment\":%d,\"client\":\"%s\",\"tid\":%u,\"file\":\"%s\",",
							this->mGID,
							this->mClientSession,
							logSegment,
							this->mClientName,
							this->mTID,
							this->mLogFileName);

					strcat(vectorJSON, tmpJSON);
					strcat(vectorJSON, "}");

					if (tmpJSON) delete [] tmpJSON;

					this->mpOwner->cast(BIGNODE_NODE_NAME, vectorJSON, strlen(vectorJSON), DB_MESSAGE);
					//NodeNetwork::sendNodeMessage(BIGNODE_NODE_NAME, vectorJSON, strlen(vectorJSON), DB_MESSAGE);

					if (vectorJSON) delete [] vectorJSON;
				#if (SAVE_PARTIAL_LOG == 1)
				}
				#endif
			}
		}
		break;
		case EVT_TYPE_INFO:
		{
			int fd = open(this->mInfoFileName, O_RDWR | O_APPEND, 0755);
			int nWritten = 0;
			char version[80];
			time_t now;

			time(&now);

			char *t = ctime(&now);

			LOGD("Save Info %d bytes from %s", pLPacket->getDataLength(), this->mClientName);

			memset(version, 0, 80);
			sprintf(version, "\n<info ver %d %s\n", mLogVersion, t);

			nWritten = (int)write(fd, version, strlen(version));
			nWritten = (int)write(fd, pLPacket->getData(), pLPacket->getDataLength());

			memset(version, 0, 80);
			sprintf(version, "\n>info ver %d\n", mLogVersion);

			nWritten = (int)write(fd, version, strlen(version));

			close(fd);
		}
		break;
		case EVT_TYPE_ERROR:
		{
			int id = pEventXml->getID();

			switch(id)
			{
				case ERROR_KEYWORD(SYS):
				{
					LOGD("System Error: %s", this->mClientName);

					this->mErrorId = SYSTEM_ERROR;
					this->mState = CLIENT_ERROR;
					this->mpBigNode->addFreeList(this);
					NodeNetwork::sendNodeMessage(this->mClientNodeName, NULL, 0, KILL_MESSAGE);
					this->mExitNode = TRUE;
					this->updateStatus();
				}
				break;
				case ERROR_KEYWORD(CMD):
				{
					LOGD("Command Error: %s", this->mClientName);

					this->mErrorId = COMMAND_ERROR;
					this->mState = CLIENT_ERROR;
					this->mpBigNode->addFreeList(this);
					NodeNetwork::sendNodeMessage(this->mClientNodeName, NULL, 0, KILL_MESSAGE);
					this->mExitNode = TRUE;
					this->updateStatus();
				}
				break;
				default:
				break;
			}
		}
		break;
		case EVT_TYPE_IMG:
		{
			int imgFileNameLength = (int)strlen(this->mLogFileName);
			char imgFileName[imgFileNameLength + 1];

			LOGD("Save Image: %d bytes from %s", pLPacket->getDataLength(), this->mClientName);

			memset(imgFileName, 0, imgFileNameLength+1);

			strncpy(imgFileName, this->mLogFileName, imgFileNameLength-4);
			strcat(imgFileName, ".jpg");

			//LOGI("Image File: %s", imgFileName);
			int fd = open(imgFileName, O_RDWR | O_CREAT, 0755);
			int nWritten = 0;

			nWritten = (int)write(fd, pLPacket->getData(), pLPacket->getDataLength());

			close(fd);
		}
		break;
		case EVT_TYPE_CMD:
		{
			int res = pEventXml->getRes();

			LOGD("Command Response: %d from %s", res, this->mClientName);

			this->mErrorId = NONE_ERROR;
			this->mState = CLIENT_DONE;
			this->mRes = res;
			this->updateStatus();
		}
		break;
		case EVT_TYPE_TC:
		{
			int res = pEventXml->getRes();
			int id = pEventXml->getID();

			LOGD("TestCase %d , Response: %d from %s", id, res, this->mClientName);

			this->mErrorId = NONE_ERROR;
			this->mState = CLIENT_DONE;
			this->mRes = res;
			this->updateStatus();
		}
		break;
		default:
		break;
	}
}

int ClientNode::nodeCallback(void *data, unsigned int length, int type)
{
	LOCK(this->mLock)
	{
		if (this->mState == CLIENT_ZOMBIE || this->mState == CLIENT_NET_ERROR) break;
		if (this->mGarbageCollecting == TRUE) break;
		if (this->mExitNode == TRUE) break;

		//LOGD("Message: %s, type: %d", (char *)data, type);

		switch (type)
		{
			case LOCAL_MESSAGE:
			case BC_LOCAL_MESSAGE:
			{
				XMLParser *pXmlParser = XMLParser::getInstance();

				IXML *pIXml = pXmlParser->parseXML((char *)data, length);

				if (pIXml == NULL)
				{
					LOGW("Invalid XML, Custom Data?: %s", (char *)data);
					delete pXmlParser;

					LOGI((char *)data);

					return -1;
				}

				switch(pIXml->getXMLType())
				{
					case XML_TYPE_EVENT:
					break;
					case XML_TYPE_COMMAND:
					{
						CommandXML *pCmdXml = (CommandXML*)pIXml;


						switch (pCmdXml->getType())
						{
							case CMD_TYPE_START:
							{
								ArgumentXML *pArgList = pCmdXml->getArgumentList();

								ArgumentXML *pArg;
								unsigned int session = 0;
								unsigned int tid = 0;

								LIST_FOR_EACH(pArg, pArgList)
								{
									if (strcmp(pArg->getName(), "session") == 0)
									{
										session = atoi(pArg->getValue());

										continue;
									}

									if (strcmp(pArg->getName(), "tid") == 0)
									{
										tid = atoi(pArg->getValue());
									}
								}

								this->setClientSession(session);
								this->setTID(tid);
								this->mState = CLIENT_RUN;
							}
							break;
							case CMD_TYPE_STOP:
							{
								this->mState = CLIENT_STOP;
								this->mRes = 2; // unknown
								this->mClientSession = 0;
							}
							break;
							case CMD_TYPE_COMPLETE:
							{
								ArgumentXML *pArgList = pCmdXml->getArgumentList();

								ArgumentXML *pArg;
								int result = 2;

								LIST_FOR_EACH(pArg, pArgList)
								{
									if (strcmp(pArg->getName(), "result") == 0)
									{
										result = atoi(pArg->getValue());

										break;
									}
								}

								this->mState = CLIENT_COMPLETE;
								this->mRes = result;
								this->mClientSession = 0;
							}
							break;
							default:
							break;
						}
					}
					break;
					default:
					break;
				}

				LOGD("Local Message Arrived: %s", this->getName());

				delete pXmlParser;
				delete pIXml;
			}
			break;
			case CUSTOM_MESSAGE:
			{
				//LOGD("CUSTOM Message Arrived: %s, %s", this->getName(), (char *)data);

				if (strncmp((char*)data, (char*)CMD_UPDATE_SIMILARITY, CMD_LENGTH) == 0)
				{
					// Update Similarity.
					this->updateSimilarity();
				}
				else if (strncmp((char*)data, CMD_START_LOG, CMD_LENGTH) == 0)
				{
					NBUSPacket *pPacket = new NBUSPacket;
					CommandXML *pCmdXml = new CommandXML;

					pCmdXml->setType(CMD_KEYWORD(LOG)); // Start Log Send.
					char *xml = pCmdXml->toFullXML();

					pPacket->copyHeader(xml, (unsigned int)strlen(xml));

					LOGD("LOG Command to Client %s", this->getName());
					this->writeNode(pPacket->getPacket(), pPacket->getPacketLength());

					if (this->mpLastRunPacket == NULL) this->mpLastRunPacket = new NBUSPacket;
					this->mpLastRunPacket->parserPacket(pPacket->getPacket(), pPacket->getPacketLength()); // Back Up.

					delete [] xml;
					delete pCmdXml;
					delete pPacket;
				}
				else if (strncmp((char*)data, CMD_STOP_LOG, CMD_LENGTH) == 0)
				{
					NBUSPacket *pPacket = new NBUSPacket;
					CommandXML *pCmdXml = new CommandXML;

					pCmdXml->setType(CMD_KEYWORD(LOGOFF)); // Start Log Send.
					char *xml = pCmdXml->toFullXML();

					pPacket->copyHeader(xml, (unsigned int)strlen(xml));

					LOGD("LOGOFF Command to Client %s", this->getName());
					this->writeNode(pPacket->getPacket(), pPacket->getPacketLength());

					if (this->mpLastRunPacket == NULL) this->mpLastRunPacket = new NBUSPacket;
					this->mpLastRunPacket->parserPacket(pPacket->getPacket(), pPacket->getPacketLength()); // Back Up.

					delete [] xml;
					delete pCmdXml;
					delete pPacket;
				}
			}
			break;
			case GLOBAL_MESSAGE:
			{
				NBUSPacket packet;

				packet.parserPacket(data, length);

				LOGD("Global Message Arrived from %s", this->getName());

				IXML *pIXml = packet.getXML();

				switch(pIXml->getXMLType())
				{
					case XML_TYPE_EVENT:
					{
						this->processEvent(&packet);
					}
					break;
					case XML_TYPE_COMMAND:
					{
						this->processCommand(&packet);
					}
					break;
					default:
					break;
				}
			}
			break;
			case CLIENT_MESSAGE:
			case BC_CLIENT_MESSAGE:
			{
				NBUSPacket *pPacket = (NBUSPacket *)data;
				this->writeNode(pPacket->getPacket(), pPacket->getPacketLength());

				if (this->mpLastRunPacket == NULL) this->mpLastRunPacket = new NBUSPacket;
				this->mpLastRunPacket->parserPacket(pPacket->getPacket(), pPacket->getPacketLength()); // Back Up.
			}
			break;
			default:
			break;
		}
	}

	return 0;
}

ClientNode::~ClientNode()
{
	if (this->mSd > 0)
	{
		close(this->mSd);
	}

	if (this->mpPrevVector && this->mpPrevVector->isGarbage() == TRUE)
	{
		delete this->mpPrevVector;
	}

	TermVector *pVector = NULL;

	LIST_FOR_EACH(pVector, this->mpVectorList)
	{
		LIST_DEL(pVector);

		delete pVector;

		pVector = this->mpVectorList;
	}

	delete this->mpVectorList;

	if (this->mpTerms)
	{
		for (int i = 0; i < this->mNumOfTerms; i++)
		{
			if (this->mpTerms[i]) delete [] this->mpTerms[i];
		}

		delete [] this->mpTerms;
	}

	if (this->mpLastRunPacket) delete this->mpLastRunPacket;

	if (this->mLock) Lock::deleteMutex(this->mLock);

	if (this->mpRouter) delete this->mpRouter;
}


float ClientNode::getSimilarity()
{
	float similarity = 0;

	similarity = this->mSimilarity;

	return similarity;
}

float ClientNode::updateSimilarity()
{
	if (this->mState == CLIENT_WAIT) return 0;

	TermVector *pMinVector = NULL;
	float similarity = this->mSimilarity;

	LIST_FOR_EACH(pMinVector, this->mpVectorList)
	{
		float avg = this->mpBigNode->getVectorLength(pMinVector->getLogSession(), this->mClientSession);
		similarity += pow(avg - pMinVector->getLength(), 2);
	}

	similarity = sqrt(similarity);
	this->mSimilarity = similarity;

	LOGD("Similarity %s: %f", this->mClientName, similarity);

	/*
	CommandXML *pCmdXml = new CommandXML;
	NBUSPacket *pPacket = new NBUSPacket;
	ArgumentXML *pArgXml = new ArgumentXML;

	pCmdXml->setType(CMD_KEYWORD(INFO));

	pArgXml->setValue(INFO_TYPE_SOC);
	pCmdXml->addArgument(pArgXml);

	char *xml = pCmdXml->toFullXML();

    pPacket->copyHeader(xml, (unsigned int)strlen(xml));

	if (this->writeNode(pPacket->getPacket(), pPacket->getPacketLength()) == 0)
	{
		LOGD("ClientNode Write Disconnected: %s", this->mClientName);
		NodeNetwork::sendNodeMessage(this->mClientNodeName, NULL, 0, KILL_MESSAGE);
		this->mExitNode = TRUE;
		this->mState = CLIENT_NET_ERROR;

		this->mpBigNode->addFreeList(this);
	}

	delete pCmdXml;
	delete [] xml;
	delete pPacket;
	*/

	this->updateStatus();

	return similarity;
}

void ClientNode::cleanUp()
{
	LOCK(this->mLock)
	{
		if (this->mExitNode == TRUE)
		{
			LOGD("Exit ClientNode:%s", this->mClientName);
		}
		else // Must be Error.
		{
			this->mState = CLIENT_NET_ERROR;
			this->updateStatus();

			NodeNetwork::sendNodeMessage(this->mClientNodeName, NULL, 0, KILL_MESSAGE);
			this->mExitNode = TRUE;

			this->mpBigNode->addFreeList(this);
		}

		if (this->mSd > 0) close(this->mSd);
		this->mSd = -1;
	}
}

int ClientNode::safeRead(void *buff, unsigned int length)
{
	int recv = 0;

	struct pollfd fds[1];

	fds[0].fd = this->mSd;
	fds[0].events = POLLIN;
	fds[0].revents = 0;

	for(;;)
	{
		poll(fds, 1, SOCKET_TIME_OUT);

		if (!(fds[0].revents & POLLIN))
		{
			bool bExit = FALSE;

			LOCK(this->mLock)
			{
				if ( this->mExitNode != FALSE )
				{
					recv = -1;
					this->mErrorId = NONE_ERROR;

					bExit = TRUE;
				}
			}

			if (bExit == TRUE)
			{
				recv = -2;

				break;
			}

			continue;
		}

		recv = (int)read(this->mSd, buff, length);

		if (recv <= 0)
		{
			strerror(errno);

			LOCK(this->mLock)
			{
				this->mErrorId = CONNECTION_CLOSED;
			}

			LOGE("Connection Closed: %s", this->mClientName);
		}

		break;
	}

	return recv;
}

void ClientNode::readNode()
{
    int packetPreffixLength = NBUS_PACKET_HEADER_LEGNTH_BYTES + strlen(NBUS_PACKET_START_CODE);
    char *packetPreffix = new char[packetPreffixLength];

	for (;;)
	{
		int readBytes = 0;
		int wantBytes = 0;

		wantBytes = packetPreffixLength;

		do
		{
			int recv = this->safeRead(packetPreffix + readBytes, wantBytes);

			if (recv <= 0)
			{
				readBytes = 0;
				break;
			}
			readBytes += recv;
			wantBytes -= recv;
		}
		while(readBytes < packetPreffixLength);

		if (readBytes <= 0)
		{
			this->cleanUp();
			break;
		}

		if (strncmp(packetPreffix, (char *)NBUS_PACKET_START_CODE, strlen(NBUS_PACKET_START_CODE)))
		{
			LOGE("Invalid Start Code");
			this->mErrorId = INVALID_START_CODE;
			continue;
		}

		int headerLength = 0;

		headerLength = *(int *)(strlen(NBUS_PACKET_START_CODE) + packetPreffix);

		char *packetHeader = new char[headerLength];

		readBytes = 0;
		wantBytes = headerLength;

		do
		{
			int recv = this->safeRead(packetHeader + readBytes, wantBytes);

			if (recv <= 0)
			{
				readBytes = 0;
				break;
			}
			wantBytes -= recv;
			readBytes += recv;
		}
		while(readBytes < headerLength);

		if (readBytes <= 0)
		{
			delete [] packetHeader;
			this->cleanUp();
			break;
		}

		NBUSPacket packet;

		if (packet.parseHeader(packetHeader, headerLength) < 0)
		{
			LOGE("Packet Error");

			LOCK(this->mLock)
			{
				this->mErrorId = PACKET_HEADER_ERROR;
			}

			delete [] packetHeader;
			continue;
		}

		memcpy(packet.getPacket(), packetPreffix, packetPreffixLength);

		delete [] packetHeader;

		if (packet.getDataLength())
		{
			readBytes = 0;
			wantBytes = packet.getDataLength();

			do
			{
				int recv = this->safeRead((char *)packet.getData() + readBytes, wantBytes);

				if (recv <= 0)
				{
					readBytes = 0;
					break;
				}
				wantBytes -= recv;
				readBytes += recv;
			}
			while(readBytes < packet.getDataLength());

			if (readBytes <= 0)
			{
				this->cleanUp();
				break;
			}

			if (readBytes != packet.getDataLength())
			{
				LOGE("Packet Data Error");

				LOCK(this->mLock)
				{
					this->mErrorId = PACKET_DATA_ERROR;
				}

				continue;
			}
		}

		NBUS_CMD item;

        item.mpData = new char[packet.getPacketLength()];
		memcpy(item.mpData, packet.getPacket(), packet.getPacketLength());
		item.mLength = packet.getPacketLength();
		item.mType = GLOBAL_MESSAGE;

		// Queueing
		LOCK(this->mLock)
		{
			this->mQ.push(item);
			this->mpLooper->wakeup();
		}
	}

	if (packetPreffix) delete [] packetPreffix;

	LOCK(this->mLock)
	{
		LOGD("Router EXIT");
		this->mRouterExit = TRUE;
	}
}

unsigned int ClientNode::writeNode(const void *data, unsigned int length)
{
	unsigned int numWritten = 0;
	unsigned int sizeToSend = length;

	do
	{
		int r = (int)write(this->mSd, (char *)data + numWritten, sizeToSend);

		if (r <= 0)
		{
			strerror(errno);
			LOGE("Client Dead? : %s", this->mClientName);
			numWritten = 0;
			break;
		}

		sizeToSend -= r;
		numWritten += r;
	}
	while(sizeToSend);

	return numWritten;
}

void ClientNode::setName(const char *pName)
{
	if (pName)
	{
		memcpy(this->mClientNodeName, pName, NODE_NAME_LENGTH);
	}
}

int ClientNode::setRun()
{
	//LOGD("Update RUN Status: %s", this->getName());

	char statusJSON[MAX_CLIENT_STATUS_JSON_LENGTH];

	memset(statusJSON, 0, MAX_CLIENT_STATUS_JSON_LENGTH);

	/*
	char encodeJSON[MAX_CLIENT_STATUS_JSON_LENGTH];
	memset(encodeJSON, 0, MAX_CLIENT_STATUS_JSON_LENGTH);

	if (this->getLastRunPacket() == NULL)
	{
		sprintf(statusJSON, "client${\"_id\":%u,\"client\":\"%s\",\"state\":\"%s\",\"similarity\":%f,\"xml\":\"NONE\",\"logfile\":\"%s\"}",
			this->getGID(),
			this->getName(),
			CLIENT_STATE_TABLE[this->getState()],
			this->getSimilarity(),
			this->getLogFileName()
			);
	}
	else
	{
		char *xml = (char*)this->getLastRunPacket()->getHeader();

		for (int i = 0, j = 0; i < this->getLastRunPacket()->getHeaderLength(); i++, j++)
		{
			if (xml[i] == '"')
			{
				encodeJSON[j] = '\'';
			}
			else
			{
				encodeJSON[j] = xml[i];
			}
		}

		sprintf(statusJSON, "client${\"_id\":%u,\"client\":\"%s\",\"state\":\"%s\",\"similarity\":%f,\"xml\":\"%s\",\"logfile\":\"%s\"}",
				this->getGID(),
				this->getName(),
				CLIENT_STATE_TABLE[this->getState()],
				this->getSimilarity(),
				encodeJSON,
				this->getLogFileName());
	}
	*/

	sprintf(statusJSON,
			"client${\"_id\":%u,\"client\":\"%s\",\"session\":%u,\"file\":\"%s\",\"tid\":%u,\"status\":\"%s\",\"similarity\":%f,\"version\":%d}",
			this->getGID(),
			this->getName(),
			this->getClientSession(),
			this->getLogFileName(),
			this->getTID(),
			CLIENT_STATE_TABLE[this->getState()],
			this->getSimilarity(),
			0 // version 0
			);

	//this->mpOwner->cast(MGS_NODE_NAME, statusJSON, strlen(statusJSON));
	this->mpOwner->cast(BIGNODE_NODE_NAME, statusJSON, strlen(statusJSON), DB_MESSAGE);

	//LOGD("Complete Update RUN Status: %s", this->getName());

	return 0;
}

int ClientNode::setError()
{
	char statusJSON[MAX_CLIENT_STATUS_JSON_LENGTH];

	memset(statusJSON, 0, MAX_CLIENT_STATUS_JSON_LENGTH);

	sprintf(statusJSON, "error${\"client\":\"%s\",\"tid\":%u,\"session\":%u,\"description\":\"%s\",\"version\":%d}",
			this->getName(),
			this->getTID(),
			this->getClientSession(),
			CLIENT_STATE_TABLE[this->getState()],
			0);

	//this->mpOwner->cast(MGS_NODE_NAME, statusJSON, strlen(statusJSON));
	this->mpOwner->cast(BIGNODE_NODE_NAME, statusJSON, strlen(statusJSON), DB_MESSAGE);

	return 0;
}

int ClientNode::setComplete()
{
	char statusJSON[MAX_CLIENT_STATUS_JSON_LENGTH];
	char encodeJSON[MAX_CLIENT_STATUS_JSON_LENGTH];

	memset(statusJSON, 0, MAX_CLIENT_STATUS_JSON_LENGTH);
	memset(encodeJSON, 0, MAX_CLIENT_STATUS_JSON_LENGTH);

	char *xml = (char*)this->getLastRunPacket()->getHeader();

	for (int i = 0, j = 0; i < this->getLastRunPacket()->getHeaderLength(); i++, j++)
	{
		if (xml[i] == '"')
		{
			encodeJSON[j] = '\'';
		}
		else
		{
			encodeJSON[j] = xml[i];
		}
	}

	sprintf(statusJSON,
			"complete${\"client\":\"%s\",\"tid\":%d,\"session\":%u,\"similarity\":%f,\"result\":%d,\"file\":\"%s\",\"version\":%d}",
			this->getName(),
			this->getTID(),
			this->getClientSession(),
			this->getSimilarity(),
			this->getRes(),
			this->getLogFileName(),
			0);

	//this->mpOwner->cast(MGS_NODE_NAME, statusJSON, strlen(statusJSON));
	this->mpOwner->cast(BIGNODE_NODE_NAME, statusJSON, strlen(statusJSON), DB_MESSAGE);

	return 0;
}

int ClientNode::setWait()
{
	char statusJSON[MAX_CLIENT_STATUS_JSON_LENGTH];

	memset(statusJSON, 0, MAX_CLIENT_STATUS_JSON_LENGTH);

	sprintf(statusJSON,
			"client${\"_id\":%u,\"client\":\"%s\",\"session\":%u,\"file\":\"%s\",\"tid\":%u,\"status\":\"%s\",\"similarity\":%f,\"version\":%d}",
			this->getGID(),
			this->getName(),
			this->getClientSession(),
			this->getLogFileName(),
			this->getTID(),
			CLIENT_STATE_TABLE[this->getState()],
			this->getSimilarity(),
			0 // version 0
			);

	//this->mpOwner->cast(MGS_NODE_NAME, statusJSON, strlen(statusJSON));
	this->mpOwner->cast(BIGNODE_NODE_NAME, statusJSON, strlen(statusJSON), DB_MESSAGE);

	return 0;
}

int ClientNode::updateStatus()
{
	int status = this->getState();

	switch(status)
	{
		case CLIENT_WAIT:
		{
			this->setWait();
		}
		break;
		case CLIENT_RUN:
		case CLIENT_DONE:
		{
			this->setRun();
		}
		break;
		case CLIENT_ZOMBIE:
		case CLIENT_ERROR:
		case CLIENT_NET_ERROR:
		{
			this->setError();
		}
		break;
		case CLIENT_COMPLETE:
		{
			this->setComplete();
		}
		break;
		default:
		break;
	}

	return 0;
}

#ifdef __cplusplus
}
#endif




