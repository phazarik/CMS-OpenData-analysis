import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils
import FWCore.PythonUtilities.LumiList as LumiList
import FWCore.ParameterSet.Types as CfgTypes

import os
import sys


relBase = os.environ['CMSSW_BASE']


process = cms.Process("CMSOPENDATAPIPELINE")

# ------- Log and Framework Messaging system --------------- #

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.threshold = "INFO"
process.MessageLogger.categories.append("CMSOPENDATAPIPELINE")
process.MessageLogger.cerr.INFO = cms.untracked.PSet(
    limit=cms.untracked.int32(-1)
)

process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

# ------------------ Maximum Number of Events --------------- #

#-------------------------------------------------------------#
# Set "input = cms.untracked.int32(-1)" to run all the events.#
# Set to 1000 by default for faster processing of events.     #
#-------------------------------------------------------------#

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(1000))  

# ------------- Additional Configuration Files -------------- #

process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

#--------------- sourceFile --------------#

#-------------------------------------------------------------#
#             Instructions on Source Files                    #
#-------------------------------------------------------------#
# The Source files are root files provided in the CERN Open   #
# Data portal. CMS Datasets are available in ".txt" formats   #
# containing the root files. Download them in the "datasets/" #
# directory. Rename the name of the "filename" accordingly.   #
#                                                             #
# files=FileUtils.loadListFromFile("../datasets/filename.txt")#
#                                                             #
# In this specific configuration file, the default datasets   #
# are CMS MonteCarlo AODSIM datasets, with pileup information #
#                                                             #
# Uncomment the file you wish to use for analysis.            #
# While you uncomment one file, the other should be           # 
# commented out.                                              #
#-------------------------------------------------------------#


#PileUp_file
files = FileUtils.loadListFromFile("../datasets/CMS_MonteCarlo2012_Summer12_DR53X_QCD_Pt-15to3000_TuneZ2star_Flat_8TeV_pythia6_AODSIM_PU_RD1_START53_V7N-v1_20000_file_index.txt")

#-------------------------------------------------------------#
# To run on larger scale or multiple input text files, one    #
# could use "files.extend" (mentioned below) to add more      #
# files to the analysis.                                      #
#-------------------------------------------------------------#

#files.extend(FileUtils.loadListFromFile("../datasets/filename1.txt")) 
#files.extend(FileUtils.loadListFromFile("../datasets/filename2.txt"))

#-------------------------------------------------------------#
# NoPileUpfile (Uncomment below file for no pileup dataset)   

#files = FileUtils.loadListFromFile("../datasets/CMS_MonteCarlo2012_Summer12_DR53X_QCD_Pt-15to3000_TuneZ2star_Flat_8TeV_pythia6_AODSIM_NoPileUp_START53_V7N-v1_20000_file_index.txt")

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
                                *files
    )
)

# ---------------------------------------------------------- #
# Working with Data will require a data quality filter.      #
# One can find the JSON files required for specific dataset  #
# on the CERN Open Data Portal.                              #  
# -----------------------------------------------------------#

#Uncomment this while using data

#goodJSON = "../interface/Cert_190456-208686_8TeV_22Jan2013ReReco_Collisions12_JSON.txt"
#myLumis = LumiList.LumiList(filename=goodJSON).getCMSSWString().split(",")
#process.source.lumisToProcess = CfgTypes.untracked(
#    CfgTypes.VLuminosityBlockRange())
#process.source.lumisToProcess.extend(myLumis)



# ----------------- Analyzer Module ------------------------ #

process.Events = cms.EDAnalyzer('MasterAnalyzer')


# ------------ Configure output root file -------------------#

#------------------------------------------------------------#
# The output root files are stored in the output_files       #
# directory.                                                 #
#------------------------------------------------------------#

PU_output_filename = "../output_files/sample_input_PU.root" 

noPU_output_filename = "../output_files/sample_input_noPU.root"


process.TFileService = cms.Service("TFileService",
                                   #if pileup (uncomment this)
                                   fileName = cms.string(PU_output_filename)
                                   #if no_pileup (uncomment this)
                                   #fileName = cms.string(noPU_output_filename)
)


#-------------- This will run everything ------------------- #
process.p = cms.Path(process.Events)



