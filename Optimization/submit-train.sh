#!/bin/sh

NBKGS=$1
MODEL=$2
NVARIABLES=$3

cd /afs/cern.ch/user/n/ntrevisa/work/CMSSW_8_0_5/src/

eval `scramv1 runtime -sh`

cd MUCCA/Optimization/

`root -l -q Train.cxx\($NBKGS,$MODEL,$NVARIABLES,\"BDTG4,BDT4\"\)`

