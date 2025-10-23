# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdomange <romitdomange@gmail.com>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 14:35:21 by rdomange          #+#    #+#              #
#    Updated: 2025/10/23 14:48:06 by rdomange         ###   ########.fr        #
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

MAKEFLAGS += --no-print-directory -s
PRINT_LEVEL := 2

CATS := CHR FUN LIST MEM NBR SPLIT STR WRT

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
	@echo "libft making"
	@$(MKD) $(foreach c, $(CATS), $@/$(call tolower,$(c)))

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(MKD) $(dir $@)
	@$(CC) -c $< -o $@
	@if [ $(PRINT_LEVEL) -eq 0 ]; then \
		:; \
	elif [ $(PRINT_LEVEL) -eq 1 ]; then \
		printf "%s " $(notdir $@) | sed 's/^ft_//'; \
	else \
	t=$$(echo $(OBJ) | wc -w); \
	i=$$(find $(OBJ_DIR) -type f -name '*.o' 2>/dev/null | wc -l); \
	p=$$((100 * i / t)); \
	cat=$(notdir $(patsubst %/,%,$(dir $@))); \
	name=$(subst ft_,,$(basename $(notdir $@))); \
	if [ $(PRINT_LEVEL) -eq 2 ]; then \
		printf "\n\033[A\033[K%3s%% %s" "$$p" ""; \
	elif [ $(PRINT_LEVEL) -eq 3 ]; then \
	spin_sequence='-\|/-+*+'; \
	spin_len=$$(( $$(echo "$$spin_sequence" | wc -c) - 1)); \
	spin_speed=4; \
	spin=$$(echo "$$spin_sequence" | cut -c $$(( (( $$i / $$spin_speed ) % $$spin_len ) + 1 )) ); \
	bar_len=16; \
	bar_full_count=$$(((p * bar_len) / 100)); \
	bar_empty_count=$$((bar_len - bar_full_count)); \
	bar_full=$$(printf '#%.0s' $$(seq 1 $$bar_full_count)); \
	bar_emtpy=""; \
	if [ $$bar_empty_count -gt 0 ]; then \
	bar_empty=$$(printf '_%.0s' $$(seq 1 $$bar_empty_count)); fi; \
	if [ $$i -eq 1 ] && [ $(PRINT_LEVEL) -ge 3 ]; then echo '---'; fi; \
	printf "\n\033[A\033[K\033[A\033[K[%s][%s%s][%s]\n%10s,%s" \
	"$$spin" "$$bar_full" "$$bar_empty" "$$spin" "$$cat" "$$name"; \
	fi; fi

$(NAME): $(OBJ_DIR) $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@if [ $(PRINT_LEVEL) -ge 2 ]; then printf "\n\033[A\033[K"; fi
	@if [ $(PRINT_LEVEL) -eq 3 ]; then printf "\033[A\033[K"; fi
	@echo "$(NAME)"

clean: testclean
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)
	@echo "libft fcleaning"
	@$(MAKE) -C tests fclean
	#@-./ftscript.sh rmlinks

re: fclean all

bonus: all

## test rules  ##

TEST_A := a.test
TEST_C := test.c
TEST_T := .test.txt

testclean:
	@$(RM) $(TEST_C) $(TEST_A) $(TEST_A).dSYM

$(TEST_C):
	cp $(TEST_T) $(TEST_C)

test: all $(TEST_C)
	$(CC) -g $(TEST_C) $(NAME) -o $(TEST_A)
	@echo "letsgo :)\nvvvvv"
	./$(TEST_A) | cat -e
	@printf "###\n^^^^^\ndone :)\n"

tests: all
	$(MAKE) -C tests test

.PHONY: all clean fclean bonus test tests
