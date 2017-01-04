#!/bin/bash

TOP_PATH=$(cd "$(dirname "$0")"/../; pwd)

if [ -z $1 ]; then
	exit
fi

scp ${TOP_PATH}/fpga/lib/libFpga* $1 
scp ${TOP_PATH}/source/lib/libSource* $1
