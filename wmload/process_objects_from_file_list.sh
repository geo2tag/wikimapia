#!/bin/bash

if [ $# -ne "1" ]
then
  echo "Usage: ./process_objects_from_file_list.sh file"
  exit 1
fi


list=`cat $1`;

for i in ${list}
do
	echo "Processing $i file"
	./wmloader ${i} karelia karelia_wikimapia 29.212646 37.990723 60.586967 66.700824 2>&1
done
