#!/usr/bin/python3

import os

scriptDir = os.path.dirname(__file__)
rootDir = os.path.dirname(scriptDir)
includeDir = os.path.join(rootDir, "include")
srcDir = os.path.join(rootDir, "src")
buildDir = os.path.join(rootDir, "build")

if "VCPKG_PATH" not in os.environ:
	raise Exception("environment variable VCPKG_PATH not set")
vcpkgPath = os.environ["VCPKG_PATH"]

print(scriptDir)
print(rootDir)
print(includeDir)
print(srcDir)
print(vcpkgPath)
