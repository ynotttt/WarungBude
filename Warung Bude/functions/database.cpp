#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Database
struct Dish {
    char foodName[255];
    int price, quantity;
    Dish *prev, *next;
} *headDish, *tailDish, *currDish, *newDish, *delDish;

Dish *createDish(char *foodName, int price, int quantity) {
    Dish *temp = (Dish*)malloc(sizeof(Dish));
    strcpy(temp->foodName, foodName);
    temp->price = price;
    temp->quantity = quantity;
    temp->next = temp->prev = NULL;
    return temp;
}

// Global Variables
int ctrDish = 0, longestDishName = 0;

