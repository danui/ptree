HFILES=		src/app.h		\
		src/model.h		\

OFILES=		obj/ptree.o		\
		obj/model.o		\

default: out/ptree

out/ptree: out $(OFILES)
	gcc $(OFILES) -o out/ptree

obj/ptree.o: obj src/ptree.c $(HFILES)
	gcc -c src/ptree.c -o obj/ptree.o

obj/model.o: obj src/model.c $(HFILES)
	gcc -c src/model.c -o obj/model.o

out:
	mkdir out

obj:
	mkdir obj

clean:
	rm -rf obj out
	rm -f *~ src/*~
