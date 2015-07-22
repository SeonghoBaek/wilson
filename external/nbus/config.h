#ifndef _CONFIG_H_
#define _CONFIG_H_

//#define MAC_OS_X
#if defined(MAC_OS_X)
#define DOMAIN_PREFIX "/var/tmp/"
#else
#define DOMAIN_PREFIX
#endif

#define SERVICE_NAME_LENGTH 64

#define NODE_NAME_LENGTH	64

#define NBUS_BUFF_SIZE 		2048

#define DEFAULT_GLOBAL_SERVICE_NAME DOMAIN_PREFIX "nodebus.global.service.defaultservice"

#define DEFAULT_LOCAL_SERVICE_NAME DOMAIN_PREFIX "nodebus.local.service.defaultservice"

enum
{
	POWER_OFF = 0,
	POWER_ON,

	CH_CHANGE = 11,
	CH_GETINFO,
	CH_SEARCH,
	CH_UP,
	CH_DN,
	CH_PREV,

	VOL_UP = 20,
	VOL_DN,
	VOL_MUTEON,
	VOL_MUTEOFF,

	INPUT_CHANGE = 30,

	TM_START_TIMESHIFT = 40,
	TM_STOP_TIMESHIFT,
	TM_START_RECORD,
	TM_STOP_RECORD,
	TM_TRICKPLAY,
	TM_JUMP,
	TM_PLAY_RECORD,
	TM_PLAY_STOP,

	NODE_JOIN = 90,
	NODE_DROP,

};

#ifndef NULL
#define NULL 0
#endif

#endif
