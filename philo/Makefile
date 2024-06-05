# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asuc <asuc@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/12 17:42:16 by asuc              #+#    #+#              #
#    Updated: 2024/06/05 16:49:22 by asuc             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BGreen		=	\033[1;32m
RESET		=	\033[0m
BRed		=	\033[1;31m
BCyan		=	\033[1;36m
Green		=	\033[0;32m
NAME		=	philo
COMP		=	cc
CFLAGS		=	-Wall -Werror -Wextra -gdwarf-2 -g3
SRC			=	philo.c\
				main.c \
				init.c \
				parsing.c \
				utils.c \
				monitor.c \
				ft_strlen.c

OBJ = $(SRC:.c=.o)

TOTAL = $(words $(OBJ))
CURR = 0

define update_progress
  $(eval CURR=$(shell echo $$(($(CURR)+1))))
  @echo -n "\033[1A\033[K"
  @echo -n "$(Green)[`echo "scale=2; $(CURR)/$(TOTAL)*100" | bc`%] Compiling $< \n$(RESET)"
endef

all : $(NAME)

%.o : %.c
	@if [ $(CURR) -eq 0 ]; then \
		echo "\n$(BCyan)Compiling object files for $(NAME)...$(RESET)\n"; \
	fi
	@$(COMP) $(CFLAGS) -o $@ -c $<
	@$(call update_progress)

start :
	@echo "$(BCyan)Compilation Start$(NAME)$(RESET)\n\n"

$(NAME) : $(OBJ)
	@$(COMP) $(CFLAGS) -o $(NAME) $(OBJ) 
	@echo "\n$(BGreen)Compilation Final $(NAME)$(RESET)"

clean :
	@rm -f $(OBJ)
	@echo "$(BRed)Erase all .o files$(RESET)"

fclean : clean
	@rm -f $(NAME)
	@echo "$(BRed)Erase $(NAME)$(RESET)"

re : fclean all

.PHONY: all fclean clean re


