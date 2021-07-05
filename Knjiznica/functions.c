
#define _CRT_SECURE_NO_WARNINGS

#include "Header.h"
#include "books.h"
#include "izbornik.h"
FILE* fp;

static int zad_id_clanova;


void provjera_Kreiranje_file(const char* ime) {
	fp = fopen(ime, "rb+");
	if (fp == NULL) {
		zad_id_clanova = 0;
		fp = fopen(ime, "ab+");
		//fwrite(&zad_id_Clanova, sizeof(int), 1, fp);
		if (fp == NULL) {
			perror("Kreiranje nemoguce");
			exit(-1);
		}

	}
	else {
		fread(&zad_id_clanova, sizeof(int), 1, fp);
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
	fwrite(&zad_id_clanova, sizeof(int), 1, fp_temp);
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

void ispis_clanova(LISTA_CLANOVA* lista,LISTA_KNJIGA*lista_knjiga) {
	int br = 1;
	int br_2 = 0;
	CLAN* pointer = lista->glava;
	KNJIGA* p = NULL;
	printf("\n");
	if (lista->glava == NULL) {
		return;
	}
	printf("\tID\t      IME\t    PREZIME\tBROJ KNJIGA\n");
	while (pointer->next != NULL) {

		printf("%d.\t%d\t%10s\t%10s\t%d\n", br, pointer->id, pointer->ime, pointer->prezime,pointer->book);
		if (pointer->book != 0) {

			p = nadi_knjigu(lista_knjiga, pointer->books[br_2++]);
			if (p == NULL) {
				break;
			}
			printf("%s", p->ime);
		}
		pointer = pointer->next;
		br++;
	}
	printf("%d.\t%d\t%10s\t%10s\t%d\n", br, pointer->id, pointer->ime, pointer->prezime,pointer->book);
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
	zad_id_clanova++;
	headNode->id = zad_id_clanova;
	printf("(%d)\n", zad_id_clanova);
	//fp = fopen(ime_datoteke, "ab+");
	if (fp == NULL) {
		perror("File error");
		system("pause");
		exit(-1);
	}
	fseek(fp, 0, SEEK_SET);
	fwrite(&zad_id_clanova, sizeof(int), 1, fp);
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

void MergeSort(CLAN** listaClanova){
    CLAN* head = *listaClanova;
    CLAN* a;
    CLAN* b;
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
 
    FrontBackSplit(head, &a, &b);
 
    MergeSort(&a);
    MergeSort(&b);

    *listaClanova = SortedMerge(a, b);
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
	slow->next->prev = NULL;
	*backRef = slow->next;

	slow->next = NULL;
}

void uredi_clana(CLAN* head) {
	if (head->next == NULL && head->prev == NULL) {
		return NULL;
	}
	char choice;
	printf("\tID\t\tIME\t\tAUTOR\t   ZANR\n");
	printf("\t%d\t%10s\t%10s\n\n", head->id, head->ime, head->prezime);
	do {

		printf("Koju varijablu zelite urediti\n");
		printf("1.\tID\n");
		printf("2.\tIME CLANA\n");
		printf("3.\tPREZIME CLANA\n");
		choice = _getch();
		switch (choice) {
		case'1':
			getchar();
			printf("Unesi novi ID: ");
			scanf("%d", &head->id);
			break;
		case'2':
			getchar();
			printf("Unesi novo ime clana: ");
			scanf("%[^\n]", &head->ime);
			return;
		case'3':
			getchar();
			printf("Unesi novo prezime clana: ");
			scanf("%s", &head->prezime);
			break;
		}
	} while (choice != 'z');

}

void zapis_edita_clana(LISTA_CLANOVA* head) {
	provjera_Kreiranje_file("clanovi.bin");
	int ret;
	FILE* fp_temp;
	CLAN* flg = head->glava;
	fp_temp = fopen("tmp_cln.bin", "wb");
	if (!fp_temp) {
		printf("nemoguce otvoriti temp file u brisanju");
		return NULL;
	}
	fwrite(&zad_id_clanova, sizeof(int), 1, fp_temp);
	while (flg->next != NULL) {
		if (fwrite(flg, sizeof(CLAN), 1, fp_temp) == -1) {
			printf("greska pisanja");
			break;
		}
		flg = flg->next;
	}
	fwrite(flg, sizeof(CLAN), 1, fp_temp);
	fclose(fp);

	fclose(fp_temp);
	ret = remove("clanovi.bin");

	if (ret == 0) {
		printf("File deleted successfully");
	}
	else {
		printf("Error: unable to delete the file");
	}

	rename("tmp_cln.bin", "clanovi.bin");
}

void posudba(CLAN* clan,KNJIGA*knjiga) {
	knjiga->id_clana = clan->id;
	knjiga->state = 1;
	time_t vrijeme = time(NULL);
	struct tm datum = *localtime(&vrijeme);
	knjiga->date = datum.tm_yday;
	clan->book+=1;
	for (int i = 0; i < clan->book; i++) {
		if (clan->books[i] == 0) {
			clan->books[i] = knjiga->id;
		}
	}
}