
#define _CRT_SECURE_NO_WARNINGS

#include "Header.h"
#include "books.h"
#include "izbornik.h"
FILE* fp;

static int zad_id_Clanova;


void provjera_Kreiranje_file(const char* ime) {
	fp = fopen(ime, "rb+");
	if (fp == NULL) {
		zad_id_Clanova = 0;
		fp = fopen(ime, "ab+");
		//fwrite(&zad_id_Clanova, sizeof(int), 1, fp);
		if (fp == NULL) {
			perror("Kreiranje nemoguce");
			exit(-1);
		}

	}
	else {
		fread(&zad_id_Clanova, sizeof(int), 1, fp);
	}
}
void init_list(LISTA_CLANOVA* lista) {
	lista->glava->next = lista->rep;
	lista->rep->prev = lista->glava;
}

void dodaj_clan(LISTA_CLANOVA* dll, CLAN* temp) {
	if (dll->glava == NULL) {
		dll->glava = temp;
		return;
	}
	else if (dll->glava != NULL && dll->rep == NULL) {
		dll->rep = temp;
		init_list(dll);
		return;
	}
	else {
		temp->prev = dll->rep;
		dll->rep->next = temp;
		dll->rep = temp;
		return;
	}
}
void obrisi_clana(LISTA_CLANOVA* dll) {
	FILE* fp;
	FILE* fp_temp;
	CLAN temp_dat;
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
	CLAN * temp;
	temp = dll->glava;
	if (temp->id == id_clan){
		temp->next->prev = NULL;
		dll->glava = dll->glava->next;
		free(temp);
	}else if (dll->rep->id == id_clan){
		CLAN* obrisat = dll->rep;
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
	fwrite(&zad_id_Clanova, sizeof(int), 1, fp_temp);
	int fill;
	fread(&fill, sizeof(int), 1, fp);
	while (fread(&temp_dat, sizeof (CLAN), 1, fp) != NULL) {
		if (temp_dat.id==id_clan) {
			printf("Pronadjen i obrisan iz datoteke.\n\n");
			foundDat = 1;
		}
		else {
			fwrite(&temp_dat, sizeof(CLAN), 1, fp_temp);
		}
	}
	if (!foundDat) {
		printf("Nije pronaden nijedan clan s ID: %d u datoteci.\n\n", id_clan);
	}

	fclose(fp);
	fclose(fp_temp);

	remove("clanovi.bin");
	rename("tmp.bin", "clanovi.bin");


}

CLAN* nadi_clana(LISTA_CLANOVA* dll, int id) {
	CLAN* clan = dll->glava;
	while (clan->id != id) {
		if (clan->next == NULL) {
			return NULL;
		}
		clan = clan->next;
	}
	return clan;
}

void ispis_clanova(LISTA_CLANOVA* lista) {
	int br = 1;
	CLAN* pointer = lista->glava;
	printf("\n");
	if (lista->glava == NULL) {
		return;
	}
	printf("\tID\t      IME\t    PREZIME\n");
	while (pointer->next != NULL) {

		printf("%d.\t%d\t%10s\t%10s\n", br, pointer->id, pointer->ime, pointer->prezime);
		pointer = pointer->next;
		br++;
	}
	printf("%d.\t%d\t%10s\t%10s\n", br, pointer->id, pointer->ime, pointer->prezime);
}

LISTA_CLANOVA* ucitaj_podatke(char* ime_datoteke) {
	LISTA_CLANOVA* lista = (LISTA_CLANOVA*)calloc(1, sizeof(LISTA_CLANOVA));
	if (lista == NULL) {
		perror("kreiranje");
		return NULL;
	}
	provjera_Kreiranje_file(ime_datoteke);
	CLAN* clan = (CLAN*)calloc(1, sizeof(CLAN));
	if (clan == NULL) {
		perror("kreiranje");
		return NULL;
	}
	while (fread(clan, sizeof(CLAN), 1, fp)) {
		dodaj_clan(lista, clan);
		clan = (CLAN*)calloc(1, sizeof(CLAN));
	}
	fclose(fp);
	return lista;
}

CLAN* zapisi_clana(char* ime_datoteke) {
	CLAN* headNode = (CLAN*)calloc(1, sizeof(CLAN));
	if (headNode == NULL) {
		perror("kreiranje");
		return NULL;
	}
	provjera_Kreiranje_file(ime_datoteke);
	zad_id_Clanova++;
	headNode->id = zad_id_Clanova;
	printf("(%d)\n", zad_id_Clanova);
	//fp = fopen(ime_datoteke, "ab+");
	if (fp == NULL) {
		perror("File error");
		system("pause");
		exit(-1);
	}
	fseek(fp, 0, SEEK_SET);
	fwrite(&zad_id_Clanova, sizeof(int), 1, fp);
	if (headNode == NULL) {
		perror("kreiranje liste na pocetku");
		return NULL;
	}
	else {
		printf("Unesite ime novog korisnika: ");
		scanf("%s", &headNode->ime);
		printf("Unesite prezime novog korisnika: ");
		scanf("%s", &headNode->prezime);
	}
	fclose(fp);
	fp = fopen(ime_datoteke, "ab+");
	fwrite(headNode, sizeof(CLAN), 1, fp);
	//fprintf(fp, "%s", "\n");
	fclose(fp);
}

void MergeSort(LISTA_CLANOVA* listaClanova){
    CLAN* head = listaClanova->glava;
    CLAN* a;
    CLAN* b;
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
 
    FrontBackSplit(head, &a, &b);
 
    MergeSort(&a);
    MergeSort(&b);

    listaClanova->glava = SortedMerge(a, b);
}
 
CLAN* SortedMerge(CLAN* a, CLAN* b)
{
    CLAN* result = NULL;
 
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);
    if (strcmp(a->ime, b->ime)==-1) {
        result = a;
        result->next = SortedMerge(a->next, b);
		result->next->prev = result;
		result->prev = NULL;
    }
    else {
        result = b;
        result->next = SortedMerge(a, b->next);
		result->next->prev = result;
		result->prev = NULL;
    }
    return (result);
}
 
void FrontBackSplit(CLAN* source, CLAN** frontRef, CLAN** backRef)
{
	CLAN* fast;
	CLAN* slow;
    slow = source;
    fast = source->next;
 
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}