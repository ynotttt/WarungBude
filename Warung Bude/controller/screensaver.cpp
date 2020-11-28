extern int longestDishName, ctrDish, ctrCust;
#include "utilities.cpp"
#include "source.cpp"

// screensaver
void mainMenu();
void addDish(); // 1
void removeDish(); // 2
void addCustomer(); // 3
void searchCustomer(); // 4
void viewWarteg(); // 5
void order(); // 6
void payment(); // 7
void endProgram(); // 8

/* Main Menu */
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
                addCustomer();
                break;
            case 4:
                searchCustomer();
                break;
            case 5:
                viewWarteg();
                break;
            case 6:
                order();
                break;
            case 7:
                payment();
                break;
            case 8:
                endProgram();
                break;
        }
    } while (optionMainMenu < 1 || optionMainMenu > 8);
}


/* 1. Add Dish */
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
    enterPrompt();
    cls(); mainMenu();
}

/* 2. Remove Dish */
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
        if (removeThisDish[0] - '0' == 0)
        {
            cls(); mainMenu();
        }
        flagRemoveDish = popThisDish(removeThisDish);
    }
    ctrDish--;
    puts("The dish has been removed!");
    enterPrompt();
    cls(); mainMenu();
}

/* 3. Add Customer */
void addCustomer() {
    cls();
    char tempCust[255]; int flagCustomer = 1;
    do
    {
        flagCustomer = 0;
        printf("Insert the customer's name [Without space]: "); scanf("%[^\n]", tempCust); getchar();
        if (tempCust[0] - '0' == 0)
        {
            cls(); mainMenu();
        }
        for (int i = 0; tempCust[i] != '\0'; i++)
        {
            if (tempCust[i] == ' ' || tempCust[i] < 'A' || ('Z' < tempCust[i] && tempCust[i] < 'a') || tempCust[i] > 'z')
            {
                flagCustomer = 1;
                break;
            }
        }
    } while (flagCustomer);

    insert(tempCust);
    ctrCust++;
    editFileCust(); delay();
    puts("Customer has been added!");
    enterPrompt();
    cls(); mainMenu();
}

/* 4. Search Customer */
void searchCustomer() {
    cls();
    char tempSearch[255]; int flagSearch = 1;
    do
    {
        flagSearch = 0;
        printf("Insert the customer’s name to be searched: "); scanf("%[^\n]", tempSearch); getchar();
        if (tempSearch[0] - '0' == 0)
        {
            cls(); mainMenu();
        }
        for (int i = 0; tempSearch[i] != '\0'; i++)
        {
            if (tempSearch[i] == ' ' || tempSearch[i] < 'A' || ('Z' < tempSearch[i] && tempSearch[i] < 'a') || tempSearch[i] > 'z')
            {
                flagSearch = 1;
                break;
            }
        }
    } while (flagSearch);

    bool lostAndFound = search(tempSearch);
    lostAndFound == true ? printf("%s is present.\n", tempSearch) : printf("%s is not present.\n", tempSearch);
    enterPrompt();
    cls(); mainMenu();
}

/* 5. View Warteg */
void viewWarteg() {
    cls();
    puts("Customer's List");

    for (int i = 0; i < 26; i++)
    {
        if(headCustomer[i])
        {
            currCustomer = headCustomer[i];
            while (currCustomer)
            {
                printf("%02d. %s\n", i, currCustomer->name);
                currCustomer = currCustomer->next;
            }
        }
    }

    enterPrompt();
    cls(); mainMenu();
}

/* 6. Order */
void order() {
    if (!ctrDish)
    {
        puts("There's no available dishes currently...");
        enterPrompt();
        cls(); mainMenu();
    }
    if (!ctrCust)
    {
        puts("There's no customers currently...");
        enterPrompt();
        cls(); mainMenu();
    }
    cls();
    char userOrder[255];
    while (1)
    {
        int flagOrder = 1;
        do
        {
            flagOrder = 0;
            printf("Insert the customer’s name to be searched: "); scanf("%[^\n]", userOrder); getchar();
            if (userOrder[0] - '0' == 0)
            {
                cls(); mainMenu();
            }
            for (int i = 0; userOrder[i] != '\0'; i++)
            {
                if (userOrder[i] == ' ' || userOrder[i] < 'A' || ('Z' < userOrder[i] && userOrder[i] < 'a') || userOrder[i] > 'z')
                {
                    flagOrder = 1;
                    break;
                }
            }
        } while (flagOrder);

        bool lostAndFound = search(userOrder);
        if (!lostAndFound) continue;
        else break;
    }
    
    int nOrder;
    do
    {
        printf("Insert the amount of dish: "); scanf("%d", &nOrder); getchar();
        if (nOrder == 0)
        {
            cls(); mainMenu();
        }
    } while (nOrder < 0);
    
    char arr[255];
    for (int i = 0; i < nOrder; i++)
    {
        ;
    }

    puts("Order success!");
    enterPrompt();
    cls(); mainMenu();
}

void payment() {
    if (!ctrCust) {
        puts("There's no customers currently...");
        enterPrompt(); cls(); mainMenu();
    }

    int idx;
    do
    {
        printf("Insert the customer’s index: "); scanf("%d", &idx); getchar();
    } while (idx < 0 || idx > 26);
    puts("");
    if (!headCustomer[idx]) {
        puts("There's no order for that customer's ID");
        enterPrompt(); cls(); mainMenu();
    }

    
}

/* 8. Exit Warteg */
void endProgram() {
    puts("Please expand your terminal to full screen!");
    enterPrompt();
    AlgorithmBootcamp();
    exit(0);
}