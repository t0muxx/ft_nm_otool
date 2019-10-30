#!/bin/zsh
rm errftnm errnm 
for file in $@ $1
do
	echo "diff on $file"
	echo $file >> errftnm
	../nm_mac $file > resnm 2>> errnm
	../nm/ft_nm $file > resftnm 2>> errftnm
	diff resnm resftnm
done
rm resnm resftnm
