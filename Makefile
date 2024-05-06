##
## EPITECH PROJECT, 2024
## B-CNA-410-PAR-4-1-trade-thibaud.cathala
## File description:
## Makefile
##

SRC				:=	$(shell find src/ -name "*.cpp")

CPPFLAGS		=	-std=c++20 -Wall -Wextra \
					$(ADDITIONAL_FLAGS)

INCLUDE_PATH	=	-I./include/ -I./include/lib

NAME			=	trade

LIB_PATH		=	lib/

LIB_NAME		=	lib/my_cpplib.a

SRC_TESTS		:=	$(shell find tests/ -name "*.cpp")

RUN_TEST		=	--coverage -lcriterion

NAME_TESTS		=	unit_tests

OBJ				=	$(SRC:.cpp=.o)

%.o: %.cpp
	@g++ $(CPPFLAGS) $(INCLUDE_PATH) -c $< -o $@ && \
	printf "[\e[92mOK\e[0m] g++ $(CPPFLAGS) -c $< -o $@\n" || \
	printf "[\e[1;91mKO\e[0m] g++ $(CPPFLAGS) -c $< -o $@\n"

$(NAME): $(OBJ)
	@cd $(LIB_PATH) && $(MAKE) ADDITIONAL_FLAGS="$(ADDITIONAL_FLAGS)"
	@if g++ -o $(NAME) $(OBJ) $(LIB_NAME) $(CPPFLAGS) $(INCLUDE_PATH); then \
		printf "[\e[92mCOMPILATION OK\e[0m] "; \
		printf "g++ -o $(NAME) $(OBJ) $(LIB_NAME) $(CPPFLAGS)\n"; \
	else \
		printf "[\e[1;91mCOMPILATION KO\e[0m] "; \
		printf "g++ -o $(NAME) $(OBJ) $(LIB_NAME) $(CPPFLAGS)\n"; \
		exit 1; \
	fi

all: $(NAME)

clean:
	rm -f $(OBJ) $(shell find src/ -name "*.o")
	@rm -f $(shell find src/ -name "*.gcno")
	@rm -f $(shell find src/ -name "*.gcda")
	rm -f *.gcno *.gcda gmon.out compile_commands.json

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_TESTS)
	@cd $(LIB_PATH) && $(MAKE) fclean

re: fclean all

unit_tests: SRC := $(patsubst src/main.cpp%,%,$(SRC))
unit_tests: fclean
	@cd $(LIB_PATH) && $(MAKE)
	@if g++ -o $(NAME_TESTS) $(SRC_TESTS) $(SRC) \
		$(LIB_NAME) $(CPPFLAGS) $(RUN_TEST) $(INCLUDE_PATH); then \
		printf "[\e[92mCOMPILATION OK\e[0m] "; \
		printf "g++ -o -o $(NAME_TESTS) $(SRC_TESTS) $(SRC)"; \
		printf "$(LIB_NAME) $(CPPFLAGS) $(RUN_TEST)\n"; \
	else \
		printf "[\e[1;91mCOMPILATION KO\e[0m] "; \
		printf "g++ -o -o $(NAME_TESTS) $(SRC_TESTS) $(OBJ)"; \
		printf "$(LIB_NAME) $(CPPFLAGS) $(RUN_TEST)\n"; \
		exit 1; \
	fi

tests_run: unit_tests
	./$(NAME_TESTS)

gcovr:
	@gcovr --sort-percentage --exclude tests/
	@gcovr --sort-percentage --exclude tests/ --branches

debug: CPPFLAGS += -g3
debug: clean all
	gdb -ex "run $(arg)" -ex "bt full" -ex "detach" -ex "quit" $(NAME)

profiling: CPPFLAGS += -pg
profiling: clean all
	@printf "\e[0m------------------------------\e[0m\n"
	./$(NAME) $(arg)
	@printf "\e[0m------------------------------\e[0m\n"
	gprof $(NAME) gmon.out

compilation_database: clean
	bear -- make

code_analyse: compilation_database
	clang-tidy -header-filter=.* --use-color $(SRC)

.PHONY: all clean fclean re unit_tests tests_run gcovr \
	debug profiling compilation_database code_analyse
