#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure pour un utilisateur
typedef struct {
    char username[50];
    char password[50];
    char role[10];
} User;

// Structure pour un livre
typedef struct {
    int id;
    char title[100];
    char author[100];
    float price;
    int quantity;
} Book;

// nom des Fichiers text on prefere les declares ici au cas ou on a un changement
// on change seulement ici et on utilise le pointeur de char 
//car cest pas dans main
const char *usersFile = "users.txt";
const char *booksFile = "books.txt";

// Variables globales pour l'ID des livres
int lastBookID = 1;

// Prototypes des fonctions
void generateUsers();
void registerUser();
int loginUser(char *role);
void generateBooks();
void addBook();
void viewBooks();
void updateBook();
void deleteBook();

void borrowBook();

int isUsernameUnique(const char *username);
int authenticateUser(const char *username, const char *password, char *role);
void menuAdmin();
void menuMember();

int main() {
    int choice;
    char role[7];
    
    printf("LIBRARY MANAGMENT SYSTEM\n");
    generateUsers();
    generateBooks();
    //WHILE crée un menu interactif qui se répète jusqu'à  que USER quitte LE 1 CEST POUR DIRE QUE WHILE(x) x>0 alors condition vrai rester dans 
    //la boucle
    while (1) {
        printf("\n1. Enregistrer\n");
        printf("2. Se connecter\n");
        printf("3. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choice);
        //ON PEUX UTILISER IF ELSE AUSSI
        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (loginUser(role)) {
                    if (strcmp(role, "Admin") == 0) {
                        menuAdmin();
                    } else {
                        menuMember();
                    }
                }
                break;
            case 3:
                printf("Au revoir !\n");
                exit(0); // Le paramètre 0 indique que le programme se termine normalement, sans erreur. exit est une fonction de stdio.h
            default:
                printf("Choix invalide.\n");
        }
    }
    return 0;
}

void generateUsers() {
    FILE *file = fopen(usersFile, "r"); // ouvrir en mode lecture pour verifier lexistence du fichier

    if (file != NULL) {
        fclose(file); // fichier existe deja
        printf("le fichier %s existe.\n", usersFile);
        return;
    }

    // si il nexiste pas creation dun nouveau fichier en mode ecriture
    file = fopen(usersFile, "w");
    if (file == NULL) {
        printf("Erreur : La creation du fichier %s a echoue.\n", usersFile);
        return;
    }

    // Ajouter un utilisateur administrateur de base
    fprintf(file, "RYM,1234,Admin\n");

    fclose(file); // Ne pas oublier de fermer le fichier
    printf("Fichier %s cree avec succes avec un user admin par defaut.\n", usersFile);
}
void generateBooks() {
    FILE *fileB =fopen(booksFile,"r");
    if(fileB != NULL){
        fclose(fileB);
        printf("fichier %s existe deja.\n",booksFile);
        return;
    }
    fileB=fopen(booksFile,"w");
    if(fileB==NULL){
        printf("echec de la creation du fichier %s .\n",booksFile);
        return;
    }
    fprintf(fileB,"1,FIRST,RYM,500.0,4\n");
    fclose(fileB);
    printf("fichier %s cree avec succes avec un livre par default.\n");
}
