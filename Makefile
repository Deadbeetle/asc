static:
	cd build; \
	gcc -I./inc -c ../src/*.c
	ar rcs libasc.a build/*
	rm .dynamic
	touch .static
dynamic:
	cd build; \
	gcc -I./inc -fPIC ../src/*.c
	gcc -shared -Wl,-soname,libasc.so.1 -o libasc.so.1.0.1 build/*
	rm .static
	touch .dynamic
clean:
	rm build/*
	rm lib*
remove:
	rm /usr/lib/libasc.*
	rm /usr/bin/asc
install:
	cp inc/* /usr/include/ASC
	rm .static 2>/dev/null && \
	mv libasc.so.1.0.1 /usr/lib
	rm .dynamic 2>/dev/null && \
	mv libasc.a /usr/lib

