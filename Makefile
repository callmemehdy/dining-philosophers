NAME	=	philosophers

CFL		=	-Wall -Wextra -Werror

SRC_DIR =	SRCS/

OBJ_DIR	= 	OBJS_DEPS/

SRCS_FS	=	main.c utils_1.c philo_cr.c simulation.c

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
