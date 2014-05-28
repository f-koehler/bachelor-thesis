#!/bin/bash

# make sure clusterpack is an empty existing dir
if [[ ! -d clusterpack ]]; then
	mkdir clusterpack
else
	rm -rf clusterpack/*
fi

# delete old clusterpack
if [[ -a clusterpack.tar.gz ]]; then
	rm -f clusterpack.tar.gz
fi

cp -r ./jobs clusterpack
cp -r ./primefac/*.cpp ./primefac/*.hpp ./primefac/Makefile clusterpack

tar -pczf clusterpack.tar.gz clusterpack/*

# clean up
rm -rf clusterpack/*
