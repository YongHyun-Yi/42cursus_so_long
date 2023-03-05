

CC = cc

CFLAGS = -Wall -Wextra -I./includes -I./libft/includes #-Werror -Iincludes -Ilibft/includes

RM = rm -rf

LIBFT_A = libft/libft.a

MLX_A = minilibx-linux/libmlx.a

NAME = so_long

#-------------------------------------------

MANDATORY_SRCS = tutorial.c
MANDATORY_OBJS = $(MANDATORY_SRCS:.c=.o)

#-------------------------------------------

BONUS_SRCS = $()
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

#-------------------------------------------

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Iminilibx-linux -O3 -c $< -o $@

$(NAME): $(LIBFT_A) $(MLX_A) $(MANDATORY_OBJS)
		$(CC) $(CFLAGS) $^ -L./libft -lft -L./minilibx-linux -lmlx -L/usr/lib -I./minilibx-linux -lXext -lX11 -lm -lz -o $@

$(LIBFT_A):
		make -C ./libft

$(MLX_A):
		make -C ./minilibx-linux

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT_A) $(BONUS_OBJS)
		$(CC) $(CFLAGS) -L./libft -lft $^ -o $@

clean:
		cd libft; make clean
		cd minilibx-linux; make clean
		$(RM) ${MANDATORY_OBJS} ${BONUS_OBJS}

fclean:
		cd libft; make fclean
		make clean
		$(RM) $(NAME) $(BONUS_NAME)

re:
		make fclean
		make all