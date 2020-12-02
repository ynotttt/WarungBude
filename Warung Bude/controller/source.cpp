extern int longestDishName, ctrDish, ctrCust;
#include "../model/database.cpp"

unsigned long djb2(char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash % 25;
}

struct Dish *searchThisDishByName(char *orderDishName)
{
    if (!headDish)
    {
        return NULL;
    }
    else if (headDish == tailDish)
    {
        if (strcmp(headDish->foodName, orderDishName) == 0)
        {
            return headDish;
        }
    }
    else if (strcmp(headDish->foodName, orderDishName) == 0)
    {
        return headDish;
    }
    else if (strcmp(tailDish->foodName, orderDishName) == 0)
    {
        return tailDish;
    }
    else
    {
        currDish = headDish;
        while (currDish != NULL)
        {
            if (strcmp(currDish->foodName, orderDishName) == 0)
            {
                return currDish;
            }
            currDish = currDish->next;
        }
    }
    return NULL;
}

struct Customer *searchThisCustomerByName(char *orderCustomerName)
{
    int idx = djb2(orderCustomerName);

    if (headCustomer[idx] == NULL)
    {
        return NULL;
    }

    currCustomer = headCustomer[idx];
    while (currCustomer != NULL)
    {
        if (strcmp(orderCustomerName, currCustomer->name) == 0)
        {
            return currCustomer;
        }
        currCustomer = currCustomer->next;
    }

    return NULL;
}

struct Customer *searchThisHeadCustomerByName(char *name) {
    int idx = djb2(name);

    if(!headCustomer[idx]) {
        return NULL;
    }
    else {
        currCustomer = headCustomer[idx];
        if(strcmp(name, currCustomer->name) == 0) {
            return currCustomer;
        }
    }
    return NULL;
}

void popCustomerHead(int idx)
{
    if (headCustomer[idx] == NULL)
    {
        return;
    }
    if (headCustomer[idx] == tailCustomer[idx])
    {
        headCustomer[idx] = tailCustomer[idx] = NULL;
        free(headCustomer[idx]);
    }
    else
    {
        struct Customer *newHead = headCustomer[idx];
        newHead = newHead->next;
        newHead->prev = NULL;
        headCustomer[idx] = NULL;
        free(headCustomer[idx]);
        headCustomer[idx] = newHead;
    }
}

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

void AlgorithmBootcamp()
{
    char ch;
    FILE *fp = fopen("../model/splash.txt", "r");
    while ((ch = fgetc(fp)) != EOF)
    {
        printf("%c", ch);
    }
    puts("");
    fclose(fp);
}

void insert(char *str)
{
    int idx = djb2(str);

    if (headCustomer[idx])
    {
        Customer *temp = createCustomer(str);
        tailCustomer[idx]->next = temp;
        tailCustomer[idx] = temp;
    }
    else
    {
        headCustomer[idx] = tailCustomer[idx] = createCustomer(str);
    }
}

void editFileDish()
{
    FILE *fdish = fopen("dish.txt", "w");

    currDish = headDish;
    for (int i = 0; i < ctrDish; i++)
    {
        fprintf(fdish, "Nama Dish: %s\n", currDish->foodName);
        fprintf(fdish, "Harga: Rp%d\n", currDish->price);
        fprintf(fdish, "Jumlah: %d\n", currDish->quantity);
        if (currDish != tailDish)
            fprintf(fdish, "\n");
        currDish = currDish->next;
    }
    fclose(fdish);
}

void editFileCust()
{
    FILE *fcust = fopen("customer.txt", "w");

    for (int i = 0; i < 26; i++)
    {
        if (headCustomer[i])
        {
            currCustomer = headCustomer[i];
            int flag = 0;
            while (currCustomer)
            {
                if (flag == 0)
                    fprintf(fcust, "%d. ", i);
                fprintf(fcust, "%s", currCustomer->name);
                if (!currCustomer->next)
                    fprintf(fcust, "\n");
                else
                {
                    fprintf(fcust, " -> ");
                    flag = 1;
                }
                currCustomer = currCustomer->next;
            }
        }
    }
    fclose(fcust);
}

void printDishes()
{
    currDish = headDish;
    for (int i = 0; i < ctrDish; i++)
    {
        printf("%d. ", i + 1);
        int diff = longestDishName - strctr(currDish->foodName);

        for (int i = 0; i < diff / 2; i++)
            printf(" ");
        printf(" %s ", currDish->foodName);
        for (int i = 0; i < diff / 2; i++)
            printf(" ");

        printf("   %03d    ", currDish->quantity);

        currDish->price >= 10000 ? printf(" Rp%ld\n", currDish->price) : printf("  Rp%ld\n", currDish->price);
        currDish = currDish->next;
    }
}

void popDishHead()
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
}

void popDishTail()
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
}

void formatOrder(char *inputUnformatted, char **orderDishName, int *dishAmount)
{
    char tempDishName[255];
    int idx = 0, j = 0;
    for (idx = 0; inputUnformatted[idx + 1] != 'x'; idx++)
    {
        tempDishName[idx] = inputUnformatted[idx];
    }
    tempDishName[idx] = '\0';

    idx += 2;
    for (int i = idx; inputUnformatted[i] != '\0'; i++, j++)
    {
        (*dishAmount) = ((*dishAmount) * 10) + (inputUnformatted[i] - '0');
    }

    (*orderDishName) = strdup(tempDishName);
}

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

void pushOrderTail(struct Customer *orderByThisName, struct Order *temp)
{
    int idx = djb2(orderByThisName->name);

    currCustomer = headCustomer[idx];
    while (currCustomer) {
        if (strcmp(currCustomer->name, orderByThisName->name) == 0) {
            break;
        }
        currCustomer = currCustomer->next;
    }

    if (!currCustomer->headOrder) {
        currCustomer->headOrder = currCustomer->tailOrder = temp;
    }
    else {
        currCustomer->tailOrder->next = temp;
        temp->prev = currCustomer->tailOrder;
        currCustomer->tailOrder = temp;
    }
}

void printHeader(int len, int xtra)
{
    int max_length = len + 23 + xtra;

    for (int i = 0; i < max_length; i++)
        printf("=");
    puts("");

    for (int i = 0; i < (max_length - 11) / 2; i++)
        printf(" ");
    printf("Bude's Menu");
    for (int i = 0; i < (max_length - 11) / 2; i++)
        printf(" ");
    puts("");

    for (int i = 0; i < max_length; i++)
        printf("=");
    puts("");

    printf("No.");
    for (int i = 0; i < (xtra + 1); i++)
        printf(" ");

    for (int i = 0; i < (len - 4) / 2; i++)
        printf(" ");
    printf("Name");
    for (int i = 0; i < (len - 4) / 2; i++)
        printf(" ");

    printf("  Quantity");
    printf("   Price\n");
}

int checkUniqueDish(char *tempName)
{
    currDish = headDish;
    while (currDish)
    {
        if (strcmp(tempName, currDish->foodName) == 0)
        {
            return 1;
        }
        currDish = currDish->next;
    }
    return 0;
}

int popThisDish(char *name)
{
    if (!headDish)
    {
        return 1;
    }
    else if (strcmp(name, headDish->foodName) == 0)
    {
        popDishHead();
        return 0;
    }
    else if (strcmp(name, tailDish->foodName) == 0)
    {
        popDishTail();
        return 0;
    }
    else
    {
        currDish = headDish;
        while (currDish && (strcasecmp(name, currDish->foodName)) != 0)
        {
            currDish = currDish->next;
        }

        if (!currDish)
        {
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

int checkExtraCount()
{
    int extra_ctr = 0, jumlahMenu = ctrDish;
    if (jumlahMenu > 99)
    {
        do
        {
            extra_ctr++;
            jumlahMenu /= 10;
        } while (jumlahMenu != 0);
        extra_ctr -= 2;
    }
    return extra_ctr;
}

bool search(char *name)
{
    for (int i = 0; i < 26; i++)
    {
        if (headCustomer[i])
        {
            currCustomer = headCustomer[i];
            while (currCustomer)
            {
                if (strcmp(name, currCustomer->name) == 0)
                {
                    return true;
                }
                currCustomer = currCustomer->next;
            }
        }
    }
    return false;
}