# --- Compilar con .so ---
# (Compilar con una librería dinámica disminuirá el peso del ejecutable)
# (Pros: Tamaño del ejecutable reducido)
# (Contras: Deberás proporcionar también la librería)
#
# $ g++ -std=c++1 -c main.cpp
# $ g++ -std=c++1 -c healthbar.cpp
# ... (cada archivo del proyecto)
# $ g++ -o test *.o -L../../lib/ -lS2M -lSDL2 -lSDL2_image -Wl,-rpath=../../lib/

# --- Compilar con .a ---
# (Compilar con una librería estática la añadirá al ejecutable e incrementará su peso)
# (Pros: No dependemos de librerías externas)
# (Contras: Mayor peso del ejecutable)
# 
# $ g++ -std=c++1 -c main.cpp
# $ g++ -std=c++1 -c healthbar.cpp
# ... (cada archivo del proyecto)
# $ g++ -o test *.o -L../../lib/ -lSDL2 -lSDL2_image -l:libS2M.a


CoreSources=graphics.cpp options.cpp room.cpp object.cpp pause.cpp script.cpp gui.cpp joystick.cpp
ImplSources= entity.cpp
Executable=test

CFlags=-std=c++11 -c #-g #-Ofast
LDFlags=-lSDL2 -lSDL2_image -L./S2M
ObjectDir=obj/
CoreDir=../../src/
ImplDir=../../src/platformer/
TestDir=
BinDir=

CC=g++
RM=rm

#!!!!!DO NOT EDIT ANYTHING UNDER THIS LINE!!!!!
Objects=$(CoreSources:.cpp=.o) $(ImplSources:.cpp=.o)
CCoreSources=$(addprefix $(CoreDir),$(CoreSources))
CImplSources=$(addprefix $(ImplDir),$(ImplSources))
CObjects=$(addprefix $(ObjectDir),$(Objects)) $(addprefix $(ObjectDir),$(Objects2))
CExecutable=$(addprefix $(BinDir),$(Executable))

all: test

test: $(CCoreSources) $(CImplSources) obj/main.o obj/healthbar.o $(CExecutable)

$(CExecutable): $(CObjects)
	$(CC) $(CObjects) obj/main.o obj/healthbar.o -o $@ $(LDFlags)

$(ObjectDir)%.o: $(CoreDir)%.cpp 
	$(CC) $(CFlags) $< $(LDFlags) -o $@
	
$(ObjectDir)%.o: $(ImplDir)%.cpp
	$(CC) $(CFlags) $< $(LDFlags) -o $@
	
obj/main.o: main.cpp
	$(CC) $(CFlags) main.cpp $(LDFlags) -o obj/main.o

obj/healthbar.o: healthbar.cpp
	$(CC) $(CFlags) healthbar.cpp $(LDFlags) -o obj/healthbar.o

clean:
	$(RM) -rf obj/*o game
