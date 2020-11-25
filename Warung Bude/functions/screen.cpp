#include <stdio.h>
#include "utilities.h"
#include "screen.h"
#include "database.cpp"

void mainMenu() {
    detectOS();
    outputLocalTime();

    puts("1. Add Dish");
    puts("2. Remove Dish");
    puts("3. Add Customer");
    puts("4. Search Customer");
    puts("5. View Warteg");
    puts("6. Order");
    puts("7. Payment");
    puts("8. Exit Warteg");

    int optionMainMenu;
    do
    {
        printf(">> "); scanf("%d", &optionMainMenu); getchar();
        switch (optionMainMenu)
        {
            case 1:
                addDish();
                break;
            case 2:
                removeDish();
                break;
            case 3:
                puts("3");
                break;
            case 4:
                puts("4");
                break;
            case 5:
                puts("5");
                break;
            case 6:
                puts("6");
                break;
            case 7:
                puts("7");
                break;
            case 8:
                endProgram();
                break;
        }
    } while (optionMainMenu < 1 || optionMainMenu > 8);
}

void addDish() {
    cls();
    char dishName[255]; int price, quantity;
    while(1)
    {
        int flagLowercase = 1;
        do
        {
            flagLowercase = 0;
            printf("Insert the name of the dish [Lowercase letters]: "); scanf("%[^\n]", dishName); getchar();
            for (int i = 0; dishName[i] != '\0'; i++)
            {
                if ('A' <= dishName[i] && dishName[i] <= 'Z')
                {
                    flagLowercase = 1; break;
                }
            }
        } while (flagLowercase);

        int flagUnique = checkUniqueDish(dishName);
        if (flagUnique) continue;
        break;
    }

    do
    {
        printf("Insert the price of the dish [1000..50000]: "); scanf("%d", &price); getchar();
    } while (price < 1000 || price > 50000);

    do
    {
        printf("Insert the quantity of the dish [1..999]: "); scanf("%d", &quantity); getchar();
    } while (quantity < 1 || quantity > 999);
    
    pushDishTail(dishName, price, quantity);
    ctrDish++;
    editFileDish(); delay();
    puts("Dish has been added!");
    printf("Press enter to continue..."); getchar();
    cls();
    mainMenu();
}

void removeDish() {
    cls();
    currDish = headDish;
    if (!currDish)
    {
        puts("No menu available to be deleted.");
        puts("Press enter to continue..."); getchar();
        mainMenu();
    }

    checkDishLongestName();
    int xtra = checkExtraCount();
    printHeader(longestDishName, xtra);

    printDishes();
    int max_length = longestDishName + 23 + xtra;
    for (int i = 0; i < max_length; i++) printf("=");
    puts("");

    int flagRemoveDish = 1; char *removeThisDish = (char *)malloc(sizeof(char));
    while (flagRemoveDish == 1)
    {
        printf("Insert dish's name to be deleted: "); scanf("%[^\n]", removeThisDish); getchar();
        flagRemoveDish = popThisDish(removeThisDish);
    }
    ctrDish--;
    puts("The dish has been removed!");
    puts("Press enter to continue..."); getchar();
    cls();
    mainMenu();
}

void endProgram() {
    puts("Please expand your terminal to full screen!");
    printf("Press enter to continue..."); getchar();
    AlgorithmBootcamp(); exit(0);
}