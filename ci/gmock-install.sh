#!/bin/bash

DIR=`mktemp -d`

git clone https://github.com/google/googletest ${DIR}
cd ${DIR}

cmake . -DBUILD_GMOCK=on -DBUILD_GTEST=on
make -j ${THREADS}
make install

cd -
rm -rf ${DIR}

