# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/23 12:31:27 by cchaumar          #+#    #+#              #
#    Updated: 2016/10/23 17:46:25 by cchaumar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = fractol
CFLG   = -O3 -march=native -Wextra -Wall -Werror -Ofast
FILES  = main.c opencl.c terminate.c hook.c draw.c eve.c \
		 buddha.c color.c vect.c vect_calc.c vect2.c mat.c cam.c boxes.c \
		 objs.c hook2.c draw_items.c draw_boxes.c mouse_funcs.c
SRCD   = srcs/
OBJD   = objs/
SRCS   = $(addprefix $(SRCD),$(FILES))
OBJS   = $(addprefix $(OBJD),$(FILES:.c=.o))
INC    = -Iincludes/ -Imlx/ -Ilibft -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/System/Library/Frameworks/Tk.framework/Versions/Current/Headers
HEAD   = includes/fractol.h includes/defines.h
all : $(NAME)

$(OBJD)%.o:$(SRCD)%.c ${HEAD}
	@echo ".\c"
	@gcc $(CFLG) $(INC) -c -o $@ $<

libs:
	make -C libft re
	make -C mlx re

$(NAME): $(OBJS)
		@echo "\n"
		gcc $(CFLG) -o $(NAME) $(INC) $(OBJS) -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework Appkit -framework OpenCL

nolib:
		gcc $(CFLG) -o $(NAME) $(INC) $(SRCS) -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework Appkit -framework OpenCL

clean:
		rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all
