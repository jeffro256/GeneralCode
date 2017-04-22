EXECUTABLE=bin/April3DEngine
LIB_FLAGS=$(shell pkg-config --libs glfw3)
INC_FLAGS=-I external/include/ $(shell pkg-config --cflags glfw3)
C_COMPILE=cc -c -pedantic -Wall -Werror -std=c99 $< -o $@ $(INC_FLAGS)
CPP_COMPILE=c++ -pedantic -Wall -Werror -std=c++11 -c $< -o $@ $(INC_FLAGS)

all: $(EXECUTABLE)

$(EXECUTABLE): build/main.o build/shader_help.o build/glad.o 
	c++ $^ -o $@ $(LIB_FLAGS)

build/main.o: src/main.cpp src/shader_help.h external/include/glad/glad.h
	$(CPP_COMPILE)

build/shader_help.o: src/shader_help.c src/shader_help.h external/include/glad/glad.h
	$(C_COMPILE)

build/glad.o: external/lib/glad.c external/include/glad/glad.h
	$(C_COMPILE)

clean:
	rm -f build/*.o
	rm bin/April3DEngine