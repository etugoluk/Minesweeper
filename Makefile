NAME    =   minesweeper
OBJ_DIR =   ./obj/
SRC_DIR =   ./src/
INC_DIR =   ./inc/

CC      =   g++
FLAGS   =   -Wall -Wextra -Werror
SRC     =   main.cpp Exception.cpp
OBJ     =   $(addprefix $(OBJ_DIR), $(SRC:.cpp=.o))

LFLAGS  =  -L. -lgui -llogic

all: $(NAME)

$(NAME): logic gui $(OBJ)
	@$(CC) $(FLAGS) $(LFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[32m[ ✔ ] "$(NAME) is ready." \033[0m"

logic:
	@make -C Logic
	@mv Logic/liblogic.so .

gui:
	@make -C GUI
	@mv GUI/libgui.so .

$(OBJ): $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
	@$(CC) -c $< -o $@ $(FLAGS) -std=c++11

clean:
	@make -C Logic clean
	@make -C GUI clean
	@rm -f $(OBJ)

fclean: clean
	@rm  -f libgui.so
	@rm  -f liblogic.so
	@make -C Logic fclean
	@make -C GUI fclean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@echo "\033[31m[ × ] "$(NAME) removed." \033[0m"

re: fclean all

.PHONY: all logic gui clean fclean re