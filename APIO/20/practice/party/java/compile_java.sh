#!/bin/bash

problem=party

javac "grader.java" "${problem}.java"
jar cfe "${problem}.jar" "grader" *.class
