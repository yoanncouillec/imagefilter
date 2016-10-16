all:test.out

test.out: test.o image.o pgm_image.o noyau.o tableaux.o trans_image.o
	gcc -o $@ $^ -g

%.o: %.c
	gcc -c $^ -g

test: test.out
	./test.out --input images/vache.pgm --output images/vaches_neg.pgm --kernel noyau/noyau_deriv.txt --negative
	./test.out --rotate 90 -i images/vache.pgm -o images/vache_rotate.pgm

clean	:
	rm -f *.o *.out *~
