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