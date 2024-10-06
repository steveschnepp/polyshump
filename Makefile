CFLAGS=$(shell pkg-config --cflags sdl2 )
LDLIBS=$(shell pkg-config --libs sdl2 )

ifeq ($(SDLEXTRA), 1)
CFLAGS+=$(shell pkg-config --cflags SDL2_net )
LDLIBS+=$(shell pkg-config --libs SDL2_net )
CFLAGS+=$(shell pkg-config --cflags SDL2_image )
LDLIBS+=$(shell pkg-config --libs SDL2_image )
CFLAGS+=$(shell pkg-config --cflags SDL2_ttf)
LDLIBS+=$(shell pkg-config --libs SDL2_ttf)
CFLAGS+=$(shell pkg-config --cflags SDL2_mixer)
LDLIBS+=$(shell pkg-config --libs SDL2_mixer)

endif

ifeq ($(EMSCRIPTEN), 1)
CFLAGS=
LDLIBS=
EXT=.html
CC=emcc -v -s USE_SDL=2
OPTIM_LEVEL=0
endif

SRCS=$(wildcard *.c usdl/*.c)
OBJS=$(SRCS:.c=.o)
DEPS=$(SRCS:.c=.d)
BINS=$(lastword $(subst /, ,$(dir $(realpath $(lastword $(MAKEFILE_LIST))))))

ifeq ($(OS),Windows_NT)
EXT=.exe
# show stdout
LDLIBS+=-mconsole
endif

EXES=$(BINS:=$(EXT))

$(EXES): $(OBJS)
	$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@

OPTIM_LEVEL?=g
CFLAGS+=-g
CFLAGS+=-O$(OPTIM_LEVEL)
LDLIBS+=-lm
CFLAGS+=-DUSDL_APPNAME=$(BINS)
CFLAGS+=-Wall -Werror -pedantic
CFLAGS+=-Iusdl

ifeq ($(GL), 1)
CFLAGS+=-DOPENGL_ENABLED=1
CFLAGS+=$(shell pkg-config --cflags gl glu)
LDLIBS+=$(shell pkg-config --libs gl glu)
endif

ifeq ($(SCREENSHOTS), 1)
CFLAGS+=-DSCREENSHOTS_ENABLED=1
CFLAGS+=$(shell pkg-config --cflags SDL2_image)
LDLIBS+=$(shell pkg-config --libs SDL2_image)
endif

ifeq ($(ANTIALIAS), 1)
CFLAGS+=-DANTIALIAS_ENABLED=1
endif

.DEFAULT: all

all: $(EXES) screenshots
	echo OS:$(OS) EXE:$(EXES)

screenshots:
	mkdir -p screenshots

clean: $(SUBDIRS)
	rm -f $(OBJS) $(EXES)
	rm -Rf screenshots

realclean: clean $(SUBDIRS)
	rm -f $(DEPS)
	rm -f *~ */*~

indent:
	indent -v -slc -l135 -linux *.c */*.h */*.c

.PHONY: all clean indent
