while true
do
	radamsa sample_1 > fuzzed
	../../nm/ft_nm fuzzed
	test $? -gt 127 && break
done
