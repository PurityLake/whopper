CC=gcc
CFLAGS=-Wall -pedantic -std=c11
EXECUTABLE=./bin/whopper
SRC_DIR=./src
LIB_FILE=./bin/libwhopper.a
SHARED_LIB_FILE=./bin/libwhopper.so
INCLUDE=-I./include

lib-shared:
	mkdir -p bin
	$(CC) $(CFLAGS) -o entry.o -c $(SRC_DIR)/entry.c $(INCLUDE)
	$(CC) $(CFLAGS) -o zip.o -c $(SRC_DIR)/zip.c $(INCLUDE)
	$(CC) $(CFLAGS) -o unzip.o -c $(SRC_DIR)/unzip.c $(INCLUDE)
	$(CC) -shared -o $(SHARED_LIB_FILE) *.o

lib-static:
	mkdir -p bin
	$(CC) $(CFLAGS) -o entry.o -c $(SRC_DIR)/entry.c $(INCLUDE)
	$(CC) $(CFLAGS) -o zip.o -c $(SRC_DIR)/zip.c $(INCLUDE)
	$(CC) $(CFLAGS) -o unzip.o -c $(SRC_DIR)/unzip.c $(INCLUDE)
	ar rcs $(LIB_FILE) entry.o zip.o unzip.o

exe:
	mkdir -p bin
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SRC_DIR)/*.c main.c $(INCLUDE)

.PHONY: clean
clean:
	rm -rf bin
	rm -f *.o
	rm -f $(EXECUTABLE)
	rm -f *.whop
	rm -rf infer-out