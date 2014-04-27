#!/bin/bash
TEX="lualatex"
TEXFLAGS="--output-format=pdf --shell-escape --output-directory=. --halt-on-error"

eval $TEX $TEXFLAGS $1
