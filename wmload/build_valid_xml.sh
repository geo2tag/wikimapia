#!/bin/bash


if [ $# -ne 1 ]
then
	echo "Usage: ./build_valid_xml.sh file.xml "
	exit
fi

valid_file_name="$1_valid"
cat $1 | sed -e '/<?xml version="1.0" encoding="utf-8"?>/d' -e '/<?access-control allow="\*"?>/d' | sed '1i <?xml version="1.0" encoding="utf-8"?><objects>' > $valid_file_name
echo "</objects>" >> $valid_file_name
