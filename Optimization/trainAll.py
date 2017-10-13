import os

nvariables=['0']
channel=['em','sf']
massPoints=['high','low','new','superHigh']
trainings=['BDTG','BDTG2','BDTG3','BDTG4','BDTG5','BDTG6','BDTG7','BDTG8','BDTG9','BDTG10','BDTG11','BDTG12','BDTG13','BDTG14','BDTG15','BDTG16','BDTG17','BDTG18','BDTG19','BDT','BDT2','BDT3','BDT4','BDT5','BDT6','BDT7','BDT8','BDT9','BDT10','BDT11','BDT12','BDT13','BDT14','BDT15','BDT16']

os.system("mkdir -p jobs")

for bkg in range(6,7) :
    for model in range (1,3) :
        for index in range(len(nvariables)) :
            for indexCh in range(len(channel)) :
                for indexMass in range(len(massPoints)) :
                    #for indexTrain in range(len(trainings)) :
                    print("bsub -q 1nd -o jobs/" + str(bkg) + "_" + str(model) + "_" + nvariables[index] + "_" + channel[indexCh] + "_" + massPoints[indexMass] + ".out -e  jobs/" + str(bkg) + "_" + str(model) + "_" + nvariables[index] + "_" + channel[indexCh] + "_" + massPoints[indexMass] + ".err submit-train.sh " + str(bkg) + " " + str(model) + " \\\"" + nvariables[index] + "\\\" \\\"" + channel[indexCh] + "\\\"  \\\"" + massPoints[indexMass] + "\\\"")
                    #os.system("bsub -q 8nh -o jobs/" + str(bkg) + "_" + str(model) + "_" + nvariables[index] + "_" + channel[indexCh] + ".out -e  jobs/" + str(bkg) + "_" + str(model) + "_" + nvariables[index] + "_" + channel[indexCh] + ".err submit-train.sh " + str(bkg) + " " + str(model) + " \\\"" + nvariables[index] + "\\\" \\\"" + channel[indexCh] + "\\\"")

                    os.system("rm -rf LSFJOB*")
