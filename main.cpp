#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <unistd.h>
#include <windows.h>

// UI functions
void header();
void headerAnimation();
void mainMenu1();
void mainMenu2();
void mainMenu3();
void mainMenu4();
void mainMenu5();

// Program functions
void insert(struct Node *root, const char *word);
void addWord();
void searchWord();
void traverse(struct Node *current, char *buffer, int depth);
int isTrieEmpty(struct Node *root);
void viewWord();
void viewWordByPrefix();
void displayWordsByPrefix(struct Node *current, char *prefix, int depth, int *counter);
void exitProgram();

struct Node{

    char description[100];
    struct Node *children[26];
    bool isEndOfWord;

};

struct Node *createNode(){

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->isEndOfWord = false;
    strcpy(newNode->description, "");
    for(int i = 0; i < 26; i++){
        newNode->children[i] = NULL;
    }
    return newNode;

}

struct Node *root = createNode();

void insert(struct Node *root, const char *word){

    struct Node *current = root;
    for(int i = 0; word[i] != '\0'; i++){
        int index = word[i] - 'a';
        if(current->children[index] == NULL){
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord = true;
    strcpy(current->description, word);

}

void addWord(){

    system("cls");
    header();
    printf("=============== Add a word ================\n\n");
    char word[100];
    char description[256];
    while (1) {
        printf("Enter the word [> 1 characters & no spacing]: ");
        fgets(word, sizeof(word), stdin);
        word[strcspn(word, "\n")] = '\0';
        int valid = 1;
        if (strlen(word) <= 1) {
            printf("Error: Word must be more than 1 character.\n");
            continue;
        }
        for (int i = 0; word[i]; i++) {
            if (!islower(word[i]) || isspace(word[i])) {
                valid = 0;
                break;
            }
        }
        if (!valid) {
            printf("Error: Word must contain only lowercase letters (a-z) and no spaces.\n");
            continue;
        }
        break;
    }
    while (1) {
        printf("Enter the description [> 2 words]: ");
        fgets(description, sizeof(description), stdin);
        description[strcspn(description, "\n")] = '\0'; 
        int count = 0, inWord = 0;
        for (int i = 0; description[i]; i++) {
            if (!isspace(description[i]) && !inWord) {
                count++;
                inWord = 1;
            } else if (isspace(description[i])) {
                inWord = 0;
            }
        }
        if (count < 3) {
            printf("Error: Description must contain more than 2 words.\n");
        } else {
            break;
        }
    }
    struct Node *current = root;
    for (int i = 0; word[i]; i++) {
        int index = word[i] - 'a';
        if (index < 0 || index >= 26) continue; 
        if (current->children[index] == NULL) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord = true;
    strcpy(current->description, description);
    printf("Word '%s' added successfully!\n", word);
    printf("\n       >> Press Enter to continue <<");
    while (1) {
        char ch = getch();
        if (ch == '\r') {  
            mainMenu1();
            break;
        }
    }

}

void searchWord(){

    system("cls");
    header();
    printf("============== Search a Word ==============\n\n");
    char word[100];
    while (1) {
        printf("Enter the word [> 1 characters & no spacing]: ");
        fgets(word, sizeof(word), stdin);
        word[strcspn(word, "\n")] = '\0'; 
        int valid = 1;
        if (strlen(word) <= 1) {
            printf("Error: Word must be more than 1 character.\n");
            continue;
        }
        for (int i = 0; word[i]; i++) {
            if (!islower(word[i]) || isspace(word[i])) {
                valid = 0;
                break;
            }
        }
        if (!valid) {
            printf("Error: Word must contain only lowercase letters (a-z) and no spaces.\n");
            continue;
        }
        break;
    }
    struct Node *current = root;
    for (int i = 0; word[i]; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            current = NULL;
            break;
        }
        current = current->children[index];
    }

    if (current != NULL && current->isEndOfWord) {
        printf("\nWord found!\n");
        printf("Word        : %s\n", word);
        printf("Description : %s\n", current->description);
    } else {
        printf("\nWord '%s' not found in dictionary.\n", word);
    }
    printf("\n       >> Enter to continue <<");
    char ch = getch();
    while (1) {
        if (ch == '\r' || ch == '\n') {
            mainMenu2();
            break;
        }
    }

}

int count = 1;  

void traverse(struct Node *current, char *buffer, int depth){

    if (current->isEndOfWord) {
        buffer[depth] = '\0';
        printf("%-4d %-20s %-50s\n", count++, buffer, current->description);
    }

    for (int i = 0; i < 26; i++) {
        if (current->children[i]) {
            buffer[depth] = 'a' + i;
            traverse(current->children[i], buffer, depth + 1);
        }
    }

}

int isTrieEmpty(struct Node *root){

    for (int i = 0; i < 26; i++) {
        if (root->children[i]) {
            return 0; 
        }
    }
    return 1; 

}

void viewWord(){

    system("cls");
    header();
    puts("============= View all words ==============\n");

    if (isTrieEmpty(root)) {
        puts("Dictionary is empty.\n");
    } else {
        puts("No.  Word\t\t  Description\n");
        char buffer[100];
        count = 1;  
        traverse(root, buffer, 0);
    }
    printf("\n       >> Press Enter to continue <<");
    while (1) {
        char ch = getch();
        if (ch == '\r') { 
            mainMenu3();
            break;
        }
    }

}


void displayWordsByPrefix(struct Node* current, char* prefix, int depth, int* counter){

    if (current->isEndOfWord) {
        printf("%d. %s\n", ++(*counter), prefix);
    }

    for (int i = 0; i < 26; i++) {
        if (current->children[i] != NULL) {
            char nextChar = 'a' + i;
            char newPrefix[100];
            strcpy(newPrefix, prefix);
            newPrefix[depth] = nextChar;
            newPrefix[depth + 1] = '\0';
            displayWordsByPrefix(current->children[i], newPrefix, depth + 1, counter);
        }
    }

}

void viewWordByPrefix(){

    char prefix[100] = "";
    int i = 0;
    while (1) {
        system("cls");
        header();
        printf("========= View a word (by prefix) =========\n");
        printf(">> %s\n\n", prefix);
        if (i > 0) {
            struct Node* current = root;
            int found = 1;

            for (int j = 0; j < i; j++) {
                int index = prefix[j] - 'a';
                if (current->children[index] == NULL) {
                    found = 0;
                    break;
                }
                current = current->children[index];
            }

            if (found) {
                int counter = 0;
                displayWordsByPrefix(current, prefix, i, &counter);
            } else {
                printf("\nNo words found with the prefix '%s'.\n", prefix);
            }
        }
        char ch = _getch();
        if (ch == '\r' || ch == '\n') {
            break;
        } else if (ch == 8) {
            if (i > 0) {
                i--;
                prefix[i] = '\0';
            }
        } else if (isalpha(ch)) {
            prefix[i++] = ch;
            prefix[i] = '\0';
        }
    }
    printf("\n       >> Press Enter to continue <<");
    while (_kbhit()) _getch();
    while (1) {
        char ch = getch();
        if (ch == '\r') {
            mainMenu4();
            break;
        }
    }
    _getch();

}

void exitProgram(){

    system("cls");
    header();
    puts("          Exiting the program...");
    Sleep(2000);
    exit(0);

}

void header(){

    puts(" ______                          __         "); 
    puts("|_   _ \\                        [  |        ");
    puts("  | |_) |   .--.    .--.   .--./)| | .---.  "); 
    puts("  |  __'. / .'`\\ \\/ .'`\\ \\/ /'`\\;| |/ /__\\\\ ");
    puts(" _| |__) || \\__. || \\__. |\\ \\._//| || \\__., "); 
    puts("|_______/  '.__.'  '.__.' .',__`[___]'.__.' ");
    puts("                         ( ( __))           "); 
    puts("");

}

void headerAnimation(){

    puts(" ______                          __         "); usleep(100000);
    puts("|_   _ \\                        [  |        "); usleep(100000);
    puts("  | |_) |   .--.    .--.   .--./)| | .---.  "); usleep(100000);
    puts("  |  __'. / .'`\\ \\/ .'`\\ \\/ /'`\\;| |/ /__\\\\ "); usleep(100000);
    puts(" _| |__) || \\__. || \\__. |\\ \\._//| || \\__., "); usleep(100000);
    puts("|_______/  '.__.'  '.__.' .',__`[___]'.__.' "); usleep(100000);
    puts("                         ( ( __))           "); usleep(100000);
    puts(""); usleep(100000);
    puts("========= 'w' and 's' to navigate ========="); usleep(100000);
    puts(""); usleep(100000);
}

void mainMenu1(){
    
    system("cls");
    header();
    puts("========= 'w' and 's' to navigate =========");
    puts("");
    puts("            >> Add a slang <<         ");
    puts("           Search a slang word             ");
    puts("              View all words               ");
    puts("          View words (by prefix)       ");
    puts("                  Exit                  ");

    char ch = getch();
    while(1){
        switch(ch){
            case 'w' : mainMenu5(); break;
            case 's' : mainMenu2(); break;
            case '\r' : addWord(); break;
            case '\n' : addWord(); break;
            default: addWord(); break;
        }
    }
    
}

void mainMenu2(){
    
    system("cls");
    header();
    puts("========= 'w' and 's' to navigate =========");
    puts("");
    puts("               Add a slang          ");
    puts("        >> Search a slang word <<             ");
    puts("              View all words               ");
    puts("          View words (by prefix)       ");
    puts("                  Exit                  ");

    char ch = getch();
    while(1){
        switch(ch){
            case 'w' : mainMenu1(); break;
            case 's' : mainMenu3(); break;
            case '\r' : searchWord(); break;
            case '\n' : searchWord(); break;
            default: searchWord(); break;
        }
    }

}

void mainMenu3(){
    
    system("cls");
    header();
    puts("========= 'w' and 's' to navigate =========");
    puts("");
    puts("               Add a slang          ");
    puts("           Search a slang word           ");
    puts("           >> View all words <<               ");
    puts("          View words (by prefix)       ");
    puts("                  Exit                  ");

    char ch = getch();
    while(1){
        switch(ch){
            case 'w' : mainMenu2(); break;
            case 's' : mainMenu4(); break;
            case '\r' : viewWord(); break;
            case '\n' : viewWord(); break;
            default: viewWord(); break;
        }
    }

}

void mainMenu4(){

    system("cls");
    header();
    puts("========= 'w' and 's' to navigate =========");
    puts("");
    puts("               Add a slang          ");
    puts("           Search a slang word           ");
    puts("              View all words               ");
    puts("       >> View words (by prefix) <<       ");
    puts("                  Exit                  ");

    char ch = getch();
    while(1){
        switch(ch){
            case 'w' : mainMenu3(); break;
            case 's' : mainMenu5(); break;
            case '\r' : viewWordByPrefix(); break;
            case '\n' : viewWordByPrefix(); break;
            default: viewWordByPrefix(); break;
        }
    }

}

void mainMenu5(){

    system("cls");
    header();
    puts("========= 'w' and 's' to navigate =========");
    puts("");
    puts("               Add a slang          ");
    puts("           Search a slang word           ");
    puts("              View all words               ");
    puts("          View words (by prefix)       ");
    puts("               >> Exit <<                  ");

    char ch = getch();
    while(1){
        switch(ch){
            case 'w' : mainMenu4(); break;
            case 's' : mainMenu1(); break;
            case '\r' : exitProgram(); break;
            case '\n' : exitProgram(); break;
            default: exitProgram(); break; 
        }
    }

}

int main(){

    headerAnimation();
    mainMenu1();

    return 0;
}