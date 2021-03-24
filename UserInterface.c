#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UserInterface.h"
#include "Authentication.h"

#define box "#################################"
#define leftMargin "    "
#define NOOP "This option does not exist"
#define MAX_LEN 40

void showMainMenu(void);
static void showAuthMenu(void);
static void showLoginMenu(void);
static void showRegisterMenu(void);
static void showContacts(bool all);
static void showAddContactMenu(void);
static void showRemoveContactMenu(void);
static void showEditContactMenu(void);

char password[MAX_LEN];

void showMainMenu() {
    bool isLoggedIn = false;
    bool isRunning = true;
    int choice;
    while (isRunning) {
        if (!isLoggedIn)
            showAuthMenu();
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
        puts(box);
        puts(leftMargin "1 Login to existing account");
        puts(leftMargin "2 Register");
        puts(leftMargin "3 Login via Facebook");
        puts(box);
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
                puts(leftMargin "just kiddin', of course you can't login via Facebook");
                break;
            default:
                puts(leftMargin NOOP);
                break;
        }
    }
}

static void showRegisterMenu(void) {
    char username[MAX_LEN];

    // Use global variable to store password for authentication
    extern char password[];

    // Print menu
    while (true) {
        puts(box);
        puts(leftMargin "Enter your username:");
        scanf("%s", username);
        while ((getchar()) != '\n');
        if (userExists(username)) {
            puts(leftMargin "User with this username already exists!");
            continue;
        }
        break;
    }
    puts(box);
    puts(leftMargin "Enter your password:");
    puts(box);
    scanf("%s", password);
    addUser(username, password);
    while ((getchar()) != '\n');
}

static void showLoginMenu(void) {
    char username[MAX_LEN];
    const char *loginStatus;
    // Use global variable
    extern char password[];
    while (true) {
        puts(box);
        puts(leftMargin "Enter your name: ");
        scanf("%s", &username);
        while ((getchar()) != '\n');
        puts(leftMargin "Enter your password: ");
        scanf("%s", &password);
        while ((getchar()) != '\n');
        loginStatus = signIn(username, password);
        printf(leftMargin "%s\n", loginStatus);
        if (!strcmp("Login successful", loginStatus))
            break;
    }
}

static void showContacts(bool all) {

}

static void showAddContactMenu(void) {

}

static void showRemoveContactMenu(void) {

}

static void showEditContactMenu(void) {

}


