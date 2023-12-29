FILE	= $(shell ls -lR mandatory/src | grep -F .c | wc -l)
CMP		= 1
CLEAR	= @clear

# COLOR #
GREEN	= \033[38;5;76m
RED		= \033[38;5;160m
YELLOW	= \033[38;5;226m
ORANGE	= \033[38;5;202m
PURPLE	= \033[38;5;213m
LBLUE	= \033[38;5;51m
BLUE	= \033[38;5;117m
INDI	= \033[38;5;99m
RESET	= \033[00m

RNBW	= @printf "                                                                     \r$(RED)Phi$(ORANGE)lo$(LBLUE) is$(INDI) re$(PURPLE)ady$(RESET)\n"

NAME		=	philo_bonus

CC			=	cc

CFLAGS		=	-g -pthread -Wall -Wextra -Werror

INCLUDE		=	-I.

SRCS		=	mandatory/src/philo.c			\
				mandatory/src/utils.c			\
				mandatory/src/init.c			\
				mandatory/src/errors.c			\
				mandatory/src/wait_conditions.c	\

OBJS        =    $(addprefix obj/, $(SRCS:.c=.o))
OBJS_DIRS    =    $(sort $(dir $(OBJS))) 

all:			${NAME}
	$(RNBW)

obj/%.o: %.c
	@printf "$(ORANGE)[$(RESET)$(CMP)$(ORANGE)] $(RESET)Compilating philosophers... $(RED)$<$(ORANGE) [$(RESET)$(CMP)$(ORANGE)/$(RESET)$(FILE)$(ORANGE)]$(RESET)           \r"
	$(CC) $(CFLAGS) -c $< -o  $@
	@$(eval CMP=$(shell echo $$(($(CMP)+1))))

$(OBJS_DIRS):
	@mkdir -p $@

$(NAME): $(OBJS_DIRS) $(OBJS)
			${CC} ${CFLAGS} $(OBJS) -o $@

clean:
			rm -rf obj/

fclean:			clean
			rm -f ${NAME} ${NAME_BONUS}

re:				fclean all

.SILENT:
	all

.PHONY:			all clean fclean re