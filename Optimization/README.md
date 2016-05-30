Training
====

source of root, needed for the GUI later


    To train the MVA maybe you want to use this:

    source /afs/cern.ch/sw/lcg/external/gcc/4.9/x86_64-slc6-gcc49-opt/setup.sh
    source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.04.10/x86_64-slc6-gcc49-opt/root/bin/thisroot.sh
    source /afs/cern.ch/project/eos/installation/user/etc/setup.sh
    cd /tmp/ntrevisa/    
    eosmount eos
    cd -


    But to use the GUI I would use this:

    source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.21/x86_64-slc5-gcc47-opt/root/bin/thisroot.sh

 

Train:

    root -l -q Train.cxx\(1,\"BDT,BDTB,BDTD,BDTG,MLPBNN,SVM,KNN,LD,FDA_GA,MLP\"\)
    root -l -q Train.cxx\(2,\"BDT,BDTB,BDTD,BDTG,MLPBNN,SVM,KNN,LD,FDA_GA,MLP\"\)
    root -l -q Train.cxx\(3,\"BDT,BDTB,BDTD,BDTG,MLPBNN,SVM,KNN,LD,FDA_GA,MLP\"\)

    root -l -q Train.cxx\(4,\"BDTG\"\)
    root -l -q Train.cxx\(5,\"BDTG\"\)
    
    root -l -q Train.cxx\(1\)
    root -l -q Train.cxx\(2\)
    root -l -q Train.cxx\(3\)
    root -l -q Train.cxx\(4\)
    root -l -q Train.cxx\(5\)

    
    root -l TrainMulti.cxx\(\"BDTG\"\)
    root -l TrainMulti.cxx\(\"MLP\"\)

Test:

	python myScript.py TMVA-ggZH
	python myScript.py TMVA-qqZH
	python myScript.py TMVA-ZH

    root -l 'TMVAGui.C("TMVA-1.root")'
    root -l 'TMVAGui.C("TMVA-2.root")'
    root -l 'TMVAGui.C("TMVA-3.root")'

    root -l TMVAGui.C\(\"TMVA-2.root \"\)
    root -l TMVAGui.C\(\"TMVA-3.root \"\)
    root -l TMVAGui.C\(\"TMVA-4.root \"\)
    root -l TMVAGui.C\(\"TMVA-5.root \"\)

    root -l TMVAGui.C\(\"TMVA-1-variables.root \"\)
    root -l TMVAGui.C\(\"TMVA-2-variables.root \"\)
    root -l TMVAGui.C\(\"TMVA-3-variables.root \"\)
    root -l TMVAGui.C\(\"TMVA-4-variables.root \"\)
    root -l TMVAGui.C\(\"TMVA-5-variables.root \"\)

    
To run gardener:

    cp Weights-1/TMVAClassification_BDTG.weights.xml   /afs/cern.ch/user/a/amassiro/Framework/CMSSW_7_6_3/src/LatinoAnalysis/Gardener/python/data/mucca/TMVAClassification_BDTG.weights.bkg1.xml
    cp Weights-2/TMVAClassification_BDTG.weights.xml   /afs/cern.ch/user/a/amassiro/Framework/CMSSW_7_6_3/src/LatinoAnalysis/Gardener/python/data/mucca/TMVAClassification_BDTG.weights.bkg2.xml
    cp Weights-3/TMVAClassification_BDTG.weights.xml   /afs/cern.ch/user/a/amassiro/Framework/CMSSW_7_6_3/src/LatinoAnalysis/Gardener/python/data/mucca/TMVAClassification_BDTG.weights.bkg3.xml
    cp Weights-4/TMVAClassification_BDTG.weights.xml   /afs/cern.ch/user/a/amassiro/Framework/CMSSW_7_6_3/src/LatinoAnalysis/Gardener/python/data/mucca/TMVAClassification_BDTG.weights.bkg4.xml
    cp Weights-5/TMVAClassification_BDTG.weights.xml   /afs/cern.ch/user/a/amassiro/Framework/CMSSW_7_6_3/src/LatinoAnalysis/Gardener/python/data/mucca/TMVAClassification_BDTG.weights.bkg5.xml
    
    
where:

    /home/amassiro/Cern/Code/HIG/MUCCA/
    /afs/cern.ch/user/a/amassiro/work/Latinos/Framework/MUCCA/
