/** 
*
*  @author		Seongho Baek
*  @date		2014.08.12
*/

#include "DefaultService.h"
#include "Configure.h"
#include "Log.h"
#include "List.h"
#include "NodeEntry.h"
#include "XMLTypes.h"
#include "XMLParser.h"
#include "NodeEntry.h"
#include "NodeBus.h"
#include "NodeLooper.h"
#include "NodeNetwork.h"
#include "Packet.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>

int DefaultService::Coordinator::localAction(void *data, unsigned int length, int type)
{
	LOCK(this->mCLock) // For safe use.
	{
		NBUS_CMD item(length);

		_GOODNESS(data, -1);
		_GOODNESS(length, -1);

		memcpy(item.mpData, data, length);
		item.mType = type;

		this->mpOwner->mQ.push(item);
		this->mpOwner->mpLooper->wakeup();

		//LOGI("Client: %s, %d", (char *)item.mpData, item.mLength);
	}

	return 0;
}

void DefaultService::Dispatcher::thread()
{
	this->mpOwner->mpLooper->wait(-1); // Loop.
}

int DefaultService::Dispatcher::dispatch(const char *wakeup_event)
{
	// Currently we don't need to check wakeup_event.

	//LOGI("Dispatcher Wake Up");
	this->mpOwner->processMessage();

	return 0;
}

void DefaultService::setupService(const char *serviceName)
{
	if (serviceName == NULL) return;
    
    memset(mDefaultNode, 0, NODE_NAME_LENGTH+1);

	memset(mServiceName, 0, SERVICE_NAME_LENGTH);
	strcpy(mServiceName, serviceName);

	mNumOfNode = 0;
	mpNodeListHead = new NodeEntry(); // Descriptor NULL. This is list head entry.

	mLock = Lock::createMutex();
	mInitialized = 0;
	mLastStatus = BUS_NOT_READY;

	LOGI("Create Coordinator\n");

	mpCoordinator = new Coordinator(this);

	LOGI("Create Dispatcher\n");

	mpDispatcher = new Dispatcher(this);

	LOGI("Create NodeLooper\n");

    mpLooper = new NodeLooper(mpDispatcher);
}

DefaultService::DefaultService()
{
	setupService(DEFAULT_LOCAL_SERVICE_NAME);
}

DefaultService::DefaultService(const char *serviceName)
{
	setupService(serviceName);
}

void DefaultService::run()
{
	if (this->getStatus() == BUS_READY)
	{
		LOGI("Run Local Coordinator\n");
		this->mpCoordinator->startThread();
		this->join(this->mpCoordinator->getNamespace());

		LOGI("Run Dispatcher\n");
		this->mpDispatcher->startThread();

		this->mNodePort.setOwner(this);

		// Need to check.
		LOGI("Register to Server\n");

		if (this->mNodePort.connect(this->mpServerAddress, this->mServerPort) > 0)
		{
			this->mNodePort.run();
		}
		else
		{
			LOGE("Register Failed\n");
		}
	}
	else
	{
		LOGE("DefaultLocalService Not Ready.\n");
	}
}

NodeEntry* DefaultService::addNodeEntry(NodeEntry *entry)
{
	_GOODNESS(entry, NULL);

	LOCK(this->mLock)
	{
		LIST_ADD(entry, this->mpNodeListHead);

		this->mNumOfNode++;

		//LOGI("Add NodeEntry: %s", entry->getDescriptor());
	}

	return this->mpNodeListHead;
}

int DefaultService::drop(const char* pNodeName)
{
	_GOODNESS(pNodeName, -1);

	NodeEntry *pNode = NULL;
	NodeEntry *pNodeList = getNodeListHead();

	_GOODNESS(pNodeList, -1);

    LOCK(this->mLock)
    {
		LIST_FOR_EACH(pNode, pNodeList)
		{
			if (strcmp(pNode->getDescriptor(), pNodeName) == 0)
			{
				this->mNumOfNode--;

				delete pNode; // LIST_DEL
                
                if (strcmp(pNodeName, this->mDefaultNode) == 0)
                {
                    memset(this->mDefaultNode, 0, NODE_NAME_LENGTH);
                }

				break;
			}
		}
    }

    return 0;
}

int DefaultService::join(const char* pNodeName, int type)
{
    _GOODNESS(pNodeName, -1);

    NodeEntry *entry = NULL;

    if (type == NODE_ENTRY_CLIENT)
    {
    	entry = new ClientNodeEntry(pNodeName);
    }
    else if (type == NODE_ENTRY_LOCAL)
    {
    	entry = new LocalNodeEntry(pNodeName);
    }

    /*
     *  Drop node with same name.
     */
    drop(pNodeName);

	LOGI("Join to NodeBus: %s", pNodeName);

	if (this->addNodeEntry(entry) == NULL) return -1;

	/*
	char* xml = NULL;

	NBUSXML *pNBusXml = new NBUSXML;

	pNBusXml->setType(NBUS_TYPE_EVENT);
	pNBusXml->setId(NBUS_EVENT_NODE_ADDED);
	pNBusXml->setNodeName(pNodeName);

	xml = pNBusXml->toXML();

	NodeNetwork::sendNodeMessage(pNodeName, xml, strlen(xml), LOCAL_MESSAGE);

	delete [] xml;
	delete pNBusXml;
    */

	return 0;
}

int DefaultService::join(const char* pNodeName)
{
    _GOODNESS(pNodeName, -1);
    
	NodeEntry *entry = new LocalNodeEntry(pNodeName);
    
    /*
     *  Drop node with same name.
     */
    drop(pNodeName);

	LOGI("Join to NodeBus: %s", pNodeName);

	if (this->addNodeEntry(entry) == NULL) return -1;

	/*
	char* xml = NULL;

	NBUSXML *pNBusXml = new NBUSXML;

	pNBusXml->setType(NBUS_TYPE_EVENT);
	pNBusXml->setId(NBUS_EVENT_NODE_ADDED);
	pNBusXml->setNodeName(pNodeName);

	xml = pNBusXml->toXML();

	NodeNetwork::sendNodeMessage(pNodeName, xml, strlen(xml), LOCAL_MESSAGE);

	delete [] xml;
	delete pNBusXml;
    */

	return 0;
}

int DefaultService::broadcast(const void *manifest, unsigned int length, int type)
{
	if (type == NODE_ENTRY_LOCAL) return this->broadcast(manifest, length);

	_GOODNESS(manifest, -1);

    //LOGI("NBus Client BroadCast: %s\n", manifest);

    NodeEntry *pNodeList = getNodeListHead();
    NodeEntry *pNode = NULL;

    LOCK(this->mLock)
    {
		LIST_FOR_EACH(pNode, pNodeList)
		{
			if (pNode->getType() == type)
			{
				NodeEntry *pPrevNode = LIST_PREV(pNode);

				//LOGI("Broadcast to %s", pNode->getDescriptor());
				if (NodeNetwork::sendNodeMessage(pNode->getDescriptor(), manifest, length, BC_CLIENT_MESSAGE) < 0)
				{
					LOGE("Node Closed: Dropping %s", pNode->getDescriptor());

					this->mNumOfNode--;

					delete pNode;

					pNode = pPrevNode;
				}

				continue;
			}
		}
    }

	return 0;
}
// Broadcast is applicable to local networked nodes
int DefaultService::broadcast(const void *manifest, unsigned int length)
{
	_GOODNESS(manifest, -1);

    //LOGI("NBus Local BroadCast: %s\n", manifest);

    NodeEntry *pNodeList = getNodeListHead();
    NodeEntry *pNode = NULL;

    LOCK(this->mLock)
    {
		LIST_FOR_EACH(pNode, pNodeList)
		{
			if (pNode->getType() == NODE_ENTRY_LOCAL)
			{
				NodeEntry *pPrevNode = LIST_PREV(pNode);

				if (NodeNetwork::sendNodeMessage(pNode->getDescriptor(), manifest, length, BC_LOCAL_MESSAGE) < 0)
				{
					LOGE("Node Closed: Dropping %s", pNode->getDescriptor());

					this->mNumOfNode--;

					delete pNode;

					pNode = pPrevNode;
				}

				continue;
			}
		}
    }

    return 0;
}

int DefaultService::cast(const char* nodename, const void *manifest, unsigned int length)
{
	_GOODNESS(manifest, -1);

    //LOGI("NodeBus::cast: manifest: %s\n", manifest);
	NodeNetwork::sendNodeMessage(nodename, manifest, length, LOCAL_MESSAGE);

    return 0;
}

int DefaultService::cast(const char* nodename, const void *manifest, unsigned int length, int type)
{
	_GOODNESS(manifest, -1);

    //LOGI("NodeBus::cast: manifest: %s\n", manifest);
	NodeNetwork::sendNodeMessage(nodename, manifest, length, type);

    return 0;
}

int DefaultService::exist(const char *pNodeName)
{
    NodeEntry *pNodeList = getNodeListHead();
    NodeEntry *pNode = NULL;

    _GOODNESS(pNodeName, -1);

    LOCK(this->mLock)
    {
		LIST_FOR_EACH(pNode, pNodeList)
		{
			//LOGI("NodeBus::unicast: check node exists: %s, %s\n", name, pNode->getDescriptor());

			if (strcmp(pNodeName, pNode->getDescriptor()) == 0)
			{
				//LOGI("NodeBus::exist: Node %s already exists\n", name);

				return 1;
			}
		}
    }

    return 0;
}

void DefaultService::processMessage()
{
	while (this->mQ.getSize())
	{
		NBUS_CMD* pItem = this->mQ.pop();

		//LOGI("DefaultService Processor: %s", pItem->mpData);

		if (!pItem->valid())
		{
			delete pItem;
			return;
		}

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

				switch (pBusXml->getType())
				{
					case NBUS_TYPE_REQUEST:
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
									// Node Failure.
									this->drop(nbusXml.getNodeName());
								}

								delete [] pXml;
							}
							break;
							case NBUS_CMD_DROP:
							{
								this->drop(pBusXml->getNodeName());
							}
							break;
							default:
							break;
						}

					}
					break;
					case NBUS_TYPE_RESPONSE: // No need.
					{
					}
					break;
					case NBUS_TYPE_EVENT:
					{
						switch (pBusXml->getId())
						{
							case NBUS_EVENT_SET_DEFAULT_NODE:
							{
								this->setDefaultNode(pBusXml->getNodeName());
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

				delete pBusXml;
			}
			else
			{
				// Do not process.
				delete pXml;
			}
			
			delete pXmlParser;
		}
		else if (pItem->mType == GLOBAL_MESSAGE) // From network
		{
			//LOGI("Global Command Received: %s, %d", pItem->mpData, pItem->mLength);
			
			if (strlen(this->getDefaultNode()))
			{
				NodeNetwork::sendNodeMessage(this->getDefaultNode(), pItem->mpData, pItem->mLength, GLOBAL_MESSAGE);
			}
			else
			{
				LOGW("DefaultNode Not Ready Yet");
			}
		}
		else if (pItem->mType == BC_LOCAL_MESSAGE)
		{
			//LOGI("BroadCast Command Received: %s, %d", pItem->mpData, pItem->mLength);
			this->broadcast(pItem->mpData, pItem->mLength);
		}
		else if (pItem->mType == BC_CLIENT_MESSAGE)
		{
			// Do not process at DefaultSerice. Only for GlobalService.
		}

		delete pItem;
	}
}

