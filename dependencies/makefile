main: main.o chaine.o file.o manage.o
	gcc -Wall main.o chaine.o file.o manage.o -o main

main.o: ../src/main.c ../include/chaine.h ../include/file.h ../include/manage.h ../include/tcp_packet.h
	gcc -Wall -c ../src/main.c

chaine.o: ../src/chaine.c ../include/chaine.h
	gcc -Wall -c ../src/chaine.c

file.o: ../src/file.c ../include/file.h
	gcc -Wall -c ../src/file.c

manage.o: ../src/manage.c ../include/manage.h ../include/tcp_packet.h
	gcc -Wall -c ../src/manage.c