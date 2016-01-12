/**
*
*  @author		Seongho Baek
*  @date		2014.08.12
*/

#include "NodeNetwork.h"
#include "Types.h"
#include "NodePort.h"
#include "Log.h"
#include "DefaultService.h"
#include "DefaultGlobalService.h"
#include "Packet.h"
#include "Configure.h"
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/file.h>

unsigned int gGlobalClientID = 0;

int NodePort::Router::routerAction(void *data, unsigned int length, int type)
{
	//LOGI("Router: %d", length);

	int sent = this->mpOwner->send(data, length);

	return sent;
}

NodePort::NodePort()
{
	mSd = -1;
	mpOwner = NULL;
	mpRouter = new NodePort::Router(this);

	this->setThreadName((char *)"NodePort");
}

void NodePort::run()
{
	this->startThread();
	mpRouter->startThread();
	this->mpOwner->join(mpRouter->getNamespace());
}

int NodePort::listen()
{
	int nReadBytes = 0;
	void *buff = new char[ACTION_BUFFER_SIZE+1];
	char *pUniqueClientName = new char[NODE_NAME_LENGTH+1];

	sockaddr_in localSockAddr;
    socklen_t addrLen = sizeof(localSockAddr);
    getsockname(this->mSd, (sockaddr*) &localSockAddr, &addrLen);
    char* localIp = inet_ntoa(localSockAddr.sin_addr);

    //LOGI("Client Local IP: %s", localIp);

	/* Start Register */

	nReadBytes = (int)read(this->mSd, buff, ACTION_BUFFER_SIZE);

	if (nReadBytes <= 0)
	{
		delete [] (char *)buff;
		delete [] pUniqueClientName;

		LOGE("Connection Closed.\n");

		if (this->mSd > 0) close(this->mSd);
		this->mSd = -1;

		return -1;
	}

	//LOGI("Client External IP: %s", buff);

	sprintf(pUniqueClientName, "%s%s_%s", NBUS_PACKET_START_CODE, localIp, (char *)buff);

	// Send local ip : external ip : port
	this->send(pUniqueClientName, NODE_NAME_LENGTH);

	delete [] pUniqueClientName;
	delete [] (char *)buff;

	int packetPreffixLength = NBUS_PACKET_HEADER_LEGNTH_BYTES + strlen(NBUS_PACKET_START_CODE);
    char *packetPreffix = new char[packetPreffixLength];

	for (;;)
	{
		int readBytes = 0;
		int r = 0;
		int sizeToRead = packetPreffixLength;
		do
		{
			r = (int)read(this->mSd, packetPreffix + readBytes, sizeToRead);

			if (r <= 0)
			{
				readBytes = 0;
				break;
			}

			readBytes += r;
			sizeToRead -= r;
		}
		while(sizeToRead);

		if (readBytes <= 0)
		{
			// Connection Broken
			// Fail action here.
			LOGE("Connection Closed.\n");

			if (this->mSd > 0) close(this->mSd);
			this->mSd = -1;

			break;
		}

		if (strncmp(packetPreffix, (char *)NBUS_PACKET_START_CODE, strlen(NBUS_PACKET_START_CODE)))
		{
			LOGE("Invalid Start Code");
			continue;
		}

		int headerLength = 0;

		headerLength = *(int *)(strlen(NBUS_PACKET_START_CODE) + packetPreffix);

		char *packetHeader = new char[headerLength];

		readBytes = (int)read(this->mSd, packetHeader, headerLength);

		if (readBytes <= 0)
		{
			// Connection Broken
			// Fail action here.
			LOGE("Connection Closed.\n");

			if (this->mSd > 0) close(this->mSd);
			this->mSd = -1;

			delete [] packetHeader;

			break;
		}

		NBUSPacket packet;

		if (packet.parseHeader(packetHeader, headerLength) < 0)
		{
			LOGE("Packet Error");
			delete [] packetHeader;
			continue;
		}

		memcpy(packet.getPacket(), packetPreffix, packetPreffixLength);

		delete [] packetHeader;

		if (packet.getDataLength())
		{
			readBytes = 0;
			sizeToRead = packet.getDataLength();
			do
			{
				int r = (int)read(this->mSd, (char *)packet.getData() + readBytes, sizeToRead);

				if ( r <= 0 )
				{
					readBytes = 0;
					break;
				}

				readBytes += r;
				sizeToRead -= r;
			}
			while(sizeToRead);

			if (readBytes <= 0)
			{
				// Connection Broken
				// Fail action here.
				LOGE("Connection Closed.\n");

				if (this->mSd > 0) close(this->mSd);
				this->mSd = -1;

				delete [] packetHeader;

				break;
			}
			else if (readBytes != packet.getDataLength())
			{
				LOGE("Packet Data Error");
				delete [] packetHeader;
				continue;
			}
		}

		NBUS_CMD item;

        item.mpData = new char[packet.getPacketLength()];
		memcpy(item.mpData, packet.getPacket(), packet.getPacketLength());
		item.mLength = packet.getPacketLength();
		item.mType = GLOBAL_MESSAGE;

		//LOGI("packet: %s", packet.getHeader());
		// Queueing
		this->mpOwner->mQ.push(item);
		this->mpOwner->mpLooper->wakeup();
	}

	if (packetPreffix) delete packetPreffix;

	return 0;
}

int NodePort::send(void *data, int length)
{
	int nBytes = NodeNetwork::sendToSocket(this->mSd, data, length);

	return nBytes;
}

int NodePort::connect(const char *ip, int port)
{
	int sock = NodeNetwork::connectGlobal(ip, port);

	if (sock < 0) return -1;

	this->mSd = sock;

	return sock;
}

ServerNodePort::ServerNodePort()
{
	this->mpOwner = NULL;
	this->setThreadName((char *)"ServerNodePort");
}

#if (USE_NODE_CREATION_THREAD == 1)
struct ClientNodeArgument
{
	int sock;
	unsigned int gid;
	char clientName[NODE_NAME_LENGTH+1];
	DefaultGlobalService *pOwner;
};

void* createClientNodeThread(void *pArg)
{
	int sent = 0;
	ClientNodeArgument *pNodeArg = (ClientNodeArgument *)pArg;
	char logFileName[LOG_FILE_NAME_LENGTH];
	char dirPath[LOG_FILE_NAME_LENGTH];

	memset(dirPath, 0, LOG_FILE_NAME_LENGTH);

	sprintf(dirPath, "%s/%s", (char *)LOCK_DIR, pNodeArg->clientName);

	memset(logFileName, 0, LOG_FILE_NAME_LENGTH);

	// Send IP string
	sent = NodeNetwork::sendToSocket(pNodeArg->sock, pNodeArg->clientName, NODE_NAME_LENGTH);

	if (sent <= 0)
	{
		delete pNodeArg;

		return NULL;
	}

	// Receive Private IP_Public IP
	int tempLength = NODE_NAME_LENGTH + 1 + strlen(NBUS_PACKET_START_CODE);
	char tempBuffer[tempLength];

	sent = NodeNetwork::receiveFromSocket(pNodeArg->sock, tempBuffer, tempLength-1);

	if (strncmp(NBUS_PACKET_START_CODE, tempBuffer, strlen(NBUS_PACKET_START_CODE)))
	{
		LOGE("Invalid Client Accepted");

		delete pNodeArg;
		return NULL;
	}
	//sent = NodeNetwork::receiveFromSocket(pNodeArg->sock, pNodeArg->clientName, NODE_NAME_LENGTH);

	if (sent <= 0)
	{
		delete pNodeArg;

		return NULL;
	}

	strncpy(pNodeArg->clientName, tempBuffer + strlen(NBUS_PACKET_START_CODE), NODE_NAME_LENGTH);

	snprintf(logFileName, NODE_NAME_LENGTH, "%s", pNodeArg->clientName);
	LOGI("New Client Node Accepted: %s", pNodeArg->clientName);

	ClientNode* pClientNode;

	pClientNode = new ClientNode(pNodeArg->sock, pNodeArg->clientName, pNodeArg->pOwner);

	if (pClientNode->getGID() == 0)
	{
		pClientNode->setGID(pNodeArg->gid);
	}

	pClientNode->prepare(logFileName);

	unlink(dirPath);

	delete pNodeArg;

	return NULL;
}
#endif

int ServerNodePort::waitNodeConnection()
{
	int sock = 0;

	sock = NodeNetwork::setupServerSocket(this->mpOwner->mpServerAddress, this->mpOwner->mServerPort);

	if (sock < 0)
	{
		LOGE("Server Socket Setup Failure\n");
		return sock;
	}

	int loop = 1;

	while (loop == 1)
	{
        ClientAddress_t addr;
        char logFileName[LOG_FILE_NAME_LENGTH];
        memset(logFileName, 0, LOG_FILE_NAME_LENGTH);

		int client = NodeNetwork::acceptOnSocket(sock, &addr);

		// Create IP string
		char clientName[NODE_NAME_LENGTH+1];
        sprintf(clientName, "%s", addr.ipstr);

	#if (USE_IP_CHECKER == 1)

        char IP_CHECK[NODE_NAME_LENGTH+1];
        sprintf(IP_CHECK, "%s", addr.ipstr);

        char *host = strtok(IP_CHECK, ".");
        host = strtok(NULL, ".");
        host = strtok(NULL, ".");
        host = strtok(NULL, ".");

        if (strcmp(host, "0") == 0)
		{
        	LOGW("Illegal Connection: %s", clientName);

        	close(sock);

        	close(client);

			sleep(2);

        	sock = NodeNetwork::setupServerSocket(this->mpOwner->mpServerAddress, this->mpOwner->mServerPort);

			if (sock < 0)
			{
				LOGE("Server Socket Setup Failure\n");
				return sock;
			}

        	continue;
		}

	#endif

        char dirPath[LOG_FILE_NAME_LENGTH];

		memset(dirPath, 0, LOG_FILE_NAME_LENGTH);

		sprintf(dirPath, "%s/%s", (char *)LOCK_DIR, clientName);

		int fd = open(dirPath, O_RDWR, 0755);

		if (fd < 0)
		{
			fd = creat(dirPath, 0755);
			close(fd);
		}
		else
		{
			close(fd);

			continue;
		}

	#if (USE_NODE_CREATION_THREAD == 1)

        ClientNodeArgument *pArg = new ClientNodeArgument;

        pArg->sock = client;
        memset(pArg->clientName, 0, NODE_NAME_LENGTH+1);
        strcpy(pArg->clientName, clientName);
        pArg->pOwner = this->mpOwner;
        pArg->gid = this->mpOwner->getGID()+1;
        this->mpOwner->setGID(pArg->gid);

        //pArg->gid = ++gGlobalClientID;

        ThreadHelper::run(createClientNodeThread, pArg, TRUE);
		
	#else
		// Send IP string
		NodeNetwork::sendToSocket(client, clientName, NODE_NAME_LENGTH);

		// Receive Private IP_Public IP
		NodeNetwork::receiveFromSocket(client, clientName, NODE_NAME_LENGTH);

        sprintf(logFileName, "%s", clientName);
		LOGI("New Client Node Accepted: %s", clientName);

		// Register End.

		ClientNode* pClientNode;

		pClientNode = new ClientNode(client, clientName, this->mpOwner);
		pClientNode->prepare(logFileName);

		unlink(dirPath);
	#endif
	}

	return sock;
}

