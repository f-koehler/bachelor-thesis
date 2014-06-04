TEX=./buildtex.sh
PY=python3

HEADERS=$(wildcard header/*.tex)
SECTIONS=$(wildcard sections/*.tex)
PSEUDOCODE=$(wildcard pseudocode/*.tex)
PLOTS=plot/runtime-theo/runtime.pdf plot/runtime-theo/comparison.pdf
BIB=literature.bib

all: build/thesis.pdf

# generate data for theory
data/runtime-theo/data.txt: data/runtime-theo/runtime.py
	$(PY) $<

# make plots
plot/runtime-theo/runtime.pdf: plot/runtime-theo/runtime.py data/runtime-theo/data.txt matplotlibrc
	$(PY) $<
plot/runtime-theo/comparison.pdf: plot/runtime-theo/comparison.py data/runtime-theo/data.txt matplotlibrc
	$(PY) $<

# build the thesis
build/thesis.pdf: thesis.tex $(HEADERS) $(SECTIONS) $(PSEUDOCODE) $(BIB) $(PLOTS)
	@$(TEX) $< thesis

.PHONY: clean
clean:
	rm -rf build $(PLOTS)
