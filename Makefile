##
## EPITECH PROJECT, 2024
## gomoku
## File description:
## Makefile
##

SRC_MAIN	=	Main.cpp

SRC			=	Core.cpp				\
				GameBoard.cpp			\
				PatternMatching.cpp		\
				MiniMax.cpp

OBJ_MAIN 	= $(addprefix src/, $(SRC_MAIN:.cpp=.o))

OBJ 		= $(addprefix src/, $(SRC:.cpp=.o))

%.o:	%.cpp
	g++ -c -o $@ -I./include $<

NAME = pbrain-gomoku-ai

FLAGS = -Wall -Wextra

DEBUG_FLAGS = -g3

$(NAME): $(OBJ_MAIN) $(OBJ)
	g++ -o $(NAME) $(OBJ_MAIN) $(OBJ) -std=c++20 $(FLAGS)

all: $(NAME)

clean:
	rm -f $(OBJ_MAIN)
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug: $(OBJ_MAIN) $(OBJ)
	g++ -o $(NAME) $(OBJ_MAIN) $(OBJ) -std=c++20 $(FLAGS) $(DEBUG_FLAGS)

.PHONY: all clean fclean
