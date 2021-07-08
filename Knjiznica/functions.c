
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
	CLAN temp_dat;
	int foundDat = 0;
	int id_clan;
	if (dll->glava == NULL&&dll->rep==NULL) {
		return;
	}
	printf("Unesite ID clana kojeg zelite obrisati: ");
	scanf("%d", &id_clan);
	CLAN * temp;
	temp = dll->glava;
	if (temp->id == id_clan){
		if (temp->next == NULL) {
			dll->glava = NULL;
		}
		else {
			temp->next->prev = NULL;
			dll->glava = dll->glava->next;
		}
		free(temp);
	}else if (dll->rep->id == id_clan){
		CLAN* obrisat = dll->rep;
		dll->rep->prev->next = NULL;
		dll->rep = dll->rep->prev;
		free(obrisat);
	}
	else {
		while (temp->id != id_clan){
			temp = temp->next;
			if (temp == NULL) {
				printf("\nTaj clan ne postoji");
				return;
			}
		}
		temp->next->prev = temp->prev;
		temp->prev->next= temp->next;
		free(temp);
	}

	zapis_edita_clana(dll);

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
	printf("\tID\t      IME\t    PREZIME\tBROJ KNJIGA\t IMENA KNJIGA\n");
	while (pointer->next != NULL) {

		printf("%d.\t%d\t%10s\t%10s\t   %d \t\t", br, pointer->id, pointer->ime, pointer->prezime,pointer->book);
		for (int i = 0; i < 10; i++) {
			p = nadi_knjigu(lista_knjiga, pointer->books[br_2++]);
			if (p != NULL) {
				printf("%s\t", p->ime);
			}
		}

			
		br_2 = 0;
		pointer = pointer->next;
		br++;
		printf("\n");
	}
	br_2 = 0;
	printf("%d.\t%d\t%10s\t%10s\t   %d \t\t", br, pointer->id, pointer->ime, pointer->prezime,pointer->book);
	do {
		p = nadi_knjigu(lista_knjiga, pointer->books[br_2++]);
		if (p == NULL) {
			break;
		}
		printf("%s\t", p->ime);
	} while (pointer->book != 0);
	printf("\n");
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
		getchar();
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

void uredi_clana(LISTA_CLANOVA* lista) {
	int choice_id;
	if (lista->glava == NULL && lista->rep == NULL) {
		return;
	}
	printf("\nIzaberite ID clana kojeg zelite urediti:");

	scanf("%d", &choice_id);
	CLAN*temp=nadi_clana(lista, choice_id);
	char choice;
	printf("\tID\t\tIME\t\tAUTOR\n");
	printf("\t%d\t%10s\t%10s\n\n", temp->id, temp->ime, temp->prezime);
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
			scanf("%d", &temp->id);
			return;
		case'2':
			getchar();
			printf("Unesi novo ime clana: ");
			scanf("%[^\n]", &temp->ime);
			return;
		case'3':
			getchar();
			printf("Unesi novo prezime clana: ");
			scanf("%s", &temp->prezime);
			return;
		}
	} while (choice != 8);

}

void zapis_edita_clana(LISTA_CLANOVA* head) {
	provjera_Kreiranje_file("clanovi.bin");
	int ret;
	FILE* fp_temp;
	CLAN* flg = head->glava;
	if (head->glava == NULL) {
		return;
	}
	fp_temp = fopen("tmp_cln.bin", "wb");
	if (!fp_temp) {
		printf("nemoguce otvoriti temp file u brisanju");
		return ;
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
		printf("\nUspjesno upisani u datoteku clanovi\n");
	}
	else {
		printf("Error: nije moguc upis u datoteku clanova\n");
	}

	rename("tmp_cln.bin", "clanovi.bin");
}

void posudba(LISTA_CLANOVA* clan,LISTA_KNJIGA*knjiga) {
	int choice_id;
	int choice_id_knjiga;
	CLAN* check=NULL;
	KNJIGA* check_knj=NULL;
	if (clan->glava == NULL || knjiga->glava == NULL) {
		return;
	}
	ispis_clanova(clan, knjiga);

	do {
		printf("\nUnesite ID-clana koji posuduje knjigu: ");
		scanf("%d", &choice_id);
		check = nadi_clana(clan, choice_id);
	} while (check == NULL&&printf("\nKnjiga s tim ID-om ne postoji\n"));

	ispis_knjiga(knjiga);
	getchar();
	do {
		printf("\nUnesite ID-knjige koji posuduje knjigu: ");
		scanf("%d", &choice_id_knjiga);
		check_knj = nadi_knjigu(knjiga, choice_id_knjiga);
	} while ((check_knj == NULL || check_knj->state == 1) && printf("\nKnjiga je posudena ili ne postoji\n"));
	check_knj->id_clana = check->id;
	check_knj->state = 1;
	time_t vrijeme ;
	struct tm* datum;
	time(&vrijeme);
	datum = localtime(&vrijeme);
	strftime(check_knj->date, 30, "%c", datum);
	check->book+=1;
	for (int i = 0; i < check->book; i++) {
		if (check->books[i] == 0) {
			check->books[i] = check_knj->id;
		}
	}
}

void vracanje(LISTA_CLANOVA* clan, LISTA_KNJIGA* knjiga) {
	int j=0,br=0;
	int choice_id;
	int choice_id_knjiga;
	CLAN* check = NULL;
	KNJIGA* check_knj = NULL;
	KNJIGA* p = NULL;
	if (clan->glava == NULL || knjiga->glava == NULL) {
		return;
	}
	ispis_clanova(clan, knjiga);
	do {
		printf("\nUnesite ID-clana koji vraca knjigu: ");
		scanf("%d", &choice_id);
		check = nadi_clana(clan, choice_id);
	
	} while ((check == NULL || check->book == 0) && printf("\nKorisnik nema posudenu knjigu ili ne postoji\n"));
	
	printf("ID\tIME KNJIGE\tAUTOR KNJIGE\n\n");
	do {
		p = nadi_knjigu(knjiga, check->books[br++]);
		if (p == NULL) {
			break;
		}
		printf("%d\t%s\t\t%s\t\n", p->id, p->ime, p->autor_prezime);
	} while (check->book != 0);
	br = 0;
	getchar();
	do {
		printf("\nUnesite ID-knjige koju korisnik vraca: ");
		scanf("%d", &choice_id_knjiga);
		check_knj = nadi_knjigu(knjiga, choice_id_knjiga);
	} while ((check_knj == NULL || check_knj->id_clana != check->id) && printf("\nDrugi korisnik je posudio ovu knjigu ili ne postoji\n"));

	check_knj->id_clana = 0;
	check_knj->state = 0;
	while (j < 30) {
		check_knj->date[j++] = '\0';
	}
	
	for (int i = 0; i < check->book; i++) {
		if (check->books[i] == check_knj->id) {
			check->books[i] = 0;
		}
	}
	check->book -= 1;
}

void det_ispis(LISTA_KNJIGA* lista, LISTA_CLANOVA* lista_clan) {
	int br = 1;
	KNJIGA* pointer = lista->glava;
	printf("\n");
	if (lista->glava == NULL) {
		return;
	}
	printf("   ID\t\tDATUM POSUDBE\t\t\tIME\t  AUTOR\t\t  ZANR\t STATUS\n");
	while (pointer->next != NULL) {

		printf("%d. %d%30s\t %10s\t  %s %s\t%5s", br,pointer->id, pointer->date, pointer->ime, pointer->autor_ime, pointer->autor_prezime, pointer->zanr);
		if (pointer->state == 1) {
			printf("\tPOSUDENA\n");

		}
		else(printf("\tNIJE POSUDENA\n"));
		pointer = pointer->next;
		br++;
	}
	printf("%d. %d%30s\t %10s\t  %s %s\t%5s", br,pointer->id, pointer->date, pointer->ime, pointer->autor_ime, pointer->autor_prezime, pointer->zanr);
	if (pointer->state == 1) {
		printf("\tPOSUDENA\n");
	}
	else if (pointer->state == 0) {
		printf("\tNIJE POSUDENA\n");
	}
	
}