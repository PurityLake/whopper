EXECUTABLE=whopper
INCLUDE=-I./include

all:
	gcc -o $(EXECUTABLE) main.c $(INCLUDE)

.PHONY: clean
clean:
	rm -rf sample2
	rm -rf $(EXECUTABLE)
	rm -rf *.whop