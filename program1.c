/*youb nader
instagram: unnamed0._
program: vending machine*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//------------------------------------------------------------------------
//clear screen command based on the os
#ifdef _WIN32
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif
//------------------------------------------------------------------------
#define MAX_DRINKS 100 //max number of drinks
#define NAME_SIZE 20 //max size od drink name
//------------------------------------------------------------------------
//record structure of a drink
typedef struct {
    char name[NAME_SIZE]; //drink name
    int price; //drink price
    int stock; //quantity in stock
    int sales; //amount sold
} drink;
//------------------------------------------------------------------------
//function to clear the sceen
void clearScreen() {
    system(CLEAR_SCREEN);
}
//------------------------------------------------------------------------
//function to wait for user to press enter to continue
void attendreEntree() {
    printf("Press enter to continue...\n");
    getchar(); 
    getchar(); 
}
//---------------------------------------------------------------------------
//function to display progress bar
void displayProgress() {
    printf("Preparing drink: [");
    for (int i = 0; i < 40; i++) {
        printf("#");
        fflush(stdout); //immediately display the character
        usleep(100000); //sleep for 100000 microseconds (0.1 seconds)
    }
    printf("]\nDone\n");
}
//---------------------------------------------------------------------------------
//function to display menu
void displayMenu(drink *drinks, int size) {
    clearScreen();
    printf("Drink Menu:\n");
    printf("+----+----------------------+--------+----------+\n");
    printf("| No | Drink Name           | Price  | In Stock |\n");
    printf("+----+----------------------+--------+----------+\n");
    for (int i = 0; i < size; i++) {
        printf("| %-2d | %-20s | %-6d | %-8d |\n", i + 1, drinks[i].name, drinks[i].price, drinks[i].stock);
    }
    printf("+----+----------------------+--------+----------+\n");
}
//------------------------------------------------------------------------
//function to order a drink
void orderDrink(drink *drinks, int size) {
    displayMenu(drinks, size);
    int choice, amount;
    printf("Please choose a drink (1-%d): ", size);
    scanf("%d", &choice);
    if (choice < 1 || choice > size) {
        printf("Invalid choice. Please try again.\n");
        return;
    }
    drink *selectedDrink = &drinks[choice - 1];
    if (selectedDrink->stock <= 0) {
        printf("Sorry, this drink is out of stock.\n");
        return;
    }
    displayProgress();
    printf("You selected: %s. Please insert %d DA.\n", selectedDrink->name, selectedDrink->price);
    printf("insert here: ");
    scanf("%d", &amount);
    if (amount < selectedDrink->price) {
        printf("Insufficient amount. Transaction cancelled.\n");
    } else {
        printf("Transaction successful. Please take your %s.\n", selectedDrink->name);
        selectedDrink->stock--;
        selectedDrink->sales++;
        if (amount > selectedDrink->price) {
            printf("Please take your change: %d DA\n", amount - selectedDrink->price);
        }
    }
}
//------------------------------------------------------------------------
//function to add a drink
void addDrink(drink *drinks, int *size) {
    if (*size >= MAX_DRINKS) {
        printf("Cannot add more drinks. Maximum capacity reached.\n");
        return;
    }
    drink newDrink;
    printf("Enter the name of the new drink: ");
    scanf("%s", newDrink.name);
    printf("Enter the price of the new drink: ");
    scanf("%d", &newDrink.price);
    printf("Enter the stock quantity of the new drink: ");
    scanf("%d", &newDrink.stock);
    newDrink.sales = 0;
    drinks[*size] = newDrink;
    (*size)++;
    displayProgress();
    printf("Drink added successfully!\n");
}
//------------------------------------------------------------------------
//function to delete a drink
void deleteDrink(drink *drinks, int *size) {
    displayMenu(drinks, *size);
    int choice;
    printf("Please choose a drink to delete (1-%d): ", *size);
    scanf("%d", &choice);
    if (choice < 1 || choice > *size) {
        printf("Invalid choice. Please try again.\n");
        return;
    }
    printf("Deleting %s from the menu.\n", drinks[choice - 1].name);
    for (int i = choice - 1; i < *size - 1; i++) {
        drinks[i] = drinks[i + 1];
    }
    (*size)--;
    displayProgress();
    printf("Drink deleted successfully!\n");
}
//------------------------------------------------------------------------
//function to update the stock
void updateStock(drink *drinks, int size) {
    displayMenu(drinks, size);
    int choice, newStock;
    printf("Please choose a drink to update stock (1-%d): ", size);
    scanf("%d", &choice);
    if (choice < 1 || choice > size) {
        printf("Invalid choice. Please try again.\n");
        return;
    }
    drink *selectedDrink = &drinks[choice - 1];
    printf("Enter the new stock quantity for %s: ", selectedDrink->name);
    scanf("%d", &newStock);
    selectedDrink->stock = newStock;
    displayProgress();
    printf("Stock updated successfully!\n");
}
//------------------------------------------------------------------------
void displaySales(drink *drinks, int size) {
    clearScreen();
    printf("Total Sales:\n");
    printf("+----------------------+--------+--------+\n");
    printf("| Drink Name           | Sales  | Revenue|\n");
    printf("+----------------------+--------+--------+\n");
    for (int i = 0; i < size; i++) {
        printf("| %-20s | %-6d | %-6d |\n", drinks[i].name, drinks[i].sales, drinks[i].sales * drinks[i].price);
    }
    printf("+----------------------+--------+--------+\n");
}
//------------------------------------------------------------------------
void displayDrinkDetails(drink *drinks, int size) {
    clearScreen();
    printf("Detailed Drink Information:\n");
    printf("+----+----------------------+--------+--------+--------+\n");
    printf("| No | Drink Name           | Price  | Stock  | Sales  |\n");
    printf("+----+----------------------+--------+--------+--------+\n");
    for (int i = 0; i < size; i++) {
        printf("| %-2d | %-20s | %-6d | %-6d | %-6d |\n", i + 1, drinks[i].name, drinks[i].price, drinks[i].stock, drinks[i].sales);
    }
    printf("+----+----------------------+--------+--------+--------+\n");
}
//------------------------------------------------------------------------
void manageTransactions(drink *drinks, int size) {
    clearScreen();
    int totalSalesAmount = 0, totalSold = 0;
    printf("Transaction Management:\n");
    printf("+----+----------------------+--------+--------+--------+\n");
    printf("| No | Drink Name           | Price  | Sales  | Revenue|\n");
    printf("+----+----------------------+--------+--------+--------+\n");
    for (int i = 0; i < size; i++) {
        int revenue = drinks[i].sales * drinks[i].price;
        totalSalesAmount += revenue;
        totalSold += drinks[i].sales;
        printf("| %-2d | %-20s | %-6d | %-6d | %-6d |\n", i + 1, drinks[i].name, drinks[i].price, drinks[i].sales, revenue);
    }
    printf("+----+----------------------+--------+--------+--------+\n");
    printf("| %-2s | %-20s | %-6s | %-6d | %-6d |\n", "", "Total", "", totalSold, totalSalesAmount);
    printf("+----+----------------------+--------+--------+--------+\n");
}
//------------------------------------------------------------------------
void mainMenu(drink *drinks, int size) {
    int userType;
    while (1) {
        clearScreen();
        printf("Are you a maintenance agent or a customer?\n");
        printf("1. Maintenance Agent\n");
        printf("2. Customer\n");
        printf("3. Exit\n");
        printf("Please choose your user type: ");
        scanf("%d", &userType);
        switch (userType) {
            case 1:
                maintenanceMenu(drinks, size);
                attendreEntree();
                break;
            case 2:
                customerMenu(drinks, size);
                attendreEntree();
                break;
            case 3:
                printf("Exiting...\n");
                return;
            default:
                printf("Invalid user type. Please try again.\n");
        }
    }
}
//------------------------------------------------------------------------
void maintenanceMenu(drink *drinks, int size) {
    int choice;
    while (1) {
        clearScreen();
        printf("Maintenance Agent Menu:\n");
        printf("1. Display Menu\n");
        printf("2. Add a drink\n");
        printf("3. Delete a drink\n");
        printf("4. Update stock\n");
        printf("5. Manage transactions\n");
        printf("6. Quit\n");
        printf("Please choose an option: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                displayMenu(drinks, size);
                attendreEntree();
                break;
            case 2:
                addDrink(drinks, &size);
                attendreEntree();
                break;
            case 3:
                deleteDrink(drinks, &size);
                attendreEntree();
                break;
            case 4:
                updateStock(drinks, size);
                attendreEntree();
                break;
            case 5:
                manageTransactions(drinks, size);
                attendreEntree();
                break;
            case 6:
                printf("Exiting maintenance mode.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
//------------------------------------------------------------------------
void customerMenu(drink *drinks, int size) {
    int choice;
    while (1) {
        clearScreen();
        printf("Customer Menu:\n");
        printf("1. Display Menu\n");
        printf("2. Order a drink\n");
        printf("3. Quit\n");
        printf("Please choose an option: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                displayMenu(drinks, size);
                attendreEntree();
                break;
            case 2:
                orderDrink(drinks, size);
                attendreEntree();
                break;
            case 3:
                printf("Exiting customer mode.\n");
                attendreEntree();
                mainMenu(drinks, size);
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
//------------------------------------------------------------------------
int main() {
    int size = 5;
    drink *drinks = malloc(MAX_DRINKS * sizeof(drink));
    if (drinks == NULL) {
        fprintf(stderr, "Memory error. Unable to initialize the vending machine.\n");
        return 1;
    }
    strcpy(drinks[0].name, "Selecto");
    drinks[0].price = 50;
    drinks[0].stock = 10;
    drinks[0].sales = 0;
    strcpy(drinks[1].name, "Ngaous");
    drinks[1].price = 45;
    drinks[1].stock = 10;
    drinks[1].sales = 0;
    strcpy(drinks[2].name, "iFtuit");
    drinks[2].price = 60;
    drinks[2].stock = 10;
    drinks[2].sales = 0;
    strcpy(drinks[3].name, "Caprisun");
    drinks[3].price = 45;
    drinks[3].stock = 10;
    drinks[3].sales = 0;
    strcpy(drinks[4].name, "Water");
    drinks[4].price = 25;
    drinks[4].stock = 20;
    drinks[4].sales = 0;
    mainMenu(drinks, size);
    free(drinks);
    printf("Thank you and see you again!\n");
    return 0;
}