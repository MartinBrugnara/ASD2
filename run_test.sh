#!/bin/bash

# 19 not computable
tests=18
if [[ -n $1 ]]; then
    tests=$1
fi
range=0..`echo $tests`

clang++ -std=c++11 -O2 -o psy psy.cpp -DEVAL

for i in $(eval echo {$range})
do
        cp DatasetP1/input/input$i.txt input.txt
        echo -n "$i: "
        (time ./generali) &> /tmp/res && cat /tmp/res | grep real 
        echo -n "   "
        ./DatasetP1/cor DatasetP1/input/input$i.txt DatasetP1/helper/helper$i.txt output.txt
        echo ""
done
