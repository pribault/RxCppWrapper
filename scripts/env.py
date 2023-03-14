#!/usr/bin/python3

import os

scriptDir = os.path.dirname(__file__)
rootDir = os.path.dirname(scriptDir)
includeDir = os.path.join(rootDir, "include")
srcDir = os.path.join(rootDir, "src")
buildDir = os.path.join(rootDir, "build")
resourcesDir = os.path.join(rootDir, "resources")

if "VCPKG_PATH" not in os.environ:
	print("environment variable VCPKG_PATH not set")
	vcpkgPath = ""
else:
	vcpkgPath = os.environ["VCPKG_PATH"]

print("================================= ENVIRONMENT ==================================")
print("directories:")
print(" - root: %s" % rootDir)
print(" - script: %s" % scriptDir)
print(" - include: %s" % includeDir)
print(" - sources: %s" % srcDir)
print(" - resources: %s" % resourcesDir)
print(" - vcpkg: %s" % vcpkgPath)
print("================================================================================")
