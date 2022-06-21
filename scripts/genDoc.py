#!/usr/bin/python3

import os
from env import *

# save working directory
workDir = os.getcwd()
# move to root
os.chdir(rootDir)
# run doxygen
os.system("doxygen Doxyfile")
# move back to working directory
os.chdir(workDir)
