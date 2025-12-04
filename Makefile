# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/27 18:01:31 by amtan             #+#    #+#              #
#    Updated: 2025/12/04 18:03:38 by amtan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= libftprintf.a

CC					= cc
CFLAGS				= -Wall -Wextra -Werror

AR					= ar
ARFLAGS				= rcs

RM					= rm -f

HDRS				= ft_printf.h

SRCS				= ft_printf.c print_char.c print_str.c print_unsigned_base.c print_signed_base.c print_pointer.c

OBJS				= $(SRCS:.c=.o)

BONUS_SRCS			= 

BONUS_OBJS			= $(BONUS_SRCS:.c=.o)

ifeq ($(BONUS), 1)
ALL_OBJS    		= $(OBJS) $(BONUS_OBJS)
else
ALL_OBJS    		= $(OBJS)
endif

all					: $(NAME)

$(NAME)				: $(ALL_OBJS)
						$(AR) $(ARFLAGS) $@ $^

bonus				:
						$(MAKE) BONUS=1 $(NAME)

%.o					: %.c $(HDRS)
						$(CC) $(CFLAGS) -c $< -o $@

clean				:
						$(RM) $(OBJS) $(BONUS_OBJS)

fclean				: clean
						$(RM) $(NAME)

re					: fclean all

.PHONY				: all bonus clean fclean re