##Makefile for myMenu Program

CC_PTHREAD_FLAGS	= -lpthread
CC_FLAGS		= -c
CC_OUTPUT_FILE		= -o
CC			= gcc
RM			= rm
RM_FLAGS		= -f

TARGET 		= test
OBJS		= linktable.o myMenu.o test.o

all:	$(OBJS)
	$(CC) $(CC_OUTPUT_FILE) $(TARGET) $(OBJS)

.c.o:
	$(CC) $(CC_FLAGS) $^

clean:
	$(RM) $(RM_FLAGS) $(OBJS) $(TARGET) *.bak
