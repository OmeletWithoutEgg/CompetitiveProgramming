#!/bin/bash

NAME=gondola

/usr/bin/g++ -Dlocal -static -O2 -std=c++11 -o $NAME grader.cpp $NAME.cpp
