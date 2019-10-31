#!/bin/zsh
for file in $@ $1
do
	echo "nm on $file"
	nm $file > "$file.out" 2>> "$file.err"
done
