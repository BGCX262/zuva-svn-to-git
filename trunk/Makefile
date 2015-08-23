CC = gcc
TARGET  = uva.exe
SRCS    = uva_259.c
CCFLAGS = -O2 -pipe -ansi -DONLINE_JUDGE
LDFLAGS = -lm
LIBS    = 
OBJS    := $(SRCS:.c=.o)

.PHONY: all clean
all:: $(TARGET) 

$(TARGET): $(OBJS) 
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
	
$(OBJS): %.o: %.c
	$(CC) $(CCFLAGS) -o $@ -c $< 

clean: 
	rm -f *.o *.exe *.stackdump