#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "utilities.h"

void checkDishLongestName()
{
    currDish = headDish;
    while (currDish)
    {
        int len = strctr(currDish->foodName);
        longestDishName < len ? longestDishName = len : longestDishName;
        currDish = currDish->next;
    }
}

int checkExtraCount()
{
    int extra_ctr = 0, jumlahMenu = ctrDish;
    if (jumlahMenu > 99) {
        do
        {
            extra_ctr++;
            jumlahMenu /= 10;
        } while (jumlahMenu != 0);
        extra_ctr -= 2;
    }
    return extra_ctr;
}

void AlgorithmBootcamp() {
    char ch;
    FILE *fp = fopen("splash.txt","r");
    while((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
    }
    puts("");
    fclose(fp);
}

int checkUniqueDish(char *tempName) {
    currDish = headDish;
    while (currDish)
    {
        if (strcasecmp(tempName, currDish->foodName) == 0)
        {
            return 1;
        }
        currDish = currDish->next;
    }
    return 0;
}

void editFileDish() {
    FILE *fdish = fopen("dish.txt", "w");

    currDish = headDish;
    for (int i = 0; i < ctrDish; i++)
    {
        fprintf(fdish, "Nama Dish: %s\n", currDish->foodName);
        fprintf(fdish, "Harga: Rp%d\n", currDish->price);
        fprintf(fdish, "Jumlah: %d\n", currDish->quantity);
        if(currDish != tailDish) fprintf(fdish,"\n");
        currDish = currDish->next;
    }
    fclose(fdish);
}

void printHeader(int len, int xtra) {
    int max_length = len + 23 + xtra;

    for (int i = 0; i < max_length; i++) printf("=");
    puts("");

    for (int i = 0; i < (max_length-11)/2; i++) printf(" ");
    printf("Bude's Menu");
    for (int i = 0; i < (max_length-11)/2; i++) printf(" ");
    puts("");

    for (int i = 0; i < max_length; i++) printf("=");
    puts("");

    printf("No.");
    for (int i = 0; i < (xtra + 1); i++) printf(" ");

    for (int i = 0; i < (len - 4)/2; i++) printf(" ");
    printf("Name");
    for (int i = 0; i < (len - 4)/2; i++) printf(" ");

    printf("  Quantity");
    printf("   Price\n");
}

void printDishes() {
    currDish = headDish;
    for (int i = 0; i < ctrDish; i++)
    {
        printf("%d. ", i+1);
        int diff = longestDishName - strctr(currDish->foodName);

        for (int i = 0; i < diff/2; i++) printf(" ");
        printf(" %s ", currDish->foodName);
        for (int i = 0; i < diff/2; i++) printf(" ");

        printf("   %03d    ", currDish->quantity);

        currDish->price >= 10000 ? printf(" Rp%ld\n", currDish->price) : printf("  Rp%ld\n", currDish->price);
        currDish = currDish->next;
    }
}

/* ========================================================================================================== */

void pushDishTail(char *foodName, int price, int quantity)
{
    Dish *temp = createDish(foodName, price, quantity);

    if (!headDish)
    {
        headDish = tailDish = temp;
    }
    else
    {
        tailDish->next = temp;
        temp->prev = tailDish;
        tailDish = temp;
    }
}

int popThisDish(char *name)
{
    if (!headDish)
    {
        return 1;
    }
    else if (strcasecmp(name, headDish->foodName) == 0)
    {
        if (headDish && headDish == tailDish)
        {
            headDish = tailDish = NULL;
            free(headDish);
        }
        else
        {
            Dish *newHead = headDish->next;
            headDish->next = newHead->prev = NULL;
            free(headDish);
            headDish = newHead;
        }
        return 0;
    }
    else if (strcasecmp(name, tailDish->foodName) == 0)
    {
        if (headDish && headDish == tailDish)
        {
            headDish = tailDish = NULL;
            free(headDish);
        }
        else
        {
            Dish *newTail = tailDish->prev;
            tailDish->prev = newTail->next = NULL;
            free(tailDish);
            tailDish = newTail;
        }
        return 0;
    }
    else
    {
        currDish = headDish;
        while (currDish && (strcasecmp(name, currDish->foodName)) != 0)
        {
            currDish = currDish->next;
        }
        
        if (!currDish) {
            return 1;
        }

        currDish->prev->next = currDish->next;
        currDish->next->prev = currDish->prev;

        currDish->next = currDish->prev = NULL;
        free(currDish);
        return 0;
    }
    return 1;
}