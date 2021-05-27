#pragma once
#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
typedef struct Knjiga {
	int id;
	char ime[30];
	char autor_ime[20];
	char autor_prezime[30];
	char zanr[20];
	int state;
	int date[10];
	struct Knjiga* next;
	struct Knjiga* prev;
} BOOK;

typedef struct Clan {
	int id;
	int book;
	int books[10];
	char ime[20];
	char prezime[30];
	struct Clan* next;
	struct Clan* prev;
} MEMBER;

typedef struct Lista {
	struct Clan* glava;
	struct Clan* rep;
}LISTA;

void izbornik();
MEMBER* zapisi_clana(void);
MEMBER* dodaj_novu_nodu(MEMBER*);
void init_list_mem(MEMBER*,MEMBER*);
void init_list(LISTA*);
void dodaj_clan(LISTA*, MEMBER*);
void dodaj_clan_mem(MEMBER*, MEMBER*,MEMBER*);
//MEMBER* citanje_clan(MEMBER**,MEMBER**,FILE*);
void ispis_liste_clanova(MEMBER*);
void provjera_Kreiranje_file(const char*);

void ispis_clanova(LISTA*);
void otvaranje_clanovi();
void unos_char(char*);
LISTA* ucitaj_podatke(char*);
#endif