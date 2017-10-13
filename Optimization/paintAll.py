import os

models=['2HDM','Zbar']
backgrounds=['TTbar']#['qqZH','ggZH','ZH','Higgs','WW','TTbar']
nvariables=['0']
channels=['em','sf']
massPoints=['high','low','new','superHigh']

print 'source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.21/x86_64-slc5-gcc47-opt/root/bin/thisroot.sh'
os.system('source /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.21/x86_64-slc5-gcc47-opt/root/bin/thisroot.sh')

for indexModel in range(len(models)) :
    for indexBkg in range(len(backgrounds)) :
        for indexVar in range(len(nvariables)) :
            for indexCh in range(len(channels)) :
                for indexMass in range(len(massPoints)):
                    print 'python myScript.py rootFiles_' + models[indexModel] + '_' + backgrounds[indexBkg] + '_' + nvariables[indexVar] + 'var_' + channels[indexCh] + '_' + massPoints[indexMass] + ' TMVA-' + models[indexModel] + '_' + backgrounds[indexBkg] + '_' + nvariables[indexVar] + 'var_' + channels[indexCh] + '_' + massPoints[indexMass]
                    #os.system('python myScript.py rootFiles_' + models[indexModel] + '_' + backgrounds[indexBkg] + '_' + nvariables[indexVar] + 'var_' + channels[indexCh] + '_' + massPoints[indexMass] + '/TMVA-' + models[indexModel] + '_' + backgrounds[indexBkg] + '_' + nvariables[indexVar] + 'var_' + channels[indexCh] + '_' + massPoints[indexMass])
                    


#os.system('python myScript.py TMVA-' + models[indexModel] + '_' + backgrounds[indexBkg] + '_' + nvariables[indexVar] + 'var_' + channels[indexCh] + '_' + massPoints[indexMass])


# rootFiles_2HDM_TTbar_0var_em_new
