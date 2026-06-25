#include <stdio.h>
#include <string.h>

// --- BUS DATA ---
int busNumber[10]  = {101, 102, 103};
char from[10][50]  = {"City A", "City B", "City C"};
char to[10][50]    = {"City D", "City E", "City F"};
int totalSeats[10] = {50, 40, 30};
int freeSeats[10]  = {50, 40, 30};
float price[10]    = {500.0, 400.0, 300.0};
int busCount       = 3;

FILE *logFile;  // global file pointer for result file

// Write to both screen and file
void log(char *msg) {
    printf("%s", msg);
    fprintf(logFile, "%s", msg);
}

// --- FIND BUS ---
int findBus(int num) {
    int i;
    for (i = 0; i < busCount; i++) {
        if (busNumber[i] == num)
            return i;
    }
    return -1;
}

// --- BOOK TICKET ---
void bookTicket() {
    int num, seats, i;
    char buf[200];

    printf("Enter Bus Number: ");
    scanf("%d", &num);
    i = findBus(num);

    if (i == -1) { log("Bus not found!\n"); return; }

    printf("Free Seats: %d\n", freeSeats[i]);
    printf("Enter seats to book: ");
    scanf("%d", &seats);

    if (seats > freeSeats[i]) {
        log("Not enough seats!\n");
    } else {
        freeSeats[i] -= seats;
        sprintf(buf, "Booked %d seat(s) on Bus %d. Cost: %.2f\n", seats, num, seats * price[i]);
        log(buf);
    }
}

// --- CANCEL TICKET ---
void cancelTicket() {
    int num, seats, i;
    char buf[200];

    printf("Enter Bus Number: ");
    scanf("%d", &num);
    i = findBus(num);

    if (i == -1) { log("Bus not found!\n"); return; }

    printf("Enter seats to cancel: ");
    scanf("%d", &seats);

    int booked = totalSeats[i] - freeSeats[i];
    if (seats > booked) {
        sprintf(buf, "Only %d seat(s) were booked!\n", booked);
        log(buf);
    } else {
        freeSeats[i] += seats;
        sprintf(buf, "Cancelled %d seat(s) on Bus %d.\n", seats, num);
        log(buf);
    }
}

// --- CHECK BUS ---
void checkBus() {
    int num, i;
    char buf[200];

    printf("Enter Bus Number: ");
    scanf("%d", &num);
    i = findBus(num);

    if (i == -1) { log("Bus not found!\n"); return; }

    sprintf(buf, "\nBus No : %d\nFrom   : %s\nTo     : %s\nSeats  : %d / %d free\nPrice  : %.2f\n",
            busNumber[i], from[i], to[i], freeSeats[i], totalSeats[i], price[i]);
    log(buf);
}

// --- ADD BUS (Admin) ---
void addBus() {
    char buf[200];

    printf("Enter Bus Number: ");
    scanf("%d", &busNumber[busCount]);
    printf("Enter From: ");
    scanf("%s", from[busCount]);
    printf("Enter To: ");
    scanf("%s", to[busCount]);
    printf("Enter Total Seats: ");
    scanf("%d", &totalSeats[busCount]);
    freeSeats[busCount] = totalSeats[busCount];
    printf("Enter Price: ");
    scanf("%f", &price[busCount]);

    sprintf(buf, "Bus %d added: %s -> %s, Seats: %d, Price: %.2f\n",
            busNumber[busCount], from[busCount], to[busCount], totalSeats[busCount], price[busCount]);
    busCount++;
    log(buf);
}

// --- EDIT BUS (Admin) ---
void editBus() {
    int num, i, choice;
    char buf[200];

    printf("Enter Bus Number to edit: ");
    scanf("%d", &num);
    i = findBus(num);

    if (i == -1) { log("Bus not found!\n"); return; }

    printf("1. From\n2. To\n3. Price\n");
    printf("What to edit? ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("New From: ");
        scanf("%s", from[i]);
        sprintf(buf, "Bus %d From updated to: %s\n", busNumber[i], from[i]);
        log(buf);
    } else if (choice == 2) {
        printf("New To: ");
        scanf("%s", to[i]);
        sprintf(buf, "Bus %d To updated to: %s\n", busNumber[i], to[i]);
        log(buf);
    } else if (choice == 3) {
        printf("New Price: ");
        scanf("%f", &price[i]);
        sprintf(buf, "Bus %d Price updated to: %.2f\n", busNumber[i], price[i]);
        log(buf);
    } else {
        log("Invalid choice!\n");
    }
}

// --- MAIN ---
int main() {
    char name[50], pass[50];
    int choice;
    int loggedIn = 0;

    // Open result file
    logFile = fopen("result.txt", "w");
    if (logFile == NULL) {
        printf("Error: Could not create result.txt\n");
        return 1;
    }

    fprintf(logFile, "=== Bus Reservation System - Session Log ===\n\n");

    while (1) {

        // LOGIN SCREEN
        if (loggedIn == 0) {
            printf("\n=== Main Menu ===\n");
            printf("1. Login\n2. Exit\n");
            printf("Choice: ");
            scanf("%d", &choice);

            if (choice == 2) {
                log("User exited the system.\n");
                printf("Goodbye!\n");
                break;
            }

            printf("Username: "); scanf("%s", name);
            printf("Password: "); scanf("%s", pass);

            if (strcmp(name, "admin") == 0 && strcmp(pass, "123") == 0) {
                loggedIn = 1;
                log("Admin logged in.\n");
                printf("Welcome Admin!\n");
            } else if (strcmp(name, "user") == 0 && strcmp(pass, "567") == 0) {
                loggedIn = 2;
                log("User logged in.\n");
                printf("Welcome User!\n");
            } else {
                log("Failed login attempt.\n");
                printf("Wrong username or password!\n");
            }

        // ADMIN MENU
        } else if (loggedIn == 1) {
            printf("\n=== Admin Menu ===\n");
            printf("1. Add Bus\n2. Edit Bus\n3. Logout\n");
            printf("Choice: ");
            scanf("%d", &choice);

            if      (choice == 1) addBus();
            else if (choice == 2) editBus();
            else if (choice == 3) { log("Admin logged out.\n"); loggedIn = 0; }
            else    log("Invalid choice!\n");

        // USER MENU
        } else if (loggedIn == 2) {
            printf("\n=== User Menu ===\n");
            printf("1. Book Ticket\n2. Cancel Ticket\n3. Check Bus\n4. Logout\n");
            printf("Choice: ");
            scanf("%d", &choice);

            if      (choice == 1) bookTicket();
            else if (choice == 2) cancelTicket();
            else if (choice == 3) checkBus();
            else if (choice == 4) { log("User logged out.\n"); loggedIn = 0; }
            else    log("Invalid choice!\n");
        }
    }

    fclose(logFile);
    printf("Session saved to result.txt\n");
    return 0;
}
