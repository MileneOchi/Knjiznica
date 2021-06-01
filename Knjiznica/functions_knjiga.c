
#include "books.h"
static int zad_id_knjiga = 0;

//KNJIGA* nadi_clana(LISTA_KNJIGA* dll, int id) {
//	KNJIGA* clan = dll->glava;
//	while (clan->id != id) {
//		if (clan->next == NULL) {
//			return NULL;
//		}
//		clan = clan->next;
//	}
//	return clan;
//}

void ispis_knjiga(LISTA_KNJIGA* lista) {
	int br = 1;
	KNJIGA* pointer = lista->glava;
	printf("\n");
	if (lista->glava == NULL) {
		return;
	}
	printf("\tID\t      IME\t    PREZIME\n");
	while (pointer->next != NULL) {

		printf("%d.\t%d\t%10s\t%10s\n", br, pointer->id, pointer->ime, pointer->autor_prezime);
		pointer = pointer->next;
		br++;
	}
	printf("%d.\t%d\t%10s\t%10s\n", br, pointer->id, pointer->ime, pointer->autor_prezime);
}

LISTA_KNJIGA* ucitaj_podatke_knjiga(char* ime_datoteke) {
	LISTA_KNJIGA* lista = (LISTA_KNJIGA*)calloc(1, sizeof(LISTA_KNJIGA));
	provjera_Kreiranje_file(ime_datoteke);
	KNJIGA* clan = (KNJIGA*)calloc(1, sizeof(KNJIGA));
	while (fread(clan, sizeof(KNJIGA), 1, fp)) {
		dodaj_knjigu(lista, clan);
		clan = (KNJIGA*)calloc(1, sizeof(KNJIGA));
	}
	fclose(fp);
	return lista;
}

KNJIGA* zapisi_knjigu(char* ime_datoteke) {
	KNJIGA* headNode = (KNJIGA*)calloc(1, sizeof(KNJIGA));
	provjera_Kreiranje_knjige(ime_datoteke);
	zad_id_knjiga++;
	headNode->id = zad_id_knjiga;
	printf("(%d)\n", zad_id_knjiga);
	//fp = fopen(ime_datoteke, "ab+");
	if (fp == NULL) {
		perror("File error");
		system("pause");
		exit(-1);
	}
	fseek(fp, 0, SEEK_SET);
	fwrite(&zad_id_knjiga, sizeof(int), 1, fp);
	if (headNode == NULL) {
		perror("kreiranje liste na pocetku");
		return NULL;
	}
	else {
		printf("Unesite ime novog korisnika: ");
		scanf("%s", &headNode->ime);
		printf("Unesite ime novog korisnika: ");
		scanf("%s", &headNode->autor_ime);
		printf("Unesite ime novog korisnika: ");
		scanf("%s", &headNode->autor_prezime);
		printf("Unesite prezime novog korisnika: ");
		scanf("%s", &headNode->zanr);
	}
	fclose(fp);
	fp = fopen(ime_datoteke, "ab+");
	fwrite(headNode, sizeof(KNJIGA), 1, fp);
	fclose(fp);
}


void provjera_Kreiranje_knjige(const char* ime) {

	fp = fopen(ime, "rb+");
	if (fp == NULL) {
		zad_id_knjiga = 0;
		fp = fopen(ime, "ab+");
		//fwrite(&zad_id_Clanova, sizeof(int), 1, fp);
		if (fp == NULL) {
			perror("Kreiranje nemoguce");
			exit(-1);
		}

	}
	else {
		fread(&zad_id_knjiga, sizeof(int), 1, fp);
	}
}

void init_list_knjiga(LISTA_KNJIGA* lista) {
	lista->glava->next = lista->rep;
	lista->rep->prev = lista->glava;
}

void dodaj_knjigu(LISTA_KNJIGA* dll, KNJIGA* temp) {
	if (dll->glava == NULL) {
		dll->glava = temp;
		return;
	}
	else if (dll->glava != NULL && dll->rep == NULL) {
		dll->rep = temp;
		init_list_knjiga(dll);
		return;
	}
	else {
		temp->prev = dll->rep;
		dll->rep->next = temp;
		dll->rep = temp;
		return;
	}
}
void obrisi_knjigu(LISTA_KNJIGA* dll) {
	FILE* fp;
	FILE* fp_temp;
	KNJIGA temp_dat;
	int foundDat = 0;
	int id_clan;
	fp = fopen("clanovi.bin", "rb");
	if (!fp) {
		printf("nemoguce otvoriti");
		return NULL;
	}
	fp_temp = fopen("tmp.bin", "wb");
	if (!fp_temp) {
		printf("nemoguce otvoriti temp file u brisanju");
		return NULL;
	}
	printf("Unesite ID clana kojeg zelite obrisati: ");
	scanf("%d", &id_clan);
	KNJIGA* temp;
	temp = dll->glava;
	if (temp->id == id_clan){
		temp->next->prev = NULL;
		dll->glava = dll->glava->next;
		free(temp);
	}else if (dll->rep->id == id_clan){
		KNJIGA* obrisat = dll->rep;
		dll->rep->prev->next = NULL;
		dll->rep = dll->rep->prev;
		free(obrisat);
	}
	else {
		while (temp->id != id_clan)
			temp = temp->next;
		temp->next->prev = temp->prev;
		temp->prev->next= temp->next;
		free(temp);
	}
	fwrite(&zad_id_knjiga, sizeof(int), 1, fp_temp);
	int fill;
	fread(&fill, sizeof(int), 1, fp);
	while (fread(&temp_dat, sizeof (KNJIGA), 1, fp) != NULL) {
		if (temp_dat.id==id_clan) {
			printf("Pronadjen i obrisan iz datoteke.\n\n");
			foundDat = 1;
		}
		else {
			fwrite(&temp_dat, sizeof(KNJIGA), 1, fp_temp);
		}
	}
	if (!foundDat) {
		printf("Nije pronaden nijedan clan s ID: %d u datoteci.\n\n", id_clan);
	}

	fclose(fp);
	fclose(fp_temp);

	remove("knjige.bin");
	rename("tmp.bin", "knjige.bin");


}