all:
	@echo TODO: do not use -ini:
	@echo tie -c initex-final.ch tex.web initex.ch \# see initex.ch on ctang - init-tini
	@echo tangle tex initex-final initex
	@echo web2c/convert initex
	@echo ...
	@echo https://tex.stackexchange.com/questions/417624/installation-procedures-of-early-tex-installations
	@echo https://tex.stackexchange.com/questions/64000/executables-of-formats-engines-and-executables-of-engines
	#TODO: check if this statement is true: Run TANGLE on TEX.WEB and INITEX.CH, obtaining INITEX.PAS and TEX.POOL.
	tie -c tex-final.ch tex.web tex.ch
	tangle tex tex-final
	make -C web2c
	web2c/convert tex # creates tex0.c, texini.c, texcoerce.h and texd.h (texcoerce.h is used in texd.h)
	gcc -DHAVE_CONFIG_H -I. -I./w2c -Wimplicit -Wreturn-type -g -O2 -c -o tex0.o tex0.c # texd.h is used here
	gcc -DHAVE_CONFIG_H -I. -I./w2c -Wimplicit -Wreturn-type -g -O2 -c -o texini.o texini.c # texd.h is used here
	gcc -DHAVE_CONFIG_H -I. -I./w2c -Wimplicit -Wreturn-type -g -O2 -c -o texextra.o texextra.c # texd.h is used here
	make -C lib # creates lib.a
	gcc -Wimplicit -Wreturn-type -g -O2 -o virtex texextra.o texini.o tex0.o lib/lib.a -lkpathsea -lm
	mv virtex /usr/local/bin/
