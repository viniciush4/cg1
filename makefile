
# all: gcc
# 	@echo "Done."

# tinyxml2: tinyxml2.cpp
# 	g++ -c tinyxml2.cpp

# Color: Color.cpp
# 	g++ -c Color.cpp 
	
# gcc: Color tinyxml2
# 	g++ teste-xml.cpp -o teste-xml Color.o tinyxml2.o

all: circulo
	g++ main.cpp -o trabalhocg circulo.o -lglut -lGLU -lGL
	@echo "Done."

circulo: circulo.cpp
	g++ -c circulo.cpp 

run_test_1: 
	./trabalhocg ./Test_1/config.xml

run_test_2: 
	./trabalhocg ./Test_2/config.xml

clean:
	@rm -f *.o trabalhocg