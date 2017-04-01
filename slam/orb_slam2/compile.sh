#!/bin/bash

LIBRARIES="-L ORB_SLAM2/lib/ -lORB_SLAM2 -lpangolin -lGL $(pkg-config --libs opencv)"
INCLUDE="-I ORB_SLAM2/ -I ORB_SLAM2/include $(pkg-config --cflags opencv) $(pkg-config --cflags eigen3)"
SRC="benchmark.cpp"
EXEC="benchmark"
CFLAGS="-std=c++11"
RPATH="-Wl,-rpath,./ORB_SLAM2/lib"

g++ $SRC -o $EXEC $CFLAGS $INCLUDE $LIBRARIES $RPATH
