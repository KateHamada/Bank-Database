project_debug: user_interface.o llist.o
	g++ user_interface.o llist.o -o project_debug

user_interface.o: user_interface.cpp llist.h
	g++ -g -DDEBUG -c user_interface.cpp -o user_interface.o

llist.o: llist.cpp llist.h
	g++ -g -DDEBUG -c llist.cpp -o llist.o

clean:
	rm -f user_interface.o llist.o project_debug
