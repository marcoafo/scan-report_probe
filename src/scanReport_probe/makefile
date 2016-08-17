PROFILE = -O2 -s
CFLAGS = $(PROFILE)
LDFLAGS = 

all: main

# build it
main: a.o
	$(CC) $(LDFLAGS) a.o -o scanReportProbe

a.o: a.c
	$(CC) $(CFLAGS) -c a.c
	
# clean it
clean:
	rm *.o a