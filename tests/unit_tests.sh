#!/bin/sh
# Lancer avec Linux ou MinGW
make -j4
for file in bin/*; do $file; done