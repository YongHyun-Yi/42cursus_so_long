# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yonghyle <yonghyle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 11:29:52 by yonghyle          #+#    #+#              #
#    Updated: 2023/02/15 10:53:42 by yonghyle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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

CFLAGS = -Wall -Wextra -Werror -Iincludes

LIBFT_SRCS = ${addprefix libft_srcs/,\
						 ft_atoi.c \
						 ft_bzero.c \
						 ft_calloc.c \
						 ft_isalnum.c \
						 ft_isalpha.c \
						 ft_isascii.c \
						 ft_isdigit.c \
						 ft_isprint.c \
						 ft_itoa.c \
						 ft_lstadd_back.c \
						 ft_lstadd_front.c \
						 ft_lstclear.c \
						 ft_lstdel_node.c \
						 ft_lstdelone.c \
						 ft_lstiter.c \
						 ft_lstlast.c \
						 ft_lstmap.c \
						 ft_lstnew.c \
						 ft_lstsize.c \
						 ft_memchr.c \
						 ft_memcmp.c \
						 ft_memcpy.c \
						 ft_memmove.c \
						 ft_memset.c \
						 ft_putchar_fd.c \
						 ft_putendl_fd.c \
						 ft_putnbr_fd.c \
						 ft_putstr_fd.c \
						 ft_split.c \
						 ft_strchr.c \
						 ft_strdup.c \
						 ft_striteri.c \
						 ft_strjoin.c \
						 ft_strlcat.c \
						 ft_strlcpy.c \
						 ft_strlen.c \
						 ft_strmapi.c \
						 ft_strncmp.c \
						 ft_strnstr.c \
						 ft_strrchr.c \
						 ft_strtrim.c \
						 ft_substr.c \
						 ft_tolower.c \
						 ft_toupper.c \
						 ft_strisnum.c \
						 ft_strisint.c \
						 ft_check_intdup.c \
}

LIBFT_OBJS = ${LIBFT_SRCS:.c=.o}

FT_PRINTF_SRCS = ${addprefix ft_printf_srcs/,\
							 ft_flags_utils.c \
							 ft_pf_char_fd.c \
							 ft_pf_hex_fd.c \
							 ft_pf_hexlen.c \
							 ft_pf_nbr_nosign_fd.c \
							 ft_pf_nbrlen.c \
							 ft_pf_nchar_fd.c \
							 ft_pf_nstr_fd.c \
							 ft_pf_ptr_fd.c \
							 ft_pf_str_fd.c \
							 ft_print_data_utils.c \
							 ft_printf.c \
}

FT_PRINTF_OBJS = ${FT_PRINTF_SRCS:.c=.o}

GNL_SRCS = ${addprefix gnl_srcs/,\
					   get_next_line.c\
					   get_next_line_utils.c \
}

GNL_OBJS = ${GNL_SRCS:.c=.o}

# 과제별로 폴더를 나누고 그 안에서 소스파일을 관리

ALL_OBJS = ${LIBFT_OBJS} ${FT_PRINTF_OBJS} ${GNL_OBJS}

# 이후 OBJS의 추가 수정을 쉽게 하기위해 변수 하나에 모두 묶어줌

NAME = libft.a

RM = rm -f

all: ${NAME}

${NAME}: ${ALL_OBJS}
		@ar crs ${NAME} ${ALL_OBJS}
		@echo $(GREEN)"\n==========================================================\n"$(EOC)
		@echo $(YELLOW)"                       FT_LIBFT DONE"
		@echo $(GREEN)"\n==========================================================\n"$(EOC)

.c.o:
		@$(CC) $(CFLAGS) -c $< -o $@
# @echo $(CYAN)"Compile " $<$(EOC)

clean:
		@${RM} ${ALL_OBJS}

fclean: clean
		@${RM} ${NAME}
		@echo $(GREEN)"\n==========================================================\n"$(EOC)
		@echo $(YELLOW)"                       FT_LIBFT FCLEAN"
		@echo $(GREEN)"\n==========================================================\n"$(EOC)

re:
		make fclean
		make all

.PHONY: all clean fclean re