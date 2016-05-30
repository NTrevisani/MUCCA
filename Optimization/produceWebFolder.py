import os
import sys
import time

# print sys.argv
# if len(sys.argv) <= 1 :
#     print "please tell me today's date: \n"
#     exit()

os.system('mkdir ~/www/figuresLxplus/')
os.system('mkdir ~/www/figuresLxplus/' + time.strftime("%d%b%Y") + '/')
os.system('mkdir ~/www/figuresLxplus/' + time.strftime("%d%b%Y") + '/monoH')
os.system('mkdir ~/www/figuresLxplus/' + time.strftime("%d%b%Y") + '/monoH/TMVA')

os.system('cp ~/www/index.php ~/www/figuresLxplus/' + time.strftime("%d%b%Y") + '/monoH/TMVA/')

os.system('cp -r ggZH qqZH ZH ~/www/index.php ~/www/figuresLxplus/' + time.strftime("%d%b%Y") + '/monoH/TMVA/')

os.system('cp ~/www/index.php ~/www/figuresLxplus/' + time.strftime("%d%b%Y") + '/monoH/TMVA/ggZH')
os.system('cp ~/www/index.php ~/www/figuresLxplus/' + time.strftime("%d%b%Y") + '/monoH/TMVA/qqZH')
os.system('cp ~/www/index.php ~/www/figuresLxplus/' + time.strftime("%d%b%Y") + '/monoH/TMVA/ZH')


