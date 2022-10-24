#!/bin/bash
g++ -std=c++17 $1.cpp -o main
if [ "$2" = "1" ];
then
    ./main < input.txt > output.txt
else
    ./main < input.txt
fi

rm main
