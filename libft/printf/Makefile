# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/23 12:31:27 by cchaumar          #+#    #+#              #
#    Updated: 2016/10/23 07:19:46 by cchaumar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = libftprintf.a
CFLG   =  -Wextra -Wall -Werror -Ofast -g
FILES  = printf.c funcs.c parse.c output.c casts.c get.c itoa64.c wchar.c \
		 casts2.c terminate.c
SRCD   = srcs/
OBJD   = objs/
GITLIB = 'https://github.com\/sethquantix/libft.git'
SRCS   = $(addprefix $(SRCD),$(FILES))
OBJS   = $(addprefix $(OBJD),$(FILES:.c=.o))
LIBD   = ../
LIBF   = ft_atoi.c ft_bzero.c ft_isdigit.c ft_iswhite.c ft_isinside.c ft_memalloc.c \
		 ft_memcpy.c ft_memdel.c ft_memset.c ft_print_bits.c ft_putchar.c \
		 ft_putchar_fd.c ft_strchr.c ft_strdup.c ft_strjoinfree.c ft_strlen.c \
		 ft_strncmp.c ft_strndup.c ft_toupper.c ft_islower.c
LIBS   = $(addprefix $(LIBD), $(LIBF))
LIBO   = $(addprefix $(LIBD), $(LIBF:.c=.o))
HEAD   = includes/printf.h includes/defines.h includes/parse.h
INC    = -Iincludes -Ilibft

.PHONY : all clean

all : $(NAME)

$(OBJD)%.o: $(SRCD)%.c ${HEAD}
	@mkdir -p objs
	gcc $(CFLG) $(INC) -c -o $@ $<

$(LIBD)%.o: $(LIBD)%.c
	gcc $(CFLG) -c -o $@ $<

$(NAME): $(OBJS) $(LIBO)
		test -f $(NAME) || ar rc $(NAME) $(OBJS) $(LIBO)
		test -f $(NAME) || ranlib $(NAME)

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all
