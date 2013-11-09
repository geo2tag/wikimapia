#!/bin/bash

if [ $# -ne "6" ]
then
  echo "Usage: ./process_wikimapia_dump.sh lat_min lat_max lon_min lon_max dump_dir results_dir"
  exit 1
fi

echoStderr()
{
	echo $@ 1>&2;
}

getFileExtention()
{
	if [ $# -ne "1" ]
	then
	  echo "Usage: getFileExtention file "
	  exit 1
	fi
	
	echo $1 |awk -F . '{print $NF}'
}


processDumpDirectoryEntry()
{
	if [ $# -ne "1" ]
	then
	  echo "Usage: processDumpDirectoryEntry entry"
	  exit 1
	fi
	
	entry=$1;
	# Determine type of the entry: bz2 archive (tar.bz2), xml file, directory, other
	
	if [[ -d ${entry} ]]; 
	then
		echo "dir"
	else
		extension=`getFileExtention ${entry}`;
		echo ${extension}
	fi
}

processXmlFile()
{
	if [ $# -ne "1" ]
	then
	  echo "Usage: processXmlFile file"
	  exit 1
	fi
	
	xmlFile=$1;	

	# TODO add xml processing
	check_result=`checkCoordinates ${xmlFile}`;	
	if [ ${check_result} == "1" ]
	then
		echo "File ${xmlFile} contains neccessary coordinates."
		cp ${xmlFile} ${results_directory}
	else
		echo "File ${xmlFile} will be skipped"
	fi
}

# Usage: checkCoordinates xmlFile
# Return value: 1 if at least one type of coordinates lies in boundaries
#		0 if both (lat/lon) does not lie in boundaries
checkCoordinates()
{
	xmlFile=$1;

	pairCheckResult=`cat ${xmlFile} | grep -o '<lon>[^<]*</lon><lat>[^<]*</lat>' | sed 's|</[a-z]*><[a-z]*>| |g' | sed 's|<[/a-z]*>||g' | checkCoordinatePair | wc -l `;
	echoStderr "pairCheckResult=${pairCheckResult}" 
#checkCoordinatePair | wc -l`;

	if [[ ${pairCheckResult} == "0" ]]
	then 
		echo "0";
	else
		echo "1";
	fi

}

# Usage: echo "111.11" | checkCoordinate  
# Return value: 1 if at least one coordinate is =<maxValue and >=minValue ,
#		nothing if no coordinates are in bounaries 
checkCoordinatePair()
{
	read pair
	echoStderr "pair=${pair}"
	lon=`echo ${pair} | grep -o "^[^ ]*"`;	
	lat=`echo ${pair} | grep -o "[^ ]*$"`;	

	lat_check=`checkBounds $lat_min $lat_max $lat`;
	lon_check=`checkBounds $lon_min $lon_max $lon`;
	if [[ ${lat_check} == "1" && ${lon_check} == "1" ]]
	then 
		echo "1"
	fi
	
}

checkBounds()
{
	#read value_to_test
	min_value=$1;
	max_value=$2;
	value_to_test=$3;
	isNumber=`echo ${value_to_test} | grep -Eo "^[0-9]+([.][0-9]+)?$" | wc -l`;
	echoStderr "value_to_test=${value_to_test}"
	echoStderr "${value_to_test}>=${min_value}"
	echoStderr "${value_to_test}<=${max_value}"
	if [ ${isNumber} == "0" ]
	then
		echoStderr "value_to_test is no a number!!"
		return 0
	fi	


	ge_min=`echo "${value_to_test}>=${min_value}" | bc -l`;
	le_max=`echo "${value_to_test}<=${max_value}" | bc -l`;
	echoStderr "ge_min=${ge_min}"
	echoStderr "le_min=${le_max}"
	if [ ${ge_min} == "1" ]
	then
		if [ ${le_max} == "1" ]
		then
			echo "1";
		fi

	fi
}
# | grep -o "<lat>[^<]*</lat>" | grep -o '[0-9\.]*

lat_min=$1;
lat_max=$2;
lon_min=$3;
lon_max=$4;

dump_directory=$5;
results_directory=$6;

files=`ls $dump_directory`;

for dump_directory_entry in $files
do
	echo "Processing ${dump_directory}/${dump_directory_entry}"
	entry_type=`processDumpDirectoryEntry ${dump_directory}/${dump_directory_entry}`;
	echoStderr "entry_type=${entry_type}" 

	if [ $entry_type == "dir" ] 
	then

		./process_wikimapia_dump.sh ${lat_min} ${lat_max} ${lon_min} ${lon_max} ${dump_directory}/${dump_directory_entry} ${results_directory}

	elif [ $entry_type == "bz2" ]
	then
		dir_name=`basename ${dump_directory_entry} .bz2`;
		old_pwd=`pwd`;
		
		echoStderr "dir_name=${dir_name}"
		echoStderr "old_pwd=${old_pwd}"
		echoStderr "dump_directory_entry=${dump_directory_entry}"
		echoStderr "dump_directory=${dump_directory}"

		cd ${dump_directory}/
		tar -xjf ${dump_directory_entry}
		pwd
		cd ${old_pwd}
		if [ -d ${dump_directory}/${dir_name} ]
		then
			./process_wikimapia_dump.sh ${lat_min} ${lat_max} ${lon_min} ${lon_max} ${dump_directory}/${dir_name} ${results_directory}
			rm -rf ${dump_directory}/${dir_name}
		fi

	elif [ $entry_type == "xml" ]
	then
		processXmlFile ${dump_directory}/${dump_directory_entry}
	fi
	

done
