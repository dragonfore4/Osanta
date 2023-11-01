for file in $(find . -type f -name "*.c")
do
	printf "%s" $file
done
