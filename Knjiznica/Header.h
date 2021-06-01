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
}LISTA_CLANOVA;

void izbornik();
void init_list(LISTA_CLANOVA*);
void dodaj_clan(LISTA_CLANOVA*, MEMBER*);
void obrisi_clana(LISTA_CLANOVA*);
MEMBER* nadi_clana(LISTA_CLANOVA*, int);
void ispis_clanova(LISTA_CLANOVA*);
LISTA_CLANOVA* ucitaj_podatke(char*);
MEMBER* zapisi_clana(char*);
void provjera_Kreiranje_file(const char*);
BOOK* zapisi_knjigu(char*);
void provjera_Kreiranje_knjige(const char*);
#endif