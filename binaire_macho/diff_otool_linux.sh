#!/bin/zsh
rm errftotool errotool 
for file in $@ $1
do
	echo "diff on $file"
	dir=${file%/*}
	filename=${file##*/}
	if [ -s "$dir/otool_out/$filename.otool_err" ]
	then
		echo "err by nm"
	else
		echo $file >> errftnm
		cat $dir/otool_out/$filename.otool_out > resotool 2>> errotool
		../otool/ft_otool $file > resftotool 2>> errftotool
		colordiff -u resotool resftotool 
		if [ $? -eq 1 ]
		then
			echo "[!] output from nm and ft_nm differ."
			read
			#exit
		fi

	fi
done
