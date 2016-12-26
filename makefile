CXX=/usr/local/bin/g++
a: a.cpp
	$(CXX) -g -o a a.cpp 
clean:
	rm a
