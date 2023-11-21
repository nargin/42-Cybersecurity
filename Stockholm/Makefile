all :
	gcc -Wall -Werror -Wextra stockholm.c -lsodium -o stockholm

clean :
	rm -f stockholm
	rm -f *.o
	rm -f key.cript

fclean : clean

re : fclean all

.PHONY : all clean fclean re