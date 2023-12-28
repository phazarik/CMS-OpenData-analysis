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

## How to make ntuples:


The NTuple maker codes can be found in the './NTupleMaker' directory.

### Requirements:
1. CMS-OpenData-Virtual Machine should be up and running in the system.
2. CMS Environment should be set up with version CMSSW_5_3_32.
3. The NTupleMaker file shall be placed in the directory './CMSSW_5_3_32/src/' 

For more information on how to set up the CMS-OpenData Virtual Machine visit (https://opendata.cern.ch/docs/about-cms)
> **Note :** For setting up the CMS environment, CMSSW_5_3_32, do the following:
	1. Open CMS Shell.
	2. Set up the software architecture and version by doing:
	```
	export SCRAM_ARCH=slc6_amd64_gcc472
	```
	3. Set up a new release area for CMSSW_5_3_32:
	```
	cmsrel CMSSW_5_3_32
	```

### Steps to make the NTuples:
1. Open the CMS Shell Terminal and locate the NTupleMaker directory.
2. Set up the runtime environment needed to work with CMSSW by doing:
```
cmsenv
```
3. Compile the code by doing:
```
scram b
```
4. Open the './python' directory to find the python exectuable configuration file, "./masteranalyzer.py". This file is going to run the CMSSW process, or in this case, give the output root file. 
5. To execute the configuration file and get the output NTuple do:
```
cmsRun masteranalyzer.py
```
6. That's it.
The output NTuples should be available in the './output_files' directory. 
