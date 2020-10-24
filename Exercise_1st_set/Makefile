# Makefile

bin/main : src/main.cpp lib/lib_exercise.a Makefile
	g++ -I include/ -o bin/main src/main.cpp lib/lib_exercise.a

lib/lib_exercise.a : lib/count_ones.o lib/check_sum.o Makefile
	ar rs lib/lib_exercise.a lib/count_ones.o lib/check_sum.o

lib/check_ones.o : src/count_ones.cpp Makefile
	g++ -I include/ -c -o lib/count_ones.o src/count_ones.cpp

lib/check_sum.o : src/check_sum.cpp Makefile
	g++ -I include/ -c -o lib/check_sum.o src/check_sum.cpp

.PHONY: clean
clean:
	rm -f bin/main lib/count_ones.o lib/check_sum.o lib/lib_exercise.a

