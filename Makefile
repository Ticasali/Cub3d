# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dderny <dderny@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/25 01:28:43 by ticasali          #+#    #+#              #
#    Updated: 2025/05/12 12:59:39 by dderny           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				cub3D

DIR_SRCS =			src

SRCS =				$(DIR_SRCS)/vec3d/add.c 				\
				$(DIR_SRCS)/vec3d/cross.c 				\
				$(DIR_SRCS)/vec3d/dist.c 				\
				$(DIR_SRCS)/vec3d/sqrdist.c 				\
				$(DIR_SRCS)/vec3d/dist.c 				\
				$(DIR_SRCS)/vec3d/div.c 				\
				$(DIR_SRCS)/vec3d/dot.c 				\
				$(DIR_SRCS)/vec3d/normalize.c 				\
				$(DIR_SRCS)/vec3d/rotate.c 				\
				$(DIR_SRCS)/vec3d/equal.c 				\
				$(DIR_SRCS)/vec3d/iszero.c 				\
				$(DIR_SRCS)/vec3d/len.c 				\
				$(DIR_SRCS)/vec3d/lerp.c 				\
				$(DIR_SRCS)/vec3d/mul.c 				\
				$(DIR_SRCS)/vec3d/reflect.c 				\
				$(DIR_SRCS)/vec3d/scale.c 				\
				$(DIR_SRCS)/vec3d/slerp.c 				\
				$(DIR_SRCS)/vec3d/sqrlen.c 				\
				$(DIR_SRCS)/vec3d/sub.c 				\
				$(DIR_SRCS)/cub3d.c 				\
				$(DIR_SRCS)/draw.c 				\
				$(DIR_SRCS)/plan.c 				\
				$(DIR_SRCS)/tick.c 				\

DIR_OBJS =			.objs

OBJS =				$(SRCS:$(DIR_SRCS)/%.c=$(DIR_OBJS)/%.o)
DEPS = 				$(SRCS:$(DIR_SRCS)/%.c=$(DIR_OBJS)/%.d)

-include $(DEPS)

CFLAGS =			-Wall -Wextra -Werror -MMD -march=native -O3 -ffast-math -ffinite-math-only -fPIE -g3 -I./include -I./libft/headers -Iminilibx-linux
LIBS =				-L./libft -lft -L./minilibx-linux -lmlx -lXext -lX11 -lm -lz

all:				libs
					$(MAKE) -j $(nproc) $(NAME)

libs:
					@$(MAKE) -C libft debug
					@$(MAKE) -C minilibx-linux

$(DIR_OBJS)/%.o:	$(DIR_SRCS)/%.c
					@mkdir -p $(dir $@)
					$(CC) $(CFLAGS) -c $< -o $@

#$(DIR_OBJS)/%.i.c:	$(DIR_SRCS)/%.c
#					@mkdir -p $(dir $@)
#					gpp -n -U "" "" "(" "," ")" "(" ")" "@" "" -M "\n//@\w" "\n" " " " " "\n" "" "" +s "\"" "\"" "\\" +s "'" "'" "\\" -m --nostdinc $< > $@

$(NAME):			$(OBJS) libft/libft.a minilibx-linux/libmlx.a
					$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
					$(MAKE) -C libft clean
					$(MAKE) -C minilibx-linux clean
					$(RM) -r $(DIR_OBJS)

fclean:				clean
					$(MAKE) -C libft fclean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re exec libft

.DEFAULT_GOAL = all

