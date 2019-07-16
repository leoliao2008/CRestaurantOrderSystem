CC=gcc
Lib=-lpthread -ljson -lsqlite3
Objs=$(addprefix ../../Objs/,$(patsubst %.c,%.o,$(wildcard *.c)))
CFLAGS=-o0
Includes=-I../Includes/

.PHONY:all clean

all:$(Objs)

$(Objs):$(patsubst %.o,%.c,$(notdir $@)) $(addprefix ../Includes/,$(patsubst %.o,%.h,$(notdir $@))) ../Includes/base_includes.h ../Includes/types.h
	$(CC) $(CFLAGS) -c $(patsubst %.o, %.c, $(notdir $@)) $(Includes) -o $@ $(Lib)

test:../../Objs/*.o
	$(CC) $(CFLAGS) $^ -o test $(Lib)

clean:
	-rm -rf $(Objs) test .*.*.sw?	
