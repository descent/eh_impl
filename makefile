CXX=/usr/local/bin/g++
a.static: a.o
	/usr/local/libexec/gcc/x86_64-unknown-linux-gnu/5.4.0/collect2 -plugin /usr/local/libexec/gcc/x86_64-unknown-linux-gnu/5.4.0/liblto_plugin.so -plugin-opt=/usr/local/libexec/gcc/x86_64-unknown-linux-gnu/5.4.0/lto-wrapper -plugin-opt=-fresolution=/tmp/ccnKcDbO.res -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_eh -plugin-opt=-pass-through=-lc -m elf_x86_64 -static -o a /usr/local/lib/crt1.o /usr/local/lib/crti.o /usr/local/lib/gcc/x86_64-unknown-linux-gnu/5.4.0/crtbeginT.o -L/usr/local/lib/gcc/x86_64-unknown-linux-gnu/5.4.0 -L/usr/local/lib/gcc/x86_64-unknown-linux-gnu/5.4.0/../../../../lib64 -L/lib/x86_64-linux-gnu -L/lib/../lib64 -L/usr/local/lib -L/usr/local/lib/gcc/x86_64-unknown-linux-gnu/5.4.0/../../.. a.o -lstdc++ -lm --start-group -lunwind -lgcc -lgcc_eh -lc --end-group /usr/local/lib/gcc/x86_64-unknown-linux-gnu/5.4.0/crtend.o /usr/local/lib/crtn.o


a: a.cpp
	$(CXX) -g -o a a.cpp 
	#$(CXX) -fomit-frame-pointer -g -o a a.cpp 
	#$(CXX) -fno-omit-frame-pointer -g -o a a.cpp 
a.o: a.cpp
	$(CXX) -g -c $<
a.s: a.cpp
	$(CXX) -g -S $<
clean:
	rm a a.s a.o a.static
