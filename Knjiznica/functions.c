#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Header.h"
extern FILE* fp;
FILE* fp = NULL;

static int brojClanova = 0;
static int brojKnjiga= 0;

void izbornik() {
	provjera_Kreiranje_file("clanovi.bin");
	BOOK* bookHead = NULL;
	BOOK* bookTail = NULL;
	BOOK* bookTemp = NULL;
	MEMBER* membHead = NULL;
	MEMBER* membTail = NULL;
	char choice;
	char choice_two;
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
				citanje_clan(&membHead,&membTail,fp);
				ispis_liste_clanova(membHead);
				break;
			case'2':

				system("cls");
				otvaranje_clanovi();
				dodaj_clan(&membHead);
				fread(&brojClanova, sizeof(int), 1, fp);
				fseek(fp, 0, SEEK_SET);
				brojClanova++;
				fwrite(&brojClanova, sizeof(int), 1, fp);

				fclose(fp);
				break;
			case 27:
				exit(-1);
			}
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

void citanje_clan(MEMBER**h,MEMBER**t,FILE*fp) {
	fp = fopen("clanovi.bin", "rb+" );
	if (fp = NULL) {
		perror("FILE ERROR");
		system("pause");
		exit(-1);
	}
	

}

void ispis_liste_clanova(MEMBER*h) {
	MEMBER* temp = NULL;
	while (h != NULL) {
		printf("ID: %d\tIme: %s\tPrezime: %s", h->id, h->ime, h->prezime);
		temp = h;
		h = h->next;
	}

}

void provjera_Kreiranje_file(const char*ime){
	fp = fopen(ime, "rb+");
	if (fp == NULL) {
		fp = fopen(ime, "ab+");
		if (fp == NULL) {
			perror("Kreiranje nemoguce");
			exit(-1);
		}
		else {
			fclose(fp);
			fp = NULL;
		}
	}

}

void dodaj_clan(MEMBER** h) {
	MEMBER* temp = (MEMBER*)malloc(sizeof(MEMBER));
	MEMBER* zadnji = *h;
	temp->id = brojClanova + 1;
	printf("Unesite ime clana: ");
	strcpy(temp->ime, unos(20));
	printf("Unesite prezime clana: ");
	strcpy(temp->prezime, unos(30));
	temp->next = NULL;
	if (*h == NULL) {
		temp->prev = NULL;
		*h = temp;
		return;
	}
	while (zadnji->next != NULL)
		zadnji = zadnji->next;
	zadnji->next = temp;
	temp->prev = zadnji;
	return;
}

void otvaranje_clanovi() {
	if (fp != NULL) {
		fclose(fp);
		fp = NULL;
	}
	fp = fopen("clanovi.bin", "rb+");
	if (fp == NULL) {
		perror("File error");
		system("pause");
		exit(-1);
	}
}

char *unos(int broj) {
	char* temp = (char*)malloc(broj * sizeof(char));
	fgets(temp, broj - 1, stdin);
	int tempc = 0;
	while (*(temp + tempc) != '\n')
		++tempc;
	*(temp + tempc) = '\0';
	return temp;
}