# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/27 18:01:31 by amtan             #+#    #+#              #
#    Updated: 2025/12/09 10:10:23 by amtan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= libftprintf.a

CC					= cc
CFLAGS				= -Wall -Wextra -Werror

AR					= ar
ARFLAGS				= rcs

RM					= rm -f

HDRS				= ft_printf.h

SRCS				= ft_printf.c print_char.c print_str.c print_pointer.c \
						print_unsigned_base.c print_signed_base.c

OBJS				= $(SRCS:.c=.o)

all					: $(NAME)

$(NAME)				: $(ALL_OBJS)
						$(AR) $(ARFLAGS) $@ $^

%.o					: %.c $(HDRS)
						$(CC) $(CFLAGS) -c $< -o $@

clean				:
						$(RM) $(OBJS)

fclean				: clean
						$(RM) $(NAME)

re					: fclean all

.PHONY				: all clean fclean re