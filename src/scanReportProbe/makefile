# Set the libraries to link
LFLAGS += -lpcap
CFLAGS += -O2 -s
# Debug
#CFLAGS += -g

# The target
TARGET = scanReportProbe
# Object files
OBJECTS = scanReportProbe.o radiotap.o 

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LFLAGS) -o $(TARGET)

# Dependencies:

radiotap.o: radiotap.h radiotap_iter.h platform.h


# This is a predefined rule of makefile, it knows the dependencies and thus can compile the related ".c" files in to ".o"
# The macro $< means "the first suffix of current target", i.e. ".c"
.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o
	rm $(TARGET)
