TEX=./buildtex.sh

HEADERS=$(wildcard header/*.tex)
SECTIONS=$(wildcard sections/*.tex)
PSEUDOCODE=$(wildcard pseudocode/*.tex)
BIB=literature.bib

all: build/thesis.pdf
build/thesis.pdf: thesis.tex $(HEADERS) $(SECTIONS) $(PSEUDOCODE) $(BIB)
	@$(TEX) $< thesis

.PHONY: clean
clean:
	rm -rf build
