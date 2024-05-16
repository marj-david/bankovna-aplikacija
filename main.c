#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "func.h"


int main() {
    int loginChoice;
    FILE* fp;
    fp = fopen("korisnici.txt", "r");
	if (fp == NULL) {
		perror("Datoteka:");
		return 1;
	}

    int numOfUsers = 0;    
    USER users[100];
    if (fp != NULL) {
        while (fscanf(fp, "%d %49s %49s %8s %f", &users[numOfUsers].id, users[numOfUsers].name, users[numOfUsers].lastName, users[numOfUsers].PIN, &users[numOfUsers].balance) == 5) {
            numOfUsers++;
        }
    }

    loginChoice=logIn();

    if (loginChoice == 1) {
        adminMenu();
    }
    //else if (loginChoice == 2) {
    //    userMenu();
    //}
 
    fclose(fp);
    return 0;
}