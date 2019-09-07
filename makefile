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