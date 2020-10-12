#!/bin/bash

TopDir=`pwd`

RunN=$1
Idx=$2
MaxEvents=$3

Name="LNuLLA"
s1root="s1_${Name}_${RunN}_${Idx}.root"
s21root="s21_${Name}_${RunN}_${Idx}.root"
s22root="s22_${Name}_${RunN}_${Idx}.root"
s3root="s3_${Name}_${RunN}_${Idx}.root"
s4root="s4_${Name}_${RunN}_${Idx}.root"


./runStep1_LNuLLA.sh $s1root $RunN $Idx $MaxEvents
./runStep2_LNuLLA.sh $s1root $s21root $s22root
./runStep3_LNuLLA.sh $s22root $s3root
./runStep4_LNuLLA.sh $s3root $s4root




