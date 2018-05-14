NAME = avm

SRC = main.cpp Check.cpp CommandException.cpp ExceptionRead.cpp FactoryMethod.cpp LexerExpextion.cpp ParserExpextion.cpp TypeAnalysis.cpp

OBJ = $(SRC:.cpp=.o)

CFLAGS = -std=c++11 -Wall -Wextra -Werror

CC = clang++

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all