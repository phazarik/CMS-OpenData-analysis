# CMS-OpenData-analysis
## How to run the analysis codes:
The analysis codes are kept in the directory `./analysis codes`. Go to the directory and compile to code from the ROOT prompt by doing the following.
```
.L AnaOpenData.C+
``` 
The `+` makes sure that it creates a physics `.so` file in the same directory, which can be used later. After this step, the compiled library is loaded, and it can be used from the ROOT prompt. Next, the driver file is run as follows to run the analysis while feeding the appropriate values to the input-output parameters.
```
.x driver.C(0)
``` 
That's it!<br>
The verbosity number in the `Process()` function of the main C script can be tweaked to display a status after some desired number of processed events. 

> **Note :** This particular set of codes works with a specific structure of the input ntuple. If there is any change made to the branches of the flat ntuple, The `TTreeReader` method in the `AnaOpenData.h` file needs to be modified accordingly. Otherwise it leads to "Segmentation error" during runtime.