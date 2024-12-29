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