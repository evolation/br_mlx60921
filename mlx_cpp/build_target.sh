#!/bin/sh
#SR=$PWD
#LOC=/home/integreedy/workspace/buildroot/output/host/bin/
#cd $LOC
#./arm-none-linux-gnueabihf-g++  -Wall $SR/main_app.cpp -o $SR/main_app
cd $PWD
make

sshpass -p root scp $PWD/mlx90621Log root@192.168.0.11:/workspace/
sshpass -p root ssh -t root@192.168.0.11 'cd /workspace && ./mlx90621Log'
