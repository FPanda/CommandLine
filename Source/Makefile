CC      := g++
LD      := ld
CFLAGS  := -fPIC
LDFLAGS := -shared
SOFLAGS := -fvisibility=hidden
SOURCE  := $(wildcard *.cpp)
OBJS    := $(patsubst %.cpp,%.o,$(SOURCE))
TARGET_LIB := libCommandLineParser.so

all:$(OBJS)
	echo $(OBJS)
	$(LD) $(LDFLAGS) -o $(TARGET_LIB) $(OBJS)
	rm -rf *.o

%.o:%.cpp
	@echo Compiling $< ...
	$(CC) -c $(CFLAGS)  $< -o $*.o -fvisibility=hidden

.PHONY: clean

clean:
	rm *.so *.o -rf
