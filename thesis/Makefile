TEX=./buildtex.sh

SECTIONS=$(wildcard sections/*.tex)

all: build/thesis.pdf
build/thesis.pdf: thesis.tex $(SECTIONS)
	@$(TEX) $< thesis

.PHONY: clean
clean:
	rm -rf build
