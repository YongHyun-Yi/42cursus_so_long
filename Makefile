
#-------------------------------------------

BLACK       =   "\033[0;30m"
GRAY        =   "\033[1;30m"
RED         =   "\033[1;31m"
GREEN       =   "\033[0;32m"
YELLOW      =   "\033[1;33m"
PURPLE      =   "\033[0;35m"
CYAN        =   "\033[1;36m"
WHITE       =   "\033[1;37m"
EOC         =   "\033[0;0m"
LINE_CLEAR  =   "\x1b[1A\x1b[M"

GREEN_BACK	=	"\033[102m"

#-------------------------------------------

CC = cc

CFLAGS = #-Wall -Wextra -Werror

INC = -I./includes -I./libft/includes

RM = rm -rf

LIBFT_A = libft/libft.a

NAME = so_long

#-------------------------------------------

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
	MLX_DIR		:= ./minilibx_mms_20200219
	MLX_A		:= $(MLX_DIR)/libmlx.dylib
	MLX_FLAGS	:= -L$(MLX_DIR) -framework OpenGL -framework AppKit
	EMOJI		:= 🍎
else ifeq ($(UNAME), Linux)
	MLX_DIR		:= ./minilibx-linux
	MLX_A		:= $(MLX_DIR)/libmlx.a
	MLX_FLAGS	:= -L$(MLX_DIR) -lXext -lX11 -lm -lz
	EMOJI		:= 🐧
else
	$(error "This OS ($(UNAME)) not supported")
endif

INC += -I$(MLX_DIR) -I./includes/os_$(UNAME)

#-------------------------------------------

MANDATORY_SRCS = tutorial.c
MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)

#-------------------------------------------

BONUS_SRCS = $()
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

#-------------------------------------------

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -O3 -c $< -o $@
# @echo $(CYAN)"Compile " $< " to " $@$(EOC)

$(NAME): $(LIBFT_A) $(MLX_A) $(MANDATORY_OBJS)
		@$(CC) $(CFLAGS) $^ $(LIBFT_A) $(MLX_A) $(MLX_FLAGS) -o $@
		@echo $(GREEN)"\n==========================================================\n"$(EOC)
		@echo $(YELLOW)"                       SO_LONG DONE"$(EOC)
		@echo $(GREEN)"\n==========================================================\n"$(EOC)
		@echo "Now your program in: "$(YELLOW)$(UNAME)!$(EOC) $(EMOJI)$(EMOJI)$(EMOJI)"...\n";

$(LIBFT_A):
		@make --no-print-directory -C ./libft

$(MLX_A):
		@make --no-print-directory -C $(MLX_DIR)
ifeq ($(UNAME), Darwin)
	install_name_tool -id $(MLX_A) $(MLX_A)
endif

# bonus: $(BONUS_NAME)

# $(BONUS_NAME): $(LIBFT_A) $(BONUS_OBJS)
# 		$(CC) $(CFLAGS) -L./libft -lft $^ -o $@

clean:
		@cd libft; make --no-print-directory clean
		@cd $(MLX_DIR); make --no-print-directory clean
		@$(RM) ${MANDATORY_OBJS} ${BONUS_OBJS}

fclean:
		@cd libft; make --no-print-directory fclean
		@make --no-print-directory clean
		@$(RM) $(NAME) $(BONUS_NAME)
		@echo $(GREEN)"\n==========================================================\n"$(EOC)
		@echo $(YELLOW)"                       SO_LONG FCLEAN"
		@echo $(GREEN)"\n==========================================================\n"$(EOC)

re:
		@make fclean
		@make all
