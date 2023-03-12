#!/usr/bin/python3

import getopt
import os
import re
import shutil
import sys
from env import *

# global variables
allowedBuildTypes = ["Release", "Debug"]
releaseDir = os.path.join(buildDir, "release")
releaseIncludeDir = os.path.join(releaseDir, "include")
releaseBinDir = os.path.join(releaseDir, "bin")
releaseLibDir = os.path.join(releaseDir, "lib")

# print usage
def printUsage():
	print("release.py [-h] [--help] [-b <Debug|Release>] [--buildType <Debug|Release>]")
	print("  -h or --help: dysplay help and quit")
	print("  -b or --buildType: set build type ('Release' or 'Debug')")

# filter strings with the given pattern
def glob_re(pattern, strings):
	regex = re.compile(pattern)
	return filter(regex.match, strings)

# copy files matching the given pattern from srcDir to dstDir
def copy(srcDir, pattern, dstDir):
	# ensure dst directory exists
	if not os.path.exists(dstDir):
		os.makedirs(dstDir)
	# iterate over files matching pattern
	for file in glob_re(pattern, os.listdir(srcDir)):
		srcFile = os.path.join(srcDir, file)
		dstFile = os.path.join(dstDir, file)
		# copy file or directory
		if os.path.isdir(srcFile):
			shutil.copytree(srcFile, dstFile, dirs_exist_ok=True)
		else:
			shutil.copy(srcFile, dstFile)

# platform independant steps to make release
def releaseCommon():
	# ensure release directory exists
	if not os.path.exists(releaseDir):
		os.makedirs(releaseDir)
	# copy includes
	copy(includeDir, "^.+$", releaseIncludeDir)

# windows specific steps to make release
def releaseWindows(buildType):
	binDir = os.path.join(buildDir, "bin", buildType)
	copy(binDir, "^.+\\.(?P<ext>exe|dll)$", releaseBinDir)
	copy(binDir, "^.+\\.(?P<ext>lib|pdb)$", releaseLibDir)

# unix specific steps to make release
def releaseUnix():
	binDir = os.path.join(buildDir, "bin")
	copy(binDir, "^\\w+$", releaseBinDir)
	copy(binDir, "^.+\\.(?P<ext>so|a|dylib)$", releaseLibDir)

if __name__ == '__main__':

	# define default variables
	buildType = "Release"

	# retrieve arguments
	opts, args = getopt.getopt(sys.argv[1:], "hb:", ["help", "buildType="])

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
		# build type
		if opt in ("-b", "--buildType"):
			if not arg in allowedBuildTypes:
				print("unknown build type '%s'" % arg)
				printUsage()
				exit(1)
			buildType = arg

	# make release
	print("creating '%s' release at '%s'" % (buildType, releaseDir))
	releaseCommon()
	if sys.platform.startswith('win'):
		releaseWindows(buildType)
	else:
		releaseUnix()
	print("release created!")
