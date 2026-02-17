# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: migusant <migusant@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 18:13:33 by migusant          #+#    #+#              #
#    Updated: 2025/11/06 16:54:14 by migusant         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                PROJECT SETTINGS                              #
# **************************************************************************** #

NAME = libft.a

# **************************************************************************** #
#                                COMPILER SETTINGS                             #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

# **************************************************************************** #
#                               DIRECTORY STRUCTURE                            #
# **************************************************************************** #

CFILES_DIR = sources/
OFILES_DIR = objects/

CHARS_DIR = $(CFILES_DIR)chars/
CONVERTERS_DIR = $(CFILES_DIR)converters/
GETNEXTLINE_DIR = $(CFILES_DIR)getnextline/
LISTS_DIR = $(CFILES_DIR)lists/
MEMORY_DIR = $(CFILES_DIR)memory/
PRINTF_DIR = $(CFILES_DIR)printf/
STRINGS_DIR = $(CFILES_DIR)strings/

# **************************************************************************** #
#                                    COLORS                                    #
# **************************************************************************** #

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RESET = \033[0m

# **************************************************************************** #
#                                SOURCE FILES                                  #
# **************************************************************************** #

CHARS = $(CHARS_DIR)ft_isalnum.c $(CHARS_DIR)ft_isalpha.c $(CHARS_DIR)ft_isascii.c \
        $(CHARS_DIR)ft_isdigit.c $(CHARS_DIR)ft_isprint.c $(CHARS_DIR)ft_putchar_fd.c

CONVERTERS = $(CONVERTERS_DIR)ft_atoi.c $(CONVERTERS_DIR)ft_itoa.c \
            $(CONVERTERS_DIR)ft_tolower.c $(CONVERTERS_DIR)ft_toupper.c

GETNEXTLINE = $(GETNEXTLINE_DIR)get_next_line.c $(GETNEXTLINE_DIR)get_next_line_utils.c \
              $(GETNEXTLINE_DIR)get_next_line_bonus.c

LISTS = $(LISTS_DIR)ft_lstadd_back.c $(LISTS_DIR)ft_lstadd_front.c \
        $(LISTS_DIR)ft_lstclear.c $(LISTS_DIR)ft_lstdelone.c $(LISTS_DIR)ft_lstiter.c \
        $(LISTS_DIR)ft_lstlast.c $(LISTS_DIR)ft_lstmap.c $(LISTS_DIR)ft_lstnew.c \
        $(LISTS_DIR)ft_lstsize.c

MEMORY = $(MEMORY_DIR)ft_bzero.c $(MEMORY_DIR)ft_calloc.c $(MEMORY_DIR)ft_memchr.c \
         $(MEMORY_DIR)ft_memcmp.c $(MEMORY_DIR)ft_memcpy.c $(MEMORY_DIR)ft_memmove.c \
         $(MEMORY_DIR)ft_memset.c

PRINTF = $(PRINTF_DIR)ft_printf.c $(PRINTF_DIR)ft_printf_utils.c

STRINGS = $(STRINGS_DIR)ft_putendl_fd.c $(STRINGS_DIR)ft_putnbr_fd.c \
          $(STRINGS_DIR)ft_putstr_fd.c $(STRINGS_DIR)ft_split.c \
          $(STRINGS_DIR)ft_strchr.c $(STRINGS_DIR)ft_strdup.c \
          $(STRINGS_DIR)ft_striteri.c $(STRINGS_DIR)ft_strjoin.c \
          $(STRINGS_DIR)ft_strlcat.c $(STRINGS_DIR)ft_strlcpy.c \
          $(STRINGS_DIR)ft_strlen.c $(STRINGS_DIR)ft_strmapi.c \
          $(STRINGS_DIR)ft_strncmp.c $(STRINGS_DIR)ft_strnstr.c \
          $(STRINGS_DIR)ft_strrchr.c $(STRINGS_DIR)ft_strtrim.c \
          $(STRINGS_DIR)ft_substr.c

CFILES = $(CHARS) $(CONVERTERS) $(GETNEXTLINE) $(LISTS) \
         $(MEMORY) $(PRINTF) $(STRINGS)

OFILES = $(addprefix $(OFILES_DIR), $(CFILES:$(CFILES_DIR)%.c=%.o))

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OFILES)
	@$(AR) $(NAME) $(OFILES)
	@echo "$(GREEN)Library $(NAME) successfully created!$(RESET)"

$(OFILES_DIR)%.o: $(CFILES_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling: $<$(RESET)"
	@$(CC) -c $(CFLAGS) -I ./includes $< -o $@

# **************************************************************************** #
#                                CLEANING RULES                                #
# **************************************************************************** #

clean:
	@if [ -d "$(OFILES_DIR)" ]; then \
		$(RM) -r $(OFILES_DIR); \
		echo "$(RED)Object files have been cleaned!$(RESET)"; \
		echo "$(YELLOW)└── Removed directory: libft/$(OFILES_DIR)$(RESET)"; \
	else \
		echo "$(BLUE)Nothing to clean - object files don't exist.$(RESET)"; \
	fi

fclean: 
	@if [ -d "$(OFILES_DIR)" ] || [ -f "$(NAME)" ]; then \
		if [ -d "$(OFILES_DIR)" ]; then \
			$(RM) -r $(OFILES_DIR); \
			echo "$(RED)Object files have been cleaned!$(RESET)"; \
			echo "$(YELLOW)└── Removed directory: libft/$(OFILES_DIR)$(RESET)"; \
		fi; \
		if [ -f "$(NAME)" ]; then \
			$(RM) $(NAME); \
			echo "$(RED)Everything has been cleaned!$(RESET)"; \
			echo "$(YELLOW)└── Removed library: $(NAME)$(RESET)"; \
		fi; \
	else \
		echo "$(BLUE)Nothing to clean - no generated files exist.$(RESET)"; \
	fi

re: fclean all

.PHONY: all clean fclean re