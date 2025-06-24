# CMS-OpenData-analysis

## How to run the analysis codes:
The analysis codes are kept in the directory `./analysis codes`. Go to the directory and compile the code from the ROOT prompt by doing the following.
```
.L AnaOpenData.C+
``` 
The `+` makes sure that it creates an `.so` file in the same directory, which can be used later. After this step, the compiled library is loaded, and it can be used from the ROOT prompt. Next, the driver file is executed to feed the appropriate values to the input-output parameters and run the analysis.
```
.x driver.C(0)
``` 
That's it!<br>
The verbosity number in the `Process()` function of the main C script can be tweaked to display a status-update after some number of processed events. 

> **Note :** This particular set of codes works with a specific structure of the input ntuple. If there is any change made to the branches of the flat ntuple, The `TTreeReader` method in the `AnaOpenData.h` file needs to be modified accordingly. Otherwise it leads to "Segmentation error" during runtime.

## How to make AOD2FunAOD:


The AOD2FunAOD maker codes can be found in the `./AOD2FunAOD` directory.

## For CMS-OpenData-Virtual Machine:

### Requirements:
1. CMS-OpenData-Virtual Machine should be up and running on the system.
2. CMS Environment should be set up with version `CMSSW_5_3_32.`
3. The NTupleMaker files shall be placed in the directory `./CMSSW_5_3_32/src/`

For more information on how to set up the CMS-OpenData Virtual Machine visit (https://opendata.cern.ch/docs/about-cms)
> **Note :** For setting up the CMS environment, CMSSW_5_3_32, open CMS Shell, set up the software architecture and version by doing `export SCRAM_ARCH=slc6_amd64_gcc472`, set up a new release area for CMSSW_5_3_32 by doing `cmsrel CMSSW_5_3_32`.

### Steps to make the NTuples:
1. Open the CMS Shell Terminal and locate the AOD2FunAOD directory.
2. Set up the runtime environment needed to work with CMSSW by doing:
```
cmsenv
```
3. Compile the code by doing:
```
scram b -j 8
```
4. Open the `./python` directory to find the python exectuable configuration file, `masterntuplemaker_cfg.py`. This file is going to give the output root file. 
5. To execute the configuration file and get the output NTuple do:

### For Data:
#### For 7TeV:
```
cmsRun masterntuplemaker_cfg.py isData=True is7TeV=True nEvents=1000
```
#### For 8TeV:

```
cmsRun masterntuplemaker_cfg.py isData=True is8TeV=True nEvents=1000
```
### For MC:

```
cmsRun masterntuplemaker_cfg.py isData=False nEvents=1000
```
6. That's it.
The output NTuples should be available in the `./output_files` directory.

### Getting the output ROOT files to the local machine:
1. Open the Outer Shell Terminal (not the CMS Terminal) and locate the `./output_files` directory.
2. Now use the secure copy command `scp` to move the file to the desired local machine directory.
```
scp -C [output_filename.root] username_localmachine@[Host_IP_Address]:/home/username_localmachine/desired/path/to/store/the/output_file

```
3. Now one can access the NTuples in their local machine and run the Analysis Codes.

## For Docker:

### Requirements:
1. Docker-Desktop should be up and running on the system.
2. Docker container image containing CMSSW_5_3_32 (For Run 1)  or CMSSW_7_6_7 (For Run 2) should be installed.
3. The AOD2FunAOD files shall be placed in the directory `./CMSSW_5_3_32/src/`.

For more information on how to set up the Docker-Desktop visit (https://opendata.cern.ch/docs/cms-guide-docker)

### Steps to make the NTuples:
1. Open the terminal and run `docker start -i [name_of_container]`
### For AOD2FunAOD (Run1 Data) 
2. Git Clone this repository in the directory`/code/CMSSW_5_3_32/src/`. Navigate to director `/code/CMSSW_5_3_32/src/CMS-OpenData-analysis/AOD2FunAOD/`
3. Compile the code by doing:
```
scram b -j 8
```
4. Open the `./python` directory to find the python exectuable configuration file, `masterntuplemaker_cfg.py` (for Run 1). 
5. To execute the configuration file and get the output NTuple do:

### For Data (Run 1):
For 7TeV:
```
cmsRun masterntuplemaker_cfg.py isData=True is7TeV=True nEvents=1000
```
For 8TeV:

```
cmsRun masterntuplemaker_cfg.py isData=True is8TeV=True nEvents=1000
```
### For MC:

```
cmsRun masterntuplemaker_cfg.py isData=False nEvents=1000
```
6. That's it.
The output NTuples should be available in the `./output_files` directory.

### Getting the output ROOT files to the local machine:
1. Open another terminal on your local machine.
2. Do the following:
<br>
For Run 1:<br>

### if Data:
```
docker cp CMSSW_5_3_32:/code/CMSSW_5_3_32/CMS-OpenData-analysis/AOD2FunAOD/ouput_files/CMS_Data_AOD.root  /home/username_localmachine/desired/path/to/store/the/output_file
```

### if MC:

```
docker cp CMSSW_5_3_32:/code/CMSSW_5_3_32/CMS-OpenData-analysis/AOD2FunAOD/ouput_files/CMS_MC_AODSIM.root  /home/username_localmachine/desired/path/to/store/the/output_file
```
3. Now one can access the NTuples in their local machine and run the Analysis Codes.
