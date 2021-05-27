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
void init_list(LISTA*);
void dodaj_clan(LISTA*, MEMBER*);
void obrisi_clana(LISTA*, int);
MEMBER* nadi_clana(LISTA*, int);
void ispis_clanova(LISTA*);
LISTA* ucitaj_podatke(char*);
void otvaranje_clanovi();
MEMBER* zapisi_clana(char*);
void provjera_Kreiranje_file(const char*);
#endif