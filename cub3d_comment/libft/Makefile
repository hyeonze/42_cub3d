# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By:      <                  >                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/30 14:15:24 by                   #+#    #+#              #
#    Updated: 2021/02/10 17:43:00 by                  ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c \
ft_only_digit.c \
ft_bzero.c \
ft_isalnum.c \
ft_isalpha.c \
ft_isascii.c \
ft_isdigit.c \
ft_isprint.c \
ft_memccpy.c \
ft_memchr.c \
ft_memcmp.c \
ft_memcpy.c \
ft_memmove.c \
ft_memset.c \
ft_strchr.c \
ft_strlcat.c \
ft_strlcpy.c \
ft_strlen.c \
ft_strncmp.c \
ft_strnstr.c \
ft_strrchr.c \
ft_tolower.c \
ft_toupper.c \
ft_strdup.c \
ft_calloc.c \
ft_split.c \
ft_substr.c \
ft_strjoin.c \
ft_strtrim.c \
ft_itoa.c \
ft_strmapi.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_putstr.c

SRCS_B = ft_lstadd_back.c \
ft_lstadd_front.c \
ft_lstclear.c \
ft_lstiter.c \
ft_lstdelone.c \
ft_lstiter.c \
ft_lstlast.c \
ft_lstnew.c \
ft_lstsize.c \
ft_lstmap.c

OBJS = $(SRCS:.c=.o)

OBJS_B = $(SRCS_B:.c=.o)

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -I ./

$(NAME):	$(OBJS)
		ar rc $(NAME) $(OBJS)

all :		$(NAME)

bonus :		$(NAME) $(OBJS_B)
		ar rc $(NAME) $(OBJS_B)

clean :
			$(RM) -f $(OBJS) $(OBJS_B)
			
fclean :	clean
			$(RM) $(NAME) $(bonus)

re :		fclean all

.PHONY : all bonus clean fclean re .c.o
