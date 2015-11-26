CXX = g++

NAME = sudoku-solver

RM = rm -rf
MKDIR = mkdir -p

CXXFLAGS += -I./$(INC_PATH)
CXXFLAGS += -Wall -Wextra -W -std=c++11

SRC_PATH = src
SRC = main.cpp \
	SudokuGrid.cpp \
	SudokuSolver.cpp

OBJ_PATH = obj
OBJ = $(SRC:%.cpp=$(OBJ_PATH)/%.o)

INC_PATH	= inc
INC = ASudokuGrid.hh \
	ISudokuSolver.hh \
	SudokuGrid.hh \
	SudokuSolver.hh

DEP = $(patsubst %,$(INC_PATH)/%,$(INC))

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(DEP)
	@$(MKDIR) $(OBJ_PATH)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CXX) $(OBJ) $(LDFLAGS) -o $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJ_PATH)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re fclean clean all
