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
void registerUser() {
   char username[20];
   char password[10];
   char role[10];
   printf("bienvenue veuillez suivre les etapes suivantes si vous navez pas de comptes\n");
   printf("\nentrez le nom dutilisateurs:");
   scanf("%s",username);
   if(isUsernameUnique(username) ==0){
     printf("erreur ce nom existe deja");
     return;
   }
   printf("\nentrez le mot de passe(sans espace):");
   scanf("%s",password);
   printf("entrez le role:\n");
   scanf("%s",role);
   FILE *file =fopen(usersFile,"a");
   fprintf(file,"%s,%s,%s\n",username,password,role);
   fclose(file);
   printf("inscription avec succees.\n");
   printf("veuillez maintenant vous connecter .\n");
}
int isUsernameUnique(const char *username){
    //"%[^,]" :Ce format indique à sscanf d'extraire tous les caractères jusqu'à la première virgule , dans la ligne.
    // sscanf lit des données à partir DUNE CHAR (en mémoire), au lieu de l'entree.
    //  extrait data dune char existante en suivant le format.
    FILE *file =fopen(usersFile,"r");
    char userligne[20];
    char ligne[150];
    //sscanf(data, "%d", &age); lit a partir de la chaine data
    while(fgets(ligne,sizeof(ligne),file)){
        //while fgets na pas terminer toute les ligne elle renvoit 1 donc vrai la boucle while termine
        sscanf(ligne,"%[^,]",userligne);
        if(strcmp(username,userligne)==0){
            fclose(file);
            return 0; // on sort de la fonction is usernameunique
        }
    }
    fclose(file);
    return 1; //si on trouve que le mot nexiste pas
}
int loginUser(char *role){
    char username[20];
    char password[10];
    printf("\nveuiller entrer votre nom dutilisateur:");
    scanf("%s",username);
    printf("\nveuiller entrer votre mot de passe:");
    scanf("%s",password);
    if(authenticateUser(username,password,role)==0){
      printf("nom ou mot de passe invalide veuillez verifier vos donnees.\n");
      return 1;
    }else{
        printf("connexion reussie role %s.\n",role);
        return 0;
    }
}
int authenticateUser(const char *username, const char *password,char *role){
    FILE *file =fopen(usersFile,"r");
    if (file == NULL) {
        printf("Erreur : echec douverture du fichier %s.\n", usersFile);
        return 0;
    }
    char stokUsername[50], stokPassword[50], stokRole[10];
    char ligne[150];
    while(fgets(ligne,sizeof(ligne),file)){
        sscanf(ligne,"%[^,],%[^,],%s",stokUsername,stokPassword,stokRole);
        if(strcmp(username, stokUsername) == 0 && strcmp(password, stokPassword) == 0){
            strcpy(role, stokRole);
            fclose(file);
            return 0; // on sort de la fonction is usernameunique
        }
    }
    fclose(file);
    return 1;
}
void menuAdmin(){
    int choix;
    while(1){
        printf("bienvenue au menu admin en quoi on peux vous aider.\n");
        printf("1.voir la liste des livres.\n");
        printf("2.ajouter un livre.\n");
        printf("3.modifier un livre existant.\n");
        printf("4.deconnexion.\n");
        printf("choisissez un nombre :\n");
        scanf("%d",&choix);
        switch(choix){
            case 1:
             viewBooks();
             break;
            case 2:
             addBook();
             break;
            case 3:
             updateBook();
             break;
            case 4:
             return;
            default:
             printf("choic invalid choisissez entre 1 et 4\n");
        }
    }
}
void menuMember(){
    int choix;
    while(1){
        printf("bienvenue au menu membre en quoi on peux vous aider.\n");
        printf("1.voir la liste des livres.\n");
        printf("2.empreinter un livre.\n");
        printf("3.deconnexion.\n");
        printf("choisissez un nombre :\n");
        scanf("%d",&choix);
        switch(choix){
            case 1:
             viewBooks();
             break;
            case 2:
             borrowBook();
             break;
            case 3:
             return;
            default:
             printf("choic invalid choisissez entre 1 et 3\n");
        }
    }
}
void updateBook(){
    FILE *fileB = fopen(booksFile,"r");
    if(fileB == NULL){
        printf("echec douverture du fichier book.\n");
        return;
    }
    printf("veuillez rentrer lid du livre que vous voulez modifier:");
    int id;
    scanf("%d",id);
    FILE *ftemp = fopen("temp.txt","w");
    if(ftemp == NULL){
        printf("\nerreur lhors de louverture du fichier temporaraire pour update book.\n");
        return;
    }
    char ligne[150];
    int found =0;
    while(fgets(ligne,sizeof(ligne),fileB)){
        Book book; //book est un element de la structure Book
        sscanf(ligne,"%[^,],%[^,],%f,%d",&book.id,&book.title,&book.author,&book.price,&book.quantity);
        if(book.id == id){
           found=1;
           printf("veuillez entrez le nouveau titre du livre:");
           //getchar() Lit un seul caractère du flux input standard (stdin). elle consomme le carac de nouvelle ligne (\n)
           //qui reste dans le buffer d'entrée après la saisie 
           //d'un nombre par scanf() quon vas utilise dans price et quantity
           getchar();
           fgets(book.title,sizeof(book.title),stdin);
           //stdin: la ligne doit etre lue depuis le flux ENTREE standard le clavier.
           printf("\nveuillez entrez le nouveau auteur du livre:");
           getchar();
           fgets(book.author,sizeof(book.author),stdin);
           printf("\nveuillez entrez le nouveau prix du livre:");
           scanf("%f",&book.price);
           printf("\nveuillez entrez la quantite du livre:");
           scanf("%d",&book.quantity);
        }
        fprintf(ftemp, "%d,%s,%s,%f,%d\n", book.id, book.title, book.author, book.price, book.quantity);
    }
    fclose(fileB);
    fclose(ftemp);
    remove(booksFile);
    rename("temp.txt",booksFile);
    if(found){
       // si found = 0 alors la conditions de if nest pas valable
         printf("livre trouve et modifier veuillez verfier avec loptien view.\n");
    }else{
     printf("livre non trouve vous vous etes tromper did peut etre reesayer.\n");
    }
}
void addBook() {
    Book book;
    printf("Entrez le titre du livre : ");
    getchar(); // Pour consommer le caractère '\n' 
    fgets(book.title, sizeof(book.title), stdin);
    strtok(book.title, "\n");
    printf("Entrez lauteur du livre : ");
    fgets(book.author, sizeof(book.author), stdin);
    strtok(book.author, "\n");
    printf("Entrez le prix du livre : ");
    scanf("%f", &book.price);

    printf("\nEntrez la quantite du livre : ");
    scanf("%d", &book.quantity);
    
    book.id = ++lastBookID;

    FILE *file = fopen(booksFile, "a");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s.\n", booksFile);
        return;
    }
    lastBookID= book.id;

    fprintf(file, "%d,%s,%s,%.2f,%d\n", book.id, book.title, book.author, book.price, book.quantity);
    fclose(file);
    printf("Livre ajoute avec succes.\n");
}

// Afficher les livres
void viewBooks() {
    FILE *file = fopen(booksFile, "r");
    if (file == NULL) {
        printf("Aucun livre disponible.\n");
        return;
    }

    char ligne[150];
    printf("\n=== Liste des livres ===\n");
    while (fgets(ligne, sizeof(ligne), file)) {
        Book book;
        sscanf(ligne, "%d,%[^,],%[^,],%f,%d", &book.id, book.title, book.author, &book.price, &book.quantity);
        printf("ID: %d, Titre: %s, Auther: %s, Price: %.2f, Quantity: %d\n",
               book.id, book.title, book.author, book.price, book.quantity);
    }

    fclose(file);
}
void borrowBook() {
    int id, quantity;
    printf("\nEntrez id du livre a emprunter : ");
    scanf("%d", &id);
    printf("\nEntrez la quantite a emprunter : ");
    scanf("%d", &quantity);

    FILE *file = fopen(booksFile, "r");
    if (file == NULL) {
        printf("Aucun livre trouve.\n");
        return;
    }

    FILE *ftemp = fopen("temp.txt", "w");
    if (ftemp == NULL) {
        printf("Impossible de creer un fichier temporaire.\n");
        fclose(file);
        return;
    }

    char ligne[150];
    int found = 0, suffisant = 1;
    while (fgets(ligne, sizeof(ligne), file)) {
        Book book;
        sscanf(ligne, "%d,%[^,],%[^,],%f,%d", &book.id, book.title, book.author, &book.price, &book.quantity);

        if (book.id == id) {
            found = 1;
            if (book.quantity < quantity) {
                suffisant = 0;
            } else {
                book.quantity -= quantity;
            }
        }

        fprintf(ftemp, "%d,%s,%s,%.2f,%d\n", book.id, book.title, book.author, book.price, book.quantity);
    }

    fclose(file);
    fclose(ftemp);

    remove(booksFile);
    rename("temp.txt", booksFile);

    if (!found) {
        printf("Livre non trouve.\n");
    } else if (!suffisant) {
        printf("Quantite insuffisante.\n");
    } else {
        printf("Livre emprunte avec succes.\n");
    }
}
void deleteBook() {
    int id;
    printf("Entrez ID du livre a supprimer : ");
    scanf("%d", &id);

    FILE *file = fopen(booksFile, "r");
    if (file == NULL) {
        printf("Aucun livre trouve.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf(" Impossible de creer un fichier temporaire.\n");
        fclose(file);
        return;
    }

    char ligne[150];
    int found = 0;
    while (fgets(ligne, sizeof(ligne), file)) {
        Book book;
        sscanf(ligne, "%d,%[^,],%[^,],%f,%d", &book.id, book.title, book.author, &book.price, &book.quantity);

        if (book.id == id) {
            found = 1;
            continue; // Ne pas écrire ce livre dans le fichier temporaire
        }

        fprintf(temp, "%d,%s,%s,%.2f,%d\n", book.id, book.title, book.author, book.price, book.quantity);
    }

    fclose(file);
    fclose(temp);

    remove(booksFile);
    rename("temp.txt", booksFile);

    if (found) {
        printf("Livre supprime avec succes.\n");
    } else {
        printf("Livre non trouve.\n");
    }
}