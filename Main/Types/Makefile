CC=gcc
Lib=-lpthread -ljson -lsqlite3
Objs=$(patsubst %.c,%.o,$(wildcard ./*.c))
CFLAGS=-o0

.PHONY:all clean

all:$(Objs)

%.o:%.c %.h
	$(CC) $(CFLAGS) -c $< -o $@ $(Lib)

test:$(Objs) 
	$(CC) $(CFLAGS) $^ -o test $(Lib)

clean:
	-rm -rf *.o test .*.*.sw?	
