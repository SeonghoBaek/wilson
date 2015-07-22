/*
 * ClientNode.h
 *
 *  Created on: Sep 4, 2014
 *      Author: major
 */

#ifndef CLIENTNODE_H_
#define CLIENTNODE_H_

#include "List.h"
#include "Configure.h"
#include "Types.h"
#include "Thread.h"
#include "BigNode.h"
#include "Packet.h"
#include "Normalizer.h"
#include "Lock.h"

enum
{
	CLIENT_WAIT,
	CLIENT_RUN,
	CLIENT_DONE,
	CLIENT_ERROR,
	CLIENT_NET_ERROR,
	CLIENT_ZOMBIE,
	CLIENT_COMPLETE,
	CLIENT_STOP,
	CLIENT_NONE
};

#define CMD_LENGTH 4
#define CMD_UPDATE_SIMILARITY "USIM"
#define CMD_START_LOG "SLOG"
#define CMD_STOP_LOG "NLOG"

class BigNode;
class ClientNode : public NodeAdapter, public INode
{
	LINKED_LIST(ClientNode);

	private:

		int 	mSd;
		char	mClientName[NODE_NAME_LENGTH];
		char 	mClientNodeName[NODE_NAME_LENGTH];
		DefaultGlobalService *mpOwner;
		BigNode	*mpBigNode;
		unsigned int mGID; // Client Unique ID
		unsigned int mTID; // Testcase ID
		unsigned int mClientSession; // Test Set Session ID

		bool 			mExitNode;
		unsigned int 	mLogVersion;
		unsigned int   mLogSession;
		char 			mLogFileName[LOG_FILE_NAME_LENGTH];
		char 			mInfoFileName[LOG_FILE_NAME_LENGTH];
		int 			mErrorId;
		int				mRes;
		NBUSPacket		*mpLastRunPacket;
		bool			mNewSession;

		char 			**mpTerms;
		int				mNumOfTerms;
		TermVector*		mpVectorList;
		int				mNumOfVectors;
		TermVector*		mpPrevVector;
		float			mSimilarity;

		int				mState;  // Status

		void readNode(); // Router thread function.

		void cleanUp();

		int safeRead(void *buff, unsigned int length);

		// Read network packet and save in queue.
		class Router : public Thread
		{
			private:

				ClientNode *mpOwner;

			public :

				IMPLEMENT_THREAD(thread())

				Router(ClientNode *);
				virtual ~Router() {}

				void thread();
		} *mpRouter;

		int setWait();
		int setRun();
		int setError();
		int setComplete();
		int updateStatus();

	public:
		Mutex_t mLock;
		bool	mGarbageCollecting;
		bool 	mRouterExit;
		// Dummy
		ClientNode();
		ClientNode(int socket, char* pClientName, DefaultGlobalService *pOwner);
		virtual ~ClientNode();

		unsigned int writeNode(const void *data, unsigned int length);
		void 	setName(const char *pName);
		char* 	getLogFileName() { return this->mLogFileName; }
		// Node Simple Name
		char* 	getName() {return mClientName;}
		// Node Full Path Name
		char* 	getNodeName() {return mClientNodeName;}
		void 	exitNode();
		void 	prepare(const char* pLogDirName);
		void	createLogFile(const char* pLogDirName);
		void	loadVectorDef();
		void 	processEvent(NBUSPacket *pPacket);
		void	processCommand(NBUSPacket *pPacket);
		int 	nodeCallback(void *data, unsigned int length, int type);
		void 	setError(int id) { this->mErrorId = id; }
		int 	getLastError() { return this->mErrorId; }
		int 	normalizeLogData(char *data, int length);
		int 	getState() {return this->mState;}
		void 	setState(int state) {this->mState = state;}
		NBUSPacket* getLastRunPacket() {return this->mpLastRunPacket;}
		void 	setLastRunPacket(NBUSPacket *packet) {this->mpLastRunPacket = packet;}
		float	getSimilarity();
		void 	setSimilarity(float s) {this->mSimilarity = s;}
		float	updateSimilarity();
		void	setGID(unsigned int gid) {this->mGID = gid;}
		unsigned int getGID() {return this->mGID;}
		void	setTID(unsigned int tid) {this->mTID = tid;}
		unsigned int getTID() {return this->mTID;}
		void 	setClientSession(unsigned int session) {this->mClientSession = session;}
		unsigned int getClientSession() {return this->mClientSession;}
		void	setRes(int res) {this->mRes = res;}
		int		getRes() {return this->mRes;}
};

#endif /* CLIENTNODE_H_ */
