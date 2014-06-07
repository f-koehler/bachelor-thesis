TEX=./buildtex.sh
PY=python3

HEADERS=$(wildcard header/*.tex)
SECTIONS=$(wildcard sections/*.tex)
PSEUDOCODE=$(wildcard pseudocode/*.tex)
MATPLOTLIB=matplotlibrc header/matplotlib.tex
PLOTS=plot/runtime/time.pdf plot/runtime-theo/runtime.pdf plot/runtime-theo/comparison.pdf
BIB=literature.bib

all: build/thesis.pdf

# analyse data
data/runtime/results.txt: data/runtime/analyse.py
	$(PY) $<
data/runtime-theo/data.txt: data/runtime-theo/runtime.py
	$(PY) $<

# create plots
plot/runtime/time.pdf: plot/runtime/plot.py data/runtime/results.txt $(MATPLOTLIB)
	$(PY) $<
plot/runtime-theo/runtime.pdf: plot/runtime-theo/runtime.py data/runtime-theo/data.txt $(MATPLOTLIB)
	$(PY) $<
plot/runtime-theo/comparison.pdf: plot/runtime-theo/comparison.py data/runtime-theo/data.txt $(MATPLOTLIB)
	$(PY) $<

# build the thesis
build/thesis.pdf: thesis.tex $(HEADERS) $(SECTIONS) $(PSEUDOCODE) $(BIB) $(PLOTS)
	@$(TEX) $< thesis

.PHONY: clean
clean:
	rm -rf build $(PLOTS)
