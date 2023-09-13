# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paulo <paulo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 15:43:01 by paulo             #+#    #+#              #
#    Updated: 2023/09/13 15:50:22 by paulo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# atualizar cabeçalho

NAME = philo
SRC_DIR = src
OBJ_DIR = objs

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/checks.c \
		$(SRC_DIR)/exit.c

OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

CC = clang
HEAD = -I./includes
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
LFLAGS = -pthread
RM = /bin/rm -rf

all: $(NAME)

$(NAME): $(OBJ)
		@$(CC) $(OBJ) $(HEAD) $(CFLAGS) $(LFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(CFLAGS) $(HEAD) -c $< -o $@
		@echo "\033[0;32m[OK]\033[0m    \033[0;38;5;199mCompiling\033[0m $(<F)"

clean:
		@$(RM) $(OBJ_DIR)
		@echo "\033[0;32m[OK]\033[0m    \033[0;38;5;44mRemoving objects\033[0m"

fclean: clean
		@$(RM) $(NAME)
		@echo "\033[0;32m[OK]\033[0m    \033[0;38;5;44mRemoving philo\033[0m"

re: fclean all

norm:
	norminette | grep -v "OK" || true

.PONY: all clean fclean re