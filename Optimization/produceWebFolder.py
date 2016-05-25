import os
import sys

print sys.argv
if len(sys.argv) <= 1 :
    print "please tell me today's date: \n"
    exit()

os.system('mkdir ~/www/figuresLxplus/')
os.system('mkdir ~/www/figuresLxplus/' + sys.argv[1] + '/')
os.system('mkdir ~/www/figuresLxplus/' + sys.argv[1] + '/monoH')
os.system('mkdir ~/www/figuresLxplus/' + sys.argv[1] + '/monoH/TMVA')

os.system('cp ~/www/index.php ~/www/figuresLxplus/' + sys.argv[1] + '/monoH/TMVA/')

os.system('cp -r ggZH qqZH ZH ~/www/index.php ~/www/figuresLxplus/' + sys.argv[1] + '/monoH/TMVA/')

os.system('cp ~/www/index.php ~/www/figuresLxplus/' + sys.argv[1] + '/monoH/TMVA/ggZH')
os.system('cp ~/www/index.php ~/www/figuresLxplus/' + sys.argv[1] + '/monoH/TMVA/qqZH')
os.system('cp ~/www/index.php ~/www/figuresLxplus/' + sys.argv[1] + '/monoH/TMVA/ZH')

