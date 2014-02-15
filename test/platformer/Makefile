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

Executable=test

CFlags=-std=c++11 -c #-g #-Ofast
LDFlags=-L../../lib/ -lSDL2 -lSDL2_image -lS2M -Wl,-rpath=../../lib/
ObjectDir=obj/
SrcDir=
TestDir=
BinDir=
Library=../../

CC=g++
RM=rm

#!!!!!DO NOT EDIT ANYTHING UNDER THIS LINE!!!!!
Objects=$(CoreSources:.cpp=.o) $(ImplSources:.cpp=.o)
CObjects=$(addprefix $(ObjectDir),$(Objects)) $(addprefix $(ObjectDir),$(Objects2))
CExecutable=$(addprefix $(BinDir),$(Executable))

all: library directories test

test: obj/main.o obj/healthbar.o $(CExecutable)

directories: $(ObjectDir)

library:
	cd ../.. && make

$(ObjectDir):
	mkdir -p $(ObjectDir)

$(CExecutable): $(CObjects)
	$(CC) $(CObjects) obj/main.o obj/healthbar.o -o $@ $(LDFlags)
	
$(ObjectDir)%.o: $(SrcDir)%.cpp
	$(CC) $(CFlags) $< $(LDFlags) -o $@

clean:
	$(RM) -rf obj/*o $(Executable)
	rmdir obj
