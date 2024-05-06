##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## Makefile
##

SRC			:=	$(shell find ./ -name "*.cpp")

CPPFLAGS	=	-std=c++20 -Wall -Wextra -O2 \
				-I../include/lib \
				$(ADDITIONAL_FLAGS)

NAME		=	my_cpplib.a

OBJ			=	$(SRC:.cpp=.o)

%.o: %.cpp
	@g++ $(CPPFLAGS) -c $< -o $@ && \
	printf "\e[2m[\e[92mOK\e[0;2m] g++ $(CPPFLAGS) -c $< -o $@\e[0m\n" || \
	printf "\e[2m[\e[1;91mKO\e[0;2m] g++ $(CPPFLAGS) -c $< -o $@\e[0m\n"

$(NAME): $(OBJ)
	@if ar rc -o $(NAME) $(OBJ); then \
		printf "\e[2m[\e[92mLINKING OK\e[0;2m] ar rc -o $(NAME) $(OBJ)\e[0m\n"; \
	else \
		printf "\e[2m[\e[1;91mLINKING KO\e[0;2m] ar rc -o $(NAME) $(OBJ)\e[0m\n"; \
		exit 1; \
	fi

all: $(NAME)

clean:
	@rm -f $(OBJ) $(shell find ./ -name "*.o")
	@printf "\e[2mrm -f $(OBJ)\e[0m\n"
	@rm -f $(shell find ./ -name "*.gcno")
	@rm -f $(shell find ./ -name "*.gcda")
	@rm -f gmon.out

fclean: clean
	@rm -f $(NAME)
	@printf "\e[2mrm -f $(NAME)\e[0m\n"

re: fclean all

.PHONY: all clean fclean re
