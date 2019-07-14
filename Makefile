CC=gcc
MAKE=make
CFLAGS=-o0 -lpthread -lsqlite3 -ljson
SubDir=Main/Server Main/Client Main/Structs Main/Utils Objs
export CC MAKE CFLAGS

.PHONY:All Clean

All:$(SubDir) 

$(SubDir):
	$(MAKE) -C $@ All
	

Clean:
	-rm -rf Bins/* Objs/* 
	
	
