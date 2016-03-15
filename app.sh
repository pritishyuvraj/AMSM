#!/bin/sh
ps -ax|cat >temp
top -n 1 -b | cat >consumption
rm temp2.txt

echo -n $cpu >>temp2.txt

echo -n "!" >>temp2.txt

a=$(grep "Cpu(s)" consumption);
i=0; 
for var in $a; 
do
	i=`expr 1 + $i`;
	if [ $i -eq 2 ]; 
	then 
		echo -n $var >>temp2.txt; 
	fi;
done

for var in `cat parameters`
do 
	#echo $var;
	y=$(grep "$var" temp| wc -l);
	#echo $y
	if [ $y -gt 0 ]
	then
		cpu_consump=$(awk '/'"$var"'/ {print $9}' consumption);
		mem_consump=$(awk '/'"$var"'/ {print $10}' consumption);
		echo -n "$var%$cpu_consump%$mem_consump%" >>temp2.txt
		#echo "$var%$cpu_consump%$mem_consump%"
	else
		echo -n "not running:$var%" >>temp2.txt
		#echo -n "not running:$var%" 
		#./$var &

	fi	
	#echo $ {array[*]} | cat >temp2.txt
done
