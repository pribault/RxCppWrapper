#!/usr/bin/python3

import os
from env import *

if len(vcpkgPath) == 0:
	raise Exception("cannot cmake without vcpkg")

os.system("cmake %s -DCMAKE_TOOLCHAIN_FILE=%s/scripts/buildsystems/vcpkg.cmake -B %s" % (rootDir, vcpkgPath, buildDir))
os.system("cmake %s -DCMAKE_TOOLCHAIN_FILE=%s/scripts/buildsystems/vcpkg.cmake -B %s" % (examplesDir, vcpkgPath, examplesBuildDir))
