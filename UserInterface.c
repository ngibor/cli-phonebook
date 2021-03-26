#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UserInterface.h"
#include "Authentication.h"
#include "Phonebook.h"
#include "Constants.h"


void showMainMenu(void);
static void showAuthMenu(void);
static void showLoginMenu(void);
static void showRegisterMenu(void);
static void showContacts(bool all);
static void showAddContactMenu(void);
static void showRemoveContactMenu(void);
static void showEditContactMenu(void);

char username[MAX_LEN];
char password[MAX_LEN];
typedef struct contact {
    char name[MAX_LEN];
    char number[MAX_LEN];
} contact;

void showMainMenu() {
    bool isLoggedIn = false;
    bool isRunning = true;
    int choice;
    while (isRunning) {
        if (!isLoggedIn) {
            showAuthMenu();
            isLoggedIn = true;
        }
        puts(BOX);
        puts(LEFT_MARGIN "What would you like to do?");
        puts(LEFT_MARGIN " 1 Display all contacts");
        puts(LEFT_MARGIN " 2 Search by name");
        puts(LEFT_MARGIN " 3 Add contact");
        puts(LEFT_MARGIN " 4 Remove contact");
        puts(LEFT_MARGIN " 5 Edit contact");
        puts(LEFT_MARGIN " 6 to logout");
        puts(LEFT_MARGIN " 7 Exit");
        puts(BOX);
        scanf("%d", &choice);
        while ((getchar()) != '\n');
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
                exit(EXIT_SUCCESS);
            default:
                puts(NOOP);
                break;
        }
    }



}

static void showAuthMenu(void) {
    int choice;
    while (true) {
        puts(BOX);
        puts(LEFT_MARGIN "1 Login to existing account");
        puts(LEFT_MARGIN "2 Register");
        puts(LEFT_MARGIN "3 Login via Facebook");
        puts(BOX);
        scanf("%d", &choice);
        while ((getchar()) != '\n');
        switch (choice) {
            case 1:
                showLoginMenu();
                return;
            case 2:
                showRegisterMenu();
                return;
            case 3:
                puts(LEFT_MARGIN "just kiddin', of course you can't login via Facebook");
                break;
            default:
                puts(LEFT_MARGIN NOOP);
                break;
        }
    }
}

static void showRegisterMenu(void) {

    // Use global variable to store password for authentication
    extern char username[];
    extern char password[];

    // Print menu
    while (true) {
        puts(BOX);
        puts(LEFT_MARGIN "Enter your username:");
        scanf("%s", username);
        while ((getchar()) != '\n');
        if (userExists(username)) {
            puts(LEFT_MARGIN "User with this username already exists!");
            continue;
        }
        break;
    }
    puts(BOX);
    puts(LEFT_MARGIN "Enter your password:");
    puts(BOX);
    scanf("%s", password);
    addUser(username, password);
    while ((getchar()) != '\n');
}

static void showLoginMenu(void) {
    const char *loginStatus;
    // Use global variable
    extern char username[];
    extern char password[];
    while (true) {
        puts(BOX);
        puts(LEFT_MARGIN "Enter your name: ");
        scanf("%s", &username);
        while ((getchar()) != '\n');
        puts(LEFT_MARGIN "Enter your password: ");
        scanf("%s", &password);
        while ((getchar()) != '\n');
        loginStatus = signIn(username, password);
        printf(LEFT_MARGIN "%s\n", loginStatus);
        if (!strcmp("Login successful", loginStatus))
            break;
    }
}

static void showContacts(bool all) {
    int i = 0;
    struct contact *allContacts;
    allContacts = getAllContacts();
    puts(BOX);
    puts(LEFT_MARGIN "Your contacts:");
    while ((allContacts + i) != NULL) {
        printf("%40s %40s", (allContacts + i)->name, (allContacts + i)->number);
    }

}

static void showAddContactMenu(void) {
    char name[MAX_LEN];
    char number[MAX_LEN];
    puts(BOX);
    puts(LEFT_MARGIN "Enter a name:");
    scanf("%s", name);
    while ((getchar()) != '\n');
    puts(LEFT_MARGIN "Enter phone number:");
    scanf("%s", number);
    while ((getchar()) != '\n');
    addContact(name, number);
}

static void showRemoveContactMenu(void) {

}

static void showEditContactMenu(void) {

}


