for file in $(find . -type f -name "*.c")
do
		trimmedName=`echo $file | cut -d'/' -f2 | cut -d'.' -f1`
		Name=`echo $file | cut -d'/' -f2`
		#printf "%s\t " $trimmedName 

		gcc $file -o $trimmedName 2>/dev/null
		if [ -f $trimmedName ]
		then
			ans=$(./$trimmedName)
			#printf $ans
			if [ $ans == 20 ]
			then 
				#printf '1st'
				ans=10
			else 
				#printf '2st'
				ans=7
			fi
		else
			ans=5
		fi
		printf "%s\t\t%s\n" $Name $ans
		
	done
