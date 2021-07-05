
#define _CRT_SECURE_NO_WARNINGS
#include "izbornik.h"
#include "books.h"
FILE* fp=NULL;
static int zad_id_knjiga = 0;
int br_knj = 0;
KNJIGA* nadi_knjigu(LISTA_KNJIGA* dll, int id) {
	br_knj = 0;
	KNJIGA* clan = dll->glava;
	while (clan->id != id) {
		if (clan->next == NULL) {
			return NULL;
		}
		br_knj++;
		clan = clan->next;
	}
	return clan;
}

void ispis_knjiga(LISTA_KNJIGA* lista) {
	int br = 1;
	KNJIGA* pointer = lista->glava;
	printf("\n");
	if (lista->glava == NULL) {
		return;
	}
	printf("\tID\t\tIME\t\tAUTOR\n");
	while (pointer->next != NULL) {

		printf("%d.\t%d\t%10s\t\t%10s\n", br, pointer->id, pointer->ime, pointer->autor_prezime);
		pointer = pointer->next;
		br++;
	}
	printf("%d.\t%d\t%10s\t\t%10s\n", br, pointer->id, pointer->ime, pointer->autor_prezime);
}

LISTA_KNJIGA* ucitaj_podatke_knjiga(char* ime_datoteke) {
	LISTA_KNJIGA* lista = (LISTA_KNJIGA*)calloc(1, sizeof(LISTA_KNJIGA));
	if (lista == NULL) {
		perror("kreiranje");
		return NULL;
	}
	provjera_Kreiranje_knjige(ime_datoteke);
	KNJIGA* clan = (KNJIGA*)calloc(1, sizeof(KNJIGA));
	if (clan == NULL) {
		perror("kreiranje");
		return NULL;
	}
	while (fread(clan, sizeof(KNJIGA), 1, fp)) {
		dodaj_knjigu(lista, clan);
		clan = (KNJIGA*)calloc(1, sizeof(KNJIGA));
	}
	fclose(fp);
	return lista;
}

KNJIGA* zapisi_knjigu(char* ime_datoteke) {
	KNJIGA* headNode = (KNJIGA*)calloc(1, sizeof(KNJIGA));
	if (headNode == NULL) {
		perror("kreiranje");
		return NULL;
	}
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
		
		printf("Unesite ime knjige: ");
		scanf("%[^\n]", &headNode->ime);
		printf("Unesite ime autora knjige: ");
		scanf("%s", &headNode->autor_ime);
		printf("Unesite prezime autora knjige: ");
		scanf("%s", &headNode->autor_prezime);
		
		printf("Unesite zanr kjige: ");
		scanf("%s", &headNode->zanr);
		getchar();
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
	int id_knjige;
	fp = fopen("knjige.bin", "rb");
	if (!fp) {
		printf("nemoguce otvoriti");
		return NULL;
	}
	fp_temp = fopen("tmp_knj.bin", "wb");
	if (!fp_temp) {
		printf("nemoguce otvoriti temp file u brisanju");
		return NULL;
	}
	printf("Unesite ID clana kojeg zelite obrisati: ");
	scanf("%d", &id_knjige);
	KNJIGA* temp;
	temp = dll->glava;
	if (temp->id == id_knjige){
		temp->next->prev = NULL;
		dll->glava = dll->glava->next;
		free(temp);
	}else if (dll->rep->id == id_knjige){
		KNJIGA* obrisat = dll->rep;
		dll->rep->prev->next = NULL;
		dll->rep = dll->rep->prev;
		free(obrisat);
	}
	else {
		while (temp->id != id_knjige)
			temp = temp->next;
		temp->next->prev = temp->prev;
		temp->prev->next= temp->next;
		free(temp);
	}
	fwrite(&zad_id_knjiga, sizeof(int), 1, fp_temp);
	int fill;
	fread(&fill, sizeof(int), 1, fp);
	while (fread(&temp_dat, sizeof (KNJIGA), 1, fp) != NULL) {
		if (temp_dat.id==id_knjige) {
			printf("Pronadjen i obrisan iz datoteke.\n\n");
			foundDat = 1;
		}
		else {
			fwrite(&temp_dat, sizeof(KNJIGA), 1, fp_temp);
		}
	}
	if (!foundDat) {
		printf("Nije pronaden nijedna knjiga s ID: %d u datoteci.\n\n", id_knjige);
	}

	fclose(fp);
	fclose(fp_temp);

	remove("knjige.bin");
	rename("tmp_knj.bin", "knjige.bin");


}


void MergeSortKnjiga(KNJIGA** listaClanova) {
	KNJIGA* head = *listaClanova;
	KNJIGA* a;
	KNJIGA* b;
	if ((head == NULL) || (head->next == NULL)) {
		return;
	}

	FrontBackSplitKnjiga(head, &a, &b);

	MergeSortKnjiga(&a);
	MergeSortKnjiga(&b);

	*listaClanova = SortedMergeKnjiga(a, b);
}

KNJIGA* SortedMergeKnjiga(KNJIGA* a, KNJIGA* b)
{
	KNJIGA* result = NULL;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (strcmp(a->ime, b->ime) == -1) {
		result = a;
		result->next = SortedMergeKnjiga(a->next, b);
		result->next->prev = result;
		result->prev = NULL;
	}
	else {
		result = b;
		result->next = SortedMergeKnjiga(a, b->next);
		result->next->prev = result;
		result->prev = NULL;
	}
	return (result);
}

void FrontBackSplitKnjiga(KNJIGA* source, KNJIGA** frontRef, KNJIGA** backRef)
{
	KNJIGA* fast;
	KNJIGA* slow;
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
	slow->next->prev = NULL;
	*backRef = slow->next;
	
	slow->next = NULL;
}

void uredi_knjigu(KNJIGA*head) {
	if (head->next == NULL && head->prev == NULL) {
		return NULL;
	}
	char choice;
	printf("\tID\t\tIME\t\tAUTOR\t   ZANR\n");
	printf("\t%d\t%10s\t%10s\t%10s\n\n", head->id, head->ime, head->autor_prezime,head->zanr);
	do {
		
		printf("Koju varijablu zelite urediti\n");
		printf("1.\tID\n");
		printf("2.\tIME KNJIGE\n");
		printf("3.\tIME AUTORA\n");
		printf("4.\tPREZIME AUTORA\n");
		printf("5.\tZANR\n");
		choice = _getch();
		switch (choice) {
		case'1':
			getchar();
			printf("Unesi novi ID:");
			scanf("%d", &head->id);
			break;
		case'2':
			getchar();
			printf("Unesi novo ime knjige");
			scanf("%[^\n]", &head->ime);
			return;
		case'3':
			getchar();
			printf("Unesi novo ime autora");
			scanf("%s", &head->autor_ime);
			break;
		case'4':
			getchar();
			printf("Unesi novo prezime autora knjige: ");
			scanf("%s", &head->autor_prezime);
			break;
		}
	} while (choice != 'z');
	
}

void zapis_edita_knjige(LISTA_KNJIGA*head){
	provjera_Kreiranje_knjige("knjige.bin");
	int ret;
	FILE* fp_temp;
	KNJIGA* flg = head->glava;
	fp_temp = fopen("tmp_knj.bin", "wb");
	if (!fp_temp) {
		printf("nemoguce otvoriti temp file u brisanju");
		return NULL;
	}
	fwrite(&zad_id_knjiga, sizeof(int), 1, fp_temp);
	while(flg->next!=NULL){
		if (fwrite(flg, sizeof(KNJIGA), 1, fp_temp) == -1) {
			printf("greska pisanja");
			break;
		}
		flg = flg->next;
	}
	fwrite(flg, sizeof(KNJIGA), 1, fp_temp);
	fclose(fp);

	fclose(fp_temp);
	ret=remove("knjige.bin");

	if (ret == 0) {
		printf("File deleted successfully");
	}
	else {
		printf("Error: unable to delete the file");
	}

	rename("tmp_knj.bin", "knjige.bin");
}
