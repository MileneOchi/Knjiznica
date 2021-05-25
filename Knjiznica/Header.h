#pragma once
#ifndef HEADER_H
#define HEADER_H

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

void izbornik();

void citanje_clan(MEMBER**,MEMBER**,FILE*);
#endif