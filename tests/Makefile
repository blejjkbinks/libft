NAME := libft_tests
LIBFT_DIR := ..
LIBFT := $(LIBFT_DIR)/libft.a

SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)

CC := cc
CFLAGS := -Wall -Wextra -Werror -I$(LIBFT_DIR)/inc -I.

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

test: all
	./$(NAME)

.PHONY: all clean fclean re test
