NAME 		=	libgui.so

CC			=	g++
FLAGS  		=	-std=c++11 -fPIC -Wall -Wextra -Werror
LIB_FLAG	=	-shared
SFML_FLAG	=	-lsfml-graphics -lsfml-window -lsfml-system

SRC_FILES	=	GUI.cpp ../Logic/Logic.cpp ../Logic/Cell.cpp
OBJ_FILES 	=	$(SRC_FILES:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(CC) $(FLAGS) -o $@ $(OBJ_FILES) $(LIB_FLAG) $(SFML_FLAG)
	@echo "\033[32m[ ✔ ] "GUI library is ready." \033[0m"

%.o:%.cpp
	@$(CC) $(FLAGS) -c -o $@ $<

clean:
	@rm -rf $(OBJ_FILES)

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[31m[ × ] "GUI library removed." \033[0m"

re: fclean all

.PHONY: all clean fclean re