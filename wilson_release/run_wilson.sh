#!/bin/sh

if [ $# -ne 1 ];then
	echo "usage: $0 [server ip]"
	exit 1
fi

~/bin/wilson $1 8088 ~/wilson > ~/wilson/server.log &
