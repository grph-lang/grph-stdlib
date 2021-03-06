##
##  Makefile
##  GRPH stdlib - libgrph
##
##  Created by Emil Pedersen on 26/01/2022.
##
##  This Source Code Form is subject to the terms of the Mozilla Public
##  License, v. 2.0. If a copy of the MPL was not distributed with this
##  file, You can obtain one at https://mozilla.org/MPL/2.0/.
##

GRPH_SRC	=	$(wildcard sources/libgrph/*.c)
GRPH_BS_SRC	=	$(wildcard sources/libgrph/*.grph)
TEST_SRC	=	$(wildcard tests/*.c)

GRPH_OBJ	=	$(GRPH_SRC:sources/%.c=build/%.c.o) \
				$(GRPH_BS_SRC:sources/%.grph=build/%.grph.o)

TEST_OBJ	=	$(GRPH_SRC:sources/libgrph/%.c=build/cov/%.o) \
				$(GRPH_BS_SRC:sources/libgrph/%.grph=build/%.grph.o) \
				$(TEST_SRC:tests/%.c=build/tests/%.o)

OS_UNAME		?=	$(shell uname)

GRPH_STATIC	=	libgrph.a

CC			?=	gcc
GRPHC		=	grph compile

GRPH_FLAGS	=	--disable-top-level-code --disable-mangling --pic
CFLAGS		=	-fPIC
CPPFLAGS	=	-Wall -Wextra -Wno-old-style-declaration -iquote include
TEST_FLAGS	=	-g
COV_FLAGS	=	-g --coverage
LDLIBS		=	-lm
LDFLAGS		=
LDTESTLIBS	=	--coverage -lcriterion

ifeq ($(OS_UNAME),Darwin)
	GRPH_DYN	=	libgrph.dylib
	DYN_CMD		=	$(CC) -dynamiclib -Wl,-U,_grph_entrypoint
	INSTALL_CMD	=	cp -c
	POSTINSTALL_CMD	=
else
	GRPH_DYN	=	libgrph.so
	DYN_CMD		=	$(CC) -shared
	INSTALL_CMD	=	cp
	POSTINSTALL_CMD	=	ldconfig
endif

INSTALL_LOC	?=	/usr/local/lib
INSTALL_LIB	=	$(INSTALL_LOC)/$(GRPH_DYN)

STATIC_CMD	=	ar rc

TEST		=	unit_tests

all:	$(GRPH_DYN)

install:	$(INSTALL_LIB)
	$(POSTINSTALL_CMD)

tests_run:	clean_cov $(TEST)
	./$(TEST)

build/%.grph.o:	sources/%.grph
	$(GRPHC) --emit=object -o $@ $< $(GRPH_FLAGS)

build/%.c.o:	sources/%.c
	mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CFLAGS)

build/cov/%.o:	sources/%.c
	mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CFLAGS) $(COV_FLAGS)

build/tests/%.o:	tests/%.c
	mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CFLAGS) $(OTHER_CFLAGS) $(TEST_FLAGS)

$(GRPH_STATIC):	$(GRPH_OBJ)
	$(STATIC_CMD) $(GRPH_STATIC) $(GRPH_OBJ)

$(GRPH_DYN):	$(GRPH_OBJ)
	$(DYN_CMD) -o $(GRPH_DYN) $(GRPH_OBJ) $(LDLIBS) $(LDFLAGS)

$(INSTALL_LIB):	$(GRPH_DYN)
	mkdir -p $(INSTALL_LOC)
	$(INSTALL_CMD) $(GRPH_DYN) $(INSTALL_LIB)

$(TEST):	$(TEST_OBJ)
	$(CC) -o $(TEST) $(TEST_OBJ) $(LDTESTLIBS) $(LDLIBS) $(LDFLAGS) $(OTHER_LDFLAGS)

re: fclean all

clean_cov:
	find . \( -name "#*#" -or -name "*~" -or -name "*.gcda"  \) -delete

clean:	clean_cov
	$(RM) $(GRPH_OBJ) $(TEST_OBJ)
	find . -name "*.gcno" -delete

fclean:	clean
	$(RM) $(GRPH_STATIC) $(GRPH_DYN) $(TEST)

uninstall:
	$(RM) $(INSTALL_LIB)

.PHONY: all re clean_cov clean fclean tests_run install uninstall
