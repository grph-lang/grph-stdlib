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
TEST_SRC	=	$(wildcard tests/*.c)

GRPH_OBJ	=	$(GRPH_SRC:sources/libgrph/%.c=%.o)
TEST_OBJ	=	$(GRPH_SRC:sources/libgrph/%.c=%.g.o) \
				$(TEST_SRC:tests/%.c=%.t.o)

OS			?=	$(shell uname)

GRPH_STATIC	=	libgrph.a

ifeq ($(OS),Darwin)
	GRPH_DYN	=	libgrph.dylib
	DYN_CMD		=	clang -dynamiclib
else
	GRPH_DYN	=	libgrph.so
	DYN_CMD		=	clang -shared
endif

INSTALL_LOC	?=	/usr/local/lib
INSTALL_LIB	=	$(INSTALL_LOC)/$(GRPH_DYN)

STATIC_CMD	=	ar rc

TEST		=	unit_tests

all:	$(GRPH_STATIC)

install:	$(INSTALL_LIB)

tests_run:	clean_cov $(TEST)
	./$(TEST)

%.o:	sources/libgrph/%.c
	clang -Wall -Wextra -c -o $@ $< -Iinclude -fPIC

%.g.o:	sources/libgrph/%.c
	clang -Wall -Wextra --coverage -c -o $@ $< -Iinclude

%.t.o:	tests/%.c
	clang -Wall -Wextra -c -o $@ $< -Iinclude  $(OTHER_CFLAGS)

$(GRPH_STATIC):	$(GRPH_OBJ)
	$(STATIC_CMD) $(GRPH_STATIC) $(GRPH_OBJ)
	
$(GRPH_DYN):	$(GRPH_OBJ)
	$(DYN_CMD) -o $(GRPH_DYN) $(GRPH_OBJ)

$(INSTALL_LIB):	$(GRPH_DYN)
	mkdir -p $(INSTALL_LOC)
	cp $(GRPH_DYN) $(INSTALL_LIB)

$(TEST):	$(TEST_OBJ)
	clang -o $(TEST) $(TEST_OBJ) -lcriterion --coverage $(OTHER_LDFLAGS)

re: fclean all

clean_cov:
	find . \( -name "#*#" -or -name "*~" -or -name "*.gcda"  \) -delete

clean:	clean_cov
	rm -f $(GRPH_OBJ) $(TEST_OBJ)
	find . -name "*.gcno" -delete

fclean:	clean
	rm -f $(GRPH_STATIC) $(TEST)
	
.PHONY: all re clean_cov clean fclean
