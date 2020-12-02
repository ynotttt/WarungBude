// Database
struct Dish {
    char foodName[255];
    int price, quantity;
    Dish *prev, *next;
} *headDish, *tailDish, *currDish, *newDish, *delDish;

struct Order {
    char name[255];
    int quantity = 0, price;
    Order *prev, *next;
} *currOrder;

struct Customer {
    char name[255];
    Order *headOrder, *tailOrder;
    Customer *prev, *next;    
} *headCustomer[26], *tailCustomer[26], *currCustomer, *newCustomer, *delCustomer;

Dish *createDish(char *foodName, int price, int quantity) {
    Dish *temp = (Dish*)malloc(sizeof(Dish));
    strcpy(temp->foodName, foodName);
    temp->price = price;
    temp->quantity = quantity;
    temp->next = temp->prev = NULL;
    return temp;
}

Customer *createCustomer(char *name) {
    Customer *temp = (Customer *)malloc(sizeof(Customer));
    strcpy(temp->name, name);
    temp->next = temp->prev = NULL;
    return temp;
}

Order *createOrder(char *name, int price, int quantity) {
    Order *temp = (Order *)malloc(sizeof(Order));
    strcpy(temp->name, name);
    temp->price = price;
    temp->quantity = quantity;
    return temp;
}