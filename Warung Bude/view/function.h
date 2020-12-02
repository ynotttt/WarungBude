#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../controller/screensaver.cpp"

/* ================================================================================================ */

// global var
int longestDishName = 0;
int ctrDish = 0;
int ctrCust = 0;

/* ================================================================================================ */

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

// utilities
void outputLocalTime();
void enterPrompt();
void detectOS();
void delay();
void cls();
int strctr(char *str);

// source
unsigned long djb2(char *str, int total);
struct Dish *searchThisDishByName(char *orderDishName);
void checkDishLongestName();
void AlgorithmBootcamp();
void insert(char *str);
void editFileDish();
void editFileCust();
void printDishes();
void popHead();
void popTail();
void formatOrder(const char *inputUnformatted,  char **orderDishName, int *dishAmount);
void pushDishTail(char *foodName, int price, int quantity);
void printHeader(int len, int xtra); // Credit N40
int checkUniqueDish(char *tempName);
int popThisDish(char *name);
int checkExtraCount();
bool search(char *name);

/* ================================================================================================ */