# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpeggie <tpeggie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 21:37:50 by tpeggie           #+#    #+#              #
#    Updated: 2022/07/06 20:11:16 by tpeggie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = philo.c utils1.c utils2.c initialization.c run_philo.c

OBJS =  $(SRCS:.c=.o)

HEADER = philo.h

CFLAGS = -Wall -Wextra -Werror

CC = cc

all: $(NAME)

 $(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): philo.h Makefile

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
