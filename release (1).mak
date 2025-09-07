project: user_interface.o llist.o
	g++ user_interface.o llist.o -o project

user_interface.o: user_interface.cpp llist.h
	g++ -c user_interface.cpp -o user_interface.o

llist.o: llist.cpp llist.h
	g++ -c llist.cpp -o llist.o

clean:
	rm -f user_interface.o llist.o project
