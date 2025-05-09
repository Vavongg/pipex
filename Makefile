NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3
PRINTF = ft_printf/printf

SRC = src/main.c src/commands.c  src/paths.c \
	  src/libft/ft_split.c  src/libft/ft_strdup.c src/libft/ft_strjoin.c src/libft/ft_strnstr.c

UTILS = 

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o) \

RESET = \033[0m
BOLD = \033[1m
GREEN = \033[32m
YELLOW = \033[33m
RED = \033[31m
CYAN = \033[36m
BLUE = \033[34m

all: $(OBJ_DIR) $(PRINTF) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)/src
	@echo "$(CYAN)───────────────────────────────$(RESET)"
	@echo "$(BOLD)📁 Création du dossier objet...$(RESET)"
	@echo "$(CYAN)───────────────────────────────$(RESET)"

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(PRINTF) -o $@
	@echo "$(GREEN)✅ Compilation réussie !$(RESET)"
	@echo "$(CYAN)───────────────────────────────$(RESET)"

$(PRINTF):
	@echo "$(BLUE)⚙️  Compilation de ft_printf...$(RESET)"
	@$(MAKE) --no-print-directory -C ft_printf > /dev/null

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)⚙️  Compilation : $<$(RESET)"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) --no-print-directory -C ft_printf clean > /dev/null
	@echo "$(RED) Suppression des fichiers objets terminée.$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C ft_printf fclean > /dev/null
	@echo "$(RED) Suppression de l'exécutable $(NAME).$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
