MCTest : cell.o cvector.o CylCell.o CylSurface.o MCTest.o MCTube3D.o ray.o csv_reader.o mother.o
	g++ cell.o cvector.o CylCell.o CylSurface.o MCTest.o MCTube3D.o ray.o mother.o csv_reader.o -o MCTest

cell.o : cell.h cell.cpp
	g++ -c cell.cpp
cvector.o : cvector.cpp
	g++ -c cvector.cpp
CylCell.o : CylCell.h CylCell.cpp cvector.cpp ray.h CylSurface.h
	g++ -c CylCell.cpp
CylSurface.o : CylSurface.h CylSurface.cpp ray.h
	g++ -c CylSurface.cpp
MCTest.o : MCTest.cpp MCTube3D.h cvector.cpp
	g++ -c MCTest.cpp
MCTube3D.o : MCTube3D.h MCTube3D.cpp CylCell.h CylSurface.h cvector.cpp
	g++ -c MCTube3D.cpp
ray.o : ray.h ray.cpp cvector.cpp
	g++ -c ray.cpp

csv_reader.o : csv_reader.h csv_reader.cpp
	g++ -c csv_reader.cpp

mother.o : randomc.h mother.cpp
	g++ -c mother.cpp

clean :
	rm MCTest cell.o cvector.o CylCell.o CylSurface.o MCTest.o MCTube3D.o ray.o 
