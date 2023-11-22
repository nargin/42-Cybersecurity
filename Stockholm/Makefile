all :
	@gcc -Wall -Werror -Wextra stockholm.c encrypt.c decrypt.c options.c parsing.c -I ./ -lsodium -o stockholm
	@echo "\033[1;32mStockholm is ready to use\033[0m"

confirm:
	@echo "\033[1;31mYou will delete key.crypt in the process\033[0m"
	@echo "This action requires confirmation"
	@read -p "Are you sure you want to proceed? [y/N] " answer; \
	if [ "$$answer" != "y" ]; then \
		echo "Aborted"; \
		exit 1; \
	fi
	@echo "\033[1;32mProceeding...\033[0m"


clean : confirm
	@rm -f stockholm
	@rm -f *.o
	@rm -f key.crypt
	@rm -rf crypted

fclean : clean

re : fclean all

.PHONY : all clean fclean re