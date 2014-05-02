#!/bin/bash

if [ ! -d "./primelist" ]; then
	mkdir primelist
fi

sudo mount -t tmpfs -o nodev,nosuid,size=4G tmpfs ./primelist/
