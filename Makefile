CFLAGS=-Werror -Wall -Wno-psabi -g
OBJS=ntreceiver.o
LIBS=-lcurl -lopencv_core -l opencv_imgproc -lopencv_highgui -lntcore -lwpiutil -L ~/ntcore/build/libs/ntcore/shared -L ~/wpiutil/build/libs/wpiutil/shared
INC=-I ~/ntcore/src/main/native/include -I ~/wpiutil/src/main/native/include -I /usr/include/llvm-3.9

GXX=g++ $(CFLAGS) $(INC)

.PHONY: all clean

all: ntreceiver

%.o: %.cpp
	$(GXX) -c -o $@ $<

ntreceiver: $(OBJS)
	$(GXX) $(LIBS) -o $@ $(OBJS)

clean:
	rm -f *.o ntreceiver
	
