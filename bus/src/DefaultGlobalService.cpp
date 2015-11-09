/**
*
*  @author		Seongho Baek
*  @date		2014.08.12
*/

#include "Log.h"
#include "Types.h"
#include "DefaultGlobalService.h"
#include "Lock.h"
#include "Configure.h"
#include "NodePort.h"
#include "XMLTypes.h"
#include "XMLParser.h"
#include "Packet.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/poll.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

DefaultGlobalService::DefaultGlobalService(bool bMaster) : DefaultService(DEFAULT_GLOBAL_SERVICE_NAME)
{
	 this->mMasterMode = bMaster;
	 this->mListLock = Lock::createMutex();
	 this->mNumOfNode = 0;
	 this->mpBigNode = NULL;
	 this->mGID = 0;
}

void DefaultGlobalService::run()
{
	if (this->getStatus() == BUS_READY)
	{
		LOGI("Run Coordinator Service\n");

		this->mpCoordinator = new DefaultService::Coordinator(this);
		this->mpCoordinator->startThread();

		LOGI("Run Dispatcher Service\n");

		this->mpDispatcher = new DefaultService::Dispatcher(this);
		this->mpDispatcher->startThread();

		LOGI("Run ServerNodePort Service\n");

		this->mServerNodePort.setOwner(this);
		this->mServerNodePort.startThread();

		LOGI("Run BigNode Service\n");
		this->mpBigNode = new BigNode(this);

		char dirPath[LOG_FILE_NAME_LENGTH];

		memset(dirPath, 0, LOG_FILE_NAME_LENGTH);

		sprintf(dirPath, "%s/%s", (char *)SERVER_CONF_DIR, (char *)SERVER_CONF_FILE_NAME);
		FILE *frd = fopen(dirPath, "r");

		if (frd)
		{
			char line[LINE_BUFFER_LENGTH+1];

			memset(line,0,LINE_BUFFER_LENGTH+1);

			if (fgets(line, LINE_BUFFER_LENGTH, frd) == NULL)
			{
				this->mGID = 0;
			}
			else
			{
				this->mGID = atoi(line);
			}

			fclose(frd);
		}
	}
	else
	{
		LOGE("DefaultLocalService Not Ready.\n");
	}

	LOGI("DefaultGlobalService Running");
}

void DefaultGlobalService::setGID(unsigned int gid)
{
	char dirPath[LOG_FILE_NAME_LENGTH];

	this->mGID = gid;

	memset(dirPath, 0, LOG_FILE_NAME_LENGTH);

	sprintf(dirPath, "%s/%s", (char *)SERVER_CONF_DIR, (char *)SERVER_CONF_FILE_NAME);
	FILE *frd = fopen(dirPath, "w");

	if (frd)
	{
		char line[LINE_BUFFER_LENGTH+1];

		memset(line,0,LINE_BUFFER_LENGTH+1);

		sprintf(line, "%u\n", this->mGID);

		fwrite(line, 1, strlen(line), frd);

		fclose(frd);
	}
}

void DefaultGlobalService::processMessage()
{
	//LOGI("DefaultGlobalService Processor");
	NBUS_CMD* pItem = this->mQ.pop();

	if (!pItem->valid())
	{
		delete pItem;
		return;
	}

	//LOGI("Type: %d", pItem->mType);

	if (pItem->mType == LOCAL_MESSAGE)
	{
		XMLParser *pXmlParser = XMLParser::getInstance();

		IXML *pXml = pXmlParser->parseXML((char *)pItem->mpData, pItem->mLength);

		if (pXml == NULL)
		{
			LOGW("Invalid NodeBus XML, Custom Data?: %s", (char *)pItem->mpData);
			delete pXmlParser;

			LOGI((char *)pItem->mpData);

			return;
		}

		if (pXml->getXMLType() == XML_TYPE_BUS)
		{
			NBUSXML *pBusXml = (NBUSXML*)pXml;

            //LOGI("XML: %s", pBusXml->toXML());

			if (pBusXml->getType() == NBUS_TYPE_REQUEST)
			{
                switch (pBusXml->getId())
                {
                    case NBUS_CMD_JOIN:
                    {
                        this->join(pBusXml->getNodeName());
                    }
                    break;
                    case NBUS_CMD_LIST:
                    {
                        NodeEntry *pNodeList = this->getNodeListHead();
                        NodeEntry *pNode = NULL;
                        NBUSXML nbusXml;

                        nbusXml.setType(NBUS_TYPE_RESPONSE);
                        nbusXml.setSyncId(pBusXml->getSyncId());
                        nbusXml.setId(pBusXml->getId());
                        nbusXml.setSharedBufferAddrStr(pBusXml->getSharedBufferAddrStr());
                        nbusXml.setNodeName(pBusXml->getNodeName());

                        LOCK(this->mLock)
                        {
                            LIST_FOR_EACH(pNode, pNodeList)
                            {
                                nbusXml.addNode(pNode->getDescriptor());
                            }
                        }

                        char *pXml = nbusXml.toXML();

                        //LOGI("Response XML:%s", pXml);
                        int res = NodeNetwork::sendNodeMessage(nbusXml.getNodeName(), pXml, (unsigned int)strlen(pXml), LOCAL_MESSAGE);

                        if (res < 0)
                        {
                        	this->drop(nbusXml.getNodeName());
                        }

                        delete [] pXml;
                    }
                    break;
                    case NBUS_CMD_DROP:
                    {

                    }
                    break;
                    default:
                    break;
                }
			}
		}
	}
	else if (pItem->mType == GLOBAL_MESSAGE) // From network
	{
		//NBUSPacket packet;

		//packet.parserPacket(pItem->mpData, pItem->mLength);

		//LOGI("Global Packet Data Length: %d", packet.getDataLength());
	}
	else if (pItem->mType == BC_LOCAL_MESSAGE)
	{
		this->broadcast(pItem->mpData, pItem->mLength, NODE_ENTRY_LOCAL);
	}
	else if (pItem->mType == BC_CLIENT_MESSAGE)
	{
		//LOGI("Broadcast to NodeClient:%d", pItem->mLength);
		this->broadcast(pItem->mpData, pItem->mLength, NODE_ENTRY_CLIENT);
	}

	delete pItem;
}

