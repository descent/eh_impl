CXX=/usr/local/bin/g++
a: a.cpp
	$(CXX) -g -o a a.cpp 
	#$(CXX) -fomit-frame-pointer -g -o a a.cpp 
	#$(CXX) -fno-omit-frame-pointer -g -o a a.cpp 
a.o: a.cpp
	$(CXX) -g -c $<
a.s: a.cpp
	$(CXX) -g -S $<
clean:
	rm a
