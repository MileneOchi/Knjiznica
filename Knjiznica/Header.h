#pragma once
#ifndef HEADER_H
#define HEADER_H

typedef struct Book {
	int id;
	char ime[30];
	char autor_ime[20];
	char autor_prezime[30];
	char zanr[20];
	int state;
	int date[10];
	struct Book* next;
	struct Book* prev;
} BOOK;

typedef struct Member {
	int id;
	int book;
	int books[10];
	char name[20];
	char lastName[30];
	struct Member* next;
	struct Member* prev;
} MEMBER;

void izbornik();
#endif