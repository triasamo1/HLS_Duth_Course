# Makefile

bin/main : src/main.cpp lib/lib_exercise3.a Makefile
	g++ -I include/ -o bin/main src/main.cpp lib/lib_exercise3.a

lib/lib_exercise3.a : lib/runlength_encoder.o lib/blackjack.o Makefile
	ar rs lib/lib_exercise3.a lib/runlength_encoder.o lib/blackjack.o

lib/runlength_encoder.o : src/runlength_encoder.cpp Makefile
	g++ -I include/ -c -o lib/runlength_encoder.o src/runlength_encoder.cpp

lib/blackjack.o : src/blackjack.cpp Makefile
	g++ -I include/ -c -o lib/blackjack.o src/blackjack.cpp

.PHONY: clean
clean:
	rm -f bin/main lib/runlength_encoder.o lib/blackjack.o lib/lib_exercise3.a
