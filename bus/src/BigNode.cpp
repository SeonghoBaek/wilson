/**
*
*  @author		Seongho Baek
*  @date		2014.08.12
*/

#include "Types.h"
#include "NodeBus.h"
#include "BigNode.h"
#include "Configure.h"
#include "NodeNetwork.h"
#include "XMLParser.h"
#include "XMLTypes.h"
#include "NodeEntry.h"
#include "Packet.h"
#include "Lock.h"
#include "ClientNode.h"

#include <stdlib.h>
#include <string.h>

#define SCHED sleep(0)

BigNode::BigNode(DefaultGlobalService *pService) : NodeAdapter(BIGNODE_NODE_NAME, this)
{
	this->mpService = pService;
	this->mpService->join(BIGNODE_NODE_NAME);

	this->mpThread = new BigNodeThread(this);
	this->mpThread->startThread();

	this->mpRunList = new ClientNode;
	this->mpFreeList = new ClientNode;
	this->mBigLock = Lock::createMutex();
}

int BigNode::nodeAction(void *data, unsigned int length, int type)
{
	LOGD("Queue Level: %d", this->mQ.getSize());
	switch(type)
	{
		case DB_MESSAGE:
		{
			this->mpService->cast(MGS_NODE_NAME, data, length);
			SCHED;
		}
		break;
		case BC_LOCAL_MESSAGE:
		{
			LOGD("BroadCast Message Arrived: %s", (char *)data);
			XMLParser *pXmlParser = XMLParser::getInstance();

			IXML *pIXml = pXmlParser->parseXML((char *)data, length);

			if (pIXml == NULL)
			{
				LOGW("Invalid NodeBus XML: %s", (char *)data);
				delete pXmlParser;

				return -1;
			}

			if (pIXml->getXMLType() == XML_TYPE_BUS)
			{
				NBUSXML *pBusXml = (NBUSXML *)pIXml;

				switch(pBusXml->getType())
				{
					case NBUS_TYPE_EVENT:
					{
						LOGI("EVENT Arrived");
					}
					break;
					case NBUS_TYPE_REQUEST:
					{

					}
					break;
					case NBUS_TYPE_RESPONSE:
					{

					}
					break;
					default:
					break;
				}
			}

			delete pIXml;
			delete pXmlParser;
		}
		break;
		case LOCAL_MESSAGE:
		{
			XMLParser *pXmlParser = XMLParser::getInstance();

			IXML *pIXml = pXmlParser->parseXML((char *)data, length);

			if (pIXml == NULL)
			{
				LOGW("Invalid NodeBus XML, Custom Data?: %s", (char *)data);
				delete pXmlParser;

				LOGI((char *)data);

				return -1;
			}

			if (pIXml->getXMLType() == XML_TYPE_BUS)
			{
				NBUSXML *pBusXml = (NBUSXML *)pIXml;

				switch(pBusXml->getType())
				{
					case NBUS_TYPE_EVENT:
					{
						LOGI("EVENT Arrived");
					}
					break;
					case NBUS_TYPE_REQUEST:
					{

					}
					break;
					case NBUS_TYPE_RESPONSE:
					{

					}
					break;
					default:
					break;
				}
			}

			delete pIXml;
			delete pXmlParser;
		}
		break;
		case GLOBAL_MESSAGE:
		{
			// Reserved.
		}
		break;
		case CLIENT_MESSAGE:
		case BC_CLIENT_MESSAGE:
		{
			NBUSPacket *pPacket = new NBUSPacket;

			pPacket->copyHeader(data, length);

			LOGD("BroadCast LOG Event to Clients");

			this->mpService->broadcast(pPacket->getPacket(), pPacket->getPacketLength(), NODE_ENTRY_CLIENT);

			delete pPacket;
		}
		break;
		default:
		break;
	}

	return 0;
}

int BigNode::broadcastInfoCommand()
{
	CommandXML *pCmdXml = new CommandXML;
	NBUSPacket *pPacket = new NBUSPacket;

	pCmdXml->setType(CMD_KEYWORD(INFO));
	char *xml = pCmdXml->toFullXML();

    pPacket->copyHeader(xml, (unsigned)strlen(xml));

    LOGD("BroadCast INFO Event to Clients");

	this->mpService->broadcast(pPacket->getPacket(), pPacket->getPacketLength(), NODE_ENTRY_CLIENT);

	delete pCmdXml;
	delete [] xml;
	delete pPacket;

	return 0;
}

int BigNode::broadcastLogCommand()
{
	CommandXML *pCmdXml = new CommandXML;
	NBUSPacket *pPacket = new NBUSPacket;

	pCmdXml->setType(CMD_KEYWORD(LOG));
	char *xml = pCmdXml->toFullXML();

    pPacket->copyHeader(xml, (unsigned)strlen(xml));

    LOGD("BroadCast LOG Event to Clients");

	this->mpService->broadcast(pPacket->getPacket(), pPacket->getPacketLength(), NODE_ENTRY_CLIENT);

	delete pCmdXml;
	delete [] xml;
	delete pPacket;

	return 0;
}

int BigNode::process()
{
	this->run();

	ClientNode *pClient = NULL;

    int loop = 1;

    while(loop == 1)
	{
		// Check Run List
		sleep(4);

		//LOGD("Update Similarity");
		LOCK(this->mBigLock)
		{
			// Check Free List
			LIST_FOR_EACH(pClient, this->mpRunList)
			{
				this->mpService->cast(pClient->getNodeName(), (char*)CMD_UPDATE_SIMILARITY, CMD_LENGTH, CUSTOM_MESSAGE);
				SCHED;
			}
		}
		//LOGD("Complete Update Similarity");

		sleep(1);

		//LOGD("Check Free List");
		LOCK(this->mBigLock)
		{
			// Check Free List
			LIST_FOR_EACH(pClient, this->mpFreeList)
			{
				bool isExit = FALSE;

				LOCK(pClient->mLock)
				{
					isExit = (pClient->mGarbageCollecting & pClient->isExited() & pClient->mRouterExit);

					pClient->mGarbageCollecting = TRUE;
				}

				if (isExit == TRUE)
				{
					ClientNode *pDelNode = NULL;

					pDelNode = pClient;
					LIST_DEL(pDelNode);
					pClient = this->mpFreeList;

					LOGD("Delete ClientNode: %s", pDelNode->getName());

					delete pDelNode;
				}
			}
		}
		//LOGD("Complete Check Free List");
	}

	return 0;
}

ClientNode* BigNode::DelNode(ClientNode* pNode)
{
	LOCK(this->mBigLock)
	{
		LIST_DEL(pNode);
	}

	return pNode;
}

ClientNode* BigNode::findNode(char *pName)
{
	ClientNode* pNode = NULL;
	ClientNode* pTarget = NULL;

	LOGD("Find Node: %s", pName);
	LOCK(this->mBigLock)
	{
		LIST_FOR_EACH(pNode, this->mpRunList)
		{
			if (strcmp(pNode->getName(), pName) == 0)
			{
				pTarget = pNode;
				break;
			}
		}
	}

	LOGD("Complete Find Node: %s", pName);

	return pTarget;
}

int BigNode::addRunList(ClientNode *pClientNode)
{
	LOGD("Add RunList: %s", pClientNode->getName());
	LOCK(this->mBigLock)
	{
		LIST_DEL(pClientNode);
		LIST_ADD(pClientNode, this->mpRunList);
	}
	LOGD("Complete Add RunList: %s", pClientNode->getName());

	return 0;
}

int BigNode::addFreeList(ClientNode* pClientNode)
{
	LOGD("Add FreeList: %s", pClientNode->getName());

	LOCK(this->mBigLock)
	{
		LIST_DEL(pClientNode);
		LIST_ADD(pClientNode, this->mpFreeList);
	}

	LOGD("Complete Add FreeList: %s", pClientNode->getName());

	return 0;
}

float BigNode::setVectorLength(int dim, float length, int session)
{
	return this->mSMPL.calMean(dim, length, session);
}

float BigNode::getVectorLength(int dim, int session)
{
	return this->mSMPL.getMean(dim, session);
}

