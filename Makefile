CC=gcc
CFLAGS=-Wall -pedantic -std=c11
EXECUTABLE=./bin/whopper
LIB_FILE=./bin/libwhopper.a
SHARED_LIB_FILE=./bin/libwhopper.so
INCLUDE=-I./include

lib-shared:
	mkdir -p bin
	$(CC) $(CFLAGS) -o entry.o -c entry.c $(INCLUDE)
	$(CC) $(CFLAGS) -o zip.o -c zip.c $(INCLUDE)
	$(CC) $(CFLAGS) -o unzip.o -c unzip.c $(INCLUDE)
	$(CC) -shared -o $(SHARED_LIB_FILE) *.o

lib-static:
	mkdir -p bin
	$(CC) $(CFLAGS) -o entry.o -c entry.c $(INCLUDE)
	$(CC) $(CFLAGS) -o zip.o -c zip.c $(INCLUDE)
	$(CC) $(CFLAGS) -o unzip.o -c unzip.c $(INCLUDE)
	ar rcs $(LIB_FILE) entry.o zip.o unzip.o

exe:
	mkdir -p bin
	$(CC) $(CFLAGS) -o $(EXECUTABLE) *.c $(INCLUDE)

.PHONY: clean
clean:
	rm -rf bin
	rm -f *.o
	rm -f $(EXECUTABLE)
	rm -f *.whop