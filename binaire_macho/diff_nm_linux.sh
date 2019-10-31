#!/bin/zsh
rm errftnm errnm 
for file in $@ $1
do
	echo "diff on $file"
	echo $file >> errftnm
	cat $file.out > resnm 2>> errnm
	../nm/ft_nm $file > resftnm 2>> errftnm
	diff resnm resftnm
done
rm resnm resftnm