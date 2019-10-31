#!/bin/sh

if [ -z $1 ]
then
	echo "[!] Please specify program to test."
	exit
fi

if [ -z "$2" ]
then
	echo "[!] Please specify original program"
	exit
fi

if [ -z $3 ]
then
	echo "[+] Please specify a directory with executable samples."
	exit
fi

PRG="$1"
ORIG="$2"
OUT0="/tmp/out0"
OUT1="/tmp/out1"

for file in $3/*
do
	echo "[!] Testing $PRG with $file"
	$PRG $file 2>&1 > $OUT0
	if [ $? -gt 127 ]
	then
		echo "[!] Bad SIG on test case $file."
		exit
	fi
	$ORIG $file 2>&1 > $OUT1
	diff $OUT0 $OUT1
	if [ $? -eq 1 ]
	then
		echo "[!] output from $PRG and $ORIG differ."
		read
		#exit
	fi
done
