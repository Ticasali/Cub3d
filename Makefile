# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 01:28:43 by ticasali          #+#    #+#              #
#    Updated: 2025/05/08 15:12:17 by dderny           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				cub3D

DIR_SRCS =			src

SRCS =				$(DIR_SRCS)/main.c 				\

DIR_OBJS =			.objs

OBJS =				$(SRCS:$(DIR_SRCS)/%.c=$(DIR_OBJS)/%.o)
DEPS = 				$(SRCS:$(DIR_SRCS)/%.c=$(DIR_OBJS)/%.d)

-include $(DEPS)

CFLAGS =			-Wall -Wextra -Werror -MMD -g3 -I./include -I./libft/headers
LIBS =				-L./libft -lft -lreadline

all:				libft
					$(MAKE) -j $(nproc) $(NAME)

libft:
					@$(MAKE) -C libft debug

$(DIR_OBJS)/%.o:	$(DIR_SRCS)/%.c
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@

#$(DIR_OBJS)/%.i.c:	$(DIR_SRCS)/%.c
#					@mkdir -p $(dir $@)
#					gpp -n -U "" "" "(" "," ")" "(" ")" "@" "" -M "\n//@\w" "\n" " " " " "\n" "" "" +s "\"" "\"" "\\" +s "'" "'" "\\" -m --nostdinc $< > $@

$(NAME):			$(OBJS) libft/libft.a
					$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
					$(MAKE) -C libft clean
					$(RM) -r $(DIR_OBJS)

fclean:				clean
					$(MAKE) -C libft fclean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re exec libft

.DEFAULT_GOAL = all

