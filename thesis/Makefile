TEX=./buildtex.sh

HEADERS=$(wildcard header/*.tex)
SECTIONS=$(wildcard sections/*.tex)
PSEUDOCODE=$(wildcard pseudocode/*.tex)
PLOTS=plot/runtime-theo/runtime.pdf plot/runtime-theo/comparison.pdf
BIB=literature.bib

all: build/thesis.pdf

# generate data for theory
data/runtime-theo/data.txt:
	python data/runtime-theo/runtime.py

# make plots
plot/runtime-theo/runtime.pdf: data/runtime-theo/data.txt
	python plot/runtime-theo/runtime.py
plot/runtime-theo/comparison.pdf: data/runtime-theo/data.txt
	python plot/runtime-theo/comparison.py

# build the thesis
build/thesis.pdf: thesis.tex $(HEADERS) $(SECTIONS) $(PSEUDOCODE) $(BIB) $(PLOTS)
	@$(TEX) $< thesis

.PHONY: clean
clean:
	rm -rf build $(PLOTS)
