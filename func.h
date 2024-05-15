#ifndef FUNC_H
#define FUNC_H

int numOfUsersRegistered(USER users[], FILE* fp);
int adminLogin();
int userLogin();
int logIn();
void adminMenu();
void userMenu();
int readUsers();
int registerUser(USER* user, int *numOfUsers);
void listUsersID(int n, FILE *fp, USER *users);
void listUsersAlphabetically(USER *users,int n, FILE *fp);
int compareUsers(const void* a, const void* b);
void deleteUserByID(USER* users, int* numUsers, int idToDelete);



#endif
