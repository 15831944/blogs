#!/bin/bash

read -p "Please input a filename: " file

if [ -z "$file" ]; then
	echo "empty filename"
	exit 1
elif [ ! -e "$file" ]; then
	echo "file not exist"
	exit 2
elif [ -f "$file" ]; then
	echo "regular file"
elif [ -d "$file" ]; then
	echo "directory"
else
	echo "other type"
fi
