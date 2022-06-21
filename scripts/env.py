#!/usr/bin/python3

import os

scriptDir = os.path.dirname(__file__)
rootDir = os.path.dirname(scriptDir)
includeDir = os.path.join(rootDir, "include")
srcDir = os.path.join(rootDir, "src")
buildDir = os.path.join(rootDir, "build")

examplesDir = os.path.join(rootDir, "examples")
examplesBuildDir = os.path.join(examplesDir, "build")

if "VCPKG_PATH" not in os.environ:
	raise Exception("environment variable VCPKG_PATH not set")
vcpkgPath = os.environ["VCPKG_PATH"]

print("root: %s" % rootDir)
print("script: %s" % scriptDir)
print("include: %s" % includeDir)
print("sources: %s" % srcDir)
print("vcpkg: %s" % vcpkgPath)
