compile:
	g++ -o hatReader HatReader.cpp imageHAT/Image.cpp header/FileHeader.cpp encrypt/VigenereCipher.cpp compress/LZW.cpp -Wall -Wextra `pkg-config --cflags --libs opencv4`

run:
	./hatReader