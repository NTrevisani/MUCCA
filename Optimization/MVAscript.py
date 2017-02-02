import os

# Adding 2HDM mva variable

# nominal trees
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/nominal/MonoH/*         ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/nominal/MonoH/")

# sfSel
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__JESup/MonoH/*    ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__JESup/MonoH/")
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__JESdo/MonoH/*    ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__JESdo/MonoH/")
                                                                   
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__METup/MonoH/*    ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__METup/MonoH/")
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__METdo/MonoH/*    ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__METdo/MonoH/")
                                                                   
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__ElepTup/MonoH/*  ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__ElepTup/MonoH/") 
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__ElepTdo/MonoH/*  ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__ElepTdo/MonoH/")
                                                                   
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__MupTup/MonoH/*   ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__MupTup/MonoH/")
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__MupTdo/MonoH/*   ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__MupTdo/MonoH/")
                                                                   
                                                                   
# wwSel                                                            
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__JESup/MonoH/*    ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__JESup/MonoH/")
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__JESdo/MonoH/*    ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__JESdo/MonoH/")
                                                                   
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__METup/MonoH/*    ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__METup/MonoH/")
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__METdo/MonoH/*    ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__METdo/MonoH/")
                                                                   
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__ElepTup/MonoH/*  ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__ElepTup/MonoH/")
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__ElepTdo/MonoH/*  ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__ElepTdo/MonoH/")
                                                                   
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__MupTup/MonoH/*   ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__MupTup/MonoH/")
os.system("gardener.py mucca2HDMVarFiller --signal=\"2HDMadaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__MupTdo/MonoH/*   ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__MupTdo/MonoH/")



# # Adding Zbar mva variable

# #nominal trees
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/nominal/MonoH/*               ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/nominal/MonoH/")

# sfSel
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__JESup/MonoH/*          ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__JESup/MonoH/")
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__JESdo/MonoH/*          ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__JESdo/MonoH/")
                                                                   
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__METup/MonoH/*          ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__METup/MonoH/")
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__METdo/MonoH/*          ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__METdo/MonoH/")
                                                                   
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__ElepTup/MonoH/*        ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__ElepTup/MonoH/")
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__ElepTdo/MonoH/*        ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__ElepTdo/MonoH/")
                                                                   
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__MupTup/MonoH/*         ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__MupTup/MonoH/")
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__MupTdo/MonoH/*         ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/sfSel__MupTdo/MonoH/")
                                                                   
                                                                   
# wwSel
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__JESup/MonoH/*          ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__JESup/MonoH/")
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__JESdo/MonoH/*          ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__JESdo/MonoH/")
                                                                   
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__METup/MonoH/*          ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__METup/MonoH/")
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__METdo/MonoH/*          ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__METdo/MonoH/")
                                                                   
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__ElepTup/MonoH/*        ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__ElepTup/MonoH/")
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__ElepTdo/MonoH/*        ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__ElepTdo/MonoH/")
                                                                   
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__MupTup/MonoH/*         ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__MupTup/MonoH/")
os.system("gardener.py muccaZbarVarFiller --signal=\"ZbaradaptTTbar\" ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__MupTdo/MonoH/*         ~/work/CMSSW_8_0_5/src/AnalysisCMS/minitrees/wwSel__MupTdo/MonoH/")
                                                                   
                                                                   
