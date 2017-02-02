import os

nvariables=['0','1','2','3','4','5']

for bkg in range(1,7) :
    for model in range (1,3) :
        for index in range(len(nvariables)) :
            print("Weights-2HDM_TTbar_0var")
            print("bsub -q 1nh -o jobs/ submit-train.sh " + str(bkg) + " " + str(model) + " \\\"" + nvariables[index] + "\\\"")
            os.system("bsub -q 1nh -o jobs/ submit-train.sh " + str(bkg) + " " + str(model) + " \\\"" + nvariables[index] + "\\\"")
