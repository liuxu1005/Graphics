
EXE = example
DLIBS = -L./ -L/usr/lib/ -lGL -lGLU -lglut -lglui
#SLIBS = /usr/lib/libGLEW.a
INC = -I./ -I/usr/include

$(EXE) : *.cpp
	g++ $(INC) $< -o $@ $(DLIBS) $(SLIBS)

clean:
	rm -rf *.o *~ $(EXE)
