#!/bin/bash

test=$(df -h | grep /dev/sda1 | awk '{print $5}' | cut -d "%" -f 1)

if [ "$test" -gt "90" ]; then
	echo "disk almost full"
elif [ "$test" -gt "10" ]; then
	echo "disk is ok"
else
	echo "dist almost empty"
fi
