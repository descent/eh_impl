#!/bin/sh
# sc: static compile

/usr/local/libexec/gcc/x86_64-unknown-linux-gnu/5.4.0/collect2 -plugin /usr/local/libexec/gcc/x86_64-unknown-linux-gnu/5.4.0/liblto_plugin.so -plugin-opt=/usr/local/libexec/gcc/x86_64-unknown-linux-gnu/5.4.0/lto-wrapper -plugin-opt=-fresolution=/tmp/ccnKcDbO.res -plugin-opt=-pass-through=-lgcc -plugin-opt=-pass-through=-lgcc_eh -plugin-opt=-pass-through=-lc -m elf_x86_64 -static -o a /usr/local/lib/crt1.o /usr/local/lib/crti.o /usr/local/lib/gcc/x86_64-unknown-linux-gnu/5.4.0/crtbeginT.o -L/usr/local/lib/gcc/x86_64-unknown-linux-gnu/5.4.0 -L/usr/local/lib/gcc/x86_64-unknown-linux-gnu/5.4.0/../../../../lib64 -L/lib/x86_64-linux-gnu -L/lib/../lib64 -L/usr/local/lib -L/usr/local/lib/gcc/x86_64-unknown-linux-gnu/5.4.0/../../.. a.o -lstdc++ -lm --start-group -lgcc -lgcc_eh -lc --end-group /usr/local/lib/gcc/x86_64-unknown-linux-gnu/5.4.0/crtend.o /usr/local/lib/crtn.o

