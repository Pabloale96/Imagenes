# #########################################################
# Algoritmos y Programacion II (95.12)
# Trabajo Practico 1: Programacion C++
# Nombre del archivo: makefile
# #########################################################


CXXARGS  = -g -Wall
CXXFLAGS = -I. $(CXXARGS) -std=c++11
CXX = g++

OBJETS= main.o cmdline.o bmp.o

HEADER = options.h cmdline.h bmp.h BmpHeader.h

all: tp1

tp1: $(OBJETS)
		$(CXX) $(CXXFLAGS) $(OBJETS) -o tp1

main.o: main.cc $(HEADER)
		$(CXX) $(CXXFLAGS) -c main.cc

cmdline.o: cmdline.cc cmdline.h
		$(CXX) $(CXXFLAGS) -c cmdline.cc

bmp.o: bmp.cc bmp.h BmpHeader.h
				$(CXX) $(CXXFLAGS) -c bmp.cc

clean:
	$(RM) -vf *.o
