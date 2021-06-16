
#define _CRT_SECURE_NO_WARNINGS

#include "Header.h"
#include "books.h"
#include "izbornik.h"
FILE* fp;

static int zad_id_Clanova;


struct clan* first = NULL;
struct clan* last = NULL;


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

/* Merge two sorted lists. p1 and p2 are != NULL */
CLAN* merge(struct CLAN* p1, struct CLAN* p2) {
	struct CLAN* head, ** pp;
	pp = &head;
	for (;;) {
		if (strcmp(p1->Nachname, p2->Nachname) <= 0) {
			*pp = p1;
			pp = &p1->next;
			p1 = p1->next;
			if (p1 == NULL) {
				*pp = p2;
				break;
			}
		}
		else {
			*pp = p2;
			pp = &p2->next;
			p2 = p2->next;
			if (p2 == NULL) {
				*pp = p1;
				break;
			}
		}
	}
	return head;
}

void sort(void) {
	struct CLAN* p1, * p2;
	/* sort the list as a singly linked list */
	first = msort(first);
	/* reconstruct the backlinks */
	p1 = NULL;
	for (p2 = first; p2; p2 = p2->next) {
		p2->last = p1;
		p1 = p2;
	}
	last = p1;
}

/* bottom-up merge sort with sublist array */
CLAN* msort(struct CLAN* head) {
	struct CLAN* array[32] = { NULL };
	int i;

	/* handle trivial lists */
	if (head == NULL || head->next == NULL)
		return head;

	i = 0;  /* avoid warning */
	p1 = head;
	/* merge nodes into pending lists of increasing lengths */
	while (head != NULL) {
		struct CLAN* next = head->next;
		head->next = NULL;
		for (i = 0; i < 32 && array[i] != NULL; i++) {
			head = merge(array[i], head);
			array[i] = NULL;
		}
		/* do not go past end of array */
		if (i == 32)
			i--;
		array[i] = head;
		head = next;
	}
	/* merge pending lists into single list:
	 * the last element stored into the array is at offset i and
	 * all entries before it are NULL pointers. */
	for (head = array[i++]; i < 32; i++) {
		if (array[i] != NULL)
			head = merge(array[i], head);
	}
	return head;
}