# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paure <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/27 11:53:11 by paure             #+#    #+#              #
#    Updated: 2021/01/27 11:53:12 by paure            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

CC = gcc

SOURCES = main.c \
		  utils.c \
		  philo_three.c \
		  actions.c \
		  manage_forks.c \
		  clear.c \
		  init.c \
		  eat.c \
		  libft.c \
		  libft2.c


NAME = philo_three

UNAME_S := $(shell uname -s)
 
 ifeq ($(UNAME_S), Linux)
	 	     CFLAGS += -lpthread
	 	     CC = clang
 else ifeq ($(UNAME_S), Darwin)
	 	     CC = gcc

endif

CFLAGS = -Wall -Wextra -Werror

DIR_S = sources

HD = includes/philo_three.h

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))

OBJS = $(addprefix $(DIR_S)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(HD)
	@$(CC) $(OBJS) -I $(HD) $(CFLAGS) -o $(NAME)
	@echo "philo_three executable ready !"
	
clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re  