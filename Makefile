CC=gcc
CFLAGS=-Wall -pedantic -std=c11
OUTDIR=./bin
EXECUTABLE=$(OUTDIR)/whopper
SRC_DIR=./src
STATIC_LIB_FILE=$(OUTDIR)/libwhopper.a
SHARED_LIB_FILE=$(OUTDIR)/libwhopper.so
INCLUDE=-I./include
OBJS=entry.o unzip.o zip.o

%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

exe: $(OBJS) main.o
	mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $^ $(INCLUDE)

shared: $(OBJS)
	mkdir -p $(OUTDIR)
	$(CC) -shared -o $(SHARED_LIB_FILE) *.o

static: $(OBJS)
	mkdir -p $(OUTDIR)
	ar rcs $(STATIC_LIB_FILE) entry.o zip.o unzip.o

.PHONY: clean
clean:
	rm -rf bin
	rm -f *.o
	rm -rf infer-out