/**
*
*  @author		Seongho Baek
*  @date		2014.08.12
*/

#ifndef DEFAULTGLOBALSERVICE_H_
#define DEFAULTGLOBALSERVICE_H_

#include "DefaultService.h"
#include "Thread.h"
#include "List.h"
#include "Configure.h"
#include "NodePort.h"
#include "NodeBus.h"
#include "BigNode.h"
#include "Packet.h"
#include "ClientNode.h"

#include <stdio.h>

enum
{
	CLI_NORMAL_RUN,
	CLI_NORMAL_EXIT,
	CLI_ERROR,

	CLI_NONE
};

class BigNode;
class DefaultGlobalService: public DefaultService
{
	private:

		bool 			mMasterMode;
		ServerNodePort  mServerNodePort;

		BigNode			*mpBigNode;
		Mutex_t 		mListLock;
		unsigned int	mGID;

		friend class ClientNode;

	public:

		DefaultGlobalService(bool master = TRUE);

		unsigned int getGID() {return this->mGID;}

		void setGID(unsigned int gid);

		virtual ~DefaultGlobalService() {}

		virtual void run();

		virtual void processMessage();
};

#endif /* DEFAULTGLOBALSERVICE_H_ */
