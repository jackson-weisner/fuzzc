#!/bin/bash

cmake -S . -B build && make -C build && printf "\nbuild completed\n\n"