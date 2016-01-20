#!/bin/sh

p=`ps -ef | grep wilson | grep -v $$ | grep -v "grep" | awk '{ print $2 }'`

if [ ! -z "$p" ]; then
	kill -9 $p 
fi
