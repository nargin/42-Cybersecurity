#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define uint unsigned int
#define undefined int

void	no(void)
{
	printf("Nope\n");
	exit(1);
}

void	ok(void) 
{
	printf("Good job.\n");
}

int	main(void)
{
	uint uVar1;
	undefined uVar2;
	uint uVar3;
	int iVar4;
	bool bVar5;
	char cStack_3d;
	char cStack_3c;
	char cStack_3b;
	undefined uStack_3a;
	char acStack_39 [24];
	undefined auStack_21 [9];
	uint uStack_18;
	int iStack_14;
	int iStack_10;
	// undefined4 uStack_c;

	// uStack_c = 0;
	printf("Please enter key: ");
	iStack_10 = scanf("%s", acStack_39);
	if (iStack_10 != 1) {
		no();
	}
	if (acStack_39[1] != '0') {
		no();
	}
	if (acStack_39[0] != '0') {
		no();
	}
	fflush(stdin);
	memset(auStack_21,0,9);
	auStack_21[0] = 100;
	uStack_3a = 0;
	uStack_18 = 2;
	iStack_14 = 1;
	while(true) {
		uVar3 = strlen((char *)auStack_21);
		uVar1 = uStack_18;
		bVar5 = false;

		if (uVar3 < 8) {
			uVar3 = strlen(acStack_39);
			bVar5 = uVar1 < uVar3;
		}
		if (!bVar5) break;
		
		cStack_3d = acStack_39[uStack_18];
		cStack_3c = acStack_39[uStack_18 + 1];
		cStack_3b = acStack_39[uStack_18 + 2];
		uVar2 = atoi(&cStack_3d);
		auStack_21[iStack_14] = uVar2;
		uStack_18 = uStack_18 + 3;
		iStack_14 = iStack_14 + 1;
	}
	auStack_21[iStack_14] = 0;
	iVar4 = strcmp((char *)auStack_21, "delabere");
	if (iVar4 == 0) {
		ok();
	}
	else {
		no();
	}
	return 0;
}