#!/bin/sh
mkdir -p ~/wilson
mkdir -p ~/bin
export PATH=~/bin:$PATH
cp vector.def ~/wilson
cp bus/wilson ~/bin
cp bus/wilson_client ~/bin
cp run_wilson.sh ~/bin
cp kill_wilson.sh ~/bin
