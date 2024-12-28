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
