/*2. Definirati strukturu osoba (ime, prezime, godina rodenja) i napisati program koji:
a) dinamicki dodaje novi element na pocetak liste,
b) ispisuje listu,
c) dinamicki dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše odredeni element iz liste.
U zadatku se ne smiju koristiti globalne varijable.*/

/*3. Prethodnom zadatku dodati funkcije:
a) dinamicki dodaje novi element iza odredenog elementa,
b) dinamicki dodaje novi element ispred odredenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) cita listu iz datoteke.
*/

#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Person* position;

struct Person {
	char name[128], surename[128];
	int birthYear;
	position next;
};

void insertFirst(position);
void insertEnd(position);
void printList(position);
position findElement(position);
void deleteElement(position);
void addBehind(position);
void addBefore(position);
void sortList(position);
void writeInFile(position);
void readFromFile(position);
void deleteAll(position);
void deleteFirst(position);

int main()
{
	Person head;
	head.next = NULL;
	int mainChoice = 1;
	while (mainChoice != NULL) {
		printf("\n\n\t\t\t~ MENU ~\n");
		printf("\n\t~ Write number along wanted operation. ~\n\n");
		printf("0) End program.\n");
		printf("1) Add element on the beginning of the list.\n");
		printf("2) Add element on the end of the list.\n");
		printf("3) Print list.\n");
		printf("4) Find certain element in list by providing surename.\n");
		printf("5) Delete certain element in list by providing surename.\n");
		printf("6) Add new element behind wanted element(selected by surname).\n");
		printf("7) Add new element in front of wanted element(selected by surname).\n");
		printf("8) Sort list by surenames.\n");
		printf("9) Write list in file.\n");
		printf("10) Read list from file.\n");
		


		int choice;
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 0: mainChoice = NULL; break;
		case 1:
			insertFirst(&head); break;
		case 2:
			insertEnd(&head); break;
		case 3:
			printList(head.next); break;
		case 4:
			position p2;
			p2 = findElement(&head);
			printf("\nWanted person info:\t%s %s, %d.\n", p2->name, p2->surename, p2->birthYear); break;
		case 5:
			deleteElement(&head); break;
		case 6:
			addBehind(&head); break;
		case 7:
			addBefore(&head); break;
		case 8:
			sortList(&head); break;
		case 9:
			writeInFile(head.next); break;
		case 10:
			readFromFile(&head);  break;
		default:
			break;
		}

	}

	system("pause");
	return 0;
}

void insertFirst(position p) {
	position temp;
	temp = (position)malloc(sizeof(Person));
	temp->next = p->next;
	p->next = temp;
	printf("Type name, surename and birth year.\n");
	scanf_s("%s %s %d", temp->name, 128, temp->surename, 128, &temp->birthYear);
}

void insertEnd(position p) {
	position temp;
	temp = (position)malloc(sizeof(Person));
	while (p->next != NULL)
		p = p->next;
	temp->next = p->next;
	p->next = temp;
	printf("Type name, surename and birth year.\n");
	scanf_s("%s %s %d", temp->name, 128, temp->surename, 128, &temp->birthYear);

}

void printList(position p) {
	if (p == NULL)
		printf("\nList is empty.\n");
	else {
		printf("\n\t~ List content: ~\n");
		while (p != NULL) {
			printf("\n%s %s %d", p->name, p->surename, p->birthYear);
			p = p->next;
		}
	}
}

position findElement(position p) {
	position temp = NULL;
	char srnm[128];
	printf("\nType wanted surname.\t");
	scanf_s("%s", srnm, 128);

	while (p != NULL) {
		if (_strcmpi(p->surename, srnm) == 0)
			temp = p;
		p = p->next;
	}
	return temp;
}

void deleteElement(position p) {
	position temp;
	char srnm[128];
	printf("\nType wanted surname.\t");
	scanf_s("%s", srnm, 128);
	while (p != NULL) {
		if (_strcmpi(p->next->surename, srnm) == 0) {

			temp = p->next;
			p->next = temp->next;
			free(temp);
		}
		p = p->next;
	}

}

void addBehind(position p) {
	char srnm[128];
	printf("\nType surname of the person behind whom you want this new element to be.\t");
	scanf_s("%s", srnm, 128);

	position temp;
	temp = (position)malloc(sizeof(Person));
	while (p != NULL) {
		if (_strcmpi(p->surename, srnm) == 0) {
			temp->next = p->next;
			p->next = temp;

			printf("\nEnter name, surename and birth year.\n");
			scanf_s("%s %s %d", temp->name, 128, temp->surename, 128, &temp->birthYear);
		}
		p = p->next;
	}
}

void addBefore(position p) {
	position temp;
	char srnm[128];
	printf("\nType surname of the person in front whom you want this new element to be.\t");
	scanf_s("%s", srnm, 128);

	temp = (position)malloc(sizeof(Person));
	while (p->next != NULL) {
		if (_strcmpi(p->next->surename, srnm) == 0) {
			temp->next = p->next;
			p->next = temp;

			printf("\nEnter name, surename and birth year.\n");
			scanf_s("%s %s %d", temp->name, 128, temp->surename, 128, &temp->birthYear);
			p = p->next;
		}
		p = p->next;
	}

}

void sortList(position p) {
	position end = NULL, i, j, prev_j;

	while (p->next != end)
	{
		i = p;
		prev_j = i->next;
		j = prev_j->next;

		while (j != end)
		{
			if (_strcmpi(prev_j->surename, j->surename) > 0)
			{
				prev_j->next = j->next;
				i->next = j;
				j->next = prev_j;
			}
			else
				i = prev_j;
			prev_j = j;
			j = j->next;
		}
		end = prev_j;
	}

}

void writeInFile(position p) {
	FILE* stream;
	char name[128];

	printf("\nType in name of the file.\t");
	scanf_s("%s", name, 128);

	fopen_s(&stream, name, "w+");
	if (stream == NULL)
		printf("Error in opening of the file.\n");
	else
	{
		while (p != NULL)
		{
			fprintf(stream, "%s %s %d\n", p->name, p->surename, p->birthYear);
			p = p->next;
		}

		fclose(stream);
	}
}

void readFromFile(position p) {
	FILE* stream;
	char name[128];
	Person* temp; //ili 'position temp;' isto je

	printf("\nEnter name of the file you want to read list from.\t");
	scanf_s("%s", name, 128);


	fopen_s(&stream, name, "r");
	if (stream == NULL)
		printf("Error in opening of the file.\n");
	else {
		while (!feof(stream)) {
			temp = (position)malloc(sizeof(Person));
			if (temp == NULL)
				printf("Error in allocating memory.\n");
			else {
				// -----------------Ukoliko citamo iz file-a u koji smo vec ucitali podatke--------------------
				//u prvu varijablu spremi smece (od alociranja tempa). potrebno je izbrisat prvu varijablu iz liste kad se
				//zavrsi ucitavanje. to radimo funkcijom deleteFirst (neka korisnik sam pozove jer nije uvijek potrebna)
				fscanf_s(stream, "%s %s %d", temp->name, 128, temp->surename, 128, &temp->birthYear);
				temp->next = p->next;
				p->next = temp;
			}
		}
		fclose(stream);
	}
}
