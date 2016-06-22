#!/bin/bash

lcov --directory . --zero-counters

rm -f lcov_out

cd test
./unitTests
cd ..
./ApiTest/apiTests

mkdir lcov_out
cd lcov_out

lcov --directory .. --capture --output-file app.info
lcov --remove app.info "/usr/*" --output-file app.info
lcov --remove app.info "jsoncpp*" --output-file app.info
lcov --remove app.info "json.h" --output-file app.info

genhtml app.info

# O cualquier navegador que tengan a mano.
firefox index.html 
