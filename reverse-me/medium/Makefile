all :
	gcc -o level2 source.c

bonus :
	gcc -c patch.c -o patch.o
	ar rcs libpatch.a patch.o
	gcc -o level2 source.c -L. -lpatch

clean :
	rm -f level2
	rm -f patch.o
	rm -f libpatch.a

fclean : clean

re : fclean all

.PHONY : all bonus clean fclean re