NAME	=	philo

CFL		=	-Wall -Wextra -Werror

SRC_DIR =	SRCS/

OBJ_DIR	= 	OBJS_DEPS/

<<<<<<< HEAD:philo/Makefile
SRCS_FS	=	main.c utils_1.c philo_cr.c simulation.c\
			monitoring.c utils_2.c
=======
SRCS_FS	=	main.c utils_1.c philo_cr.c simulation.c
>>>>>>> 9792b9b26985609e0ec627499c07b02a289383d0:Makefile

SRCS	= $(addprefix $(SRC_DIR), $(SRCS_FS))

OBJS	= $(addprefix $(OBJ_DIR), $(SRCS_FS:.c=.o))

DEPS	=	$(OBJS:.o=.d)

all:	$(NAME)

-include $(DEPS)

$(NAME):	$(OBJS)
		cc  $(OBJS) -o $@ -fsanitize=thread

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
		mkdir -p $(OBJ_DIR)
		cc -c $(CFL) $< -o $@ -MMD

clean:
		rm -rf $(OBJ_DIR)

fclean:	clean
		rm -rf $(NAME)

re : fclean all

.PHONY: 	clean fclean
