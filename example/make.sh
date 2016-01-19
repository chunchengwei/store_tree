#!/bin/sh

# **************
# set target
# **************
Target="main"
Target_cc="${Target}.cc"

EXE="test"
dependence="pArray.o store_tree.o"

# **************
# for user start
# **************

# *************
# for user end
# *************

# set path
Snippets_Dir="/home/weicc/opt/snippets"
Snippets_Inc="-I${Snippets_Dir}/include"
Snippets_Lib="${Snippets_Dir}/lib"

ROOT_Inc=`root-config --cflags`
ROOT_Lib=`root-config --libs`

INCLUDE=${Snippets_Inc}" "${ROOT_Inc}
LIB=${ROOT_Lib}
FLAG="-std=c++0x"

# begin to build
if [ -d "build" ];
then
    rm -rf build
fi
mkdir build

# move file to folder "build" to build
cp -rf ${Target_cc} ./build
cd ./build

# copy dependence file to build
# cp ${Snippets_Lib}/{pArray.o,store_tree.o} ./
for oFile in ${dependence}
do
  cp ${Snippets_Lib}/${oFile} ./
done

# make
g++ ${Target_cc} *.o -o ${EXE} ${INCLUDE} ${LIB} ${FLAG}

# make install
cp ${EXE} ../ 
