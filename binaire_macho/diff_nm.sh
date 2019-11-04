#!/bin/zsh
rm errftnm errnm 
for file in $@ $1
do
	echo "diff on $file"
	echo $file >> errftnm
	nm $file > resnm 2> errnm
	../nm/ft_nm $file > resftnm 2>> errftnm
	if [ -s errnm ]
	then
		echo "err with nm"
	else
		diff -U 3 resnm resftnm
		if [ $? -eq 1 ]
		then
			echo "[!] output from nm and ft_nm differ."
			read
			#exit
		fi
	fi
done
rm resnm resftnm
