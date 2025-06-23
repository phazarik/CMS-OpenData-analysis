##-----------------------------------------------------
## Original Author: Raj Handique                      
## Date Created: 20 June 2025                       
## Python Source Code                                  
##-----------------------------------------------------

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
 

# ------------- Additional Configuration Files -------------- #

process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")

from Configuration.AlCa.GlobalTag import GlobalTag

process.load('Configuration.StandardSequences.Services_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

#--------------------------------------------------------------#
#                   VarParsing Options                         #
#--------------------------------------------------------------#

from FWCore.ParameterSet.VarParsing import VarParsing

opt=VarParsing('python')

opt.register('nEvents',
             -1,
             VarParsing.multiplicity.singleton,
             VarParsing.varType.int,
             "Number of Events to Process"
             )

opt.register('isData',
             False,
             VarParsing.multiplicity.singleton,
             VarParsing.varType.bool,
             "Processing on Data"
             )


opt.parseArguments()

# ------------------ Maximum Number of Events --------------- #

#-------------------------------------------------------------#
# Set "input = cms.untracked.int32(-1)" to run all the events.#
# Set to 1000 by default for faster processing of events.     # 
#-------------------------------------------------------------#

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(opt.nEvents))


# ---------------------------------------------------------- #
# Working with Data will require a data quality filter.      #
# One can find the JSON files required for specific dataset  #
# on the CERN Open Data Portal.                              #  
# -----------------------------------------------------------#



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
#                                                             #
# Uncomment the file you wish to use for analysis.            #
# While you uncomment one file, the other should be           # 
# commented out.                                              #
#-------------------------------------------------------------#



#-------------------------------------------------------------#
# To run on larger scale or multiple input text files, one    #
# could use "files.extend" (mentioned below) to add more      #
# files to the analysis.                                      #
#-------------------------------------------------------------#

#files.extend(FileUtils.loadListFromFile("../datasets/filename1.txt")) 
#files.extend(FileUtils.loadListFromFile("../datasets/filename2.txt"))


#-------------------------------------------------------------#
#                  Condition for Data & MC                    #
#-------------------------------------------------------------#

if opt.isData:
    process.GlobalTag.connect = cms.string('sqlite_file:/cvmfs/cms-opendata-conddb.cern.ch/76X_dataRun2_16Dec2015_v0.db')
    process.GlobalTag.globaltag = '76X_dataRun2_16Dec2015_v0'
    output_filename = cms.string("../output_files/CMS_Data_AOD.root")
    files = FileUtils.loadListFromFile("../datasets/CMS_Run2012D_TauParked_AOD_22Jan2013-v1_20000_file_index.txt")

    
    process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring( *files )
                                )
    
    goodJSON = "../interface/Cert_190456-208686_8TeV_22Jan2013ReReco_Collisions12_JSON.txt"
    myLumis = LumiList.LumiList(filename=goodJSON).getCMSSWString().split(",")
    process.source.lumisToProcess = CfgTypes.untracked(
    CfgTypes.VLuminosityBlockRange())
    process.source.lumisToProcess.extend(myLumis)

else:
    process.GlobalTag.connect = cms.string('sqlite_file:/cvmfs/cms-opendata-conddb.cern.ch/76X_mcRun2_asymptotic_RunIIFall15DR76_v1.db')
    process.GlobalTag.globaltag = '76X_mcRun2_asymptotic_RunIIFall15DR76_v1'
    output_filename = cms.string("../output_files/CMS_MC_AODSIM.root")
    files = FileUtils.loadListFromFile("../datasets/CMS_mc_RunIIFall15MiniAODv2_VBF_HToMuMu_M150_13TeV_powheg_pythia8_MINIAODSIM_PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1_60000_file_index.txt")

    process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring( *files )
                                )

#-------------------------------------------------------------#

# ----------------- Analyzer Module ------------------------ #
process.Events = cms.EDAnalyzer("miniNtupleMaker",
                                 isData=cms.untracked.bool(opt.isData),
                                 muons = cms.untracked.InputTag("slimmedMuons"),
                                 electrons = cms.untracked.InputTag("slimmedElectrons"),
                                 photons = cms.untracked.InputTag("slimmedPhotons"),
                                 jets = cms.untracked.InputTag("slimmedJets"),
                                 mets = cms.untracked.InputTag("slimmedMETs"),
                                 genJets = cms.untracked.InputTag("slimmedGenJets"),
                                 genParticles = cms.untracked.InputTag("prunedGenParticles"),
                                 )



# ------------ Configure output root file -------------------#

#------------------------------------------------------------#
#          The output root files are stored in the           #
#------------------------------------------------------------#

process.TFileService = cms.Service("TFileService",
                                   fileName = output_filename,
                                   closeFileFast = cms.untracked.bool(True)
)


#-------------- This will run everything :) ------------------- #
process.p = cms.Path(process.Events)

