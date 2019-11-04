#!/bin/zsh
rm errftnm errnm 
for file in $@ $1
do
	echo "diff on $file"
	dir=${file%/*}
	filename=${file##*/}
	if [ -s "$dir/nm_out/$filename.err" ]
	then
		echo "err by nm"
	else
		echo $file >> errftnm
		cat $dir/nm_out/$filename.out > resnm 2>> errnm
		../nm/ft_nm $file > resftnm 2>> errftnm
		colordiff -u resnm resftnm
		if [ $? -eq 1 ]
		then
			echo "[!] output from nm and ft_nm differ."
			read
			#exit
		fi
	fi
done
rm resnm resftnm
