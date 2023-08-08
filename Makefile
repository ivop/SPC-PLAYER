NASM ?= nasm
CC ?= gcc
AFLAGS = -f elf32
CFLAGS = -W -Wall -pedantic -O2 -m32 -ISNEeSe -Isrc
SNESEOBJS = SNEeSe/SPC700.o
SRC = src/dsp.c src/main.c src/spcplayerlinux.c SNEeSe/SPCimpl.c

spcplayer: $(SRC) $(SNESEOBJS)
	gcc $(CFLAGS) -o $@ $(SRC) $(SNESEOBJS) -lz

SNEeSe/SPC700.o: SNEeSe/SPC700.asm SNEeSe/spc.ni SNEeSe/regs.ni \
 SNEeSe/spcaddr.ni SNEeSe/spcmacro.ni SNEeSe/spcops.ni SNEeSe/misc.ni \
 Makefile
	$(NASM) $(AFLAGS) -iSNEeSe/ -o SNEeSe/SPC700.o SNEeSe/SPC700.asm

clean:
	rm -f *.o */*.o spcplayer *~ */*~
