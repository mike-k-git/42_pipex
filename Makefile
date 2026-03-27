MAKEFLAGS += --no-print-directory

CC       = cc
CFLAGS   = -Wall -Wextra -Werror -MMD -MP
INCLUDES = -I./42_libft         \
		   -I./42_ft_printf     \
		   -I./42_get_next_line

BLUE   = \033[34m
GREEN  = \033[32m
CYAN   = \033[36m
YELLOW = \033[33m
RESET  = \033[0m

NAME = pipex

SRC = main.c   \
	  io.c     \
	  env.c    \
	  error.c  \
	  utils.c  \
	  fork.c   \
	  exec.c   \
	  expand.c

SRC_BONUS = main_bonus.c       \
			io_bonus.c         \
			io_bonus_2.c       \
			env_bonus.c        \
			error_bonus.c      \
			utils_bonus.c      \
			exec_bonus.c       \
			pipe_utils_bonus.c \
			run_bonus.c        \
			rnd_bonus.c        \
			expand.c

OBJ_DIR = obj

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
DEP = $(OBJ:.o=.d)

OBJ_BONUS = $(SRC_BONUS:%.c=$(OBJ_DIR)/%.o)
DEP_BONUS = $(OBJ_BONUS:.o=.d)

LIBFTDIR = ./42_libft
LIBFT    = $(LIBFTDIR)/libft.a

LIBFTPRINTFDIR = ./42_ft_printf
LIBFTPRINTF    = $(LIBFTPRINTFDIR)/libftprintf.a

LIBGNLDIR = ./42_get_next_line
LIBGNL    = $(LIBFTPRINTFDIR)/libgnl.a

all: $(NAME)

$(LIBFT):
	@$(MAKE) -s -C $(LIBFTDIR)

$(LIBFTPRINTF):
	@$(MAKE) -s -C $(LIBFTPRINTFDIR)

$(LIBGNL):
	@$(MAKE) -s -C $(LIBGNLDIR)

$(NAME): $(LIBFT) $(LIBFTPRINTF) $(OBJ) .mandatory
	@echo "Linking $(CYAN)$@ (MANDATORY)$(RESET)."
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFTDIR) -L$(LIBFTPRINTFDIR) -lftprintf -lft -o $@

.mandatory:
	@touch .mandatory
	@rm -f .bonus

bonus: $(LIBFT) $(LIBFTPRINTF) $(LIBGNL) .bonus

.bonus: $(OBJ_BONUS)
	@echo "Linking $(CYAN)$(NAME) (BONUS)$(RESET)."
	@$(CC) $(CFLAGS) $(OBJ_BONUS) -L$(LIBFTDIR) -L$(LIBFTPRINTFDIR) -L$(LIBGNLDIR) -lftprintf -lgnl -lft -o $(NAME)
	@touch .bonus
	@rm -f .mandatory

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "Compiling $(CYAN)$<$(RESET)."
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	@echo "Cleaning $(YELLOW)$(NAME)$(RESET) object files."
	@rm -f $(OBJ) $(OBJ_BONUS)
	@$(MAKE) clean -s -C $(LIBFTDIR)
	@$(MAKE) clean -s -C $(LIBFTPRINTFDIR)
	@$(MAKE) clean -s -C $(LIBGNLDIR)

fclean:
	@echo "Cleaning $(YELLOW)$(NAME)$(RESET) object files."
	@rm -rf $(OBJ_DIR)
	@echo "Removing the $(YELLOW)$(NAME)$(RESET) binary."
	@rm -f $(NAME) .bonus .mandatory
	@$(MAKE) fclean -s -C $(LIBFTDIR)
	@$(MAKE) fclean -s -C $(LIBFTPRINTFDIR)
	@$(MAKE) fclean -s -C $(LIBGNLDIR)

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)
