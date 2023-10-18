#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct studenti {
	char ime[20];
	char prezime[20];
	double bodovi;

}student;

int BrojStud(FILE* in) {
	int br = 0;
	char tmp;
	while (!feof(in)) {
		tmp = fgetc(in);
		if (tmp == '\n') { br++; }
	}
	return br; 
}

student* Alociraj(student* pstudent, int n) {
	pstudent = (student*)malloc(n * sizeof(student));
	return pstudent; 

}

void CitajFajl(FILE* in, student* pstudent, int n) {
	double max = 0;
	int i;
	for (i = 0; i < n; i++) {
		fscanf(in, "%s %s %lf", pstudent[i].ime, pstudent[i].prezime, &pstudent[i].bodovi);
		if (pstudent[i].bodovi > max) { max = pstudent[i].bodovi; }
	}
}
void Ispis(student* pstudent, int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%s %s %lf %lf\n", pstudent[i].ime, pstudent[i].prezime, pstudent[i].bodovi, (pstudent[i].bodovi / max) * 100);
	}
}
int main() {
	FILE* in;
	int n;
	student* pstudent = NULL; 
	in = fopen("student.txt", "r");
	if (in == NULL) { printf("Neuspjesno otvaranje datoteke"); }
	n = BrojStud(in);
	pstudent = Alociraj(pstudent, n);
	rewind(in);
	CitajFajl(in, pstudent, n);
	Ispis(pstudent, n);
	fclose(in);
	free(pstudent);


	return 0;
}