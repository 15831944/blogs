#!/bin/bash

read -t 30 -p "Please input a number: " number1
read -t 30 -p "Please input an operator: " operator
read -t 30 -p "Please input another number: " number2

if [ -n "$number1" -a -n "$operator" -a "$number2" ]
	then
	test1=$(echo $number1 | sed 's/[0-9]//g')
	test2=$(echo $number2 | sed 's/[0-9]//g')
	if [ -z "$test1" -a -z "$test2" ]
		then
		if [ "$operator" == '+' ]
			then
			result=$(($number1+$number2))
		elif [ "$operator" == '-' ]
			then
			result=$(($number1-$number2))
		elif [ "$operator" == '*' ]
			then
			result=$(($number1*$number2))
		elif [ "$operator" == '/' ]
			then
			result=$(($number1/$number2))
		else
			echo "operator incorrect"
			exit 10
		fi
	else
		echo "number incorrect"
		exit 11
	fi
else
	echo "context zero"
	exit 12
fi

echo "$number1 $operator $number2 = $result"
