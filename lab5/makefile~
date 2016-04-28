CC = g++
DLIBS = -L/usr/lib -lGL -lGLU -lglut -lglui
#SLIBS = /h/mshah08/Desktop/comp175/lib/libGLEW.a
INC = -I./ -I/usr/include
EXE = lab4

$(EXE) : *.cpp
	$(CC) $(INC) *.cpp -o $@ $(DLIBS) $(SLIBS)

clean:
	rm -rf *.o *~ $(EXE)
