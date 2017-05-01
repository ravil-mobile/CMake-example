#!/bin/bash


# set all script variables 
SCRIPT="cmake_run.sh"

# copy the script to the upper folder 
# befor cleaning the current one
cp ./$SCRIPT ../$SCRIPT


# clean the folder
rm -r ./*


# copy the script.sh back to the folder
cp ../$SCRIPT ./
rm ../$SCRIPT
chmod 777 ./$SCRIPT


# clean the window
clear


# run cmake
cmake ../src


# run make if the user explicitly ask about that
if [ "$#" -eq 1 ]; then
    if [ $1="make" ]; then
    	make
    fi
fi
