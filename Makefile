.SUFFIXES:
.SUFFIXES: .c .out .h .o .S .a .s

SRC      =handler.c ioput.c main.c  \
          server.c textual.c net.c

CC       =gcc
shell    =/bin/sh
OBJ      =$(patsubst %.c, %.o, $(SRC))
OBJDIR   =obj
CFLAG    =-c -Wall -g
TAR      =TinyWeb
INCH     =./inc
INCS     =./src
DPD      =fdependent
INC      =-I$(INCH) -I$(INCS)

vpath %.o $(OBJDIR)


.PHONY:link clean

$(TAR):$(OBJ)
	$(MAKE) link

-include $(DPD)

$(DPD):$(SRC)
	$(CC) $(INC) -MM $^ >$@
ifneq ($(OBJDIR), $(wildcard $(OBJDIR)))
	mkdir $(OBJDIR)
endif


$(OBJ):%.o:%.c
	$(CC) $(INC) $(CFLAG) -o $@ $<
	mv $@ $(OBJDIR)

link:$(OBJ)
	$(CC) $(INC) -o $(TAR) $^

clean:
	-rm -rf $(TAR) $(OBJDIR)/* $(DPD)

