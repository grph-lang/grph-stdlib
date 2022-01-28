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
TEST_OBJ	=	$(GRPH_SRC:%=%.t.o) $(TEST_SRC:%=%.g.o)

GRPH_STATIC	=	libgrph.a

TEST		=	unit_tests

all:	$(GRPH_STATIC)

tests_run:	clean_cov $(TEST)
	./$(TEST)

%.o:	sources/libgrph/%.c
	clang -Wall -Wextra -c -o $@ $< -Iinclude

%.g.o:	sources/libgrph/%.c
	clang -Wall -Wextra --coverage -c -o $@ $< -Iinclude

%.t.o:	tests/%.c
	clang -Wall -Wextra -c -o $@ $< -Iinclude

$(GRPH_STATIC):	$(GRPH_OBJ)
	ar rc $(GRPH_STATIC) $(GRPH_OBJ)

$(TEST):	$(TEST_OBJ)
	clang -o $(TEST) $(TEST_OBJ) -lcriterion --coverage

re: fclean all

clean_cov:
	find . \( -name "#*#" -or -name "*~" -or -name "*.gcda"  \) -delete

clean:	clean_cov
	rm -f $(GRPH_OBJ) $(TEST_OBJ)
	find . -name "*.gcno" -delete

fclean:	clean
	rm -f $(GRPH_STATIC) $(TEST)
	
.PHONY: all re clean_cov clean fclean
