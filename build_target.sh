#!/bin/sh
SR=$PWD
LOC=/home/integreedy/workspace/buildroot/output/host/bin/
cd $LOC
./arm-none-linux-gnueabihf-g++  -Wall $SR/main_app.cpp -o $SR/main_app

sshpass -p root scp $SR/main_app root@192.168.0.11:/workspace/
sshpass -p root ssh -t root@192.168.0.11 'cd /workspace && ./main_app'
