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

 
For Full 2016, when lxbatch is slow:

    root -l -q 'Train.cxx(6,1,"0","em","BDTG4,BDT4")' &
    root -l -q 'Train.cxx(6,2,"0","em","BDTG4,BDT4")' &

    root -l -q 'Train.cxx(6,1,"0","sf","BDTG4,BDT4")' &
    root -l -q 'Train.cxx(6,2,"0","sf","BDTG4,BDT4")' &


    root -l -q 'Train.cxx(6,1,"5","em","BDTG4,BDT4")' &
    root -l -q 'Train.cxx(6,2,"5","em","BDTG4,BDT4")' &

    root -l -q 'Train.cxx(6,1,"5","sf","BDTG4,BDT4")' &
    root -l -q 'Train.cxx(6,2,"5","sf","BDTG4,BDT4")' &

    python myScript.py TMVA-2HDM_TTbar_0var_em 
    python myScript.py TMVA-Zbar_TTbar_0var_em 

    python myScript.py TMVA-2HDM_TTbar_0var_sf 
    python myScript.py TMVA-Zbar_TTbar_0var_sf 

    python myScript.py TMVA-2HDM_TTbar_5var_em 
    python myScript.py TMVA-Zbar_TTbar_5var_em 

    python myScript.py TMVA-2HDM_TTbar_5var_sf 
    python myScript.py TMVA-Zbar_TTbar_5var_sf 

Train:

# All MVA Methods	
    root -l -q Train.cxx\(1,\"BDT,BDTB,BDTD,BDTG,MLPBNN,SVM,KNN,LD,FDA_GA,MLP\"\)
    root -l -q Train.cxx\(2,\"BDT,BDTB,BDTD,BDTG,MLPBNN,SVM,KNN,LD,FDA_GA,MLP\"\)
    root -l -q Train.cxx\(3,\"BDT,BDTB,BDTD,BDTG,MLPBNN,SVM,KNN,LD,FDA_GA,MLP\"\)
    root -l -q Train.cxx\(4,\"BDT,BDTB,BDTD,BDTG,MLPBNN,SVM,KNN,LD,FDA_GA,MLP\"\)

# Focus on BDT
    root -l -q Train.cxx\(1,1,\"BDT4,BDTB,BDTG4\"\)
    root -l -q Train.cxx\(2,1,\"BDT4,BDTB,BDTG4\"\)
    root -l -q Train.cxx\(3,1,\"BDT4,BDTB,BDTG4\"\)
    root -l -q Train.cxx\(4,1,\"BDT4,BDTB,BDTG4\"\)
    root -l -q Train.cxx\(5,1,\"BDT4,BDTB,BDTG4\"\)
    root -l -q Train.cxx\(6,1,\"BDT4,BDTB,BDTG4\"\)

    root -l -q Train.cxx\(1,2,\"BDT4,BDTB,BDTG4\"\)
    root -l -q Train.cxx\(2,2,\"BDT4,BDTB,BDTG4\"\)
    root -l -q Train.cxx\(3,2,\"BDT4,BDTB,BDTG4\"\)
    root -l -q Train.cxx\(4,2,\"BDT4,BDTB,BDTG4\"\)
    root -l -q Train.cxx\(5,2,\"BDT4,BDTB,BDTG4\"\)
    root -l -q Train.cxx\(6,2,\"BDT4,BDTB,BDTG4\"\)

# Now use these:
    root -l -q Train.cxx\(6,1,\"0\",\"BDTG4,BDT4\"\)
    root -l -q Train.cxx\(6,1,\"1\",\"BDTG4,BDT4\"\)
    root -l -q Train.cxx\(6,1,\"2\",\"BDTG4,BDT4\"\)
    root -l -q Train.cxx\(6,1,\"3\",\"BDTG4,BDT4\"\)
    root -l -q Train.cxx\(6,1,\"4\",\"BDTG4,BDT4\"\)
    root -l -q Train.cxx\(6,1,\"5\",\"BDTG4,BDT4\"\)
    python myScript.py TMVA-2HDM_TTbar_0var
    python myScript.py TMVA-2HDM_TTbar_1var
    python myScript.py TMVA-2HDM_TTbar_2var
    python myScript.py TMVA-2HDM_TTbar_3var
    python myScript.py TMVA-2HDM_TTbar_4var
    python myScript.py TMVA-2HDM_TTbar_5var

    root -l -q Train.cxx\(6,2,\"0\",\"BDTG4,BDT4\"\)
    root -l -q Train.cxx\(6,2,\"1\",\"BDTG4,BDT4\"\)
    root -l -q Train.cxx\(6,2,\"2\",\"BDTG4,BDT4\"\)
    root -l -q Train.cxx\(6,2,\"3\",\"BDTG4,BDT4\"\)
    root -l -q Train.cxx\(6,2,\"4\",\"BDTG4,BDT4\"\)
    root -l -q Train.cxx\(6,2,\"5\",\"BDTG4,BDT4\"\)
    python myScript.py TMVA-Zbar_TTbar_0var
    python myScript.py TMVA-Zbar_TTbar_1var
    python myScript.py TMVA-Zbar_TTbar_2var
    python myScript.py TMVA-Zbar_TTbar_3var
    python myScript.py TMVA-Zbar_TTbar_4var
    python myScript.py TMVA-Zbar_TTbar_5var






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
	python myScript.py TMVA-Higgs
	python myScript.py TMVA-WW
	python myScript.py TMVA-TTbar

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
