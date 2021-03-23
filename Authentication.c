#include <stdbool.h>
#include <bits/types/FILE.h>
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include "Authentication.h"

#define MAX_LEN 40

// File for login-password CRUD operations
static FILE * loginPassFile;

bool userExists(const char *);
bool signIn(char *username, char *password);
void addUser(char *username, char *password);


// Check if user exists
bool userExists(const char *username) {
    if ((loginPassFile = fopen("login-pass", "a+")) == NULL) {
        puts("Can not open authentication file");
        exit(EXIT_FAILURE);
    }

    char existingUsername[MAX_LEN];
    int i = 0;

    while (fgets(existingUsername, sizeof(existingUsername), loginPassFile)) {
        // Remove newline character added by fgets
        existingUsername[strcspn(existingUsername, "\n")] = 0;
        if (i++ % 2 == 0)
            if (!strcmp(username, existingUsername))
                return true;
    }
    return false;
}


void addUser(char *username, char *password) {
    rewind(loginPassFile);
    fseek(loginPassFile, 0, SEEK_END);
    fputs(username, loginPassFile);
    fputs('\n', loginPassFile);
    fputs(password, loginPassFile);
    fputs('\n', loginPassFile);
    fclose(loginPassFile);
}

bool signIn(char *username, char *password) {
    return 0;
}
