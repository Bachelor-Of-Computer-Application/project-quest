#include <stdio.h>
#include <string.h>

// --- DATA STRUCTURES ---

struct Bus {
    int number;
    char from[50];
    char to[50];
    int totalSeats;
    int freeSeats;
    float price;
};

struct User {
    char name[50];
    char pass[50];
};

// global menue

struct User users[3] = {
    {"admin",   "123"},
    {"prapti",  "456"},
    {"manisha", "789"}
};

struct Bus buses[3] = {
    {101, "City A", "City B", 50, 50, 500.0f},
    {102, "City C", "City D", 40, 40, 400.0f},
    {103, "City E", "City F", 30, 30, 300.0f}
};

// login criteria

int login(char name[], char pass[]) {
    int i;
    for (i = 0; i < 3; i++) {
        if (strcmp(users[i].name, name) == 0 &&
            strcmp(users[i].pass, pass) == 0) {
            return i; // if credintial are correct returns login successful
        }
    }
    return -1; // login failed if any error occurs
}

// finding bus by number

int findBus(int num) {
    int i;
    for (i = 0; i < 3; i++) {
        if (buses[i].number == num)
            return i;
    }
    return -1; // not found
}

// ticket booking criteria

void bookTicket() {
    int num, seats, idx;

    printf("Enter Bus Number: ");
    scanf("%d", &num);
    idx = findBus(num);

    if (idx == -1) {
        printf("Bus not found!\n");
        return;
    }

    printf("Enter seats to book: ");
    scanf("%d", &seats);

    if (seats > buses[idx].freeSeats) {
        printf("Only %d seats available.\n", buses[idx].freeSeats);
    } else {
        buses[idx].freeSeats -= seats;
        printf("Booked %d seats on Bus %d!\n", seats, num);
    }
}

// cancelling ticket block

void cancelTicket() {
    int num, seats, idx;

    printf("Enter Bus Number: ");
    scanf("%d", &num);
    idx = findBus(num);

    if (idx == -1) {
        printf("Bus not found!\n");
        return;
    }

    printf("Enter seats to cancel: ");
    scanf("%d", &seats);

    int booked = buses[idx].totalSeats - buses[idx].freeSeats;
    if (seats > booked) {
        printf("Error: Only %d seats were booked.\n", booked);
    } else {
        buses[idx].freeSeats += seats;
        printf("Cancelled %d seats on Bus %d!\n", seats, num);
    }
}

// bus details

void checkBus() {
    int num, idx;

    printf("Enter Bus Number: ");
    scanf("%d", &num);
    idx = findBus(num);

    if (idx == -1) {
        printf("Bus not found!\n");
        return;
    }

    printf("\nBus Number  : %d\n",   buses[idx].number);
    printf("From        : %s\n",     buses[idx].from);
    printf("To          : %s\n",     buses[idx].to);
    printf("Total Seats : %d\n",     buses[idx].totalSeats);
    printf("Free Seats  : %d\n",     buses[idx].freeSeats);
    printf("Price       : %.2f\n",   buses[idx].price);
}

// main menue

int main() {
    char name[50], pass[50];
    int loggedIn = -1;
    int choice;

    while (1) {

        //show login menu if not logged in
        if (loggedIn == -1) {
            printf("\n=== Main Menu ===\n");
            printf("1. Login\n");
            printf("2. Exit\n");
            printf("Choice: ");
            scanf("%d", &choice);

            if (choice == 1) {
                printf("Username: ");
                scanf("%49s", name);
                printf("Password: ");
                scanf("%49s", pass);

                loggedIn = login(name, pass);

                if (loggedIn == -1)
                    printf("Wrong username or password!\n");
                else
                    printf("Welcome, %s!\n", name);

            } else if (choice == 2) {
                printf("Goodbye!\n");
                break;
            } else {
                printf("Invalid choice!\n");
            }

        // if logged in show user menue
        } else {
            printf("\n=== User Menu ===\n");
            printf("1. Book Ticket\n");
            printf("2. Cancel Ticket\n");
            printf("3. Check Bus\n");
            printf("4. Logout\n");
            printf("Choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: bookTicket();  break;
                case 2: cancelTicket(); break;
                case 3: checkBus();    break;
                case 4:
                    printf("Logged out.\n");
                    loggedIn = -1;
                    break;
                default:
                    printf("Invalid choice!\n");
            }
        }
    }

    return 0;
}
