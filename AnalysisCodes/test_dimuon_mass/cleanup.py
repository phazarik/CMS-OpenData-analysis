#This python script deletes the compiled files and cleans up the directory.

import os, sys, argparse

parser = argparse.ArgumentParser()
parser.add_argument('--all', action='store_true', help='removes all the output root files in test_outputs')
args = parser.parse_args()

junk = [
    "*.so",
    "*~",
    "*.pcm",
    "*#",
    "*d"
]

if args.all : junk.append("OutputHists/*")

print("Running the following commands ...")
for item in junk:
    processline = "rm -rf "+item
    print(processline)
    os.system(processline)
print("Done!")
