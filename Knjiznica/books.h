#pragma once
#ifndef BOOKS_H
#define BOOKS_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Knjiga {
	int id;
	char ime[30];
	char autor_ime[20];
	char autor_prezime[30];
	char zanr[20];
	int state;
	int id_clana;
	char date[30];
	struct Knjiga* next;
	struct Knjiga* prev;
} KNJIGA;

typedef struct Lista_knjiga {
	struct Knjiga* glava;
	struct Knjiga* rep;
}LISTA_KNJIGA;

void init_list_knjiga(LISTA_KNJIGA*);
void dodaj_knjigu(LISTA_KNJIGA*, KNJIGA*);
void provjera_Kreiranje_file(const char*);
KNJIGA* zapisi_knjigu(char*);
void provjera_Kreiranje_knjige(const char*);
void ispis_knjiga(LISTA_KNJIGA*);
LISTA_KNJIGA* ucitaj_podatke_knjiga(char*);
void obrisi_knjigu(LISTA_KNJIGA*);
void MergeSortKnjiga(KNJIGA**);
KNJIGA* SortedMergeKnjiga(KNJIGA*, KNJIGA*);
void FrontBackSplitKnjiga(KNJIGA*, KNJIGA**, KNJIGA**);
KNJIGA* nadi_knjigu(LISTA_KNJIGA*, int);
void uredi_knjigu(LISTA_KNJIGA*);
void zapis_edita_knjige(LISTA_KNJIGA*);
#endif