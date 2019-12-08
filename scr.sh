#!/bin/bash

if [[ "$1" =~ test* ]]; then 
  g++ $1 && ./a.out
else 
  g++ $1 -g && ./a.out
fi
