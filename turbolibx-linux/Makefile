STATE_FILE := .state.tmp
NAME = turbolibx.a
CC = cc
AR = ar -rcs

DIR_OBJ = obj/
SRC_DIR = src/
INC_DIR = headers/

ADDFLAGS =
CFLAGS = -Wall -Wextra -Werror -MMD -O3 -mavx2 -I../minilibx-linux -I../libft/headers $(ADDFLAGS) -I $(INC_DIR)
LIBS =	-L../libft -lft -lXext -L../minilibx-linux -lX11 -lm -lz
SRCS =	test.c

DIR_OBJ = obj/
OBJS = ${patsubst %.c,$(DIR_OBJ)%.o, $(SRCS)}

DEPS= ${patsubst %.c,$(DIR_OBJ)%.d, $(SRCS_ALL)}
-include $(DEPS)

# Colors for output
GREEN  := \033[1;32m
BLUE   := \033[1;34m
YELLOW := \033[1;33m
RED    := \033[1;31m
RESET  := \033[0m
ECHO   := /bin/echo

.PHONY: all
all: check_build
	$(MAKE) -j$(shell nproc) --no-print-directory $(NAME)
	@STATE=$$(cat $(STATE_FILE) 2>/dev/null || echo 0); \
	if [ $$STATE -eq 1 ]; then \
		$(ECHO) -e "$(BLUE)[✓] Turbolibx is up to date!$(RESET)"; \
	else \
		$(ECHO) -e "$(GREEN)[✓] Turbolibx build completed!$(RESET)"; \
	fi

# Check if recompilation is needed
.PHONY: check_build
check_build:
	@$(ECHO) "0" > $(STATE_FILE);
	@if [ -z "$(wildcard $(OBJS))" ] || [ Makefile -nt $(NAME) ]; then \
		$(ECHO) -e "$(YELLOW)[Building turbolibx]$(RESET)"; \
		$(ECHO) "0" > $(STATE_FILE); \
	elif ! find $(SRC_DIR) -type f -name '*.c' -newer $(NAME) | grep -q . && \
		! find $(INC_DIR) -type f -name '*.h' -newer $(NAME) | grep -q .; then \
		$(ECHO) "1" > $(STATE_FILE); \
	fi

.PHONY: debug
debug:
	$(MAKE) -j$(shell nproc) --no-print-directory ADDFLAGS="-D DEBUG=1 -g3" $(NAME)

.PHONY: libs
libs:
	$(MAKE) -C ../libft
	$(MAKE) -C ../minilibx-linux

test: libs ../libft/libft.a ../minilibx-linux/libmlx.a bin

bin: ADDFLAGS="-D DEBUG=1 -g3"
bin: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%/:
	mkdir -p $@

$(DIR_OBJ)%.o: $(SRC_DIR)%.c
	@$(ECHO) -e "\t$(YELLOW)Compiling $*.c$(RESET)"
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(DIR_OBJ) $(OBJS) Makefile
	$(AR) $@ $(OBJS)
	ranlib $(NAME)

.PHONY: clean
clean:
	rm -f $(STATE_FILE)
	rm -Rf $(DIR_OBJ)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re:
	$(MAKE) fclean
	$(MAKE) all

.DEFAULT_GOAL = all
