#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Header.h"

void izbornik() {
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
			printf("Pretrzivanje clana po: \n");
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
			printf("Pretrzivanje knjige po: \n");
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