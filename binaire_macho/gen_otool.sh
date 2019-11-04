#!/bin/zsh
for file in $@ $1
do
	echo "otool -t on $file"
	otool -t $file > "$file.otool_out" 2>> "$file.otool_err"
done
