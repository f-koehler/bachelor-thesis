TEX=./buildtex.sh

SECTIONS=$(wildcard ./section/*)

all: build/thesis.pdf
build/thesis.pdf: thesis.tex $(SECTIONS)
	@$(TEX) $< thesis

.PHONY: clean
clean:
	rm -rf build
