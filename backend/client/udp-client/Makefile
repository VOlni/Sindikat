default:
	g++ -g3 udpcl.cpp -o udpcl

valg:
	valgrind --tool=memcheck ./udpcl

clean:
	rm udpcl

syn:
	c++ udpcl.cpp -fsyntax-only
