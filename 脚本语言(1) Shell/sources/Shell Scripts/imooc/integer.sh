#!/bin/bash
#Program
#	User input 2 integer numbers; program will cross these two numbers.
#History
#2016/05/01 wanghuiyong First release
PATH=$PATH:~/bin
echo -e "You should input 2 numbers, I will cross them!\n"
read -p "first number: " firstnu
read -p "second number: " secondnu
total=$(($firstnu*$secondnu))
#declare -i total=$firstnu * $secondnu
echo -e "\nThe result of $firstnu * $secondnu is $total"

