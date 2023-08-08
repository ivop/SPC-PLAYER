NASM ?= nasm
CC ?= gcc
AFLAGS = -f elf32 -isneese
CFLAGS = -W -Wall -pedantic -O2 -m32 -Isneese -Isrc -no-pie
SNEESEOBJS = sneese/SPC700.o
SRC = src/dsp.c src/main.c src/spcplayerlinux.c sneese/SPCimpl.c
ZLIB = libz.a

spcplayer: $(SRC) $(SNEESEOBJS) $(ZLIB) Makefile
	gcc $(CFLAGS) -o $@ $(SRC) $(SNEESEOBJS) $(ZLIB)

sneese/SPC700.o: sneese/SPC700.asm sneese/spc.ni sneese/regs.ni \
 sneese/spcaddr.ni sneese/spcmacro.ni sneese/spcops.ni sneese/misc.ni \
 Makefile
	$(NASM) $(AFLAGS) -o sneese/SPC700.o sneese/SPC700.asm

$(ZLIB):
	cd zlib && CFLAGS=-m32 ./configure --static
	make -C zlib libz.a
	cp zlib/libz.a .
	make -C zlib distclean

clean:
	rm -f *.o */*.o spcplayer *~ */*~ libz.a
	make -C zlib distclean
