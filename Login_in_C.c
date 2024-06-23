#include <stdio.h>
#include <string.h>
#include <conio.h> 

#define user 20
#define pass 20
#define login_file "login.txt"

void getPassword(char *password) {
    char ch;
    int i = 0;

    while ((ch = getch()) != '\r') { 
        if (ch == '\b') { 
            if (i > 0) {
                i--;
                printf("\b \b"); 
            }
        } else if (i < pass) {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0'; 
}

int verifyCredentials(const char *username, const char *password) {
    FILE *file = fopen(login_file, "r");
    if (!file) {
        printf("Error opening credentials file.\n");
        return 0;
    }

    char fileUsername[user + 1];
    char filePassword[pass + 1];
    while (fscanf(file, "%s %s", fileUsername, filePassword) != EOF) {
        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            fclose(file);
            return 1; 
        }
    }

    fclose(file);
    return 0; 
}

void saveCredentials(const char *username, const char *password) {
    FILE *file = fopen(login_file, "a");
    if (!file) {
        printf("Error opening credentials file.\n");
        return;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);
}

void registerUser() {
    char username[user + 1];
    char password[pass + 1];

    printf("Register a new user\n");
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; 

    printf("Enter password: ");
    getPassword(password);
    printf("\n");

    saveCredentials(username, password);
    printf("User registered successfully.\n");
}

int main() {
    char username[user + 1];
    char password[pass + 1];
    int loginAttempts = 3; 
    int choice;

    while (1) {
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        if (choice == 1) {
            while (loginAttempts > 0) {
                printf("Enter username: ");
                fgets(username, sizeof(username), stdin);
                username[strcspn(username, "\n")] = '\0'; 

                printf("Enter password: ");
                getPassword(password);
                printf("\n");

                if (verifyCredentials(username, password)) {
                    printf("Login successful!\n");
                    return 0;
                } else {
                    printf("Invalid username or password. Please try again.\n");
                    loginAttempts--;
                }
            }

            printf("Too many failed attempts. Access denied.\n");
            return 1;
        } else if (choice == 2) {
            registerUser();
        } else if (choice == 3) {
            printf("Bye-bye\n");
            return 0;
        } else {
            printf("Invalid. Please try again.\n");
        }
    }

    return 0;
}
