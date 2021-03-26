#ifndef UNTITLED_PHONEBOOK_H
#define UNTITLED_PHONEBOOK_H
#endif //UNTITLED_PHONEBOOK_H

struct contact *getAllContacts(void);
void addContact(const char * name, const char * number);
bool deleteContact(const char *name);
struct contact getContactByName(const char *name);
