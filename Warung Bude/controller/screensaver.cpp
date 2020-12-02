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
    struct Customer *orderByThisName = NULL;
    while (1)
    {
        printf("Insert the customer's name: ");
        scanf("%[^\n]", userOrder); getchar();
        if (userOrder[0]-'0' == 0)
        {
            cls(); mainMenu();
        }
        orderByThisName = searchThisCustomerByName((char *)userOrder);
        if(orderByThisName) {
            break;
        }
        printf("That customer is currently not available!\n");
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
    
    for (int i = 0; i < nOrder; i++)
    {
        char inputUnformatted[255], orderDishName[255], dishCtr[255]; int dishAmount;
        printf("[%d] Insert the dish’s name and quantity: ", i+1); scanf("%[^\n]", inputUnformatted); getchar();
        if (inputUnformatted[0] - '0' == 0)
        {
            cls(); mainMenu();
        }
        // formatOrder((char *)inputUnformatted, &orderDishName, &dishAmount);
        int idx = 0, j = 0;
        for (idx = 0; inputUnformatted[idx+1] != 'x' && (!('0'<= inputUnformatted[idx+2] && inputUnformatted[idx+2] <= '9')); idx++)
        {
            orderDishName[idx] = inputUnformatted[idx];
        }   
        orderDishName[idx] = '\0';

        idx += 2;
        for (int i = idx; inputUnformatted[i] != '\0'; i++, j++)
        {
            dishCtr[j] = inputUnformatted[i];
        }
        dishCtr[j] = '\0';
        dishAmount = atoi(dishCtr);

        struct Dish *tempDishOrder = searchThisDishByName(orderDishName);
        if (tempDishOrder) {
            if (tempDishOrder->quantity - dishAmount < 0) {
                printf("We only got %d stock for this dish. Please input another amount.\n", tempDishOrder->quantity);
                i--; continue;
            }
            tempDishOrder->quantity -= dishAmount;
            editFileDish();
            struct Order *temp = createOrder((char*)orderDishName, tempDishOrder->price, dishAmount);
            pushOrderTail(orderByThisName, temp);
        }
        else {
            puts("That dish currently isn't available. Please input another dish.");
            i--; continue;
        }
    }

    puts("Order success!");
    enterPrompt();
    cls(); mainMenu();
}

/* 7. Payment */
void payment() {
    if (!ctrCust) {
        puts("There's no customers currently...");
        enterPrompt(); cls(); mainMenu();
    }

    int custIndex;
    while (1) {
        printf("Insert the customer’s index: "); scanf("%d", &custIndex); getchar();
        if (custIndex == -1) {
            cls(); mainMenu();
        }

        if (headCustomer[custIndex]) {
            currCustomer = headCustomer[custIndex];
            break;
        }

        puts("There are currently no customer with that customer index.");
    }

    puts("");
    printf("%s\n", currCustomer->name); getchar();
    currOrder = currCustomer->headOrder;

    int orderNumber = 1, totalPayments = 0;
    while (currOrder) {
        printf("[%d] %s x%d\n", orderNumber, currOrder->name, currOrder->quantity);
        totalPayments += currOrder->price * currOrder->quantity;
        orderNumber++;
        currOrder = currOrder->next; 
    }
    printf("Total: Rp%d\n", totalPayments);
    popCustomerHead(custIndex);
    enterPrompt();
    cls(); mainMenu();
}

/* 8. Exit Warteg */
void endProgram() {
    puts("Please expand your terminal to full screen!");
    enterPrompt();
    AlgorithmBootcamp();
    exit(0);
}