#! /bin/bash

cd ./project
make
rm -rf ./build 
rm -rf ./nbproject/private
cp ./dist/Release/GNU-Linux-x86/test_alfa ../test/test_alfa
rm -rf ./dist
cd ../
