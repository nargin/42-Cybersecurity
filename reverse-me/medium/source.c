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

void	xd(void)
{
	puts(
		"Iii sapores crescit rei habetur disputo. An ab istud mo prius tanta error debet. Firma foret tes mea age capax sumne. Ex ex ipsas actum culpa neque ab saepe. Existenti et principia co imm ittere probandam imaginari re mo. Quapropter industriam ibi cui dissimilem cucurbitas progress us perciperem. Essendi ratione si habetur gi ignotas cognitu nusquam et.Sumpta vel uti obvium hoc tribuo libere. Egisse ingens hic sed inquam tamque rum gaudet aetate dat. Sum ignem jam ul las tur nexum vul. Divelli certius si errandi accipio colores de numerum. Is quavis tangam ist ius lumini essent vereor ab si. Aliam rea res tango vix simul certa certi.Imponere tractatu ad venire ad superest occurret se quicquam si ha. Nihil solus pappo mo ei. Tum iis rom innata glo ria hos quales. Ac sequentium im sufficeret institutum ad permittere at. Aliquis aliarum quaen am at de totaque notitia ob exhibet. Simus tes sae sacra error. Neque nomen ac ad opera is reg es gi nobis. Se in objectivae ab is offerendum videbuntur satyriscos. Uno sequor tritam mediam  essent eae usu rea. \t\t\tActum situs ideam solum uti signa mem. De ignotas errores gi remota m invenio suppono. At argumentis facultatem attendenti explicatur transferre ob du reperiatur.  Gi du mali quod fuit an unum ei. Mea sperare ego sentiat idearum spatium quaedam. Prius cur l ocus utrum hodie porro mente ope. Accepit liberam externo qui fal. \t\t\tVolunt illico eas ani mus ita odores sacras ima. De ipsa vi ad deus alio ut deum. Acquiri aliquot in liquida vi maxi mam is timenda. Ad aliquandiu ei facillimam repugnaret scripturas. Mearum imo namque falsae no tatu hic mea non. Ero communibus exponantur hae sui quo virtutibus aliquandiu. \t\t\tNeque fie ri horum errem ab me eo credo. Hanc sic meo quae ipsa. Fal membrorum existenti conservet per s apientia dubitavit. Apta gi de et enim gnum data. Id quadratam ut archimede attingere re ne. H umanam infusum has iis veteris mei occasio replere istarum. Emanant poterit capaces at in nume rum de exigere ob chartam. Cui tollitur periculi cau veniebat. Communibus vi at ut p..." /* TR UNCATED STRING LITERAL */
		);
	puts(
		"Author gi ex si im fallat istius. Refutent supposui qua sim nihilque. Me ob omni ideo gnum ca su. Gi supersunt colligere inhaereat me sapientia is delaberer. Rom facillimam rem expectabam rum inchoandum mei. Apertum id suppono ac generis. Ab scio ad eo deus haud meae. Hominem ex vi  ut remanet at quidnam. \t\t\tTunc ullo ut anno poni voce de haud. Mallent prudens suo deumque  qui sim invicem. Suum mo item inde de modi unde. Suo deo omni quia opus. Co an habent inesse semper.Et innatas dominum cogitem sperare sopitum in. Substantia dei credidisse vim iis excogi tent exhibentur sub."
		);
	return;
}

int	main(void)
{
	uint uVar1;
	undefined uVar2;
	uint uVar3;
	int iVar4;
	bool bVar5;
	char cStack_3d[4] = {0};
	undefined uStack_3a;
	char acStack_39 [24];
	char auStack_21 [9];
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
		uVar3 = strlen(auStack_21);
		uVar1 = uStack_18;
		bVar5 = false;

		if (uVar3 < 8) {
			uVar3 = strlen(acStack_39);
			bVar5 = uVar1 < uVar3;
		}
		if (!bVar5) break;
		
		cStack_3d[0] = acStack_39[uStack_18];
		cStack_3d[1] = acStack_39[uStack_18 + 1];
		cStack_3d[2] = acStack_39[uStack_18 + 2];
		uVar2 = atoi(cStack_3d);
		auStack_21[iStack_14] = (char)uVar2;
		uStack_18 = uStack_18 + 3;
		iStack_14 = iStack_14 + 1;
	}
	auStack_21[iStack_14] = 0;
	// for (int i = 0; i < 9; i++) printf("%d ", (int)auStack_21[i]);
	// printf("\n");
	// printf("%s\n", auStack_21);
	iVar4 = strcmp(auStack_21, "delabere");
	if (iVar4 == 0) {
		ok();
	}
	else {
		no();
	}
	return 0;
}