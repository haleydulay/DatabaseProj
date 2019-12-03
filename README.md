# DatabaseProj
implementation of SFDS on DBLP datasets

Files needed to parse the data sets:
dblp.xml                       Link: https://dblp.uni-trier.de/xml/
dblp100KParser.cpp
dblpWWParser.cpp
rapidxml.hpp
rapidxml_print.hpp

Files needed to run the experiment/algorithms:
algorithms.cpp
dblpWW.txt
dblp100K.txt

How to compile the data sets:
g++ dblp100KParser.cpp
./a.out > dblp100K.txt
g++ dblpWWParser.cpp
./a.out > dblpWW.txt

How to compile and run the program:
g++ algorithm1.cpp
./a.out

Follow the command prompt once the program is running.
