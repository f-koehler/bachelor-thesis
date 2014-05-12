#!/bin/bash

# LuaTex environment
TEXENV=""
TEXARGS="--shell-escape --halt-on-error --interaction=batchmode --output-directory=build"
TEX="env $TEXENV lualatex $TEXARGS"

# make sure build dirs exist
if [[ ! -d build ]]; then
	mkdir build
fi
if [[ ! -d build/rubber ]]; then
	mkdir build/rubber
fi

# usage function
usage() {
	echo "Usage: $0 file [jobname]"
	exit 1
}

# build function
build() {
	retVal=0

	# build 1st time
	echo "$TEX --jobname=$2 $1"
	eval $TEX --jobname="$2" "$1" > /dev/null
	retVal=$?

	cd build
	rubber-info --errors   "$2".log > rubber/errors.txt
	rubber-info --warnings "$2".log > rubber/warnings.txt
	rubber-info --refs     "$2".log > rubber/refs.txt
	rubber-info --boxes    "$2".log > rubber/boxes.txt
	rubber-info --errors   "$2".log
	rubber-info --warnings "$2".log
	rubber-info --refs     "$2".log
	rubber-info --boxes    "$2".log
	cd ..

	if [ $retVal -gt 0 ]; then
		rm -f build/"$2".pdf
		echo "Build of $1 failed!"
		exit 1
	fi

	# bibliography
	# TODO

	# build 2nd time
	echo "$TEX --jobname=$2 $1"
	eval $TEX --jobname="$2" "$1" > /dev/null
	retVal=$?

	cd build
	rubber-info --errors   "$2".log > rubber/errors.txt
	rubber-info --warnings "$2".log > rubber/warnings.txt
	rubber-info --refs     "$2".log > rubber/refs.txt
	rubber-info --boxes    "$2".log > rubber/boxes.txt
	cd ..

	if [ $retVal -gt 0 ]; then
		rm -f build/"$2".pdf
		echo "Build of $1 failed!"
		exit 1
	fi
}

case $# in
	0)
		usage
		;;
	1)
		"$0" "$1" "${1%.*}"
		;;
	2)
		build $1 $2
		;;
esac
