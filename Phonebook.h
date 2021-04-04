#ifndef UNTITLED_PHONEBOOK_H
#define UNTITLED_PHONEBOOK_H
#endif //UNTITLED_PHONEBOOK_H

struct contact *readAllContacts(void);
void addContact(const char * name, const char * number);
bool deleteContact(const char *name);
struct contact getContactByName(const char *name);
struct contact **findContactsByName(const char *name);
bool editContact(const char *name, const char *number);
int getSize();
