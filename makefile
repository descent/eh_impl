CXX=/usr/local/bin/g++
a: a.cpp
	#$(CXX) -fomit-frame-pointer -g -o a a.cpp 
	$(CXX) -fno-omit-frame-pointer -g -o a a.cpp 
clean:
	rm a
