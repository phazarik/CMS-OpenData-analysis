# Getting Started with the Analysis Codes:

## Requirements:
ROOT Framework 6.10.0 or higher must be installed in the local machine. 

## General Instructions:
1. Make a new directory where you want to work with the Analysis Codes.
2. Locate to the directory using the terminal.
3. Clone the git repository to that directory:
```
git clone https://github.com/phazarik/CMS-OpenData-analysis.git
```
4. Locate the `./AnalysisCodes` directory.
```
cd CMS-OpenData-Analysis/AnalysisCodes/
```
5. Run the following command to start the ROOT prompt:
```
root 
```
6. Compile the Analysis Codes by doing:
```
.L AnaOpenData.C+
```
7. Run the executable driver file by doing:
```
.x driver.C(0)
```
8. Locate to the `./OutputHists` directory (outside the ROOT prompt).
9. That's it. Now one can use `TBrowser`(in the ROOT prompt) to view the `hst_sample.root` file.
