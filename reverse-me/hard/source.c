#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define uint unsigned int
#define undefined int

void	___syscall_malloc(void)
{
	printf("Nope.\n");
	exit(0);
}

void	____syscall_malloc(void)
{
	printf("Good job.\n");
	exit(0);
}

int	main(void)
{
	ulong uVar1;
	int iVar2;
	size_t sVar3;
	bool bVar4;
	char local_4c[4] = {0};
	undefined local_49;
	char local_48[31];
	char local_29[9];
	ulong local_20;
	int local_18;
	int local_14;
	int local_10;
	// undefined4 local_c;
	
	// local_c = 0;
	printf("Please enter key: ");
	local_10 = scanf("%s", local_48);
	if (local_10 != 1) {
		___syscall_malloc();
	}
	if (local_48[1] != '2') {
		___syscall_malloc();
	}
	if (local_48[0] != '4') {
		___syscall_malloc();
	}
	fflush(stdin);
	memset(local_29,0,9);
	local_29[0] = '*';
	local_49 = 0;
	local_20 = 2;
	local_14 = 1;
	while( true ) {
		sVar3 = strlen(local_29);
		uVar1 = local_20;
		bVar4 = false;
		if (sVar3 < 8) {
		sVar3 = strlen(local_48);
		bVar4 = uVar1 < sVar3;
		}
		if (!bVar4) break;
		local_4c[0] = local_48[local_20];
		local_4c[1] = local_48[local_20 + 1];
		local_4c[2] = local_48[local_20 + 2];
		iVar2 = atoi(local_4c);
		local_29[local_14] = (char)iVar2;
		local_20 = local_20 + 3;
		local_14 = local_14 + 1;
	}
	local_29[local_14] = '\0';
	local_18 = strcmp(local_29,"********");
	if (local_18 == -2) {
		___syscall_malloc();
	}
	else if (local_18 == -1) {
		___syscall_malloc();
	}
	else if (local_18 == 0) {
		____syscall_malloc();
	}
	else if (local_18 == 1) {
		___syscall_malloc();
	}
	else if (local_18 == 2) {
		___syscall_malloc();
	}
	else if (local_18 == 3) {
		___syscall_malloc();
	}
	else if (local_18 == 4) {
		___syscall_malloc();
	}
	else if (local_18 == 5) {
		___syscall_malloc();
	}
	else if (local_18 == 0x73) {
		___syscall_malloc();
	}
	else {
		___syscall_malloc();
	}
	return 0;
}