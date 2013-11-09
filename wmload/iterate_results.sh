#!/bin/bash

files=results/*.xml
for f in $files
do
  echo "Processing $f file..."
  ./wmloader ${f} karelia karelia_wikimapia 29.212646 37.990723 60.586967 66.700824 2>&1 
done
