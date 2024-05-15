#!bin/bash

echo "OK"
./hastime 1 1 1
./hastime 01 0 09
./hastime "2" 2 "12"
./hastime "2" "01" "23"

echo
echo "ERROR"
./hastime
./hastime ""
./hastime "" ""
./hastime "" "" ""
./hastime "2" "" "3"
./hastime "2" 2 "a"
./hastime 1 "2" "-1"
./hastime 1 2 3
./hastime 1 23 4



