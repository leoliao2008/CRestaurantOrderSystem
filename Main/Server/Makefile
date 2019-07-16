CC=gcc
Lib=-lpthread -ljson -lsqlite3
Objs=$(addprefix ../../Objs/,$(patsubst %.c,%.o,$(wildcard *.c)))
Includes=-I../Includes/

.PHONY:all clean

all:$(Objs)

$(Objs):$(patsubst %.o,%.c,$(notdir $@)) $(addprefix ../Includes/,$(patsubst %.o,%.h,$(notdir $@))) ../Includes/base_includes.h ../Includes/types.h
	$(CC) $(CFLAGS) -c $(patsubst %.o, %.c, $(notdir $@)) $(Includes) -o $@ $(Lib)
	
#%.o:%.c 
#	$(CC) $(CFLAGS) $(Includes) -c $< -o $@ $(Lib)

test:$(Objs) 
	$(CC) $(CFLAGS) $^ -o test $(Lib)

clean:
	-rm -rf $(Objs) test .*.*.sw?	



