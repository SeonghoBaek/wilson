/*
 * BigNode.h
 *
 *  Created on: Aug 21, 2014
 *      Author: major
 */

#ifndef BIGNODE_H_
#define BIGNODE_H_

#include "Configure.h"
#include "NodeBus.h"
#include "Thread.h"
#include "DefaultGlobalService.h"
#include "Lock.h"
#include "ClientNode.h"
#include "Normalizer.h"

#define MAX_CLIENT_STATUS_JSON_LENGTH 1024

class BigNodeThread;
class BigNode : public NodeAdapter, public INode
{
	private:
		DefaultGlobalService 	*mpService;
		BigNodeThread 			*mpThread;
		Mutex_t					mBigLock;

		// Client Node Control
		ClientNode* mpRunList;
		ClientNode* mpFreeList;
		MeanVector	mMeanLengthVector;
		SessionMeanVectorList mSMPL;

	public:

		BigNode(DefaultGlobalService *pOwner);

		virtual ~BigNode() {}

		int nodeAction(void *data, unsigned int length, int type);

		int nodeCallback(void *data, unsigned int length, int type)
		{
			return nodeAction(data, length, type);
		}

		int process();
		int broadcastLogCommand();
		int broadcastInfoCommand();

		int addRunList(ClientNode *pClientNode);
		int addFreeList(ClientNode *pClientNode);

		float setVectorLength(int dim, float length, int session);
		float getVectorLength(int dim, int session);

		ClientNode* findNode(char* pName);
		ClientNode* DelNode(ClientNode* pNode);
};

class BigNodeThread : public Thread
{
	private:
		BigNode* mpOwner;

	public:

		IMPLEMENT_THREAD(thread())

		BigNodeThread(BigNode *pOwner)
		{
			this->mpOwner = pOwner;
			this->setThreadName((char *)"BigNodeThread");
		}

		virtual ~BigNodeThread() {}
		void thread() {mpOwner->process();}
};

#endif /* BIGNODE_H_ */
