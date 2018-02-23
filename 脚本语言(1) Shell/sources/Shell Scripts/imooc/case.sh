#!/bin/bash
read -p "input your choice: " choice

case $choice in
	"yes")
		echo "you input yes"
		;;
	"no")
		echo "you input no"
		;;
	*)
		echo "input incorrect"
		;;
esac
