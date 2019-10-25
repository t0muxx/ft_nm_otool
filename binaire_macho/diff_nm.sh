#!/bin/zsh
for file in $@ $1
do
	echo "diff on $file"
	../nm_mac $file > resnm 2> errnm
	../nm/ft_nm $file > resftnm 2> errftnm
	diff resnm resftnm
done
rm resnm resftnm
