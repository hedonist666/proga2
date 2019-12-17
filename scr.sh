#!/bin/bash

if [[ "$1" =~ test* ]]; then 
  g++ $1 -fconcepts && ./a.out
else 
  g++ $1 -g -fconcepts && ./a.out
fi
