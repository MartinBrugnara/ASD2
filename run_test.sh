#!/bin/bash

clang++ -O2 -std=c++11 -o DatasetP2/cor DatasetP2/cor.cpp

# 19 not computable
tests=18
if [[ -n $1 ]]; then
    tests=$1
fi
range=0..`echo $tests`

clang++ -std=c++11 -O2 -o psy psy.cpp -DEVAL

for i in $(eval echo {$range})
do
        cp DatasetP2/input/input$i.txt input.txt
        echo -n "$i: "
        (time ./psy) &> /tmp/res && cat /tmp/res | grep real 
        echo -n "   "
        ./DatasetP2/cor DatasetP2/input/input$i.txt DatasetP2/helper/helper$i.txt output.txt
        echo ""
done

rm -f input.txt
rm -f output.txt
