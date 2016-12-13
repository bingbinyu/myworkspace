-include ./Makefile.include

.PHONY:	all dir dist

all: dir

dir: $(dirname)

$(dirname):
	mkdir $@
	(cd $(dirname) && ln ../ti2.cls && \
         cp -p ../Makefile.template Makefile)

dist: $(dirname)
	-(cd $(dirname) && make -k $(dirname).pdf clean)
	zip -r $(dirname).zip $(dirname)
