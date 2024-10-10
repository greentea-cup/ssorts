#!/bin/bash
# partial clone googletest
GTEST_VERSION=v1.15.2
rm -rf googletest
git clone -n --depth=1 --filter=tree:0 --branch=${GTEST_VERSION} -- https://github.com/google/googletest googletest
cd googletest
git sparse-checkout set --no-cone /LICENSE /CMakeLists.txt /googletest/cmake /googletest/include /googletest/src /googletest/CMakeLists.txt
git checkout
# submodules do not support partial features, just add googletest's sources directly
rm -rf .git
echo ${GTEST_VERSION} > VERSION
cd ..
