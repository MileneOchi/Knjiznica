#pragma once
#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"
typedef struct Clan {
	int id;
	int book;
	int books[10];
	char ime[20];
	char prezime[30];
	struct Clan* next;
	struct Clan* prev;
} CLAN;

typedef struct Lista {
	struct Clan* glava;
	struct Clan* rep;
}LISTA_CLANOVA;


void init_list(LISTA_CLANOVA*);
void dodaj_clan(LISTA_CLANOVA*, CLAN*);
void obrisi_clana(LISTA_CLANOVA*);
CLAN* nadi_clana(LISTA_CLANOVA*, int);
void ispis_clanova(LISTA_CLANOVA*,LISTA_KNJIGA*);
LISTA_CLANOVA* ucitaj_podatke(char*);
CLAN* zapisi_clana(char*);
void MergeSort(CLAN**);
CLAN* SortedMerge(CLAN*, CLAN*);
void FrontBackSplit(CLAN*,CLAN**, CLAN**);
void uredi_clana(LISTA_CLANOVA*);
void zapis_edita_clana(LISTA_CLANOVA*);
void posudba(LISTA_CLANOVA*,LISTA_KNJIGA*);
void vracanje(LISTA_CLANOVA*, LISTA_KNJIGA*);
void det_ispis(LISTA_KNJIGA*, LISTA_CLANOVA*);
void brisanje_file(const char*);
#endif