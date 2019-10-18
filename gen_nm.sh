#/usr/bin/bash

for file in $@ ./binaire_macho/*
do
	basename "$file"
	f="$(basename -- $file)"
	nm $file > ./binaire_macho_log/$f
done
