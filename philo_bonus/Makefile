# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpeggie <tpeggie@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 20:12:12 by tpeggie           #+#    #+#              #
#    Updated: 2022/07/06 20:12:15 by tpeggie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRCS =  philo.c run_philo.c utils1.c utils2.c

OBJS =  $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

CC = cc

all: $(NAME)

 $(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJS): philo_bonus.h Makefile

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
