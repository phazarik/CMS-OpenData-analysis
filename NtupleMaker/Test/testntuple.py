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

opt.register('is7TeV',
             False,
             VarParsing.multiplicity.singleton,
             VarParsing.varType.bool,
             "7TeV Data"
             )

opt.register('is8TeV',
             False,
             VarParsing.multiplicity.singleton,
             VarParsing.varType.bool,
             "8TeV Data"
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
    process.GlobalTag.connect = cms.string('sqlite_file:/cvmfs/cms-opendata-conddb.cern.ch/FT53_V21A_AN6_FULL_data_stripped.db')
    process.GlobalTag.globaltag = 'FT53_V21A_AN6_FULL::All'
    output_filename = cms.string("testntuple_data_sample.root")
    files = FileUtils.loadListFromFile("../datasets/CMS_Run2012D_TauParked_AOD_22Jan2013-v1_20000_file_index.txt")

    
    process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring( *files )
                                )
    
    if opt.is7TeV:
        goodJSON_7TeV = "../interface/Cert_160404-180252_7TeV_ReRecoNov08_Collisions11_JSON.txt"
        myLumis = LumiList.LumiList(filename=goodJSON_7TeV).getCMSSWString().split(",")
        process.source.lumisToProcess = CfgTypes.untracked(
            CfgTypes.VLuminosityBlockRange())
        process.source.lumisToProcess.extend(myLumis)
        
    if opt.is8TeV:
        goodJSON_8TeV = "../interface/Cert_190456-208686_8TeV_22Jan2013ReReco_Collisions12_JSON.txt"
        myLumis = LumiList.LumiList(filename=goodJSON_8TeV).getCMSSWString().split(",")
        process.source.lumisToProcess = CfgTypes.untracked(
            CfgTypes.VLuminosityBlockRange())
        process.source.lumisToProcess.extend(myLumis)

else:
    process.GlobalTag.connect = cms.string('sqlite_file:/cvmfs/cms-opendata-conddb.cern.ch/START53_V27_MC_stripped.db')
    process.GlobalTag.globaltag = 'START53_V27::All'
    output_filename = cms.string("testoutput.root")
    files = FileUtils.loadListFromFile("../datasets/CMS_MonteCarlo2011_Summer11LegDR_DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola_AODSIM_PU_S13_START53_LV6-v1_00000_file_index.txt")

    process.source = cms.Source("PoolSource",
                                fileNames = cms.untracked.vstring( *files )
                                )

#-------------------------------------------------------------#




# ----------------- Analyzer Module ------------------------ #

process.Events = cms.EDAnalyzer('testntuplemaker',
                                isData=cms.untracked.bool(opt.isData)
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



