
# Getting Started with the NTupleMaker
## Description

The NTupleMaker is an EDAnalyzer that extracts information from AOD & AODSIM formats of different physics objects and stores them in a ROOT file.

This particular NTupleMaker can extract information of ParticleFlowCandidates, RecoJets, GenJets and GenParticles. The EDAnalyzer can be executed by the configuration file called `ntuplemaker_cfg.py`

## General Instructions on Usage:

1. Install the CMS-OpenData [Virtual Machine](https://opendata.cern.ch/record/252)
2. Set up the `CMSSW_5_3_32` environment
3. Change to the `CMSSW_5_3_32/src/` directory.
4. Now clone the repository to that directory:
```
git clone https://github.com/phazarik/CMS-OpenData-analysis.git
```
5. Change to the `CMS-OpenData-analysis/NtupleMaker/` directory.
```
cd CMS-OpenData-analysis/NtupleMaker/
```
6. Now set the runtime environment by running the following command:
```
cmsenv
```
7. Compile everything by running the following command:
```
scram b
```
8. Change to `./python` directory
```
cd python
```
9. Run the CMSSW executable configuration file (the python file) by the following command:
```
cmsRun masterntuplemaker_cfg.py
```
10. That's it! <br>

The NTuples will be available at `./output_files` directory.
