NAME = philo
CFLAGS = -Wall -Werror -Wextra -g3 -O0
OBJECTS_FOLDER = ./obj/
HEADERS = ./include/

MANDATORY_SOURCES = main.c write_action.c utils.c check_args.c inits.c debug.c \
					dinner_begin.c

MANDATORY_OBJECTS = $(addprefix $(OBJECTS_FOLDER),$(MANDATORY_SOURCES:.c=.o))

all: $(OBJECTS_FOLDER) $(NAME)

$(OBJECTS_FOLDER):
	mkdir $(OBJECTS_FOLDER)

$(NAME): $(MANDATORY_OBJECTS) $(HEADERS)philo.h
	cc $(CFLAGS) -lpthread $(MANDATORY_OBJECTS) -o $(NAME)

$(OBJECTS_FOLDER)%.o: ./src/%.c $(HEADERS)philo.h
	cc $(CFLAGS) -c $< -o $@ -I $(HEADERS)

clean:
	rm -rf $(OBJECTS_FOLDER)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
