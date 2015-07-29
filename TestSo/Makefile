Test: test_main.o
	mkdir ./obj
	g++ -L../Source/ -lCommandLineParser -Wl,-rpath=./ -o Test test_main.o
	rm *.o -rf
	mv Test ./obj
	cp ../Source/libCommandLineParser.so ./obj/

test_main.o:test_main.cpp
	gcc -c -Wall -fPIC test_main.cpp -o test_main.o

.PHONEY:clean

clean:
	rm *.o Test obj -rf
