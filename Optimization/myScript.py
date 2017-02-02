import os
import sys
import time

print sys.argv
if len(sys.argv) <= 1 :
    print "please tell me which file you want me to analyze: \n"
    exit()

#input variables
os.system('root -l -b -q \'mymacros/variables.C(\"' + sys.argv[1] + '.root\")\'')
#correlation matrix
os.system('root -l -b -q \'mymacros/correlations.C(\"' + sys.argv[1] + '.root\")\'')
#ROC curve
os.system('root -l -b -q \'mymacros/efficiencies.C(\"' + sys.argv[1] + '.root\")\'')
os.system('root -l -b -q \'mymacros/mvaeffs.C(\"' + sys.argv[1] + '.root\")\'')
#check overtraining
os.system('root -l -b -q \'mymacros/mvas.C(\"' + sys.argv[1] + '.root\",0)\'')
os.system('root -l -b -q \'mymacros/mvas.C(\"' + sys.argv[1] + '.root\",1)\'')
os.system('root -l -b -q \'mymacros/mvas.C(\"' + sys.argv[1] + '.root\",2)\'')
os.system('root -l -b -q \'mymacros/mvas.C(\"' + sys.argv[1] + '.root\",3)\'') #test/training superimposed

os.system('rm -rf plots' + sys.argv[1] + '/')
os.system('mv plots plots' + sys.argv[1] + '/')

weightName = sys.argv[1]
weightNameOK = weightName.replace("TMVA-", "")

os.system('mkdir ~/www/figuresLxplus/')
os.system('mkdir ~/www/figuresLxplus/' + time.strftime("%d%b%Y") + '/')
os.system('mkdir ~/www/figuresLxplus/' + time.strftime("%d%b%Y") + '/monoH')
os.system('mkdir ~/www/figuresLxplus/' + time.strftime("%d%b%Y") + '/monoH/TMVA')
os.system('mkdir ~/www/figuresLxplus/' + time.strftime("%d%b%Y") + '/monoH/TMVA/plots' + sys.argv[1])

os.system('cp -r ~/www/index.php plots' + sys.argv[1] + '/* Weights-' + weightNameOK + ' ~/www/figuresLxplus/' + time.strftime("%d%b%Y") + '/monoH/TMVA/plots' + sys.argv[1])

