//
// Template from http://root.cern.ch/svn/root/trunk/tmva/test/TMVAClassification.C
//

// @(#)root/tmva $Id$
/**********************************************************************************
 * Project   : TMVA - a ROOT-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Root Macro: TMVAClassification                                                 *
 *                                                                                *
 * This macro provides examples for the training and testing of the               *
 * TMVA classifiers.                                                              *
 *                                                                                *
 * As input data is used a toy-MC sample consisting of four Gaussian-distributed  *
 * and linearly correlated input variables.                                       *
 *                                                                                *
 * The methods to be used can be switched on and off by means of booleans, or     *
 * via the prompt command, for example:                                           *
 *                                                                                *
 *    root -l ./TMVAClassification.C\(\"Fisher,Likelihood\"\)                     *
 *                                                                                *
 * (note that the backslashes are mandatory)                                      *
 * If no method given, a default set of classifiers is used.                      *
 *                                                                                *
 * The output file "TMVA.root" can be analysed with the use of dedicated          *
 * macros (simply say: root -l <macro.C>), which can be conveniently              *
 * invoked through a GUI that will appear at the end of the run of this macro.    *
 * Launch the GUI via the command:                                                *
 *                                                                                *
 *    root -l ./TMVAGui.C                                                         *
 *                                                                                *
 **********************************************************************************/

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"

// #include "TMVAGui.C"
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TMVA/TMVAGui.h"


#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif

using namespace TMVA;

TString outputNameS = "";
TString outputNameB = "";

// e.g. root -l -q 'TrainApr2017.cxx(6,1,"0","em","BDT7","0","0","true","true")'
// e.g. root -l -q 'TrainApr2017.cxx(6,2,"0","em","BDT7","0","0","true","true")'

// e.g. root -l -q 'TrainApr2017.cxx(7,1,"0","em","BDT7","0","0","true","true")'
// e.g. root -l -q 'TrainApr2017.cxx(7,2,"0","em","BDT7","0","0","true","true")'

void TrainApr2017( int whichBkg = 1, 
		   int whichSig = 1, 
		   TString nVariables = "1", 
		   TString channel = "em", 
		   TString myMethodList = "",
		   TString massPointA = "600", // mZ' (0 for all mass point together)
		   TString massPointB = "300", // mA0 or mChi (0 for all mass point together)
		   TString runLocal = "true",
		   TString applySignalWeights = "true"
		   ) {
  
  cout<<"myMethodList: "<<myMethodList<<endl;

  // The explicit loading of the shared libTMVA is done in TMVAlogon.C, defined in .rootrc
  // if you use your private .rootrc, or run from a different directory, please copy the
  // corresponding lines from .rootrc
  
  // methods to be processed can be given as an argument; use format:
  //
  // mylinux~> root -l TMVAClassification.C\(\"myMethod1,myMethod2,myMethod3\"\)
  //
  // if you like to use a method via the plugin mechanism, we recommend using
  //
  // mylinux~> root -l TMVAClassification.C\(\"P_myMethod\"\)
  // (an example is given for using the BDT as plugin (see below),
  // but of course the real application is when you write your own
  // method based)
  
  //Now  you know only channel 'em' and 'sf'
  if (channel != "em" && channel != "sf" && channel != "ll"){
    cout<<channel<<": I don't know this channel"<<endl;
    return;
  }

  //Put here the name you want for the output files
  if (whichSig == 1) outputNameS = "2HDM";
  if (whichSig == 2) outputNameS = "Zbar"; 

  if (whichBkg == 1) outputNameB = "ggZH";
  if (whichBkg == 2) outputNameB = "qqZH"; 
  if (whichBkg == 3) outputNameB = "ZH"; 
  if (whichBkg == 4) outputNameB = "Higgs"; 
  if (whichBkg == 5) outputNameB = "WW"; 
  if (whichBkg == 6) outputNameB = "TTbar"; 
  if (whichBkg == 7) outputNameB = "DY"; 

  // // massPoint can just be "high" or "low"
  // if (massPoint != "low" && massPoint != "high" && massPoint != "new" && massPoint != "superHigh"){
  //   cout<<"I don't know the massPoint "<<massPoint<<endl;
  //   return;
  // }  

  //---------------------------------------------------------------
  // This loads the library
  TMVA::Tools::Instance();
  
  // Default MVA methods to be trained + tested
  std::map<std::string,int> Use;
  
  // --- Cut optimisation
  Use["Cuts"]            = 1;
  Use["CutsD"]           = 1;
  Use["CutsPCA"]         = 0;
  Use["CutsGA"]          = 0;
  Use["CutsSA"]          = 0;
  // 
  // --- 1-dimensional likelihood ("naive Bayes estimator")
  Use["Likelihood"]      = 1;
  Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
  Use["LikelihoodPCA"]   = 1; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
  Use["LikelihoodKDE"]   = 0;
  Use["LikelihoodMIX"]   = 0;
  //
  // --- Mutidimensional likelihood and Nearest-Neighbour methods
  Use["PDERS"]           = 1;
  Use["PDERSD"]          = 0;
  Use["PDERSPCA"]        = 0;
  Use["PDEFoam"]         = 1;
  Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
  Use["KNN"]             = 1; // k-nearest neighbour method
  //
  // --- Linear Discriminant Analysis
  Use["LD"]              = 1; // Linear Discriminant identical to Fisher
  Use["Fisher"]          = 0;
  Use["FisherG"]         = 0;
  Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
  Use["HMatrix"]         = 0;
  //
  // --- Function Discriminant analysis
  Use["FDA_GA"]          = 1; // minimisation of user-defined function using Genetics Algorithm
  Use["FDA_SA"]          = 0;
  Use["FDA_MC"]          = 0;
  Use["FDA_MT"]          = 0;
  Use["FDA_GAMT"]        = 0;
  Use["FDA_MCMT"]        = 0;
  //
  // --- Neural Networks (all are feed-forward Multilayer Perceptrons)
  Use["MLP"]             = 1; // Recommended ANN
  Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
  Use["MLPBNN"]          = 1; // Recommended ANN with BFGS training method and bayesian regulator
  Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
  Use["TMlpANN"]         = 0; // ROOT's own ANN
  //
  // --- Support Vector Machine 
  Use["SVM"]             = 1;
  // 
  // --- Boosted Decision Trees
  Use["BDT"]             = 1; // uses Adaptive Boost
  Use["BDT2"]            = 1; // uses Adaptive Boost
  Use["BDT3"]            = 1; // uses Adaptive Boost
  Use["BDT4"]            = 1; // uses Adaptive Boost
  Use["BDT5"]            = 1; // uses Adaptive Boost
  Use["BDT6"]            = 1; // uses Adaptive Boost
  Use["BDT7"]            = 1; // uses Adaptive Boost
  Use["BDT8"]            = 1; // uses Adaptive Boost
  Use["BDT9"]            = 1; // uses Adaptive Boost
  Use["BDT10"]           = 1; // uses Adaptive Boost
  Use["BDT11"]           = 1; // uses Adaptive Boost
  Use["BDT12"]           = 1; // uses Adaptive Boost
  Use["BDT13"]           = 1; // uses Adaptive Boost
  Use["BDT14"]           = 1; // uses Adaptive Boost
  Use["BDT15"]           = 1; // uses Adaptive Boost
  Use["BDT16"]           = 1; // uses Adaptive Boost
  Use["BDTG"]            = 1; // uses Gradient Boost
  Use["BDTG2"]           = 1; // uses Gradient Boost
  Use["BDTG3"]           = 1; // uses Gradient Boost
  Use["BDTG4"]           = 1; // uses Gradient Boost
  Use["BDTG5"]           = 1; // uses Gradient Boost
  Use["BDTG6"]           = 1; // uses Gradient Boost
  Use["BDTG7"]           = 1; // uses Gradient Boost
  Use["BDTG8"]           = 1; // uses Gradient Boost
  Use["BDTG9"]           = 1; // uses Gradient Boost
  Use["BDTG10"]          = 1; // uses Gradient Boost
  Use["BDTG11"]          = 1; // uses Gradient Boost
  Use["BDTG12"]          = 1; // uses Gradient Boost
  Use["BDTG13"]          = 1; // uses Gradient Boost
  Use["BDTG14"]          = 1; // uses Gradient Boost
  Use["BDTG15"]          = 1; // uses Gradient Boost
  Use["BDTG16"]          = 1; // uses Gradient Boost
  Use["BDTG17"]          = 1; // uses Gradient Boost
  Use["BDTG18"]          = 1; // uses Gradient Boost
  Use["BDTG19"]          = 1; // uses Gradient Boost
  Use["BDTB"]            = 1; // uses Bagging
  Use["BDTB2"]           = 1; // uses Bagging
  Use["BDTB3"]           = 1; // uses Bagging
  Use["BDTB4"]           = 1; // uses Bagging
  Use["BDTB"]            = 1; // uses Bagging
  Use["BDTD"]            = 1; // decorrelation + Adaptive Boost
  Use["BDTF"]            = 1; // allow usage of fisher discriminant for node splitting 
  // 
  // --- Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
  Use["RuleFit"]         = 1;
  // ---------------------------------------------------------------
  
  std::cout << std::endl;
  std::cout << "==> Start TMVAClassification" << std::endl;
  
  // Select methods (don't look at this code - not of interest)
  if (myMethodList != "") {
    for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
    
    std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
    for (UInt_t i=0; i<mlist.size(); i++) {
      std::string regMethod(mlist[i]);
      
      if (Use.find(regMethod) == Use.end()) {
	std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
	for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
	std::cout << std::endl;
	return;
      }
      Use[regMethod] = 1;
    }
  }
  else { //---- deactivate all
    for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;
  }
  
  
  // --------------------------------------------------------------------------------------------------
  
  // --- Here the preparation phase begins
  
  // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
  TString thisFolder = "";
  thisFolder = "/afs/cern.ch/user/n/ntrevisa/work/CMSSW_8_0_26_patch1/src/MUCCA/Optimization/";

  TString outfileName = "";

  TString outputFolder = "";
  outputFolder = thisFolder + "rootFiles_" + outputNameS + "_" + outputNameB + "_" + nVariables + "var_" + channel + "_" + massPointA + "_" + massPointB;
  if (applySignalWeights == "false"){
    outputFolder = outputFolder + "_noWeights";
  }
  outputFolder = outputFolder + "/"; 

  TString mkdir = "";
  mkdir = "mkdir -p " + outputFolder;

  gSystem -> Exec(mkdir);

  if (myMethodList != "") {
    outfileName = outputFolder + "TMVA-" + outputNameS + "_" + outputNameB + "_" + nVariables + "var_" + channel + "_" + massPointA + "_" + massPointB + ".root";
    if (applySignalWeights == "false")
      outfileName = outputFolder + "TMVA-" + outputNameS + "_" + outputNameB + "_" + nVariables + "var_" + channel + "_" + massPointA + "_" + massPointB + "_noWeights.root";      
  }
  else {
    outfileName = outputFolder + "TMVA-" + outputNameS + "_" + outputNameB + "_" + nVariables + "var_" + channel + "_" + massPointA + "_" + massPointB + "-variables.root" ;
    if (applySignalWeights == "false")
      outfileName = outputFolder + "TMVA-" + outputNameS + "_" + outputNameB + "_" + nVariables + "var_" + channel + "_" + massPointA + "_" + massPointB + "-variables_noWeights.root" ;
  }
  
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
  
  // Create the factory object. Later you can choose the methods
  // whose performance you'd like to investigate. The factory is 
  // the only TMVA object you have to interact with
  //
  // The first argument is the base of the name of all the
  // weightfiles in the directory weight/
  //
  // The second argument is the output file for the training results
  // All TMVA output can be suppressed by removing the "!" (not) in
  // front of the "Silent" argument in the option string
  TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
					      "!V:!Silent:Color:DrawProgressBar:AnalysisType=Classification" );
  //                                              "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
  
  // If you wish to modify default settings
  // (please check "src/Config.h" to see all available global options)
  //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
  (TMVA::gConfig().GetIONames()).fWeightFileDir = thisFolder + "Weights-" + outputNameS + "_" + outputNameB + "_" + nVariables + "var_" + channel + "_" + massPointA + "_" + massPointB + "/"; 
  if (applySignalWeights == "false"){
  (TMVA::gConfig().GetIONames()).fWeightFileDir = thisFolder + "Weights-" + outputNameS + "_" + outputNameB + "_" + nVariables + "var_" + channel + "_" + massPointA + "_" + massPointB + "_noWeights/"; 
  }

  //"myWeightDirectory";
  
  // Define the input variables that shall be used for the MVA training
  // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
  // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]
  //  factory->AddVariable( "myvar1 := var1+var2", 'F' );
  //  factory->AddVariable( "myvar2 := var1-var2", "Expression 2", "", 'F' );
  //  factory->AddVariable( "var3",                "Variable 3", "units", 'F' );
  //  factory->AddVariable( "var4",                "Variable 4", "units", 'F' );
  

  //Variables ordered by power for BDTG4 - 2HDM

  //  if (whichSig == 1) {
    if (nVariables == "0" || nVariables == "1" || nVariables == "2" || nVariables == "3" || nVariables == "4" || nVariables == "5")
      factory->AddVariable( "mth",        'F' );
    if (nVariables == "0" || nVariables == "2" || nVariables == "3" || nVariables == "4" || nVariables == "5")
      factory->AddVariable( "mtw2", 'F' );
    if (nVariables == "0" || nVariables == "3" || nVariables == "4" || nVariables == "5")
      factory->AddVariable( "metTtrk",    'F' );
    if (nVariables == "0" || nVariables == "4" || nVariables == "5")
      factory->AddVariable( "drll",   'F' );
    if (nVariables == "0" || nVariables == "5")
      factory->AddVariable( "ptll", 'F' );
    if (nVariables == "0"){
      factory->AddVariable( "mpmet",      'F' );
      factory->AddVariable( "mtw1", 'F' );
      factory->AddVariable( "mll",  'F' );
      factory->AddVariable( "dphilmet",  'F' ); // ---- minimum among the two
      factory->AddVariable( "dphilmet1", 'F' );
      factory->AddVariable( "dphilmet2", 'F' );
      factory->AddVariable( "std_vector_lepton_pt[0]", 'F' );
      factory->AddVariable( "metPfType1", 'F' );
      factory->AddVariable( "dphill", 'F' );
      factory->AddVariable( "std_vector_lepton_pt[1]", 'F' );
      //factory->AddVariable( "njet", 'F' );
    }
    //  }

  //Variables ordered by power for BDTG4 - Z' baryonic

  // if (whichSig == 2) {
  //   if (nVariables == "0" || nVariables == "1" || nVariables == "2" || nVariables == "3" || nVariables == "4" || nVariables == "5")
  //     factory->AddVariable( "mth",        'F' );
  //   if (nVariables == "0" || nVariables == "2" || nVariables == "3" || nVariables == "4" || nVariables == "5")
  //     factory->AddVariable( "metTtrk",    'F' );
  //   if (nVariables == "0" || nVariables == "3" || nVariables == "4" || nVariables == "5")
  //     factory->AddVariable( "mtw2", 'F' );
  //   if (nVariables == "0" || nVariables == "4" || nVariables == "5")
  //     factory->AddVariable( "drll",   'F' );
  //   if (nVariables == "0" || nVariables == "5")
  //     factory->AddVariable( "ptll", 'F' );
  //   if (nVariables == "0"){
  //     factory->AddVariable( "mpmet",      'F' );
  //     factory->AddVariable( "mtw1", 'F' );
  //     factory->AddVariable( "mll",  'F' );
  //     factory->AddVariable( "dphilmet",  'F' ); // ---- minimum among the two
  //     factory->AddVariable( "dphilmet1", 'F' );
  //     factory->AddVariable( "dphilmet2", 'F' );
  //     factory->AddVariable( "std_vector_lepton_pt[0]", 'F' );
  //     factory->AddVariable( "metPfType1", 'F' );
  //     factory->AddVariable( "dphill", 'F' );
  //     factory->AddVariable( "std_vector_lepton_pt[1]", 'F' );
  //   }
  // }

  // You can add so-called "Spectator variables", which are not used in the MVA training,
  // but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the
  // input variables, the response values of all trained MVAs, and the spectator variables
  //  factory->AddSpectator( "spec1 := var1*2",  "Spectator 1", "units", 'F' );
  //  factory->AddSpectator( "spec2 := var1*3",  "Spectator 2", "units", 'F' );
  
  // Read training and test data
  // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
  //  TString fname = "./tmva_class_example.root";
  //    
  //  if (gSystem->AccessPathName( fname ))  // file does not exist in local directory
  //   gSystem->Exec("wget http://root.cern.ch/files/tmva_class_example.root");

    // Upper Folder
    TString upperFolderDF = "";
    TString upperFolderSF = "";
    if (runLocal == "true"){
      upperFolderDF = "/eos/user/n/ntrevisa/treesMUCCA/Full2016_Apr17/Apr2017_summer16/"; 
      upperFolderSF = "/eos/user/n/ntrevisa/treesMUCCA/Full2016_Apr17/Apr2017_summer16/"; 
    }

    // Input Folder for Different Flavour Channel
    TString inputFolderDF = "";
    inputFolderDF = upperFolderDF + "lepSel__MCWeights__bSFLpTEffMulti__cleanTauMC__l2loose__hadd__l2tightOR__LepTrgFix__formulasMC__wwSel__monohSel/";
    
    // Input Folder for Same Flavour Channel
    TString inputFolderSF = "";
    inputFolderSF = upperFolderSF + "lepSel__MCWeights__bSFLpTEffMulti__cleanTauMC__l2loose__hadd__l2tightOR__LepTrgFix__formulasMC__sfSel__monohSel/";
    
    TString fname;
  
    ////////////
    // Signal //
    ////////////
    
    // Signal files and trees declaration
    TFile *inputSA;
    TTree *signalA;
    
    TFile *inputSB;
    TTree *signalB;
    
    TFile *allInputsA[9];
    TTree *allSignalsA[9];
    
    TFile *allInputsB[9];
    TTree *allSignalsB[9];
    
    TFile *inputsAllA;
    TTree *signalsAllA;
    
    TFile *inputsAllB;
    TTree *signalsAllB;
    
    
  // 2HDM //
    
  if (whichSig == 1){

    if (massPointA == "0" && massPointB == "0"){

      // Different Flavour Channel
      fname = inputFolderDF + "latino_monoH_2HDM_MZp-600_MA0-300.root";
      allInputsA[0] = TFile::Open( fname );
      allSignalsA[0] = (TTree*) allInputsA[0]->Get("latino");

      fname = inputFolderDF + "latino_monoH_2HDM_MZp-800_MA0-300.root";
      allInputsA[1] = TFile::Open( fname );
      allSignalsA[1] = (TTree*) allInputsA[1]->Get("latino");
      
      fname = inputFolderDF + "latino_monoH_2HDM_MZp-1000_MA0-300.root";
      allInputsA[2] = TFile::Open( fname );
      allSignalsA[2] = (TTree*) allInputsA[2]->Get("latino");

      fname = inputFolderDF + "latino_monoH_2HDM_MZp-1200_MA0-300.root";
      allInputsA[3] = TFile::Open( fname );
      allSignalsA[3] = (TTree*) allInputsA[3]->Get("latino");

      fname = inputFolderDF + "latino_monoH_2HDM_MZp-1400_MA0-300.root";
      allInputsA[4] = TFile::Open( fname );
      allSignalsA[4] = (TTree*) allInputsA[4]->Get("latino");

      fname = inputFolderDF + "latino_monoH_2HDM_MZp-1700_MA0-300.root";
      allInputsA[5] = TFile::Open( fname );
      allSignalsA[5] = (TTree*) allInputsA[5]->Get("latino");

      fname = inputFolderDF + "latino_monoH_2HDM_MZp-2000_MA0-300.root";
      allInputsA[6] = TFile::Open( fname );
      allSignalsA[6] = (TTree*) allInputsA[6]->Get("latino");

      fname = inputFolderDF + "latino_monoH_2HDM_MZp-2500_MA0-300.root";
      allInputsA[7] = TFile::Open( fname );
      allSignalsA[7] = (TTree*) allInputsA[7]->Get("latino");

      fname = inputFolderDF + "latino_monoH_2HDM_All.root";
      inputsAllA = TFile::Open( fname );
      signalsAllA = (TTree*) inputsAllA->Get("latino");

      // Same Flavour Channel
      fname = inputFolderSF + "latino_monoH_2HDM_MZp-600_MA0-300.root";
      allInputsB[0] = TFile::Open( fname );
      allSignalsB[0] = (TTree*) allInputsB[0]->Get("latino");

      fname = inputFolderSF + "latino_monoH_2HDM_MZp-800_MA0-300.root";
      allInputsB[1] = TFile::Open( fname );
      allSignalsB[1] = (TTree*) allInputsB[1]->Get("latino");
      
      fname = inputFolderSF + "latino_monoH_2HDM_MZp-1000_MA0-300.root";
      allInputsB[2] = TFile::Open( fname );
      allSignalsB[2] = (TTree*) allInputsB[2]->Get("latino");

      fname = inputFolderSF + "latino_monoH_2HDM_MZp-1200_MA0-300.root";
      allInputsB[3] = TFile::Open( fname );
      allSignalsB[3] = (TTree*) allInputsB[3]->Get("latino");

      fname = inputFolderSF + "latino_monoH_2HDM_MZp-1400_MA0-300.root";
      allInputsB[4] = TFile::Open( fname );
      allSignalsB[4] = (TTree*) allInputsB[4]->Get("latino");

      fname = inputFolderSF + "latino_monoH_2HDM_MZp-1700_MA0-300.root";
      allInputsB[5] = TFile::Open( fname );
      allSignalsB[5] = (TTree*) allInputsB[5]->Get("latino");

      fname = inputFolderSF + "latino_monoH_2HDM_MZp-2000_MA0-300.root";
      allInputsB[6] = TFile::Open( fname );
      allSignalsB[6] = (TTree*) allInputsB[6]->Get("latino");

      fname = inputFolderSF + "latino_monoH_2HDM_MZp-2500_MA0-300.root";
      allInputsB[7] = TFile::Open( fname );
      allSignalsB[7] = (TTree*) allInputsB[7]->Get("latino");
    }

    else {
      // Different Flavour Channel
      fname = inputFolderDF + "latino_monoH_2HDM_MZp-" + massPointA + "_MA0-" + massPointB + ".root";
      inputSA = TFile::Open( fname );
      signalA = (TTree*) inputSA->Get("latino");
      
      // Same Flavour Channel
      fname = inputFolderSF + "latino_monoH_2HDM_MZp-" + massPointA + "_MA0-" + massPointB + ".root";
      inputSB = TFile::Open( fname );
      signalB = (TTree*) inputSB->Get("latino");
    }
  }

  // Z' Baryonic //

  if (whichSig == 2){

    if (massPointA == "0" && massPointB == "0"){

      // Different Flavour Channel
      fname = inputFolderDF + "latino_monoH_ZpBaryonic_MZp-10_MChi-1.root";
      allInputsA[0] = TFile::Open( fname );
      allSignalsA[0] = (TTree*) allInputsA[0]->Get("latino");

      fname = inputFolderDF + "latino_monoH_ZpBaryonic_MZp-20_MChi-1.root";
      allInputsA[1] = TFile::Open( fname );
      allSignalsA[1] = (TTree*) allInputsA[1]->Get("latino");
      
      fname = inputFolderDF + "latino_monoH_ZpBaryonic_MZp-50_MChi-1.root";
      allInputsA[2] = TFile::Open( fname );
      allSignalsA[2] = (TTree*) allInputsA[2]->Get("latino");

      fname = inputFolderDF + "latino_monoH_ZpBaryonic_MZp-100_MChi-1.root";
      allInputsA[3] = TFile::Open( fname );
      allSignalsA[3] = (TTree*) allInputsA[3]->Get("latino");

      fname = inputFolderDF + "latino_monoH_ZpBaryonic_MZp-200_MChi-1.root";
      allInputsA[4] = TFile::Open( fname );
      allSignalsA[4] = (TTree*) allInputsA[4]->Get("latino");

      fname = inputFolderDF + "latino_monoH_ZpBaryonic_MZp-300_MChi-1.root";
      allInputsA[5] = TFile::Open( fname );
      allSignalsA[5] = (TTree*) allInputsA[5]->Get("latino");

      fname = inputFolderDF + "latino_monoH_ZpBaryonic_MZp-500_MChi-1.root";
      allInputsA[6] = TFile::Open( fname );
      allSignalsA[6] = (TTree*) allInputsA[6]->Get("latino");

      fname = inputFolderDF + "latino_monoH_ZpBaryonic_MZp-1000_MChi-1.root";
      allInputsA[7] = TFile::Open( fname );
      allSignalsA[7] = (TTree*) allInputsA[7]->Get("latino");

      fname = inputFolderDF + "latino_monoH_ZpBaryonic_MZp-2000_MChi-1.root";
      allInputsA[8] = TFile::Open( fname );
      allSignalsA[8] = (TTree*) allInputsA[8]->Get("latino");

      fname = inputFolderDF + "latino_monoH_Zbar_All.root";
      inputsAllA = TFile::Open( fname );
      signalsAllA = (TTree*) inputsAllA->Get("latino");


      // Same Flavour Channel
      fname = inputFolderSF + "latino_monoH_ZpBaryonic_MZp-10_MChi-1.root";
      allInputsB[0] = TFile::Open( fname );
      allSignalsB[0] = (TTree*) allInputsB[0]->Get("latino");

      fname = inputFolderSF + "latino_monoH_ZpBaryonic_MZp-20_MChi-1.root";
      allInputsB[1] = TFile::Open( fname );
      allSignalsB[1] = (TTree*) allInputsB[1]->Get("latino");
      
      fname = inputFolderSF + "latino_monoH_ZpBaryonic_MZp-50_MChi-1.root";
      allInputsB[2] = TFile::Open( fname );
      allSignalsB[2] = (TTree*) allInputsB[2]->Get("latino");

      fname = inputFolderSF + "latino_monoH_ZpBaryonic_MZp-100_MChi-1.root";
      allInputsB[3] = TFile::Open( fname );
      allSignalsB[3] = (TTree*) allInputsB[3]->Get("latino");

      fname = inputFolderSF + "latino_monoH_ZpBaryonic_MZp-200_MChi-1.root";
      allInputsB[4] = TFile::Open( fname );
      allSignalsB[4] = (TTree*) allInputsB[4]->Get("latino");

      fname = inputFolderSF + "latino_monoH_ZpBaryonic_MZp-300_MChi-1.root";
      allInputsB[5] = TFile::Open( fname );
      allSignalsB[5] = (TTree*) allInputsB[5]->Get("latino");

      fname = inputFolderSF + "latino_monoH_ZpBaryonic_MZp-500_MChi-1.root";
      allInputsB[6] = TFile::Open( fname );
      allSignalsB[6] = (TTree*) allInputsB[6]->Get("latino");

      fname = inputFolderSF + "latino_monoH_ZpBaryonic_MZp-1000_MChi-1.root";
      allInputsB[7] = TFile::Open( fname );
      allSignalsB[7] = (TTree*) allInputsB[7]->Get("latino");

      fname = inputFolderSF + "latino_monoH_ZpBaryonic_MZp-2000_MChi-1.root";
      allInputsB[8] = TFile::Open( fname );
      allSignalsB[8] = (TTree*) allInputsB[8]->Get("latino");
    }

    else {
      // Different Flavour Channel
      fname = inputFolderDF + "latino_monoH_ZpBaryonic_MZp-" + massPointA + "_MChi-" + massPointB + ".root";
      cout<<"File name: "<<fname<<endl;
      inputSA = TFile::Open( fname );
      signalA = (TTree*) inputSA->Get("latino");
      
      // Same Flavour Channel
      fname = inputFolderSF + "latino_monoH_ZpBaryonic_MZp-" + massPointA + "_MChi-" + massPointB + ".root";
      cout<<"File name: "<<fname<<endl;
      inputSB = TFile::Open( fname );
      signalB = (TTree*) inputSB->Get("latino");
    }
  }

  /////////////////  
  // Backgrounds //
  /////////////////  
  
  // ggZH - background 1 //

  // Different Flavour Channel
  fname = inputFolderDF + "latino_GluGluZH_HToWWTo2L2Nu_M125.root";
  TFile *inputB1a = TFile::Open( fname );
  TTree *background1a = (TTree*) inputB1a->Get("latino");
  
  // Same Flavour Channel
  fname = inputFolderSF + "latino_GluGluZH_HToWWTo2L2Nu_M125.root";
  TFile *inputB1b = TFile::Open( fname );
  TTree *background1b = (TTree*) inputB1b->Get("latino");
  
  // qqZH - background 2 //

  // Different Flavour Channel
  fname = inputFolderDF + "latino_HZJ_HToWWTo2L2Nu_M125.root";
  TFile *inputB2a = TFile::Open( fname );
  TTree *background2a = (TTree*) inputB2a->Get("latino");
  
  // Same Flavour Channel
  fname = inputFolderSF + "latino_HZJ_HToWWTo2L2Nu_M125.root";
  TFile *inputB2b = TFile::Open( fname );
  TTree *background2b = (TTree*) inputB2b->Get("latino");
  
  // SM Higgs - background 3 //

  // Different Flavour Channel
  TChain *background3a = new TChain("latino");
  background3a->Add(inputFolderDF + "latino_GluGluHToWWTo2L2NuPowheg_M125.root");
  background3a->Add(inputFolderDF + "latino_VBFHToWWTo2L2Nu_alternative_M125.root");
  background3a->Add(inputFolderDF + "latino_HWminusJ_HToWW_M125.root");
  background3a->Add(inputFolderDF + "latino_HWplusJ_HToWW_M125.root");
  background3a->Add(inputFolderDF + "latino_bbHToWWTo2L2Nu_M125_yb2.root");
  background3a->Add(inputFolderDF + "latino_bbHToWWTo2L2Nu_M125_ybyt.root");
  background3a->Add(inputFolderDF + "latino_GluGluHToTauTau_M125.root");
  background3a->Add(inputFolderDF + "latino_VBFHToTauTau_M125.root");
  background3a->Add(inputFolderDF + "latino_HZJ_HToTauTau_M125.root");
  background3a->Add(inputFolderDF + "latino_HWplusJ_HToTauTau_M125.root");
  background3a->Add(inputFolderDF + "latino_HWminusJ_HToTauTau_M125.root");
  
  // Same Flavour Channel
  TChain *background3b = new TChain("latino");
  background3b->Add(inputFolderSF + "latino_GluGluHToWWTo2L2NuPowheg_M125.root");
  background3b->Add(inputFolderSF + "latino_VBFHToWWTo2L2Nu_alternative_M125.root");
  background3b->Add(inputFolderSF + "latino_HWminusJ_HToWW_M125.root");
  background3b->Add(inputFolderSF + "latino_HWplusJ_HToWW_M125.root");
  background3b->Add(inputFolderSF + "latino_bbHToWWTo2L2Nu_M125_yb2.root");
  background3b->Add(inputFolderSF + "latino_bbHToWWTo2L2Nu_M125_ybyt.root");
  background3b->Add(inputFolderSF + "latino_GluGluHToTauTau_M125.root");
  background3b->Add(inputFolderSF + "latino_VBFHToTauTau_M125.root");
  background3b->Add(inputFolderSF + "latino_HZJ_HToTauTau_M125.root");
  background3b->Add(inputFolderSF + "latino_HWplusJ_HToTauTau_M125.root");
  background3b->Add(inputFolderSF + "latino_HWminusJ_HToTauTau_M125.root");
  
  // WW - background 4 //

  // Different Flavour Channel
  TChain *background4a = new TChain("latino");
  background4a->Add(inputFolderDF + "latino_WWTo2L2Nu.root");
  background4a->Add(inputFolderDF + "latino_GluGluWWTo2L2Nu_MCFM.root");
  
  // Same Flavour Channel
  TChain *background4b = new TChain("latino");
  background4b->Add(inputFolderSF + "latino_WWTo2L2Nu.root");
  background4b->Add(inputFolderSF + "latino_GluGluWWTo2L2Nu_MCFM.root");
  
  // Top - background 5 //

  // Different Flavour Channel
  TChain *background5a = new TChain("latino");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part0.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part1.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part2.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part3.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part4.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part5.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part6.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part7.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part8.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part9.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part10.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part11.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part12.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part13.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part14.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part15.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part16.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part17.root");
  background5a->Add(inputFolderDF + "latino_TTTo2L2Nu__part18.root");
  background5a->Add(inputFolderDF + "latino_ST_tW_antitop.root");
  background5a->Add(inputFolderDF + "latino_ST_tW_top.root");
  
  // Same Flavour Channel
  TChain *background5b = new TChain("latino");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part0.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part1.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part2.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part3.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part4.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part5.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part6.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part7.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part8.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part9.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part10.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part11.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part12.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part13.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part14.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part15.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part16.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part17.root");
  background5b->Add(inputFolderSF + "latino_TTTo2L2Nu__part18.root");
  background5b->Add(inputFolderSF + "latino_ST_tW_antitop.root");
  background5b->Add(inputFolderSF + "latino_ST_tW_top.root");

  
  // DY - background 6 //

  // Different Flavour Channel
  TChain *background6a = new TChain("latino");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-10to50.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part0.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part1.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part2.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part3.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part4.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part5.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part6.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part7.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part8.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part9.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part10.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part11.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part12.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part13.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part14.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part15.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part16.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part17.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part18.root");
  background6a->Add(inputFolderDF + "latino_DYJetsToLL_M-50__part19.root");


  // Same Flavour Channel
  TChain *background6b = new TChain("latino");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-10to50.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part0.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part1.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part2.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part3.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part4.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part5.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part6.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part7.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part8.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part9.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part10.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part11.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part12.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part13.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part14.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part15.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part16.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part17.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part18.root");
  background6b->Add(inputFolderSF + "latino_DYJetsToLL_M-50__part19.root");

  cout<<"Hola"<<endl;

  // --- Register the training and test trees
  
  // global event weights per tree (see below for setting event-wise weights)
  Double_t signalWeight     = 1.0;
  Double_t backgroundWeight = 1.0;

  // You can add an arbitrary number of signal or background trees
  if (channel == "em" || channel == "ll"){
    if (applySignalWeights == "true"){
      if (massPointA == "0" && massPointB == "0")
	if (whichSig == 1){
	  factory->AddSignalTree(allSignalsA[0], 1. / 16.5956);  // 1. / events
	  factory->AddSignalTree(allSignalsA[1], 1. / 12.6303);  // 1. / events
	  factory->AddSignalTree(allSignalsA[2], 1. / 6.25251);  // 1. / events
	  factory->AddSignalTree(allSignalsA[3], 1. / 3.02949);  // 1. / events
	  factory->AddSignalTree(allSignalsA[4], 1. / 1.44171);  // 1. / events
	  factory->AddSignalTree(allSignalsA[5], 1. / 0.516394); // 1. / events
	  factory->AddSignalTree(allSignalsA[6], 1. / 0.203947); // 1. / events
	  factory->AddSignalTree(allSignalsA[7], 1. / 0.050828); // 1. / events
	}
	else if (whichSig == 2){
	  factory->AddSignalTree(allSignalsA[0], 1. / 54.5653);  // 1. / events
	  factory->AddSignalTree(allSignalsA[1], 1. / 52.1725);  // 1. / events
	  factory->AddSignalTree(allSignalsA[2], 1. / 60.0030);  // 1. / events
	  factory->AddSignalTree(allSignalsA[3], 1. / 61.2326);  // 1. / events
	  factory->AddSignalTree(allSignalsA[4], 1. / 52.4396);  // 1. / events
	  factory->AddSignalTree(allSignalsA[5], 1. / 48.5594);  // 1. / events
	  factory->AddSignalTree(allSignalsA[6], 1. / 29.7216);  // 1. / events
	  factory->AddSignalTree(allSignalsA[7], 1. / 6.66016);  // 1. / events
	  factory->AddSignalTree(allSignalsA[8], 1. / 0.507575); // 1. / events
	}
	else
	  factory->AddSignalTree( signalA, signalWeight );
    }
    else if (applySignalWeights == "false"){
      if (massPointA == "0" && massPointB == "0")
      	if (whichSig == 1){
      	  factory->AddSignalTree(signalsAllA, 1.);
      	}				
      	else if (whichSig == 2){	      
      	  factory->AddSignalTree(signalsAllA, 1.);
      	}
      	else
      	  factory->AddSignalTree( signalA, 1. );
    }
    
    if (whichBkg == 1 || whichBkg == 3 || whichBkg == 4 || whichBkg == 5 || whichBkg == 6 || whichBkg == 7)
      factory->AddBackgroundTree( background1a, backgroundWeight );
    if (whichBkg == 2 || whichBkg == 3 || whichBkg == 4 || whichBkg == 5 || whichBkg == 6 || whichBkg == 7)
      factory->AddBackgroundTree( background2a, backgroundWeight );
    if (whichBkg == 4 || whichBkg == 5 || whichBkg == 6 || whichBkg == 7)  
      factory->AddBackgroundTree( background3a, backgroundWeight );
    if (whichBkg == 5 || whichBkg == 6 || whichBkg == 7)  
      factory->AddBackgroundTree( background4a, backgroundWeight );
    if (whichBkg == 6 || whichBkg == 7)  
      factory->AddBackgroundTree( background5a, backgroundWeight );
    if  (whichBkg == 7)
      factory->AddBackgroundTree( background6a, backgroundWeight );
  }

  // SF //

  if (channel == "sf" || channel == "ll"){
    if (applySignalWeights == "true"){
      if (massPointA == "0" && massPointB == "0")
	if (whichSig == 1){
	  factory->AddSignalTree(allSignalsB[0], 1. / 16.5956);  // 1. / events
	  factory->AddSignalTree(allSignalsB[1], 1. / 12.6303);  // 1. / events
	  factory->AddSignalTree(allSignalsB[2], 1. / 6.25251);  // 1. / events
	  factory->AddSignalTree(allSignalsB[3], 1. / 3.02949);  // 1. / events
	  factory->AddSignalTree(allSignalsB[4], 1. / 1.44171);  // 1. / events
	  factory->AddSignalTree(allSignalsB[5], 1. / 0.516394); // 1. / events
	  factory->AddSignalTree(allSignalsB[6], 1. / 0.203947); // 1. / events
	  factory->AddSignalTree(allSignalsB[7], 1. / 0.050828); // 1. / events
	}
	else if (whichSig == 2){
	  factory->AddSignalTree(allSignalsB[0], 1. / 54.5653);  // 1. / events
	  factory->AddSignalTree(allSignalsB[1], 1. / 52.1725);  // 1. / events
	  factory->AddSignalTree(allSignalsB[2], 1. / 60.0030);  // 1. / events
	  factory->AddSignalTree(allSignalsB[3], 1. / 61.2326);  // 1. / events
	  factory->AddSignalTree(allSignalsB[4], 1. / 52.4396);  // 1. / events
	  factory->AddSignalTree(allSignalsB[5], 1. / 48.5594);  // 1. / events
	  factory->AddSignalTree(allSignalsB[6], 1. / 29.7216);  // 1. / events
	  factory->AddSignalTree(allSignalsB[7], 1. / 6.66016);  // 1. / events
	  factory->AddSignalTree(allSignalsB[8], 1. / 0.507575); // 1. / events
	}
	else
	  factory->AddSignalTree( signalB, signalWeight );
    }
    else if (applySignalWeights == "false"){
      if (massPointA == "0" && massPointB == "0")
      	if (whichSig == 1){
      	  factory->AddSignalTree(signalsAllB, 1.);
      	}				
      	else if (whichSig == 2){	      
      	  factory->AddSignalTree(signalsAllB, 1.);
      	}
      	else
      	  factory->AddSignalTree( signalB, 1. );
    }
    
    if (whichBkg == 1 || whichBkg == 3 || whichBkg == 4 || whichBkg == 5 || whichBkg == 6 || whichBkg == 7)
      factory->AddBackgroundTree( background1b, backgroundWeight );
    if (whichBkg == 2 || whichBkg == 3 || whichBkg == 4 || whichBkg == 5 || whichBkg == 6 || whichBkg == 7)
      factory->AddBackgroundTree( background2b, backgroundWeight );
    if (whichBkg == 4 || whichBkg == 5 || whichBkg == 6 || whichBkg == 7)  
      factory->AddBackgroundTree( background3b, backgroundWeight );
    if (whichBkg == 5 || whichBkg == 6 || whichBkg == 7)  
      factory->AddBackgroundTree( background4b, backgroundWeight );
    if (whichBkg == 6 || whichBkg == 7)  
      factory->AddBackgroundTree( background5b, backgroundWeight );
    if  (whichBkg == 7)
      factory->AddBackgroundTree( background6b, backgroundWeight );
  }
  
  //---- global weight
  // XSWeight      = 'baseW*GEN_weight_SM/abs(GEN_weight_SM)'
  // SFweight      = 'puW*bPogSF_CMVAL*effTrigW*std_vector_lepton_idisoWcut_WP_Tight80X[0]*std_vector_lepton_idisoWcut_WP_Tight80X[1]*veto_EMTFBug'
  // GenLepMatch   = 'std_vector_lepton_genmatched[0]*std_vector_lepton_genmatched[1]'

  // METFilter_Common = '(std_vector_trigger_special[0]*std_vector_trigger_special[1]*std_vector_trigger_special[2]*std_vector_trigger_special[3]*std_vector_trigger_special[5])'
  // METFilter_DATA   =  METFilter_Common + '*' + '(std_vector_trigger_special[4]*!std_vector_trigger_special[6]*!std_vector_trigger_special[7]*std_vector_trigger_special[8]*std_vector_trigger_special[9])'
  // METFilter_MCver  =  '(std_vector_trigger_special[8]==-2.)'
  // METFilter_MCOld  =  '(std_vector_trigger_special[6]*std_vector_trigger_special[7])'
  // METFilter_MCNew  =  '(std_vector_trigger_special[8]*std_vector_trigger_special[9])'

  // METFilter_MC  =  METFilter_Common + '*' + '(('+METFilter_MCver+'*'+METFilter_MCOld+')||(!'+METFilter_MCver+'*'+METFilter_MCNew+'))'

  if (applySignalWeights == "true")
    factory->SetSignalWeightExpression("baseW*SFweight2l*GenLepMatch2l*LepCut2l__ele_cut_WP_Tight80X__mu_cut_Tight80x*LepSF2l__ele_cut_WP_Tight80X__mu_cut_Tight80x*METFilter_MC");
  else if (applySignalWeights == "false")
    factory->SetSignalWeightExpression("SFweight2l*GenLepMatch2l*LepCut2l__ele_cut_WP_Tight80X__mu_cut_Tight80x*LepSF2l__ele_cut_WP_Tight80X__mu_cut_Tight80x*METFilter_MC");
  
  factory->SetBackgroundWeightExpression("baseW*SFweight2l*GenLepMatch2l*LepCut2l__ele_cut_WP_Tight80X__mu_cut_Tight80x*LepSF2l__ele_cut_WP_Tight80X__mu_cut_Tight80x*METFilter_MC");

  // --- end of tree registration 
  
  // Set individual event weights (the variables must exist in the original TTree)
  //    for signal    : factory->SetSignalWeightExpression    ("weight1*weight2");
  //    for background: factory->SetBackgroundWeightExpression("weight1*weight2");
  //    factory->SetBackgroundWeightExpression( "weight" );
  
  // Apply additional cuts on the signal and background samples (can be different)
  //  TCut mycuts = "ch1*ch2<0 && pt2>20 && mpmet>20 && pfmet>20 && mll>12 && nextra==0"; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
  //  TCut mycutb = "ch1*ch2<0 && pt2>20 && mpmet>20 && pfmet>20 && mll>12 && nextra==0"; // for example: TCut mycutb = "abs(var1)<0.5";
  
  TCut mycuts = "";

  if (channel == "em"){
    mycuts = "std_vector_lepton_pt[0]>25 && std_vector_lepton_pt[1]>20 \
            && (std_vector_lepton_flavour[0] * std_vector_lepton_flavour[1] == -11*13) \
            && std_vector_lepton_pt[2]<10 \
            && mll>12 \
            && metPfType1 > 20 \
            && mpmet > 20 \
            && ptll > 30 \
            && mll < 76   \
            && drll < 2.5 \
            && njet >= 0";
  }
  else if (channel == "ll"){
    mycuts = "std_vector_lepton_pt[0]>25 && std_vector_lepton_pt[1]>20 \
            && std_vector_lepton_pt[2]<10 \
            && (std_vector_lepton_flavour[0] * std_vector_lepton_flavour[1] == -11*13 || std_vector_lepton_flavour[0] * std_vector_lepton_flavour[1] == -11*11 || std_vector_lepton_flavour[0] * std_vector_lepton_flavour[1] == -13*13) \
            && mll>12 \
            && metPfType1 > 20 \
            && mpmet > 20 \
            && ptll > 30 \
            && mll < 76   \
            && drll < 2.5 \
            && njet >= 0";
  }
  else if (channel == "sf"){
    mycuts = "std_vector_lepton_pt[0]>25 && std_vector_lepton_pt[1]>20 \
            && std_vector_lepton_pt[2]<10 \
            && ((std_vector_lepton_flavour[0] * std_vector_lepton_flavour[1] == -11*11) || (std_vector_lepton_flavour[0] * std_vector_lepton_flavour[1] == -13*13)) \
            && mll>12 \
            && metPfType1 > 20 \
            && mpmet > 45 \
            && ptll > 45 \
            && mll < 76   \
            && drll < 2.5 \
            && njet >= 0";
  }
  else{
    cout<<channel<<": I do not know this channel"<<endl;
    return;
  }

  TCut mycutb = mycuts;
  
  
  // Tell the factory how to use the training and testing events
  //
  // If no numbers of events are given, half of the events in the tree are used 
  // for training, and the other half for testing:
  //    factory->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
  // To also specify the number of testing events, use:
  //    factory->PrepareTrainingAndTestTree( mycut,
  //                                         "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" );
  //  factory->PrepareTrainingAndTestTree( mycuts, mycutb,  "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );
  factory->PrepareTrainingAndTestTree( mycuts, mycuts, "SplitMode=Random:NormMode=NumEvents:!V");
  // if (applySignalWeights == "false")
  //   factory->PrepareTrainingAndTestTree(mycuts,"nTrain_Signal=6000:nTrain_Background=0:nTest_Signal=6000:nTest_Background=0:SplitMode=Random::NormMode=NumEvents:!V");

  // ---- Book MVA methods
  // Please lookup the various method configuration options in the corresponding cxx files, eg:
  // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
  // it is possible to preset ranges in the option string in which the cut optimisation should be done:
  // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable
  
  // Cut optimisation
  if (Use["Cuts"])
    factory->BookMethod( TMVA::Types::kCuts, "Cuts",
			 "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );
  
  if (Use["CutsD"])
    factory->BookMethod( TMVA::Types::kCuts, "CutsD",
			 "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate" );
  
  if (Use["CutsPCA"])
    factory->BookMethod( TMVA::Types::kCuts, "CutsPCA",
			 "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA" );
  
  if (Use["CutsGA"])
    factory->BookMethod( TMVA::Types::kCuts, "CutsGA",
			 "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" );
  
  if (Use["CutsSA"])
    factory->BookMethod( TMVA::Types::kCuts, "CutsSA",
			 "!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );
  
  // Likelihood ("naive Bayes estimator")
  if (Use["Likelihood"])
    factory->BookMethod( TMVA::Types::kLikelihood, "Likelihood",
			 "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );
  
  // Decorrelated likelihood
  if (Use["LikelihoodD"])
    factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodD",
			 "!H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" );
  
  // PCA-transformed likelihood
  if (Use["LikelihoodPCA"])
    factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodPCA",
			 "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA" ); 
  
  // Use a kernel density estimator to approximate the PDFs
  if (Use["LikelihoodKDE"])
    factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodKDE",
			 "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50" ); 

  // Use a variable-dependent mix of splines and kernel density estimator
  if (Use["LikelihoodMIX"])
    factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodMIX",
			 "!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=Spline2:PDFInterpolBkg[2]=Spline2:PDFInterpolSig[3]=Spline2:PDFInterpolBkg[3]=Spline2:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=50" ); 
  
  // Test the multi-dimensional probability density estimator
  // here are the options strings for the MinMax and RMS methods, respectively:
  //      "!H:!V:VolumeRangeMode=MinMax:DeltaFrac=0.2:KernelEstimator=Gauss:GaussSigma=0.3" );
  //      "!H:!V:VolumeRangeMode=RMS:DeltaFrac=3:KernelEstimator=Gauss:GaussSigma=0.3" );
  if (Use["PDERS"])
    factory->BookMethod( TMVA::Types::kPDERS, "PDERS",
			 "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" );
  
  if (Use["PDERSD"])
    factory->BookMethod( TMVA::Types::kPDERS, "PDERSD",
			 "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=Decorrelate" );
  
  if (Use["PDERSPCA"])
    factory->BookMethod( TMVA::Types::kPDERS, "PDERSPCA",
			 "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=PCA" );
  
  // Multi-dimensional likelihood estimator using self-adapting phase-space binning
  if (Use["PDEFoam"])
    factory->BookMethod( TMVA::Types::kPDEFoam, "PDEFoam",
			 "!H:!V:SigBgSeparate=F:TailCut=0.001:VolFrac=0.0666:nActiveCells=500:nSampl=2000:nBin=5:Nmin=100:Kernel=None:Compress=T" );
  
  if (Use["PDEFoamBoost"])
    factory->BookMethod( TMVA::Types::kPDEFoam, "PDEFoamBoost",
			 "!H:!V:Boost_Num=30:Boost_Transform=linear:SigBgSeparate=F:MaxDepth=4:UseYesNoCell=T:DTLogic=MisClassificationError:FillFoamWithOrigWeights=F:TailCut=0:nActiveCells=500:nBin=20:Nmin=400:Kernel=None:Compress=T" );
  
  // K-Nearest Neighbour classifier (KNN)
  if (Use["KNN"])
    factory->BookMethod( TMVA::Types::kKNN, "KNN",
			 "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );
  
  // H-Matrix (chi2-squared) method
  if (Use["HMatrix"])
    factory->BookMethod( TMVA::Types::kHMatrix, "HMatrix", "!H:!V:VarTransform=None" );
  
  // Linear discriminant (same as Fisher discriminant)
  if (Use["LD"])
    factory->BookMethod( TMVA::Types::kLD, "LD", "H:!V:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );
  
  // Fisher discriminant (same as LD)
  if (Use["Fisher"])
    factory->BookMethod( TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );
  
  // Fisher with Gauss-transformed input variables
  if (Use["FisherG"])
    factory->BookMethod( TMVA::Types::kFisher, "FisherG", "H:!V:VarTransform=Gauss" );
  
  // Composite classifier: ensemble (tree) of boosted Fisher classifiers
  if (Use["BoostedFisher"])
    factory->BookMethod( TMVA::Types::kFisher, "BoostedFisher", 
			 "H:!V:Boost_Num=20:Boost_Transform=log:Boost_Type=AdaBoost:Boost_AdaBoostBeta=0.2:!Boost_DetailedMonitoring" );
  
  // Function discrimination analysis (FDA) -- test of various fitters - the recommended one is Minuit (or GA or SA)
  if (Use["FDA_MC"])
    factory->BookMethod( TMVA::Types::kFDA, "FDA_MC",
			 "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:SampleSize=100000:Sigma=0.1" );
  
  if (Use["FDA_GA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
    factory->BookMethod( TMVA::Types::kFDA, "FDA_GA",
			 "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=300:Cycles=3:Steps=20:Trim=True:SaveBestGen=1" );
  
  if (Use["FDA_SA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
    factory->BookMethod( TMVA::Types::kFDA, "FDA_SA",
			 "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=SA:MaxCalls=15000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );
  
  if (Use["FDA_MT"])
    factory->BookMethod( TMVA::Types::kFDA, "FDA_MT",
			 "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=2:UseImprove:UseMinos:SetBatch" );
  
  if (Use["FDA_GAMT"])
    factory->BookMethod( TMVA::Types::kFDA, "FDA_GAMT",
			 "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:Cycles=1:PopSize=5:Steps=5:Trim" );
  
  if (Use["FDA_MCMT"])
    factory->BookMethod( TMVA::Types::kFDA, "FDA_MCMT",
			 "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:SampleSize=20" );
  
  // TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
  if (Use["MLP"])
    factory->BookMethod( TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" );
  
  if (Use["MLPBFGS"])
    factory->BookMethod( TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:!UseRegulator" );
  
  if (Use["MLPBNN"])
    factory->BookMethod( TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator" ); // BFGS training with bayesian regulators
  
  // CF(Clermont-Ferrand)ANN
  if (Use["CFMlpANN"])
    factory->BookMethod( TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=2000:HiddenLayers=N+1,N"  ); // n_cycles:#nodes:#nodes:...  
  
  // Tmlp(Root)ANN
  if (Use["TMlpANN"])
    factory->BookMethod( TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"  ); // n_cycles:#nodes:#nodes:...
  
  // Support Vector Machine
  if (Use["SVM"])
    factory->BookMethod( TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm" );
  
  // Boosted Decision Trees

  // Reference
  if (Use["BDTG4"]) // Gradient Boost - Reference
    factory->BookMethod( TMVA::Types::kBDT, "BDTG4",
			 "!H:!V:NTrees=500:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=500:MaxDepth=2" );

  // Changing NTrees
  if (Use["BDTG"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG",
			 "!H:!V:NTrees=250:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=500:MaxDepth=2" );

  if (Use["BDTG2"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG2",
			 "!H:!V:NTrees=1000:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=500:MaxDepth=2" );

  if (Use["BDTG3"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG3",
			 "!H:!V:NTrees=2000:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=500:MaxDepth=2" );  

  // Changing MinNodeSize
  if (Use["BDTG5"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG5",
			 "!H:!V:NTrees=500:MinNodeSize=0.5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=500:MaxDepth=2" );

  if (Use["BDTG6"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG6",
			 "!H:!V:NTrees=500:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=500:MaxDepth=2" );

  if (Use["BDTG7"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG7",
			 "!H:!V:NTrees=500:MinNodeSize=5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=500:MaxDepth=2" );  

  // Changing Shrinkage
  if (Use["BDTG8"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG8",
			 "!H:!V:NTrees=500:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.1:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=500:MaxDepth=2" );

  if (Use["BDTG9"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG9",
			 "!H:!V:NTrees=500:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.2:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=500:MaxDepth=2" );

  if (Use["BDTG10"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG10",
			 "!H:!V:NTrees=500:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.5:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=500:MaxDepth=2" );  

  // Changing GradBaggingFraction
  if (Use["BDTG11"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG11",
			 "!H:!V:NTrees=500:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:GradBaggingFraction=0.25:nCuts=500:MaxDepth=2" );

  if (Use["BDTG12"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG12",
			 "!H:!V:NTrees=500:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:GradBaggingFraction=0.75:nCuts=500:MaxDepth=2" );

  if (Use["BDTG13"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG13",
			 "!H:!V:NTrees=500:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:GradBaggingFraction=1:nCuts=500:MaxDepth=2" );  

  // Changing nCuts
  if (Use["BDTG14"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG14",
			 "!H:!V:NTrees=500:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=100:MaxDepth=2" );

  if (Use["BDTG15"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG15",
			 "!H:!V:NTrees=500:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=1000:MaxDepth=2" );

  if (Use["BDTG16"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG16",
			 "!H:!V:NTrees=500:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=10000:MaxDepth=2" );  

  // Changing MaxDepth
  if (Use["BDTG17"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG17",
			 "!H:!V:NTrees=500:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=500:MaxDepth=3" );

  if (Use["BDTG18"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG18",
			 "!H:!V:NTrees=500:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=500:MaxDepth=4" );

  if (Use["BDTG19"]) // Gradient Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTG19",
			 "!H:!V:NTrees=500:MinNodeSize=1.5%:BoostType=Grad:Shrinkage=0.05:UseBaggedBoost:GradBaggingFraction=0.5:nCuts=500:MaxDepth=5" );  

  //-----------------------------------------------------------------------------------------------------------------------------------------------

  // Adaptive Boost

  // Reference
  if (Use["BDT4"])  // Adaptive Boost - Reference
    factory->BookMethod( TMVA::Types::kBDT, "BDT4",
			 "!H:!V:NTrees=500:MinNodeSize=0.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=500" );
  
  // Changing NTrees
  if (Use["BDT"])  // Adaptive Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDT",
			 "!H:!V:NTrees=250:MinNodeSize=0.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=500" );
  
  if (Use["BDT2"])  // Adaptive Boost - Reference
    factory->BookMethod( TMVA::Types::kBDT, "BDT2",
			 "!H:!V:NTrees=1000:MinNodeSize=0.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=500" );
  
  if (Use["BDT3"])  // Adaptive Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDT3",
			 "!H:!V:NTrees=2000:MinNodeSize=0.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=500" );
  
  // Changing MinNodeSize
  if (Use["BDT5"])  // Adaptive Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDT5",
			 "!H:!V:NTrees=500:MinNodeSize=0.25%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=500" );
  
  if (Use["BDT6"])  // Adaptive Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDT6",
			 "!H:!V:NTrees=500:MinNodeSize=2.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=500" );
  
  if (Use["BDT7"])  // Adaptive Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDT7",
			 "!H:!V:NTrees=500:MinNodeSize=5.0%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=500" );
  
  // Changing MaxDepth
  if (Use["BDT8"])  // Adaptive Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDT8",
			 "!H:!V:NTrees=500:MinNodeSize=0.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=500" );
  
  if (Use["BDT9"])  // Adaptive Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDT9",
			 "!H:!V:NTrees=500:MinNodeSize=0.5%:MaxDepth=4:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=500" );
  
  if (Use["BDT10"])  // Adaptive Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDT10",
			 "!H:!V:NTrees=500:MinNodeSize=0.5%:MaxDepth=5:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=500" );
  
  // Changing AdaBoostBeta
  if (Use["BDT11"])  // Adaptive Boost - Reference
    factory->BookMethod( TMVA::Types::kBDT, "BDT11",
			 "!H:!V:NTrees=500:MinNodeSize=0.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=500" );
  
  if (Use["BDT12"])  // Adaptive Boost - Reference
    factory->BookMethod( TMVA::Types::kBDT, "BDT12",
			 "!H:!V:NTrees=500:MinNodeSize=0.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.2:SeparationType=GiniIndex:nCuts=500" );
  
  if (Use["BDT13"])  // Adaptive Boost - Reference
    factory->BookMethod( TMVA::Types::kBDT, "BDT13",
			 "!H:!V:NTrees=500:MinNodeSize=0.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.8:SeparationType=GiniIndex:nCuts=500" );

  // Changing nCuts
  if (Use["BDT14"])  // Adaptive Boost - Reference
    factory->BookMethod( TMVA::Types::kBDT, "BDT14",
			 "!H:!V:NTrees=500:MinNodeSize=0.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=100" );

  if (Use["BDT15"])  // Adaptive Boost - Reference
    factory->BookMethod( TMVA::Types::kBDT, "BDT15",
			 "!H:!V:NTrees=500:MinNodeSize=0.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=1000" );

  if (Use["BDT16"])  // Adaptive Boost - Reference
    factory->BookMethod( TMVA::Types::kBDT, "BDT16",
			 "!H:!V:NTrees=500:MinNodeSize=0.5%:MaxDepth=2:BoostType=AdaBoost:AdaBoostBeta=0.1:SeparationType=GiniIndex:nCuts=10000" );

  //-----------------------------------------------------------------------------------------------------------------------------------------------
  

  if (Use["BDTB"]) // Bagging
    factory->BookMethod( TMVA::Types::kBDT, "BDTB",
			 "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20" );
  
  if (Use["BDTB2"]) // Bagging
    factory->BookMethod( TMVA::Types::kBDT, "BDTB2",
			 "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=10" );
  
  if (Use["BDTB3"]) // Bagging
    factory->BookMethod( TMVA::Types::kBDT, "BDTB3",
			 "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=30" );
  
  if (Use["BDTB4"]) // Bagging
    factory->BookMethod( TMVA::Types::kBDT, "BDTB4",
			 "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=40" );
  
  if (Use["BDTD"]) // Decorrelation + Adaptive Boost
    factory->BookMethod( TMVA::Types::kBDT, "BDTD",
			 "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate" );
  
  if (Use["BDTF"])  // Allow Using Fisher discriminant in node splitting for (strong) linearly correlated variables
    factory->BookMethod( TMVA::Types::kBDT, "BDTMitFisher",
			 "!H:!V:NTrees=50:MinNodeSize=2.5%:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20" );
  
  // RuleFit -- TMVA implementation of Friedman's method
  if (Use["RuleFit"])
    factory->BookMethod( TMVA::Types::kRuleFit, "RuleFit",
			 "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02" );
  
  // For an example of the category classifier usage, see: TMVAClassificationCategory
  
  // --------------------------------------------------------------------------------------------------
  
  // ---- Now you can optimize the setting (configuration) of the MVAs using the set of training events
  
  // factory->OptimizeAllMethods("SigEffAt001","Scan");
  // factory->OptimizeAllMethods("ROCIntegral","FitGA");
  
  // --------------------------------------------------------------------------------------------------
  
  // ---- Now you can tell the factory to train, test, and evaluate the MVAs
  
  // Train MVAs using the set of training events
  factory->TrainAllMethods();
  
  // ---- Evaluate all MVAs using the set of test events
  factory->TestAllMethods();
  
  // ----- Evaluate and compare performance of all configured MVAs
  factory->EvaluateAllMethods();
  
  // ---- plot also spectators
  //  factory->EvaluateAllVariables();  ----> NOT supported anymore!
  
  // --------------------------------------------------------------
  
  // Save the output
  outputFile->Close();
  
  // std::string toDo;
  // toDo = "rm -r Weights-" + outputNameS + "_" + outputNameB + "_" + nVariables + "var/";
  // std::cerr << "toDo = " << toDo << std::endl;
  // system (toDo.c_str()); 
  
  // toDo = "mv weights Weights-" + outputNameS + "_" + outputNameB + "_" + nVariables + "var/";
  // std::cerr << "toDo = " << toDo << std::endl;
  // system (toDo.c_str()); 
  
  
  
  std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
  std::cout << "==> TMVAClassification is done!" << std::endl;
  
  delete factory;
  
  // Launch the GUI for the root macros
  //  if (!gROOT->IsBatch()) TMVAGui( outfileName );
}

