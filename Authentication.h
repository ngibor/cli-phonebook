//
// Created by ngibor on 3/16/21.
//

#ifndef UNTITLED_AUTHENTICATION_H
#define UNTITLED_AUTHENTICATION_H

#endif //UNTITLED_AUTHENTICATION_H

void openAuthFile();
bool userExists(const char *username);
void addUser(char *username, char *password);
char *signIn(char *username, char *password);