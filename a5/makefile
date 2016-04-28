BCC = g++
DLIBS = -L/usr/lib -lGL -lGLU -lglut -lglui
#SLIBS = /h/mshah08/Desktop/comp175/lib/libGLEW.a
INC = -I./ -I/usr/include
EXE = a5

$(EXE) : *.cpp
	$(BCC) -O2 $(INC) *.cpp -o $@ $(DLIBS) $(SLIBS)

clean:
	rm -rf *.o *~ $(EXE)
