CC = g++
SRC_FILES = src/*.cpp
BIN_NAME = CG
COMPILER_FLAGS = -w -std=c++11
LINKER_FLAGS = -lSDL2 -lSDL2_ttf
INCLUDE_FOLDER = include
SDL_TTF_INCLUDE = vendor/SDL2_ttf/include
SDL_TTF_LIB = vendor/SDL2_ttf/lib

all: $(SRC_FILES)
	$(CC) $(SRC_FILES) $(COMPILER_FLAGS) $(LINKER_FLAGS) -I$(INCLUDE_FOLDER) -I$(SDL_TTF_INCLUDE) -L$(SDL_TTF_LIB) -o $(BIN_NAME)
