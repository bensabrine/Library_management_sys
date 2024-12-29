
void borrowBook() {
    int id, quantity;
    printf("Entrez l'ID du livre à emprunter : ");
    scanf("%d", &id);
    printf("Entrez la quantité à emprunter : ");
    scanf("%d", &quantity);

    FILE *file = fopen(booksFile, "r");
    if (file == NULL) {
        printf("Aucun livre trouvé.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Erreur : Impossible de créer un fichier temporaire.\n");
        fclose(file);
        return;
    }

    char line[200];
    int found = 0, sufficient = 1;
    while (fgets(line, sizeof(line), file)) {
        Book book;
        sscanf(line, "%d,%[^,],%[^,],%f,%d", &book.id, book.title, book.author, &book.price, &book.quantity);

        if (book.id == id) {
            found = 1;
            if (book.quantity < quantity) {
                sufficient = 0;
            } else {
                book.quantity -= quantity;
            }
        }

        fprintf(temp, "%d,%s,%s,%.2f,%d\n", book.id, book.title, book.author, book.price, book.quantity);
    }

    fclose(file);
    fclose(temp);

    remove(booksFile);
    rename("temp.txt", booksFile);

    if (!found) {
        printf("Livre non trouvé.\n");
    } else if (!sufficient) {
        printf("Quantité insuffisante.\n");
    } else {
        printf("Livre emprunté avec succès.\n");
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
