GXX=g++
FLAGS= -I./include -L./lib -lRdO -std=c++11 -O2

TARGET=bin

$(TARGET):
	$(GXX) main.cc $(FLAGS) -o $(TARGET)

all:	$(TARGET)
clean:	
	rm -f $(TARGET) *.obj
