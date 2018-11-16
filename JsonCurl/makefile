$(shell mkdir -p build/)

all: build/jsonCurl

build/jsonCurl: build/main.o build/jsoncurl.o
	g++ -lcurl -ljsoncpp -o build/jsonCurl build/main.o build/jsoncurl.o

build/main.o: src/main.cpp
	g++ -c -o build/main.o src/main.cpp

build/jsoncurl.o: src/jsoncurl/jsoncurl.cpp src/jsoncurl/jsoncurl.hpp
	g++ -c -o build/jsoncurl.o src/jsoncurl/jsoncurl.cpp

clean:
	rm -R build/
