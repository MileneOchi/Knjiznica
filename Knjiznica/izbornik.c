#include "books.h"
#include "Header.h"
#include "izbornik.h"
void izbornik() {
	LISTA_CLANOVA* popisClanova;
	LISTA_KNJIGA* popisKnjiga;
	char choice;
	char choice_two;
	int br = 0;
	do {
		system("cls");
		printf("            GLAVNI IZBORNIK           \n");
		printf("1. Upravljanje: Clanovi\n");
		printf("2. Upravljanje: Knjige\n");
		printf("3. Posudba knjige\n");
		printf("4. Vracanje knjige\n");
		printf("Pritisnite ESCAPE za izlazak");
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
				printf("\nPritisnite backspace za povratak");
				choice_two = _getch();
				switch (choice_two) {
				case '1':
					system("cls");
					popisClanova = ucitaj_podatke("clanovi.bin");
					if (popisClanova->glava == NULL && popisClanova->rep == NULL) {
						printf("Nema clanova za ispis\n");

					}
					popisKnjiga = ucitaj_podatke_knjiga("knjige.bin");
					if (popisKnjiga->glava == NULL && popisKnjiga->rep == NULL) {
						printf("Nema knjiga za ispis");

					}

					ispis_clanova(popisClanova,popisKnjiga);
					printf("Pritisnite backspace za povratak");
					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;
				case'2':

					system("cls");
					zapisi_clana("clanovi.bin");
					printf("Pritisnite backspace za povratak");
					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;
				case '3':
					system("cls");
					popisClanova = ucitaj_podatke("clanovi.bin");
					if (popisClanova->glava == NULL && popisClanova->rep == NULL) {
						printf("Nema clanova za ispis\n");

					}
					popisKnjiga = ucitaj_podatke_knjiga("knjige.bin");
					if (popisKnjiga->glava == NULL && popisKnjiga->rep == NULL) {
						printf("Nema knjiga za ispis\n");

					}
					ispis_clanova(popisClanova, popisKnjiga);
					obrisi_clana(popisClanova);
					printf("\n\nPritisnite backspace za povratak");

					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;
				case'4':
					system("cls");
					popisClanova = ucitaj_podatke("clanovi.bin");
					if (popisClanova->glava == NULL && popisClanova->rep == NULL) {
						printf("Nema clanova za brisanje\n");

					}
					popisKnjiga = ucitaj_podatke_knjiga("knjige.bin");
					if (popisKnjiga->glava == NULL && popisKnjiga->rep == NULL) {
						printf("Nema knjiga za brisanje\n");

					}

					ispis_clanova(popisClanova, popisKnjiga);
					uredi_clana(popisClanova);
					ispis_clanova(popisClanova,popisKnjiga);
					zapis_edita_clana(popisClanova);
					printf("Pritisnite backspace za povratak");
					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;
				case '5':
					system("cls");
					popisClanova = ucitaj_podatke("clanovi.bin");
					if (popisClanova->glava == NULL && popisClanova->rep == NULL) {
						printf("Nema clanova za ispis\n");

					}
					popisKnjiga = ucitaj_podatke_knjiga("knjige.bin");
					if (popisKnjiga->glava == NULL && popisKnjiga->rep == NULL) {
						printf("Nema knjiga za ispis");

					}
					MergeSort(&(popisClanova->glava));
					

					ispis_clanova(popisClanova, popisKnjiga);
					printf("Pritisnite backspace za povratak");
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
				printf("6.Detaljan ispis knjiga\n");
				printf("\nPritisnite backspace za povratak...");
				choice_two = _getch();
				switch (choice_two) {
				case '1':
					system("cls");
					popisKnjiga = ucitaj_podatke_knjiga("knjige.bin");
					if (popisKnjiga->glava == NULL&&popisKnjiga->rep==NULL) {
						printf("Nema knjiga za ispis");

					}
					ispis_knjiga(popisKnjiga);
					printf("Pritisnite backspace za povratak");
					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;
				case'2':
					system("cls");
					zapisi_knjigu("knjige.bin");
					break;
				case'3':
					system("cls");
					popisKnjiga = ucitaj_podatke_knjiga("knjige.bin");
					if (popisKnjiga->glava == NULL) {
						printf("\nNema knjiga za brisanje\n");
					}
					ispis_knjiga(popisKnjiga);
					printf("\n");
					obrisi_knjigu(popisKnjiga);
					printf("\n\nPritisnite backspace za povratak...");
					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;
				case'4':
					system("cls");
					popisKnjiga = ucitaj_podatke_knjiga("knjige.bin");
					if (popisKnjiga->glava == NULL) {
						printf("\nNema knjiga za uredivanje\n");
						
					}
					
					uredi_knjigu(popisKnjiga);
					ispis_knjiga(popisKnjiga);
					zapis_edita_knjige(popisKnjiga);
					printf("Pritisnite backspace za povratak");
					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;

				case '5':
					system("cls");
					popisKnjiga= ucitaj_podatke_knjiga("knjige.bin");
					if (popisKnjiga->glava == NULL) {
						printf("\nNema knjiga za sortiranje\n");
					}
					MergeSortKnjiga(&(popisKnjiga->glava));
					ispis_knjiga(popisKnjiga);
					printf("Pritisnite backspace za povratak");
					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;
				case'6':
					system("cls");
					popisKnjiga = ucitaj_podatke_knjiga("knjige.bin");
					if (popisKnjiga->glava == NULL && popisKnjiga->rep == NULL) {
						printf("\nNema knjiga za ispis\n");
					}
					popisClanova = ucitaj_podatke("clanovi.bin");
					if (popisClanova->glava == NULL && popisClanova->rep == NULL) {
						printf("Nema clanova za detaljan ispis\n");

					}
					det_ispis(popisKnjiga, popisClanova);
					printf("Pritisnite backspace za povratak");
					do {
						choice_two = _getch();
					} while (choice_two != 8);
					break;
				}

			} while (choice_two != 8);
			
			break;
		
		case'3':
			system("cls");

			popisClanova = ucitaj_podatke("clanovi.bin");
			if (popisClanova->glava == NULL && popisClanova->rep == NULL) {
				printf("\nNema clanova za posudivanje\n");

			}
			popisKnjiga = ucitaj_podatke_knjiga("knjige.bin");
			if (popisKnjiga->glava == NULL && popisKnjiga->rep == NULL) {
				printf("Nema knjiga za posudivanje\n");

			}

			posudba(popisClanova, popisKnjiga);
			zapis_edita_clana(popisClanova);
			zapis_edita_knjige(popisKnjiga);

			printf("\nPritisnite backspace za povratak");
			do {
				choice_two = _getch();
			} while (choice_two != 8);
			break;
		case'4':
			system("cls");

			popisClanova = ucitaj_podatke("clanovi.bin");
			if (popisClanova->glava == NULL && popisClanova->rep == NULL) {
				printf("Nema clanova za vracanje");

			}
			popisKnjiga = ucitaj_podatke_knjiga("knjige.bin");
			if (popisKnjiga->glava == NULL && popisKnjiga->rep == NULL) {
				printf("Nema knjiga za vracanje");

			}
			
			vracanje(popisClanova, popisKnjiga);
			
			zapis_edita_clana(popisClanova);
			zapis_edita_knjige(popisKnjiga);
			printf("\nPritisnite backspace za povratak");
			do {
				choice_two = _getch();
			} while (choice_two != 8);
			break;
		case 27:
			exit(-1);
		}
	} while (choice != 27);
	_getch();



}