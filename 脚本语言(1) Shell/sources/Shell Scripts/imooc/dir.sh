#!/bin/bash

read -t 30 -p "please input a dir: " dir

if [ -d "$dir" ]
	then
		echo "input is a directory"
	else
		echo "input is not a directory"
fi
