
# all: gcc
# 	@echo "Done."

# tinyxml2: tinyxml2.cpp
# 	g++ -c tinyxml2.cpp

# Color: Color.cpp
# 	g++ -c Color.cpp 
	
# gcc: Color tinyxml2
# 	g++ teste-xml.cpp -o teste-xml Color.o tinyxml2.o

all: circulo tinyxml2 configuracao
	g++ main.cpp -o trabalhocg circulo.o tinyxml2.o configuracao.o -lglut -lGLU -lGL
	@echo "Done."

circulo: circulo.cpp
	g++ -c circulo.cpp 

tinyxml2: tinyxml2.cpp
	g++ -c tinyxml2.cpp

configuracao: configuracao.cpp
	g++ -c configuracao.cpp

clean:
	@rm -f *.o trabalhocg