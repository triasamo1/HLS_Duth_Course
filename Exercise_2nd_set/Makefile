# Makefile

bin/main : src/main.cpp lib/lib_exercise2.a Makefile
	g++ -I include/ -o bin/main src/main.cpp lib/lib_exercise2.a

lib/lib_exercise2.a : lib/runlength_encoder.o lib/csd_encoder.o lib/csd_multiplication.o Makefile
	ar rs lib/lib_exercise2.a lib/runlength_encoder.o lib/csd_encoder.o lib/csd_multiplication.o

lib/runlength_encoder.o : src/runlength_encoder.cpp Makefile
	g++ -I include/ -c -o lib/runlength_encoder.o src/runlength_encoder.cpp

lib/csd_encoder.o : src/csd_encoder.cpp Makefile
	g++ -I include/ -c -o lib/csd_encoder.o src/csd_encoder.cpp

lib/csd_multiplication.o : src/csd_multiplication.cpp Makefile
	g++ -I include/ -c -o lib/csd_multiplication.o src/csd_multiplication.cpp

.PHONY: clean
clean:
	rm -f bin/main lib/runlength_encoder.o lib/csd_encoder.o lib/csd_multiplication.o lib/lib_exercise2.a
