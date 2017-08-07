NAME = libft.a
CFLG = -Wextra -Wall -Werror -g
SRCS = 	ft_atoi.c \
		ft_bzero.c \
		ft_circular_find.c \
		ft_circular_funcs.c \
		ft_del.c \
		ft_deltab.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isinside.c \
		ft_islower.c \
		ft_isprint.c \
		ft_isupper.c \
		ft_iswhite.c \
		ft_itoa.c \
		ft_itoa_binary.c \
		ft_lstadd.c \
		ft_lstadd_end.c \
		ft_lstdel.c \
		ft_lst_delif.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstsize.c \
		ft_memalloc.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memdel.c \
		ft_memmove.c \
		ft_memset.c \
		ft_print_bits.c \
		ft_putchar.c \
		ft_putchar_fd.c \
		ft_putendl.c \
		ft_putendl_fd.c \
		ft_putnbr.c \
		ft_putnbr_fd.c \
		ft_putstr.c \
		ft_putstr_fd.c \
		ft_strcat.c \
		ft_strchr.c \
		ft_strclr.c \
		ft_strcmp.c \
		ft_strcpy.c \
		ft_strdel.c \
		ft_strdup.c \
		ft_strequ.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strjoinfree.c \
		ft_strlcat.c \
		ft_strlen.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strncat.c \
		ft_strncmp.c \
		ft_strncpy.c \
		ft_strndup.c \
		ft_strnequ.c \
		ft_strnew.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strsplit.c \
		ft_strstr.c \
		ft_strsub.c \
		ft_strtolower.c \
		ft_strtoupper.c \
		ft_strtrim.c \
		ft_tabsize.c \
		ft_tolower.c \
		ft_toupper.c \
		get_next_line.c
OBJS = $(SRCS:.c=.o)
DIRP = printf/objs/
OBJP = casts.o casts2.o funcs.o get.o itoa64.o output.o parse.o printf.o \
	   wchar.o terminate.o
CC   = gcc

all : $(NAME)

verbose:
	@printf "\n   \033[0;32mCompiling sources : \033[0;0m"

%.o: %.c
		@$(CC) $(CFLG) -c -o $@ $<
		@printf "\033[0;32m.\033[0;0m"

$(NAME): verbose $(OBJS)
		@make -C printf
		@echo " \033[0;35mDone !\n   \033[0;32mLinking ...\c\033[0;0m"
		@ar rc $(NAME) $(OBJS) $(addprefix $(DIRP),$(OBJP))
		@echo " \033[0;35mDone !"
		@echo "   \033[0;32mSorting ...\c\033[0;0m"
		@ranlib $(NAME)
		@echo " \033[0;35mDone !\033[0;0m"

link:
		@ar rc $(NAME) $(OBJS) $(addprefix $(DIRP),$(OBJP))

clean:
		@printf "\033[0;31mcleaning libft...\t\t\t\t"
		@rm -f $(OBJS)
		@printf "\033[0;35mDone !\033[0;31m\n"
		@printf "cleaning subdirectory : printf...\t\t"
		@make -C printf clean
		@printf "\033[0;35mDone !\033[0;0m\n"

quietclean:
		@rm -f $(OBJS)

fclean: quietclean
		@rm -f $(NAME)

re: fclean $(OBJS)
	@make -C printf re
	@echo " \033[0;35mDone !\n   \033[0;32mLinking ...\c\033[0;0m"
	@ar rc $(NAME) $(OBJS) $(addprefix $(DIRP),$(OBJP))
	@echo " \033[0;35mDone !"
	@echo "   \033[0;32mSorting ...\c\033[0;0m"
	@ranlib $(NAME)
	@echo " \033[0;35mDone !\033[0;0m"
