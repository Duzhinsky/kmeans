all: build

build: 
	g++ -o kmeans main.cpp -std=c++11 -I/usr/include/python2.7 -I/usr/include/x86_64-linux-gnu/python2.7 -I/usr/lib/python2.7/dist-packages/numpy/core/include -lpython2.7 -lpthread -ldl  -lutil -lm 
