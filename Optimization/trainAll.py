import os

nvariables=['0']
channel=['em']
massPointsA=['600','800','1000','1200','1400','1700','2000','2500']
massPointsB=['10','20','50','100','200','300','500','1000','2000','10000']
trainings=['BDTG','BDTG2','BDTG3','BDTG4','BDTG5','BDTG6','BDTG7','BDTG8','BDTG9','BDTG10','BDTG11','BDTG12','BDTG13','BDTG14','BDTG15','BDTG16','BDTG17','BDTG18','BDTG19','BDT','BDT2','BDT3','BDT4','BDT5','BDT6','BDT7','BDT8','BDT9','BDT10','BDT11','BDT12','BDT13','BDT14','BDT15','BDT16']

os.system("mkdir -p jobs")

##    for model in range (1,3) :

model = 1
massB = 300

for bkg in range(6,7) :
    for index in range(len(nvariables)) :
        for indexCh in range(len(channel)) :
            for indexMass in range(len(massPointsA)) :
                    #for indexTrain in range(len(trainings)) :
                print("bsub -q 1nd -o jobs/" + str(bkg) + "_" + str(model) + "_" + nvariables[index] + "_" + channel[indexCh] + "_" + massPointsA[indexMass] + ".out -e  jobs/" + str(bkg) + "_" + str(model) + "_" + nvariables[index] + "_" + channel[indexCh] + "_" + massPointsA[indexMass] + ".err submit-train.sh " + str(bkg) + " " + str(model) + " \\\"" + nvariables[index] + "\\\" \\\"" + channel[indexCh] + "\\\"  \\\"" + massPointsA[indexMass] + "\\\" \\\"" + str(massB) + "\\\"")
                    #os.system("bsub -q 8nh -o jobs/" + str(bkg) + "_" + str(model) + "_" + nvariables[index] + "_" + channel[indexCh] + ".out -e  jobs/" + str(bkg) + "_" + str(model) + "_" + nvariables[index] + "_" + channel[indexCh] + ".err submit-train.sh " + str(bkg) + " " + str(model) + " \\\"" + nvariables[index] + "\\\" \\\"" + channel[indexCh] + "\\\"")


model = 2
massB = 1

for bkg in range(6,7) :
    for index in range(len(nvariables)) :
        for indexCh in range(len(channel)) :
            for indexMass in range(len(massPointsB)) :
                    #for indexTrain in range(len(trainings)) :
                print("bsub -q 1nd -o jobs/" + str(bkg) + "_" + str(model) + "_" + nvariables[index] + "_" + channel[indexCh] + "_" + massPointsB[indexMass] + ".out -e  jobs/" + str(bkg) + "_" + str(model) + "_" + nvariables[index] + "_" + channel[indexCh] + "_" + massPointsB[indexMass] + ".err submit-train.sh " + str(bkg) + " " + str(model) + " \\\"" + nvariables[index] + "\\\" \\\"" + channel[indexCh] + "\\\"  \\\"" + massPointsB[indexMass] + "\\\" \\\"" + str(massB) + "\\\"")
                    #os.system("bsub -q 8nh -o jobs/" + str(bkg) + "_" + str(model) + "_" + nvariables[index] + "_" + channel[indexCh] + ".out -e  jobs/" + str(bkg) + "_" + str(model) + "_" + nvariables[index] + "_" + channel[indexCh] + ".err submit-train.sh " + str(bkg) + " " + str(model) + " \\\"" + nvariables[index] + "\\\" \\\"" + channel[indexCh] + "\\\"")


                os.system("rm -rf LSFJOB*")
