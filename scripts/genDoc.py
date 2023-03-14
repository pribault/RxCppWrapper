#!/usr/bin/python3

import getopt
import os
import sys
from env import *

# print usage
def printUsage():
	print("buildDoc.py [-h] [--help]")
	print("  -h or --help: dysplay help and quit")

if __name__ == '__main__':

	# retrieve arguments
	opts, args = getopt.getopt(sys.argv[1:], "h:", ["help"])

	# ensure all arguments are parsed
	if len(args) != 0:
		print("invalid number of arguments (%s)" % (len(args) - 1))
		printUsage()
		exit(1)

	# handle each argument
	for opt, arg in opts:
		# help
		if opt in ("-h", "--help"):
			printUsage()
			exit(0)

	# run build command
	print("starting documentation build")

	# Make sure build directory exists
	if not os.path.exists(buildDir):
		os.mkdir(buildDir)

	# save working directory
	workDir = os.getcwd()
	# move to root
	os.chdir(rootDir)
	# run doxygen
	result = os.system("doxygen %s" % os.path.join(resourcesDir, "Doxyfile"))
	# move back to working directory
	os.chdir(workDir)

	if result:
		print("Documentation build KO!")
	else:
		print("Documentation build OK!")
	sys.exit(1 if result > 0 else 0)
