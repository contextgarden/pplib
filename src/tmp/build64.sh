#!/bin/bash

if [ `uname -o` = 'Msys' ]
then
  export PATH=/usr/bin:/mingw64/bin
fi

mkdir -p current/build
cp -f Makefile current
cd current
make distclean static shared
make clean
cd ..