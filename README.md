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

## How to make miniAOD2FunAOD:

The miniAOD2FunAOD maker codes can be found in the `./miniAOD2FunAOD` directory.


### Steps to make the NTuples:
1. Open the CMS Shell Terminal and locate the miniAOD2FunAOD directory.
2. Set up the runtime environment needed to work with CMSSW by doing:
```
cmsenv
```
3. Compile the code by doing:
```
scram b -j 8
```
4. Open the `./python` directory to find the python exectuable configuration file, `miniNtupleMaker_config.py`. This file is going to give the output root file. 
5. To execute the configuration file and get the output NTuple do:

### For Data:

```
cmsRun miniNtuplemaker_config.py isData=True nEvents=1000
```
### For MC:

```
cmsRun miniNtuplemaker_config.py isData=False nEvents=1000
```
6. That's it.<br>
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
2. Docker container image containing CMSSW_7_6_7 (For Run 2) should be installed.
3. The miniAOD2FunAOD files shall be placed in the directory `./CMSSW_7_6_7/src/`

For more information on how to set up the Docker-Desktop visit (https://opendata.cern.ch/docs/cms-guide-docker)

### Steps to make the NTuples:
1. Open the terminal and run `docker start -i [name_of_container]`
### For miniAOD2FunAOD (Run2 Data)
2. Git Clone this repository in the directory`/code/CMSSW_7_6_7/src/`. Navigate to director `/code/CMSSW_7_6_7/src/CMS-OpenData-analysis/miniAOD2FunAOD/`
3. Compile the code by doing:
```
scram b -j 8
```
4. Open the `./python` directory to find the python exectuable configuration file, `miniNtupleMaker_config.py` (for Run 2). This file is going to give the output root file. 
5. To execute the configuration file and get the output NTuple do:

### For Data:
```
cmsRun miniNtuplemaker_config.py isData=True nEvents=1000
```

### For MC:

```
cmsRun miniNtuplemaker_config.py isData=False nEvents=1000
```
6. That's it.
The output NTuples should be available in the `./output_files` directory.

### Getting the output ROOT files to the local machine:
1. Open another terminal on your local machine.
2. Do the following:
<br>
 
### if Data:
```
docker cp CMSSW_7_6_7:/code/CMSSW_7_6_7/CMS-OpenData-analysis/miniAOD2FunAOD/ouput_files/CMS_Data_AOD.root  /home/username_localmachine/desired/path/to/store/the/output_file
```
### if MC:

```
docker cp CMSSW_7_6_7:/code/CMSSW_7_6_7/CMS-OpenData-analysis/miniAOD2FunAOD/ouput_files/CMS_MC_AODSIM.root  /home/username_localmachine/desired/path/to/store/the/output_file
```
3. Now one can access the NTuples in their local machine and run the Analysis Codes.
