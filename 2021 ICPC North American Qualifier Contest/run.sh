#!/bin/bash
g++ -std=c++14 $1.cpp
if [ "$2" = "1" ];
then
    ./a < input.txt > output.txt
else
    ./a < input.txt
fi

rm a.exe