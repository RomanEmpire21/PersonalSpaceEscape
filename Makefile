CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL libalut.so.0.1.0 libopenal.so.1.15.1 \
	 -pthread -lm #-lXrandr

all: spaceescape

spaceescape: spaceescape.cpp log.cpp mytime.cpp ppm.cpp josephR.cpp seanN.cpp jonathanR.cpp chrisK.cpp
	g++ $(CFLAGS) spaceescape.cpp log.cpp mytime.cpp ppm.cpp seanN.cpp josephR.cpp jonathanR.cpp chrisK.cpp \
	libggfonts.a -Wall -Wextra $(LFLAGS) -ospaceescape 

clean:
	rm -f spaceescape
	rm -f *.o

