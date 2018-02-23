#!/bin/bash
#Program:
#	User inputs his first name and last name. Program shows his full name.
#History:
#2016/05/01 wanghuiyong First release
PATH=$PATH:~/bin:~/scripts
export PATH

read -p "Please input your first name: " firstname
read -p "Please input your last name: " lastname
echo -e "\nYour full name is: $firstname $lastname"
