NAME =	ft_shmup
CXX	=	c++
CFLAGS	= -Wall -Wextra -Werror

SRC	=	struct.cpp	enemies.cpp shooting.cpp init_cleanup.cpp\

OBJ =	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CFLAGS) -c $(SRC)
	$(CXX) $(CFLAGS) -o $(NAME) $(OBJ) -lncursesw

clean:	
		rm -f *.o

fclean:	clean 
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re