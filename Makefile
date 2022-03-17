FILES=main.cpp protocol.cpp render.cpp world.cpp
LIBS=-lpthread -static-libgcc -static-libstdc++ -lao

all:
	g++ $(FILES) $(LIBS) -o cworld-x86_64-linux
deps:
	git submodule update --init --recursive

	sudo apt-get update
	sudo apt-get upgrade -y
	sudo apt-get install gcc make libncursesw5-dev libncursesw5 zip -y