import os
import sys
import time

print sys.argv
if len(sys.argv) <= 2 :
    print "please tell me which folder and which file you want me to analyze: \n"
    exit()

#input variables
os.system('root -l -b -q \'mymacros/variables.C(\"' + sys.argv[1] + '/' + sys.argv[2] + '.root\")\'')
#correlation matrix
os.system('root -l -b -q \'mymacros/correlations.C(\"' + sys.argv[1] + '/' + sys.argv[2] + '.root\")\'')
#ROC curve
os.system('root -l -b -q \'mymacros/efficiencies.C(\"' + sys.argv[1] + '/' + sys.argv[2] + '.root\")\'')
os.system('root -l -b -q \'mymacros/mvaeffs.C(\"' + sys.argv[1] + '/' + sys.argv[2] + '.root\")\'')
#check overtraining
os.system('root -l -b -q \'mymacros/mvas.C(\"' + sys.argv[1] + '/' + sys.argv[2] + '.root\",0)\'')
os.system('root -l -b -q \'mymacros/mvas.C(\"' + sys.argv[1] + '/' + sys.argv[2] + '.root\",1)\'')
os.system('root -l -b -q \'mymacros/mvas.C(\"' + sys.argv[1] + '/' + sys.argv[2] + '.root\",2)\'')
os.system('root -l -b -q \'mymacros/mvas.C(\"' + sys.argv[1] + '/' + sys.argv[2] + '.root\",3)\'') #test/training superimposed

os.system('rm -rf plots_' + sys.argv[2] + '/')
os.system('mv plots plots_' + sys.argv[2] + '/')

weightName = sys.argv[2]
weightNameOK = weightName.replace("TMVA-", "Weights-")

os.system('mkdir -p ~/www/figuresLxplus/' + time.strftime("%d%b%Y") + '/monoH/TMVA/plots_' + sys.argv[2])

os.system('cp -r ~/www/index.php plots_' + sys.argv[2] + '/* ' + weightNameOK + ' ' + sys.argv[1] + '/' + sys.argv[2] + '.root ~/www/figuresLxplus/' + time.strftime("%d%b%Y") + '/monoH/TMVA/plots_' + sys.argv[2])

