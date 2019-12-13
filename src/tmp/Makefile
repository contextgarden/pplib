
# Here is a Makefile made on the base of what is logged from automade Makefile

UNAME:=$(shell uname)
ifeq ($(UNAME), Linux)
	BUILDSUFFIX=.ux
	STATICOPTS=-Wall -O3
	SHAREDOPTS=-Wall -O3 -fPIC -DPIC
	STATICOBJA=
	SHAREDOBJA=
else
	BUILDSUFFIX=
	ASM=true
	ifeq ($(ASM), true)
		STATICOPTS=-Wall -O3 -DNO_VIZ -DASMV -DNO_UNDERLINE
		SHAREDOPTS=-Wall -O3 -fPIC -DPIC -DNO_VIZ -DPIC -DNO_UNDERLINE
		ifeq ($(ARCH), x86)
			STATICOBJA=match.o
			SHAREDOBJA=match.lo
		else
			STATICOBJA=gvmat64.o
			SHAREDOBJA=gvmat64.lo
		endif
	else
		STATICOPTS=-Wall -O3 -DNO_VIZ
		SHAREDOPTS=-Wall -O3 -fPIC -DPIC -DNO_VIZ
		STATICOBJA=
		SHAREDOBJA=
	endif
endif

# to use the asm code: make STATICOBJA=match.o, SHAREDOBJA=match.lo (doesn't work on never gcc64)

ZLIBSTATICLIB=build/libz.static$(BUILDSUFFIX).a
ZLIBSHAREDLIB=build/libz.shared$(BUILDSUFFIX).a

ZLIBSTSATICOBJS=adler32.o compress.o crc32.o deflate.o gzclose.o gzlib.o gzread.o \
	gzwrite.o infback.o inffast.o inflate.o inftrees.o trees.o uncompr.o zutil.o

ZLIBSHAREDLIBOBJS=adler32.lo compress.lo crc32.lo deflate.lo gzclose.lo gzlib.lo gzread.lo \
	gzwrite.lo infback.lo inffast.lo inflate.lo inftrees.lo trees.lo uncompr.lo zutil.lo

all: static shared

static: $(ZLIBSTATICLIB)

shared: $(ZLIBSHAREDLIB)

$(ZLIBSTSATICOBJS): %.o : %.c
	gcc $(STATICOPTS) -o $@ -c $<

$(ZLIBSHAREDLIBOBJS): %.lo : %.c
	gcc $(SHAREDOPTS) -o $@ -c $<

match.o gvmat64.o: %.o : %.S
	gcc $(STATICOPTS) -o $@ -c $<

match.lo gvmat64.lo: %.lo : %.S
	gcc $(SHAREDOPTS) -o $@ -c $<

match.S gvmat64.S:
	cp contrib/gcc_gvmat64/gvmat64.S .
	cp contrib/asm686/match.S .

$(ZLIBSTATICLIB): $(ZLIBSTSATICOBJS) $(STATICOBJA)
	ar -rcs $@ $^

$(ZLIBSHAREDLIB): $(ZLIBSHAREDLIBOBJS) $(SHAREDOBJA)
	ar -rcs $@ $^

distclean: clean
	rm -f $(ZLIBSTATICLIB) $(ZLIBSHAREDLIB)

clean:
	rm -f *.o *.lo