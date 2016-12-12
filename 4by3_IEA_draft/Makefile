texfile =Spring_modelling_draft

all:
	pdflatex $(texfile).tex
	bibtex $(texfile).aux
	pdflatex $(texfile).tex
	pdflatex $(texfile).tex

clean:
	-rm *.aux *.log *.bbl *.blg *.toc *.out *.nav *.snm *.synctex.gz
	-rm $(texfile).dvi
	
