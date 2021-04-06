#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <stdlib.h>
#include "Authentication.h"
#include "Constants.h"

// File for login-password CRUD operations
static FILE * loginPassFile;

bool userExists(const char *);
char *signIn(char *username, char *password);
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
    int i;
    //hash password
    char *hashedPass = malloc(65 * sizeof(char));
    unsigned char *hash = SHA256(password, strlen(password), 0);
    for (i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashedPass + 2*i, "%02x", hash[i]);
    }

    //write password
    fseek(loginPassFile, 0, SEEK_END);
    fprintf(loginPassFile, "%s\n%s\n", username, hashedPass);
    printf("saved pass: %s\n", hashedPass);
    free(hashedPass);
    fclose(loginPassFile);
}


char *signIn(char *username, char *password) {
    // to store return value
    char *message;
    int i;
    //hash password
    char *hashedPass = malloc(65 * sizeof(char));
    unsigned char *hash = SHA256(password, strlen(password), 0);
    for (i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashedPass + 2*i, "%02x", hash[i]);
    }
    printf("digest len %d\n", SHA256_DIGEST_LENGTH);

    if ((loginPassFile = fopen("login-pass", "a+")) == NULL) {
        puts("Can not open authentication file");
        exit(EXIT_FAILURE);
    }

    char existingUsername[MAX_LEN];
    char existingPassword[65];
    i = 0;

    while (fgets(existingUsername, sizeof(existingUsername), loginPassFile)) {

        // Remove newline character added by fgets
        existingUsername[strcspn(existingUsername, "\n")] = 0;

        if (i++ % 2 == 0) {
            if (!strcmp(username, existingUsername)) {
                fgets(existingPassword, sizeof(existingPassword), loginPassFile);
                existingPassword[strcspn(existingPassword, "\n")] = 0;
                printf("hashed pass: %s\nexisting:  %s\n", hashedPass, existingPassword);
                if (!strcmp(hashedPass, existingPassword))
                    message = "Login successful";
                else
                    message = "Wrong password";
                break;
            } else {
                message = "Wrong username";
            }
        }
    }
    free(hashedPass);
    fclose(loginPassFile);
    return message;
}
