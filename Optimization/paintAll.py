import os

models=['2HDM','Zbar']
backgrounds=['qqZH','ggZH','ZH','Higgs','WW','TTbar']
nvariables=['0','1','2','3','4','5']

print 'source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.21/x86_64-slc5-gcc47-opt/root/bin/thisroot.sh'

for indexModel in range(len(models)) :
    for indexBkg in range(len(backgrounds)) :
        for indexVar in range(len(nvariables)) :
            print 'python myScript.py TMVA-' + models[indexModel] + '_' + backgrounds[indexBkg] + '_' + nvariables[indexVar] + 'var'
            os.system('python myScript.py TMVA-' + models[indexModel] + '_' + backgrounds[indexBkg] + '_' + nvariables[indexVar] + 'var')
