all:
	rm -rfv out
	mkdir out

	g++ main.cpp protocol.cpp render.cpp world.cpp -o crpg
	mv crpg out/