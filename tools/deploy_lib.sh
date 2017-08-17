#!/bin/bash

TOP_PATH=$(cd "$(dirname "$0")"/../; pwd)

if [ -z $1 ]; then
	exit
fi

scp ${TOP_PATH}/fpga/lib/* $1 
scp ${TOP_PATH}/source/lib/* $1
scp ${TOP_PATH}/mcu/lib/* $1
scp ${TOP_PATH}/focallaw/lib/* $1
