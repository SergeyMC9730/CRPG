FILES=main.cpp protocol.cpp render.cpp world.cpp

x86_64-linux:
	g++ $(FILES) -o cworld-x86_64-linux
arm-linux:
	arm-linux-gnueabi-g++ $(FILES) -o cworld-x86_64-linux
aarch64-linux:
	aarch64-linux-gnu-g++ $(FILES) -o cworld-aarch64-linux
x86_64-win:
	x86_64-w64-mingw32-g++ $(FILES) -o cworld-x86_64-win.exe
all:
	g++ $(FILES) -o cworld-x86_64-linux
	arm-linux-gnueabi-g++ $(FILES) -o cworld-arm-linux
	aarch64-linux-gnu-g++ $(FILES) -o cworld-aarch64-linux
	x86_64-w64-mingw32-g++ $(FILES) -o cworld-x86_64-win.exe

	zip cworld.zip cworld-x86_64-linux cworld-arm-linux cworld_aarch64-linux cworld-x86_64-win.exe
deps:
	sudo apt-get update
	sudo apt-get upgrade -y
	sudo apt-get install gcc make gcc-mingw-w64-x86-64 g++-mingw-w64-x86-64 g++-aarch64-linux-gnu binutils-aarch64-linux-gnu g++-arm-linux-gnueabi binutils-arm-linux-gnueabi gcc-aarch64-linux-gnu gcc-arm-linux-gnueabi zip -y