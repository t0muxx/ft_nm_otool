while true
do
	radamsa sample_3 > fuzzed
	../../nm/ft_nm fuzzed
	test $? -gt 0 && break
done
