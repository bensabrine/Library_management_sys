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
