#!/usr/bin/python3

import os
from env import *

os.system("cmake %s -DCMAKE_TOOLCHAIN_FILE=%s/scripts/buildsystems/vcpkg.cmake -B %s" % (rootDir, vcpkgPath, buildDir))
os.system("cmake %s -DCMAKE_TOOLCHAIN_FILE=%s/scripts/buildsystems/vcpkg.cmake -B %s" % (examplesDir, vcpkgPath, examplesBuildDir))
