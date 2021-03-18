#include <stdbool.h>
#include <stdio.h>
#include "UserInterface.h"

#define box "#################################"
#define leftMargin "    "
#define NOOP "This option does not exist"
#define MAX_LEN 40

void showMainMenu(void);
char * showAuthMenu(void);
void showLoginMenu(void);
void showRegisterMenu(void);
void showContacts(bool all);
void showAddContactMenu(void);
void showRemoveContactMenu(void);
void showEditContactMenu(void);


void showMainMenu() {
    char * password;
    bool isLoggedIn = false;
    bool isRunning = true;
    int choice;
    while (isRunning) {
        if (!isLoggedIn)
            password = showAuthMenu();
        puts(box);
        puts(leftMargin "What would you like to do?");
        puts(leftMargin " 1 Display all contacts");
        puts(leftMargin " 2 Search by name");
        puts(leftMargin " 3 Add contact");
        puts(leftMargin " 4 Remove contact");
        puts(leftMargin " 5 Edit contact");
        puts(leftMargin " 6 to logout");
        puts(leftMargin " 7 Exit");
        puts(box);
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                showContacts(true);
                break;
            case 2:
                showContacts(false);
                break;
            case 3:
                showAddContactMenu();
                break;
            case 4:
                showRemoveContactMenu();
                break;
            case 5:
                showEditContactMenu();
                break;
            case 6:
                isLoggedIn = false;
                break;
            case 7:
                isRunning = false;
                break;
            default:
                puts(NOOP);
                break;
        }
    }



}

char * showAuthMenu(void) {
    int choice;
    while (true) {
        puts(box);
        puts(leftMargin "1 Login to existing account");
        puts(leftMargin "2 Register");
        puts(leftMargin "3 Login via Facebook");
        puts(box);
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                showLoginMenu();
                break;
            case 2:
                showRegisterMenu();
                break;
            case 3:
                puts(leftMargin "just kiddin', of course you can't login via Facebook");
                break;
            default:
                puts(leftMargin NOOP);
                break;
        }
    }
}

void showContacts(bool all) {

}

void showAddContactMenu(void) {

}

void showRemoveContactMenu(void) {

}

void showEditContactMenu(void) {

}
