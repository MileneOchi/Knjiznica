#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Header.h"
extern FILE* fp;
FILE* fp = NULL;

static int brojClanova = 0;
static int brojKnjiga = 0;

void izbornik() {
	provjera_Kreiranje_file("clanovi.bin");
	BOOK* bookHead = NULL;
	BOOK* bookTail = NULL;
	BOOK* bookTemp = NULL;
	MEMBER* membHead = NULL;
	MEMBER* membTail = NULL;
	LISTA* popisClanova;
	char choice;
	char choice_two;
	//membHead = napravi_listu();
	//do {
	//	membHead = dodaj_novu_nodu(membHead);
	//} while (membHead != NULL);
	do {
		system("cls");
		printf("            GLAVNI IZBORNIK           \n");
		printf("1. Upravljanje: clanovi\n");
		printf("2. Upravljanje: knjige\n");
		printf("3. Pretraga clan\n");
		printf("4. pretraga knjiga\n");
		printf("");
		choice = _getch();
		switch (choice) {
		case'1':
			do{
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
				ispis_liste_clanova(membHead);
				break;
			case'2':

				system("cls");
				zapisi_clana();
				do{
					choice_two = _getch();
				}while(choice_two != 'z');
				//otvaranje_clanovi();
				//dodaj_clan(&membHead);
				/*fread(&brojClanova, sizeof(int), 1, fp);
				fseek(fp, 0, SEEK_SET);
				brojClanova++;
				fwrite(&brojClanova, sizeof(int), 1, fp);

				fclose(fp);*/
				break;
			case '3':
				system("cls");
				popisClanova = ucitaj_podatke("clanoviDrugi.bin");
				ispis_clanova(popisClanova);
				do{
					choice_two = _getch();
				}while(choice_two != 'z');
				break;

			case 27:
				exit(-1);
			}
			}while(choice_two != '0');
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



void ispis_liste_clanova(MEMBER* h) {
	MEMBER* temp = h;
	while (temp != NULL) {

		printf("ID: %d\tIme: %s\tPrezime: %s", temp->id, temp->ime, temp->prezime);
		h = h->next;
	}
	printf("\n");
}

void provjera_Kreiranje_file(const char* ime) {
	fp = fopen(ime, "rb+");
	if (fp == NULL) {
		fp = fopen(ime, "ab+");
		if (fp == NULL) {
			perror("Kreiranje nemoguce");
			exit(-1);
		}
	}

}
void init_list(LISTA* lista){
	lista->glava->next = lista->rep;
	lista->rep->prev = lista->glava;
}

void dodaj_clan(LISTA* dll, MEMBER* temp) {
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
void obrisi_clana(LISTA* dll, int id_clan){
	MEMBER* trenutni = nadi_clana(dll, id_clan);
	if(trenutni != NULL){
			MEMBER* prethodni = trenutni->prev;
	MEMBER* sljedeci = trenutni->next;

	prethodni->next = sljedeci;
	sljedeci->prev = prethodni;
	free(trenutni);
	}

}
MEMBER* nadi_clana(LISTA* dll, int id){	
	MEMBER* clan = dll->glava;
	while(clan->id != id){
		if(clan->next == NULL){
			return NULL;
		}
		clan = clan->next;
	}
	return clan;
}

void ispis_clanova(LISTA* lista){
	MEMBER* pointer = lista->glava;
	printf("\n");
	if(pointer !=NULL){
		printf("%d ", pointer->id);
	}
	while(pointer->next != NULL){
		printf("%d	", pointer->id);
		pointer = pointer->next;
	}
}
void ispis_clanova_mem(MEMBER* cvor){
	MEMBER* pointer = cvor;
	printf("\n");
	if(pointer !=NULL){
		printf("%d ", pointer->id);
	}
	while(pointer->next != NULL){
		printf("%d	", pointer->id);
		pointer = pointer->next;
	}
}
LISTA* ucitaj_podatke(char* ime_datoteke){
	LISTA* lista = (LISTA*)calloc(1, sizeof(LISTA));
	provjera_Kreiranje_file(ime_datoteke);
	MEMBER* clan =(MEMBER*)calloc(1, sizeof(MEMBER));
	while (fread(clan, sizeof(MEMBER), 1, fp)) {
		dodaj_clan(lista, clan);
		clan =(MEMBER*)calloc(1, sizeof(MEMBER));
	}
	return lista;
}

MEMBER* zapisi_clana(void) {
	MEMBER* headNode = (MEMBER*)calloc(1, sizeof(MEMBER));
	if (headNode == NULL) {
		perror("kreiranje liste na pocetku");
		return NULL;
	}
	else {
		scanf( "%d", &headNode->id);
		scanf( "%d", &headNode->book);
		scanf( "%d", &headNode->books);
		scanf( "%s", &headNode->ime);
		scanf( "%s", &headNode->prezime);
	}
	FILE* pointer = fopen("clanoviDrugi.bin", "ab+");
	if (pointer == NULL) {
		perror("File error");
		system("pause");
		exit(-1);
	}
	fwrite(headNode, sizeof(MEMBER), 1, pointer);
	fclose(pointer);
}
