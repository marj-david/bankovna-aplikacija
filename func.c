#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include "struct.h"
#include "func.h"

int numOfUsersRegistered(USER users[], FILE* fp) {
	int n = 0;
	char line[100];
	while (fgets(line, sizeof(line), fp) != NULL) {
		n++;
	}
	return n;
}

int registerUser(USER* user, int *numUsers) {
	printf("Unesi ime: ");
	scanf("%49s", user[*numUsers].name);
	printf("Unesi prezime: ");
	scanf("%49s", user[*numUsers].lastName);
	printf("Unesi PIN: ");
	scanf("%8s", user[*numUsers].PIN);

	user[*numUsers].balance = 0;
	user[*numUsers].id = *numUsers + 1;
	(*numUsers)++;
	

	// spremanje korisnika
	FILE* file = fopen("korisnici.txt", "a"); 
	if (file == NULL) {
		perror("Pogreska pri otvaranju datoteke.\n");
		return -1;
	}

	fprintf(file, "%d %s %s %s %.2f\n", user[*numUsers - 1].id, user[*numUsers - 1].name, user[*numUsers - 1].lastName, user[*numUsers - 1].PIN, user[*numUsers - 1].balance);

	fclose(file);
	printf("Korisnik spremljen u datoteku.\n");
}


//login opcije
int adminLogin() {
	char adminName[10];
	char adminPass[10];
	
	printf("\nUnesite korisnicko ime: ");
	scanf("%s", adminName);
	printf("Unesite zaporku: ");
	scanf("%s", adminPass);
	if (strcmp(adminName, "admin") == 0 && strcmp(adminPass, "admin") == 0) {
		printf("Uspjesna prijava admina!\n");
		return 1; 
	}
	else {
		printf("Neuspjesna prijava.\n");
		return 0; 
	}
}

int userLogin() {
	FILE* fp = fopen("korisnici.txt", "r");
	if (fp == NULL) {
		perror("\nPogreska pri otvaranju datoteke");
		return -1;
	}
	char pin[9];
	
	printf("\nUnesite PIN: ");
	scanf("%8s", pin);

	USER user;
	int found = 0;

	while (fscanf(fp, "%d %s %s %s %f", &user.id, user.name, user.lastName, user.PIN, &user.balance) == 5) {
		if (user.PIN == pin) {
			printf("Uspjesna prijava! Dobrodosli, %s %s!\n", user.name, user.lastName);
			found = 1;
			break;
		}

	}

	fclose(fp);

	if (!found) {
		printf("Korisnik nije pronadjen.\n");
		return 0; 
	}
	return 1; 
}


int logIn() {
	USER users[100];
	FILE* fp = fopen("korisnici.txt", "r");
	if (fp == NULL) {
		perror("\nPogreska pri otvaranju datoteke");
		return -1;
	}
	int numOfUsers = 0;
	numOfUsers = numOfUsersRegistered(users, fp);

	int n;
	do {
		printf("Odaberite opciju prijave ili registracije: ");
		printf("\n1. ADMIN");
		printf("\n2. KORISNIK");
		printf("\n3. REGISTRACIJA");
		do {
			printf("\nOdabir: ");
			scanf("%d", &n);
		} while (n < 1 || n>3);

		switch (n)
		{
		case 1:
			if (adminLogin()) {
				return 1;
			};
			break;

		case 2:
			if (userLogin()) {
				return 2;
			};
			break;

		case 3:
			registerUser(users, &numOfUsers);
			break;

		default:
			printf("\nNetocan odabir");
			break;
		}
	} while (1);

}

//mogucnosti admina
void listUsersID(int n, FILE* fp, USER* users) {
	printf("\nRegistrirani korisnici: ");
	for (int i = 0; i < n; i++) {
		printf("\n%d %s %s %s %.2f e", users[i].id, users[i].name, users[i].lastName, users[i].PIN, users[i].balance);
	}
}

int compareUsers(const void* a, const void* b) {
	const USER* userA = (const USER*)a;
	const USER* userB = (const USER*)b;
	return strcmp(userA->lastName, userB->lastName);
}

void listUsersAlphabetically(USER* users, int n, FILE* fp) {
	printf("\nKorisnici po abecednom redu (prezimena): ");
	qsort(users, n, sizeof(USER), compareUsers);
	for (int i = 0; i < n; i++) {
		printf("\n%d %s %s %s %.2f e\n", users[i].id, users[i].name, users[i].lastName, users[i].PIN, users[i].balance);
	}
}

int readUsers() {
	FILE* fp=fopen("korisnici.txt", "r");
	if (fp == NULL) {
		perror("\nPogreska pri otvaranju datoteke");
		return -1;
	}
	int c = 0;
	USER users[100];
	int n = numOfUsersRegistered(users, fp);

	printf("\n1.Ispis po ID-u");
	printf("\n2.Ispis po abecednom redu(prezimena)");
	printf("\nOdabir: ");
	scanf("%d", &c);

	switch (c)
	{
	case 1:
		listUsersID(n, fp, users);
		break;

	case 2:
		listUsersAlphabetically(users, n, fp);
		break;
	default:
		printf("\nPogreska pri unosu");
		break;
	}
}

void deleteUserByID(USER* users, int* numUsers, int idToDelete) {
	int found = 0;
	for (int i = 0; i < *numUsers; i++) {
		if (users[i].id == idToDelete) {
			found = 1;
			
			for (int j = i; j < *numUsers - 1; j++) {
				users[j] = users[j + 1];
			}
			(*numUsers)--;
			break;
		}
	}

	if (found) {

		for (int i = 0; i < *numUsers; i++) {
			users[i].id = i + 1;
		}

	FILE* file = fopen("korisnici.txt", "w"); 
	if (file == NULL) {
		perror("Greska pri otvaranju datoteke.\n");
		return;
		}
	
	for (int i = 0; i < *numUsers; i++) {
		fprintf(file, "%d %s %s %s %.2f\n", users[i].id, users[i].name, users[i].lastName, users[i].PIN, users[i].balance);
	}
	fclose(file);
	printf("\nKorisnik s ID %d uspjesno obrisan.\n", idToDelete);
}
 else {
	 printf("\nKorisnik s ID %d nije pronadjen.\n", idToDelete);
	}
}

void adminMenu() {
	FILE* fpUsers = fopen("korisnici.txt", "a");
	if (fpUsers == NULL) {
		perror("\nPogreska pri otvaranju datoteke");
		return;
	}
	USER users[100];
	int numOfUsers = 0;
	numOfUsers = numOfUsersRegistered(users, fpUsers);

	int choice=0;

	do {
		printf("\n\t1.Ispis svih korisnika");
		printf("\n\t2.Upis novog korisnika");
		printf("\n\t3.Brisanje postojeceg korisnika");
		printf("\n\t0.Izlaz");

		printf("\nUnesite zeljenu radnju: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			readUsers();
			break;

		case 2:
			registerUser(users, &numOfUsers);
			break;

		case 3:
		{
			int idToDelete;
			printf("Unesi ID korisnika za brisanje: ");
			scanf("%d", &idToDelete);
			deleteUserByID(users, &numOfUsers, idToDelete);
			break;
		}
			
		default:
			printf("\nPokusaj ponovo");
			break;
		}
		fclose(fpUsers);
	} while (1);
	
}

//void userMenu() {
//	FILE* fpUsers = fopen("korisnici.txt", "r");
//	FILE* fpAccs = fopen("racuni.txt", "r");
//}