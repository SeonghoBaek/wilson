/**
*
*  @author		Seongho Baek
*  @date		2014.08.12
*/

#include "Log.h"
#include "NodeLooper.h"
#include "Thread.h"
#include "json/json.h"
#include "XMLTypes.h"
#include "XMLParser.h"
#include "DefaultService.h"
#include "DefaultGlobalService.h"
#include "INodeBusService.h"
#include "Configure.h"
#include "NodeBus.h"

#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		LOGI("usage: %s <bind address> <port>\n", argv[0]);

		return -1;
	}

	/*
	pid_t pid = fork();

	if (pid != 0)
	{
		exit(0);
	}
	*/

	rmdir((char *)LOCK_DIR);
	mkdir((char *)LOCK_DIR, 0755);

	char cmd[80];
	memset(cmd, 0, 80);

	sprintf(cmd, "rm -rf %s;mkdir %s", (char *)LOCK_DIR, (char *)LOCK_DIR);
	system(cmd);

	// Create NodeBus Service.
	LOGI("Create NodeBus Global Server\n");
	DefaultGlobalService *pNodeBusGlobalService = new DefaultGlobalService(TRUE);

	pNodeBusGlobalService->init();
	pNodeBusGlobalService->setGlobalServerAddress(argv[1], atoi(argv[2]));

	LOGI("Run NodeBus Global Server: %s:%d\n", argv[1], atoi(argv[2]));

	pNodeBusGlobalService->run();

	NodeLooper looper;

	LOGI("NodeBus Global Server Daemon Mode\n");
	looper.wait(-1);

	return 0;
}

