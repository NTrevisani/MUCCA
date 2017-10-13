#!/bin/sh

NBKGS=$1
MODEL=$2
NVARIABLES=$3
CHANNEL=$4
MASS=$5

cd -

cd /afs/cern.ch/user/n/ntrevisa/work/CMSSW_8_0_26_patch1/src/

eval `scramv1 runtime -sh`

cd -

date +"%T"

echo "Copying DF..."

cp -r /eos/user/n/ntrevisa/trees/Full2016_Apr17/Apr2017_summer16/lepSel__MCWeights__bSFLpTEffMulti__cleanTauMC__l2loose__hadd__l2tightOR__formulasMC__wwSel__monohSel/ .

date +"%T"

echo "Copying SF..."

cp -r /eos/user/n/ntrevisa/trees/Full2016_Apr17/Apr2017_summer16/lepSel__MCWeights__bSFLpTEffMulti__cleanTauMC__l2loose__hadd__l2tightOR__formulasMC__sfSel__monohSel/ .

date +"%T"

echo "Copied!!!"

cp /afs/cern.ch/user/n/ntrevisa/work/CMSSW_8_0_26_patch1/src/MUCCA/Optimization/TrainApr2017.cxx .

echo "Running Training..."

root -l -q TrainApr2017.cxx\($NBKGS,$MODEL,$NVARIABLES,$CHANNEL,\"BDTG,BDTG2,BDTG3,BDTG4,BDTG5,BDTG6,BDTG7,BDTG8,BDTG9,BDTG10,BDTG11,BDTG12,BDTG13,BDTG14,BDTG15,BDTG16,BDTG17,BDTG18,BDTG19,BDT,BDT2,BDT3,BDT4,BDT5,BDT6,BDT7,BDT8,BDT9,BDT10,BDT11,BDT12,BDT13,BDT14,BDT15,BDT16,\",$MASS,\"false\"\)

date +"%T"

echo "Now everything is trained!!!"

echo "Removing folders..."

rm -rf lepSel__MCWeights__bSFLpTEffMulti__cleanTauMC__l2loose__hadd__l2tightOR__formulasMC__wwSel__monohSel/

rm -rf lepSel__MCWeights__bSFLpTEffMulti__cleanTauMC__l2loose__hadd__l2tightOR__formulasMC__sfSel__monohSel/

date +"%T"

echo "End! Bye!"

