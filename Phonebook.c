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
long size = 0;
bool contactsWereRead = false;

struct contact *readAllContacts(void);
void addContact(const char * name, const char * number);
bool deleteContact(const char *name);
struct contact getContactByName(const char *name);


void addContact(const char * name, const char * number) {
    if ((userFile = fopen(username, "a+b")) == NULL) {
        puts("Can not open database file");
        exit(EXIT_FAILURE);
    }
    struct contact temp = {};
    strcpy(temp.name, name);
    strcpy(temp.number, number);
    fwrite(&temp, sizeof(struct contact), 1, userFile);
    phonebook[size++] = temp;
    fclose(userFile);

}

struct contact *readAllContacts(void) {
    if (contactsWereRead)
        return phonebook;

    size = 0;
    if ((userFile = fopen(username, "a+b")) == NULL) {
        puts("Can not open database file");
        exit(EXIT_FAILURE);
    }
    while (size < PHONEBOOK_SIZE && (fread(&phonebook[size], sizeof(struct contact), 1, userFile) == 1)) {
        size++;
    }
    fclose(userFile);
    contactsWereRead = true;
    return phonebook;
}

int getSize() {
    if (!contactsWereRead)
        readAllContacts();
    return size;
}

int findContactIndex(const char *name) {
    for (int i = 0; i < size; ++i) {
        if (!strcmp(name, phonebook[i].name))
            return i;
    }
    return -1;
}

struct contact **findContactsByName(const char *name) {
    struct contact **result = malloc(getSize() * sizeof(struct contact *));
    int i = 0;
    int j = 0;
    for (i; i < size; ++i) {
        if (strstr(phonebook[i].name, name))
            result[j++] = &phonebook[i];
    }
    result[j] = NULL;
    return result;
}


void writeAllContacts() {
    if ((userFile = fopen(username, "w+b")) == NULL) {
        puts("Can not open database file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; ++i) {
        fwrite(&phonebook[i], sizeof(struct contact), 1, userFile);
    }
    fclose(userFile);
}

bool deleteContact(const char *name) {
    if (!contactsWereRead)
        readAllContacts();
    int toRemove = findContactIndex(name);
    if (toRemove == -1)
        return false;
    for (toRemove; toRemove < size; toRemove++) {
        phonebook[toRemove] = phonebook[toRemove + 1];
    }
    size--;
    writeAllContacts();
    return true;
}

bool editContact(const char *name, const char *number) {
    if (!contactsWereRead)
        readAllContacts();
    int toEdit = findContactIndex(name);
    if (toEdit == -1)
        return false;
    struct contact temp = {};
    strcpy(temp.name, name);
    strcpy(temp.number, number);
    phonebook[toEdit] = temp;
    writeAllContacts();
    return true;
}