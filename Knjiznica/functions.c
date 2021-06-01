#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Header.h"
extern FILE* fp;
FILE* fp = NULL;

static int zad_id_Clanova;
static int zad_id_knjiga = 0;

void izbornik() {
	LISTA_CLANOVA* popisClanova;
	char choice;
	char choice_two;

	do {
		system("cls");
		printf("            GLAVNI IZBORNIK           \n");
		printf("1. Upravljanje: clanovi\n");
		printf("2. Upravljanje: knjige\n");
		printf("3. Pretraga clan\n");
		printf("4. Pretraga knjiga\n");
		printf("");
		choice = _getch();
		switch (choice) {
		case'1':
			do {
				system("cls");
				printf("Upravljanje clanovi\n");
				printf("1.Lista clanova\n");
				printf("2.Dodaj clana\n");
				printf("3.Obrisi clana\n");
				printf("4.Uredi clana\n");
				choice_two = _getch();
				switch (choice_two) {
				case '1':
					system("cls");
					popisClanova = ucitaj_podatke("clanovi.bin");
					if (popisClanova == NULL) {
						printf("nema clanova");
						break;
					}
					ispis_clanova(popisClanova);
					do {
						choice_two = _getch();
					} while (choice_two != 'z');
					break;
				case'2':

					system("cls");
					zapisi_clana("clanovi.bin");
					do {
						choice_two = _getch();
					} while (choice_two != 'z');
					break;
				case '3':

					popisClanova = ucitaj_podatke("clanovi.bin");
					if (popisClanova == NULL) {
						printf("nema clanova");
						break;
					}
					ispis_clanova(popisClanova);
					obrisi_clana(popisClanova);
					break;

				case 27:
					break;
				}
			} while (choice_two != '0');
			break;
		case'2':
			system("cls");
			printf("Upravljanje: knjige\n");
			printf("1.Lista knjiga\n");
			printf("2.Dodaj knjigu\n");
			printf("3.Obrisi knjigu\n");
			printf("4.Uredi knjigu\n");
			choice_two = _getch();
			switch (choice_two) {
			case '1':
				system("cls");
				break;
			case'2':
				system("cls");
				zapisi_knjigu("knjige.bin");
			}
			break;
		case '3':
			system("cls");
			printf("Pretrazivanje clana po: \n");
			printf("1.ID-u\n");
			printf("2.Ime\n");
			choice_two = _getch();
			switch (choice_two) {
			case '1':
				system("cls");
			}
			break;
		case '4':
			system("cls");
			printf("Pretrazivanje knjige po: \n");
			printf("1.ID-u\n");
			printf("2.Ime knjige\n");
			printf("3.Ime autora\n");
			printf("4.Zanr\n");
			choice_two = _getch();
			switch (choice_two) {
			case '1':
				system("cls");

			}
			break;


		case 27:
			exit(-1);
		}
	} while (choice != '0');
	_getch();



}

void provjera_Kreiranje_file(const char* ime) {
	fp = fopen(ime, "rb+");
	if (fp == NULL) {
		zad_id_Clanova = 0;
		fp = fopen(ime, "ab+");
		//fwrite(&zad_id_Clanova, sizeof(int), 1, fp);
		if (fp == NULL) {
			perror("Kreiranje nemoguce");
			exit(-1);
		}

	}
	else {
		fread(&zad_id_Clanova, sizeof(int), 1, fp);
	}
}
void init_list(LISTA_CLANOVA* lista) {
	lista->glava->next = lista->rep;
	lista->rep->prev = lista->glava;
}

void dodaj_clan(LISTA_CLANOVA* dll, MEMBER* temp) {
	if (dll->glava == NULL) {
		dll->glava = temp;
		return;
	}
	else if (dll->glava != NULL && dll->rep == NULL) {
		dll->rep = temp;
		init_list(dll);
		return;
	}
	else {
		temp->prev = dll->rep;
		dll->rep->next = temp;
		dll->rep = temp;
		return;
	}
}
void obrisi_clana(LISTA_CLANOVA* dll) {
	FILE* fp;
	FILE* fp_temp;
	MEMBER temp_dat;
	int found;
	int foundDat = 0;
	int id_clan;
	fp = fopen("clanovi.bin", "rb");
	if (!fp) {
		printf("nemoguce otvoriti");
		return NULL;
	}
	fp_temp = fopen("tmp.bin", "wb");
	if (!fp_temp) {
		printf("nemoguce otvoriti temp file u brisanju");
		return NULL;
	}
	printf("Unesite ID clana kojeg zelite obrisati: ");
	scanf("%d", &id_clan);
	MEMBER* ptr, * temp;
	temp = dll->glava;
	if (temp->id == id_clan){
		temp->next->prev = NULL;
		dll->glava = dll->glava->next;
		free(temp);
	}else if (dll->rep->id == id_clan){
		MEMBER* obrisat = dll->rep;
		dll->rep->prev->next = NULL;
		dll->rep = dll->rep->prev;
		free(obrisat);
	}
	else {
		while (temp->id != id_clan)
			temp = temp->next;
		temp->next->prev = temp->prev;
		temp->prev->next= temp->next;
		free(temp);
	}
	fwrite(&zad_id_Clanova, sizeof(int), 1, fp_temp);
	int fill;
	fread(&fill, sizeof(int), 1, fp);
	while (fread(&temp_dat, sizeof (MEMBER), 1, fp) != NULL) {
		if (temp_dat.id==id_clan) {
			printf("Pronadjen i obrisan iz datoteke.\n\n");
			foundDat = 1;
		}
		else {
			fwrite(&temp_dat, sizeof(MEMBER), 1, fp_temp);
		}
	}
	if (!foundDat) {
		printf("Nije pronaden nijedan clan s ID: %d u datoteci.\n\n", id_clan);
	}

	fclose(fp);
	fclose(fp_temp);

	remove("clanovi.bin");
	rename("tmp.bin", "clanovi.bin");


}
void init_list_knjiga(LISTA_KNJIGA* lista) {
	lista->glava->next = lista->rep;
	lista->rep->prev = lista->glava;
}

void dodaj_knjigu(LISTA_KNJIGA* dll, KNJIGA* temp) {
	if (dll->glava == NULL) {
		dll->glava = temp;
		return;
	}
	else if (dll->glava != NULL && dll->rep == NULL) {
		dll->rep = temp;
		init_list_knjiga(dll);
		return;
	}
	else {
		temp->prev = dll->rep;
		dll->rep->next = temp;
		dll->rep = temp;
		return;
	}
}
void obrisi_knjigu(LISTA_KNJIGA* dll) {
	FILE* fp;
	FILE* fp_temp;
	BOOK temp_dat;
	int found;
	int foundDat = 0;
	int id_clan;
	fp = fopen("clanovi.bin", "rb");
	if (!fp) {
		printf("nemoguce otvoriti");
		return NULL;
	}
	fp_temp = fopen("tmp.bin", "wb");
	if (!fp_temp) {
		printf("nemoguce otvoriti temp file u brisanju");
		return NULL;
	}
	printf("Unesite ID clana kojeg zelite obrisati: ");
	scanf("%d", &id_clan);
	BOOK* ptr, * temp;
	temp = dll->glava;
	if (temp->id == id_clan){
		temp->next->prev = NULL;
		dll->glava = dll->glava->next;
		free(temp);
	}else if (dll->rep->id == id_clan){
		KNJIGA* obrisat = dll->rep;
		dll->rep->prev->next = NULL;
		dll->rep = dll->rep->prev;
		free(obrisat);
	}
	else {
		while (temp->id != id_clan)
			temp = temp->next;
		temp->next->prev = temp->prev;
		temp->prev->next= temp->next;
		free(temp);
	}
	fwrite(&zad_id_knjiga, sizeof(int), 1, fp_temp);
	int fill;
	fread(&fill, sizeof(int), 1, fp);
	while (fread(&temp_dat, sizeof (BOOK), 1, fp) != NULL) {
		if (temp_dat.id==id_clan) {
			printf("Pronadjen i obrisan iz datoteke.\n\n");
			foundDat = 1;
		}
		else {
			fwrite(&temp_dat, sizeof(BOOK), 1, fp_temp);
		}
	}
	if (!foundDat) {
		printf("Nije pronaden nijedan clan s ID: %d u datoteci.\n\n", id_clan);
	}

	fclose(fp);
	fclose(fp_temp);

	remove("knjige.bin");
	rename("tmp.bin", "knjige.bin");


}

MEMBER* nadi_clana(LISTA_CLANOVA* dll, int id) {
	MEMBER* clan = dll->glava;
	while (clan->id != id) {
		if (clan->next == NULL) {
			return NULL;
		}
		clan = clan->next;
	}
	return clan;
}

void ispis_clanova(LISTA_CLANOVA* lista) {
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
	fwrite(headNode, sizeof(MEMBER), 1, fp);
	//fprintf(fp, "%s", "\n");
	fclose(fp);
}

