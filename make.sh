#!/bin/sh

# **************
# set target
# **************
Target="store_tree"
Target_cc="${Target}.cc"
Target_h="${Target}.h"
Target_o="${Target}.o"

# **************
# for user start
# **************

Prefix="/home/weicc/opt/snippets"
src="./src"

# *************
# for user end
# *************

# set path
Snippets_Dir="/home/weicc/opt/snippets"
Snippets_Inc="-I${Snippets_Dir}/include"

ROOT_Inc=`root-config --cflags`

INCLUDE=${Snippets_Inc}" "${ROOT_Inc}
FLAG="-std=c++0x"

# begin to build
if [ -d "build" ];
then
    rm -rf build
fi
mkdir build

# move file to folder "build" to build
cp -rf "${src}/." ./build
cd ./build

# make
g++ -c ${Target_cc} ${INCLUDE} ${FLAG}

# make install
install -d "${Prefix}/bin" "${Prefix}/include" "${Prefix}/lib"
cp ${Target_h} "${Prefix}/include"
cp ${Target_o} "${Prefix}/lib"
