all:test_image.out

test_image.out: test_image.o image.o pgm_image.o noyau.o pile.o tableaux.o trans_image.o
	gcc -o $@ $^ 

%.o: %.c
	gcc -c $^

clean	:
	rm -f *.o *.out *~
