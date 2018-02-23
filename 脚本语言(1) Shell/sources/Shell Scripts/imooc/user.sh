#!/bin/bash

test=$(env | grep -w "USER" | cut -d "=" -f 2)

if [ "$test" == "wanghuiyong" ]
	then
		echo "current user is wanghuiyong"
	else
		echo $test
fi
