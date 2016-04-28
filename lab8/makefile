CC = g++
DLIBS = -L/usr/lib -lGL -lGLU -lglut -lglui
SLIBS = /usr/lib/x86_64-linux-gnu/libGLEW.so
INC = -I./ -I/usr/include
EXE = lab8

$(EXE) : *.cpp
	$(CC) $(INC) *.cpp -o $@ $(DLIBS) $(SLIBS)

clean:
	rm -rf *.o *~ $(EXE)
