#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Phonebook.h"
#include "Constants.h"

extern char username[];
typedef struct contact {
    char name[MAX_LEN];
    char number[MAX_LEN];
} contact;

FILE *userFile;
struct contact phonebook[PHONEBOOK_SIZE];

struct contact *getAllContacts(void);
void addContact(const char * name, const char * number);
bool deleteContact(const char *name);
struct contact getContactByName(const char *name);

void addContact(const char * name, const char * number) {
    if ((userFile = fopen(username, "a+b")) == NULL) {
        puts("Can not open database file");
        exit(EXIT_FAILURE);
    }
    printf("given values:%s %s\n", name, number);
    struct contact temp = {};
    strcpy(temp.name, name);
    strcpy(temp.number, number);
    printf("struct:%s %s\n", temp.name, temp.number);
    fwrite(&temp, sizeof(struct contact), 1, userFile);
    fclose(userFile);
}

struct contact *getAllContacts(void) {
    int i = 0;
    if ((userFile = fopen(username, "a+b")) == NULL) {
        puts("Can not open database file");
        exit(EXIT_FAILURE);
    }
    while (i < PHONEBOOK_SIZE && (fread(&phonebook[i], sizeof(struct contact), 1, userFile) == 1)) {
        if (i == 0)
            puts("Reading database:");
        printf("Name: %s, Number: %s\n", phonebook[i].name, phonebook[i].number);
        i++;
    }
    fclose(userFile);
    return NULL;
}
