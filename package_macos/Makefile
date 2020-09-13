NAME = Crimsonland

SRC = $(wildcard src/*.cpp)
OBJ = $(notdir $(SRC:%.cpp=%.o))

LIB = libFramework.dylib
	# mathlib.a

INC = -Iinc

FFLAGS = -F ./Frameworks -framework SDL2 -rpath ./Frameworks \
	-F ./Frameworks -framework SDL2_image -rpath ./Frameworks \

%.o: src/%.cpp
	@clang++ -std=c++17 -c $< $(INC)

all: u  $(OBJ)
	@clang++ -std=c++17 $(LIB) $(INC) $(OBJ) -o $(NAME) $(FFLAGS) -Wunused-command-line-argument #-fsanitize=address,undefined -g3 -Og -fno-omit-frame-pointer
	@install_name_tool -change /usr/local/lib/libFramework.dylib ./libFramework.dylib $(NAME)
	@echo "\n./Crimsonland [hight_window] [width_window] [hight_map] [width_map] [num_enemies] [num_ammo]\n"

uninstall u:
	@rm -rf $(NAME)
	@rm -rf $(OBJ)