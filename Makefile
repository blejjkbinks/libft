# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 14:35:21 by rdomange          #+#    #+#              #
#    Updated: 2025/02/13 20:50:54 by rdomange         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a

#for parent Makefile
#$(MAKE) -C libft
#$(CC) $(OBJ) -Llibft -lft -o $(NAME)

#when changing: CATS, SRC_CATS, libft.h, filename, stdheader

SRC_DIR := ./src/
HDR_DIR := ./inc/
OBJ_DIR := ./obj/
CFLAGS := -Wall -Wextra -Werror -I$(HDR_DIR)
CC := cc $(CFLAGS)
CC_NOFLG := cc
AR := ar rcs
RM := rm -rf
MKD := mkdir -p
CATS := CHR FUN LIST MEM NBR SPLIT STR WRT

MAKEFLAGS += --no-print-directory

SRC_CHR := \
	isalnum		isalpha		isalpha_lower		isalpha_upper \
	isascii		isdigit		isprint		isspace		ishexdg \
	strcapital	strtolower	strtoupper	tolower	toupper \
	strisdigit \

SRC_FUN := \
	printmemory		bit		free	malloc	sort \
	random		test_libft \

SRC_LIST := \
	lstadd_back		lstadd_front	lstclear	lstdelone \
	lstlast			lstcreate_node			lstlen \
	lstindex_at		lstindex_get	lstfind \
	lstsort		lstmerge	lstadd_sort		lstmerge_sort \
	lstremove	lstreverse	lstprint \

SRC_MEM := \
	bzero	calloc	realloc	memchr	memcmp	memcpy	memmove	memset \
	strdup \

SRC_NBR := \
	atoi	atoi_base	itoa	itoa_ulong	itoa_base	atoa_base \
	abs		hexoffset	max		min		mod_range	nbrlen_base \
	numcmp \

SRC_SPLIT := \
	split	split_set	split_free	split_len \
	isquoted	split_quotes	splittrim_quotes	strtrim_quotes \
	isquoted_closed \

SRC_STR := \
	strchr	strrchr	strjoin \
	strlcat	strlcpy	strlen strnlen \
	strncmp	strcmp	strnstr	strtrim	substr \

SRC_WRT := \
	putchar_fd	putendl_fd \
	putnbr_fd	putstr_fd \
	get_next_line	printf \

tolower = $(shell echo '$1' | tr '[:upper:]' '[:lower:]')

$(foreach c, $(CATS), \
	$(foreach i, $(SRC_$(c)), \
		$(eval SRC += $(SRC_DIR)$(call tolower,$(c))/ft_$(i).c)))

OBJ := $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

all: $(NAME)

$(OBJ_DIR):
	@$(MKD) $(foreach c, $(CATS), $@/$(call tolower,$(c)))

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -c $< -o $@
	@printf "%s " $(notdir $@) | sed 's/^ft_//'

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo $(NAME)

clean: testclean
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@echo "libft fcleaning"

re: fclean all

## funny rules  ##

countfiles: all testclean
	@printf "norminette KOs: "
	@norminette | grep Error! | wc -l
	@printf "src: "
	@tree $(SRC_DIR) | grep files
	@printf "obj: "
	@tree $(OBJ_DIR) | grep files
	@$(MAKE) fclean

gitstat: fclean
	find . -name '.DS_Store' -type f -delete
	git status

m := pushed from libft makefile on $(shell date +"%d/%m %H:%M")
GIT_PUSH_MESSAGE := $(m)

gitpush: gitstat
	git add .
	git commit -m "$(GIT_PUSH_MESSAGE)"
	git push

SOURCE_TXT := libft_source.txt
source_txt:
	@> $(SOURCE_TXT)
	@for file in $(SRC); do \
		echo $$file >> $(SOURCE_TXT); \
		tail -n +14 $$file >> $(SOURCE_TXT); \
	done
	@mv $(SOURCE_TXT) ~/Desktop/$(SOURCE_TXT)
	@echo ok its on your desktop

## test rules  ##

TEST_A := a.test
TEST_C := test.c
TEST_T := .test.txt

testclean:
	@$(RM) $(TEST_C)
	@$(RM) $(TEST_A)
	@$(RM) $(TEST_A).dSYM

$(TEST_C):
	cp $(TEST_T) $(TEST_C)

test: all $(TEST_C)
	$(CC) -g $(TEST_C) $(NAME) -o $(TEST_A)
	@echo "letsgo :)\nvvvvv"
	./$(TEST_A) | cat -e
	@printf "###\n^^^^^\ndone :)\n"

.PHONY: all clean fclean bonus \
	test testclean countfiles \
	gitstat gitpush source_txt
