# -*- Makefile -*-

-include Makefile.include

.PHONY:	all clean boilerplate

all: vanilla $(dirname).pdf clean

clean:
	rm -f *.o *~ *.aux *.log

%.pdf: %.tex
	pdflatex $*
	pdflatex $*
	pdflatex $*

vanilla:
	rm -f $(dirname).pdf
