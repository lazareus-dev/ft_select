# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: tle-coza <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/04/23 19:11:16 by tle-coza     #+#   ##    ##    #+#        #
#    Updated: 2018/07/01 14:47:59 by tle-coza    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME        =   ft_select

FLAGS		= 	#-Wall -Wextra -Werror -O3

FILENAMES   =   main.c sel_lst.c sel_select.c sel_display.c sel_signal.c \
				sel_refresh.c sel_loop.c sel_error.c sel_utils.c sel_move.c

SOURCES     =   $(addprefix srcs/, $(FILENAMES))

OBJECTS     =   $(SOURCES:.c=.o)

L_FT        =   ./libft

LIB_LNK     =   -L $(L_FT) -l ft

LIB_INC     =   -I $(L_FT)/libft.h

CC			=	gcc

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJECTS)
	    @$(MAKE) -C $(L_FT)
		$(CC) -I ./includes $(OBJECTS) -ltermcap $(LIB_LNK) -o $@

%.o: ./%.c
	    $(CC) $(FLAGS) $(LIB_INC) -I ./includes -c $< -o $@

clean:
#		@$(MAKE) -C $(L_FT) clean
		rm -rf $(OBJECTS)

fclean: clean
		rm -rf $(NAME)
#		@$(MAKE) -C $(L_FT) fclean

re:
	    @$(MAKE) fclean
		@$(MAKE) all
