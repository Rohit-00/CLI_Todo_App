init:
ifeq ($(OS),Windows_NT)
	if not exist mkdir mkdir obj
	if not exist mkdir mkdir bin
	if not exist mkdir mkdir file
else
	$(MKDIR) obj
	$(MKDIR) bin
	$(MKDIR) file
endif

app: init help.o file.o parse.o main.o 
	gcc obj/help.o obj/main.o obj/file.o obj/parse.o -o bin/todo

memory_check: init help.o file.o parse.o main.o
	gcc -g obj/help.o obj/main.o obj/file.o obj/parse.o -o bin/appmem
file.o: src/file.c
	gcc -Iinclude -c src/file.c -o obj/file.o

parse.o: src/parse.c
	gcc -Iinclude -c src/parse.c -o obj/parse.o

help.o: src/help.c
	gcc -Iinclude -c src/help.c -o obj/help.o

main.o: src/main.c
	gcc -Iinclude -c src/main.c -o obj/main.o
