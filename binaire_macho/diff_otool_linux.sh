#!/bin/zsh
rm errftnm errnm 
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
		cat $dir/nm_out/$filename.otool_out > resotool 2>> errotool
		../otool/ft_otool $file > resftotool 2>> errftotool
		diff resotool resftotool
	fi
done
rm resotool resftotool
