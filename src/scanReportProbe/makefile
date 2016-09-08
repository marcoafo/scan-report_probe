# Set the libraries to link
LFLAGS += -lpcap -pthread
CFLAGS += -O2 -s
# Debug
#CFLAGS += -g

# The target
TARGET = probe_sniffer
# Object files
OBJECTS = probe_sniffer.o radiotap.o consumer.o

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
