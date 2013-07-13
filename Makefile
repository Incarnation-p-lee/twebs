.SUFFIXES:
.SUFFIXES: .c .out .h

SRC      =main.c

CC       =gcc
shell    =/bin/sh
OBJ      =$(patsubst %.c, %.o, $(SRC))
OBJDIR   =obj
CFLAG    =-c -Wall
TAR      =TinyWeb
INCH     =./inc
INCS     =./src
DPD      =fdependent
INC      =-I$(INCH) -I$(INCS)

vpath %.o $(OBJDIR)
vpath %.c ./src


.PHONY:$(TAR) link clean

-include $(DPD)


$(OBJ):%.o:%.c
	$(CC) $(INC) $(CLFAG) -o $@ $<
	mv $@ $(OBJDIR)

$(DPD):$(SRC)
	$(CC) $(INC) -MM -o $(DPD) $^

$(TAR):$(OBJ)
	$(MAKE) link

ifneq ($(OBJDIR), $(wildcard $(OBJDIR)))
	mkdir $(OBJDIR)
endif

link:$(OBJ)
	$(CC) $(INC) -o $(TAR) $^

clean:
	-rm $(TAR) $(OBJDIR)/*

