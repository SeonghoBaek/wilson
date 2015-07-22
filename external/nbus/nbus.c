/*
 * nbus.c
 *
 *  Created on: 2014. 8. 19.
 *      Author: major.baek
 */

#include <stdio.h>
#include "config.h"
#include "bridge.h"
#include "nbus.h"

int nbus_join(const char* nodeName, const char* serverName)
{
	char joinXML[NBUS_BUFF_SIZE];

	sprintf(joinXML,
			"<command sid=\"%d\" cid=\"%d\"><arguments><node protocol=\"local\" namespace=\"%s\"/></arguments></command>",
			0,
			NODE_JOIN,
			nodeName
			);

	if (serverName == NULL)
	{
		bridge_cross(DEFAULT_LOCAL_SERVICE_NAME, joinXML, NBUS_BUFF_SIZE);
	}
	else
	{
		bridge_cross(serverName, joinXML, NBUS_BUFF_SIZE);
	}

	return 0;
}

int nbus_cast(const char* nodeName, void *data, int length)
{
	if (nodeName == NULL) // Broadcast
	{
		bridge_cross(DEFAULT_LOCAL_SERVICE_NAME, data, length);
	}
	else
	{
		bridge_cross(nodeName, data, length);
	}

	return 0;
}

int nbus_drop(const char *nodeName, const char* serverName)
{
	char joinXML[NBUS_BUFF_SIZE];

	sprintf(joinXML,
				"<command sid=\"%d\" cid=\"%d\"><arguments><node protocol=\"local\" namespace=\"%s\"/></arguments></command>",
				0,
				NODE_DROP,
				nodeName
				);

	if (serverName == NULL)
	{
		bridge_cross(DEFAULT_LOCAL_SERVICE_NAME, joinXML, NBUS_BUFF_SIZE);
	}
	else
	{
		bridge_cross(serverName, joinXML, NBUS_BUFF_SIZE);
	}

	return 0;
}
