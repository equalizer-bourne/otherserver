#!/bin/sh

bin="/home/mage/Documents/tool/taf/bin/tafnode"

PID=`ps -eopid,cmd | grep "$bin"| grep "tafnode" |  grep -v "grep" |awk '{print $1}'`

echo $PID

if [ "$PID" != "" ]; then
    kill -9 $PID
    echo "kill -9 $PID"
fi


