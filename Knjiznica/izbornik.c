#include "books.h"
#include "Header.h"
#include "izbornik.h"
void izbornik() {
	LISTA_CLANOVA* popisClanova;
	LISTA_KNJIGA* popisKnjiga;
	char choice;
	char choice_two;
	int choice_id;

	do {
		system("cls");
		printf("            GLAVNI IZBORNIK           \n");
		printf("1. Upravljanje: clanovi\n");
		printf("2. Upravljanje: knjige\n");
		printf("3. Pretraga clan\n");
		printf("4. Pretraga knjiga\n");
		printf("");
		choice = _getch();
		switch (choice) {
		case'1':
			do {
				system("cls");
				printf("Upravljanje clanovi\n");
				printf("1.Lista clanova\n");
				printf("2.Dodaj clana\n");
				printf("3.Obrisi clana\n");
				printf("4.Uredi clana\n");
				printf("5.Sortiranje clanova\n");
				choice_two = _getch();
				switch (choice_two) {
				case '1':
					system("cls");
					popisClanova = ucitaj_podatke("clanovi.bin");
					if (popisClanova == NULL) {
						printf("nema clanova");
						break;
					}
					ispis_clanova(popisClanova);
					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;
				case'2':

					system("cls");
					zapisi_clana("clanovi.bin");
					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;
				case '3':

					popisClanova = ucitaj_podatke("clanovi.bin");
					if (popisClanova == NULL) {
						printf("nema clanova");
					}
					ispis_clanova(popisClanova);
					obrisi_clana(popisClanova);

					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;
				case'4':
					popisClanova = ucitaj_podatke("clanovi.bin");
					if (popisClanova == NULL) {
						printf("nema clanova");
						break;
					}
					ispis_clanova(popisClanova);
					printf("\nIzaberite ID clana kojeg zelite urediti:");

					scanf("%d", &choice_id);
					uredi_clana(nadi_clana(popisClanova, choice_id));
					ispis_clanova(popisClanova);
					zapis_edita_clana(popisClanova);
					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;
				case '5':
					popisClanova = ucitaj_podatke("clanovi.bin");
					if (popisClanova == NULL) {
						printf("nema clanova");
						break;
					}
					MergeSort(&(popisClanova->glava));
					ispis_clanova(popisClanova);
					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;
				case 27:
					break;
				}
			} while (choice_two != 8);
			break;
		case'2':
			do{
				system("cls");
				printf("Upravljanje: knjige\n");
				printf("1.Lista knjiga\n");
				printf("2.Dodaj knjigu\n");
				printf("3.Obrisi knjigu\n");
				printf("4.Uredi knjigu\n");
				printf("5.Sortiranje knjiga\n");

				choice_two = _getch();
				switch (choice_two) {
				case '1':
					system("cls");
					popisKnjiga = ucitaj_podatke_knjiga("knjige.bin");
					if (popisKnjiga->glava == NULL&&popisKnjiga->rep==NULL) {
						printf("Nema knjiga za ispis");

					}
					ispis_knjiga(popisKnjiga);
					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;
				case'2':
					system("cls");
					zapisi_knjigu("knjige.bin");
					break;
				case'3':
					popisKnjiga = ucitaj_podatke_knjiga("knjige.bin");
					if (popisKnjiga == NULL) {
						printf("nema clanova");
						break;
					}
					ispis_knjiga(popisKnjiga);
					obrisi_knjigu(popisKnjiga);
					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;
				case'4':
					popisKnjiga = ucitaj_podatke_knjiga("knjige.bin");
					if (popisKnjiga == NULL) {
						printf("nema clanova");
						break;
					}
					ispis_knjiga(popisKnjiga);
					printf("\nIzaberite ID knjige koje zelite urediti:");
					
					scanf("%d", &choice_id);
					uredi_knjigu(nadi_knjigu(popisKnjiga, choice_id));
					ispis_knjiga(popisKnjiga);
					zapis_edita_knjige(popisKnjiga, br_knj,"knjige.bin");
					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;

				case '5':
					popisKnjiga= ucitaj_podatke_knjiga("knjige.bin");
					if (popisKnjiga == NULL) {
						printf("nema clanova");
						break;
					}
					MergeSortKnjiga(&(popisKnjiga->glava));
					ispis_knjiga(popisKnjiga);
					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;
				}
			} while (choice_two != 8);
			
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
	} while (choice != 27);
	_getch();



}