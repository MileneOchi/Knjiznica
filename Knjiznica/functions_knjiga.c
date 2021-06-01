
#include "Header.h"
BOOK* nadi_clana(LISTA_KNJIGA* dll, int id) {
	BOOK* clan = dll->glava;
	while (clan->id != id) {
		if (clan->next == NULL) {
			return NULL;
		}
		clan = clan->next;
	}
	return clan;
}

void ispis_clanova(MEMBER* nadi_clana(LISTA_KNJIGA* dll, int id) {
	MEMBER* clan = dll->glava;
	while (clan->id != id) {
		if (clan->next == NULL) {
			return NULL;
		}
		clan = clan->next;
	}
	return clan;
}

void ispis_clanova(LISTA_KNJIGA* lista) {
	int br = 1;
	MEMBER* pointer = lista->glava;
	printf("\n");
	if (lista->glava == NULL) {
		return;
	}
	printf("\tID\t      IME\t    PREZIME\n");
	while (pointer->next != NULL) {

		printf("%d.\t%d\t%10s\t%10s\n", br, pointer->id, pointer->ime, pointer->prezime);
		pointer = pointer->next;
		br++;
	}
	printf("%d.\t%d\t%10s\t%10s\n", br, pointer->id, pointer->ime, pointer->prezime);
}

LISTA_KNJIGA* ucitaj_podatke(char* ime_datoteke) {
	LISTA_KNJIGA* lista = (LISTA_KNJIGA*)calloc(1, sizeof(LISTA_KNJIGA));
	provjera_Kreiranje_file(ime_datoteke);
	MEMBER* clan = (MEMBER*)calloc(1, sizeof(MEMBER));
	while (fread(clan, sizeof(MEMBER), 1, fp)) {
		dodaj_clan(lista, clan);
		clan = (MEMBER*)calloc(1, sizeof(MEMBER));
	}
	fclose(fp);
	return lista;
}

MEMBER* zapisi_clana(char* ime_datoteke) {
	MEMBER* headNode = (MEMBER*)calloc(1, sizeof(MEMBER));
	provjera_Kreiranje_file(ime_datoteke);
	zad_id_Clanova++;
	headNode->id = zad_id_Clanova;
	printf("(%d)\n", zad_id_Clanova);
	//fp = fopen(ime_datoteke, "ab+");
	if (fp == NULL) {
		perror("File error");
		system("pause");
		exit(-1);
	}
	fseek(fp, 0, SEEK_SET);
	fwrite(&zad_id_Clanova, sizeof(int), 1, fp);
	if (headNode == NULL) {
		perror("kreiranje liste na pocetku");
		return NULL;
	}
	else {
		printf("Unesite ime novog korisnika: ");
		scanf("%s", &headNode->ime);
		printf("Unesite prezime novog korisnika: ");
		scanf("%s", &headNode->prezime);
	}
	fclose(fp);
	fp = fopen(ime_datoteke, "ab+");
	fwrite(headNode, sizeof(BOOK), 1, fp);
	//fprintf(fp, "%s", "\n");
	fclose(fp);
}* lista) {
	int br = 1;
	MEMBER* pointer = lista->glava;
	printf("\n");
	if (lista->glava == NULL) {
		return;
	}
	printf("\tID\t      IME\t    PREZIME\n");
	while (pointer->next != NULL) {

		printf("%d.\t%d\t%10s\t%10s\n", br, pointer->id, pointer->ime, pointer->prezime);
		pointer = pointer->next;
		br++;
	}
	printf("%d.\t%d\t%10s\t%10s\n", br, pointer->id, pointer->ime, pointer->prezime);
}

LISTA_CLANOVA* ucitaj_podatke(char* ime_datoteke) {
	LISTA_CLANOVA* lista = (LISTA_CLANOVA*)calloc(1, sizeof(LISTA_CLANOVA));
	provjera_Kreiranje_file(ime_datoteke);
	BOOK* clan = (BOOK*)calloc(1, sizeof(BOOK));
	while (fread(clan, sizeof(BOOK), 1, fp)) {
		dodaj_clan(lista, clan);
		clan = (BOOK*)calloc(1, sizeof(BOOK));
	}
	fclose(fp);
	return lista;
}


BOOK* zapisi_knjigu(char* ime_datoteke) {
	BOOK* headNode = (BOOK*)calloc(1, sizeof(BOOK));
	provjera_Kreiranje_knjige(ime_datoteke);
	zad_id_knjiga++;
	headNode->id = zad_id_knjiga;
	printf("(%d)\n", zad_id_knjiga);
	//fp = fopen(ime_datoteke, "ab+");
	if (fp == NULL) {
		perror("File error");
		system("pause");
		exit(-1);
	}
	fseek(fp, 0, SEEK_SET);
	fwrite(&zad_id_knjiga, sizeof(int), 1, fp);
	if (headNode == NULL) {
		perror("kreiranje liste na pocetku");
		return NULL;
	}
	else {
		printf("Unesite ime novog korisnika: ");
		scanf("%s", &headNode->ime);
		printf("Unesite ime novog korisnika: ");
		scanf("%s", &headNode->autor_ime);
		printf("Unesite ime novog korisnika: ");
		scanf("%s", &headNode->autor_prezime);
		printf("Unesite prezime novog korisnika: ");
		scanf("%s", &headNode->zanr);
	}
	fclose(fp);
	fp = fopen(ime_datoteke, "ab+");
	fwrite(headNode, sizeof(BOOK), 1, fp);
	fclose(fp);
}


void provjera_Kreiranje_knjige(const char* ime) {

	fp = fopen(ime, "rb+");
	if (fp == NULL) {
		zad_id_knjiga = 0;
		fp = fopen(ime, "ab+");
		//fwrite(&zad_id_Clanova, sizeof(int), 1, fp);
		if (fp == NULL) {
			perror("Kreiranje nemoguce");
			exit(-1);
		}

	}
	else {
		fread(&zad_id_knjiga, sizeof(int), 1, fp);
	}
}