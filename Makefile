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

GRPH_SRC	=	$(shell find sources/libgrph -type f -name '*.c')
GRPH_BS_SRC	=	$(shell find sources/libgrph -type f -name '*.grph')
GRPH_YS_SRC	=	$(shell find sources/libysfml -type f -name '*.c++') \
				$(shell find sources/libysfml -type f -name '*.grph')
TEST_SRC	=	$(shell find tests -type f -name '*.c')

GRPH_OBJ	=	$(GRPH_SRC:sources/%.c=build/%.c.o) \
				$(GRPH_BS_SRC:sources/%.grph=build/%.grph.o)

GRPH_YS_OBJ	=	$(GRPH_YS_SRC:sources/%=build/%.o)

TEST_OBJ	=	$(GRPH_SRC:sources/libgrph/%.c=build/cov/%.o) \
				$(GRPH_BS_SRC:sources/libgrph/%.grph=build/%.grph.o) \
				$(TEST_SRC:tests/%.c=build/tests/%.o)

OS_UNAME		?=	$(shell uname)

GRPH_STATIC	=	libgrph.a

CC			?=	gcc
GRPHC		=	grph compile

GRPH_FLAGS	+=	--disable-top-level-code --disable-mangling --pic
CFLAGS		+=	-fPIC -Wno-old-style-declaration
CXXFLAGS	+=	-fPIC -std=c++20
CPPFLAGS	+=	-Wall -Wextra -iquote include
TEST_FLAGS	=	-g
COV_FLAGS	=	-g --coverage
LDLIBS		+=	-lm
LDFLAGS		+=	-L.
LDTESTLIBS	=	--coverage -lcriterion
LD_YS_LIBS	=	-lsfml-graphics -lsfml-window -lsfml-system -lgrph

ifeq ($(OS_UNAME),Darwin)
	GRPH_DYN	=	libgrph.dylib
	GRPH_YS_DYN	=	libgrphysfml.dylib
	DYN_CMD		=	$(CC) -dynamiclib -Wl,-U,_grph_entrypoint -Wl,-U,_grphg_init
	DYN_YS_CMD	=	$(CXX) -dynamiclib
	INSTALL_CMD	=	cp -c
	POSTINSTALL_CMD	=
else
	GRPH_DYN	=	libgrph.so
	GRPH_YS_DYN	=	libgrphysfml.so
	DYN_CMD		=	$(CC) -shared
	DYN_YS_CMD	=	$(CXX) -shared
	INSTALL_CMD	=	cp
	POSTINSTALL_CMD	=	ldconfig
endif

INSTALL_LOC		?=	/usr/local/lib
INSTALL_LIB		=	$(INSTALL_LOC)/$(GRPH_DYN)
INSTALL_LIB_YS	=	$(INSTALL_LOC)/$(GRPH_YS_DYN)
INSTALL_LIBS	=	$(INSTALL_LIB) $(INSTALL_LIB_YS)

STATIC_CMD	=	ar rc

TEST		=	unit_tests

all:	$(GRPH_DYN) $(GRPH_YS_DYN)

install:	$(INSTALL_LIBS)
	$(POSTINSTALL_CMD)

tests_run:	clean_cov $(TEST)
	./$(TEST)

build/%.grph.o:	sources/%.grph
	$(GRPHC) --emit=object -o $@ $< $(GRPH_FLAGS)

build/%.c.o:	sources/%.c
	mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CPPFLAGS) $(CFLAGS)

build/%.c++.o:	sources/%.c++
	mkdir -p $(@D)
	$(CXX) -c -o $@ $< $(CPPFLAGS) $(CXXFLAGS)

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

$(GRPH_YS_DYN):	$(GRPH_YS_OBJ)
	$(DYN_YS_CMD) -o $(GRPH_YS_DYN) $(GRPH_YS_OBJ) $(LDLIBS) $(LD_YS_LIBS) $(LDFLAGS)

$(INSTALL_LIB):	$(GRPH_DYN)
	mkdir -p $(INSTALL_LOC)
	$(INSTALL_CMD) $(GRPH_DYN) $(INSTALL_LIB)

$(INSTALL_LIB_YS):	$(GRPH_YS_DYN)
	mkdir -p $(INSTALL_LOC)
	$(INSTALL_CMD) $(GRPH_YS_DYN) $(INSTALL_LIB_YS)

$(TEST):	$(TEST_OBJ)
	$(CC) -o $(TEST) $(TEST_OBJ) $(LDTESTLIBS) $(LDLIBS) $(LDFLAGS) $(OTHER_LDFLAGS)

asan: CFLAGS += -fsanitize=address
asan: CXXFLAGS += -fsanitize=address
asan: LDFLAGS += -fsanitize=address
asan: CC = clang
asan: CXX = clang++
asan: all

re: fclean
	$(MAKE) all

clean_cov:
	find . \( -name "#*#" -or -name "*~" -or -name "*.gcda"  \) -delete

clean:	clean_cov
	$(RM) $(GRPH_OBJ) $(TEST_OBJ) $(GRPH_YS_OBJ)
	find . -name "*.gcno" -delete

fclean:	clean
	$(RM) $(GRPH_STATIC) $(GRPH_DYN) $(TEST) $(GRPH_YS_DYN)

uninstall:
	$(RM) $(INSTALL_LIBS)

.PHONY: all re clean_cov clean fclean tests_run install uninstall
