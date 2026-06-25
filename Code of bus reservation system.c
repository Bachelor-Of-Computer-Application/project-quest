<<<<<<< HEAD
#include <stdio.h>
#include <string.h>
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
struct User users[3] = {
    {"alice", "hello123"},
    {"bob",   "mypass"},
    {"carol", "abc456"}
};

struct Bus buses[3] = {
    {101, "City A", "City B", 50, 50, 500.0f},
    {102, "City C", "City D", 40, 40, 400.0f},
    {103, "City E", "City F", 30, 30, 300.0f}
};

//login by user 

int login(char name[], char pass[]) {
    int i;
    for (i = 0; i < 3; i++) {
        if (strcmp(users[i].name, name) == 0 &&
            strcmp(users[i].pass, pass) == 0) {
            return i; // login success
        }
    }
    return -1; // login failed
}

//FIND BUS BY NUMBER

int findBus(int num) {
    int i;
    for (i = 0; i < 3; i++) {
        if (buses[i].number == num)
            return i;
    }
    return -1; 
}

//BOOKING TICKET 

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

//CANCELlING TICKET 

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

// CHECK BUS STATUS

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

// MAIN BLOCK

int main() {
    char name[50], pass[50];
    int loggedIn = -1;
    int choice;

    while (1) {

        // Not logged in ? show login menu
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

        // Logged in ? show user menu
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
=======
// C Program to implement Bus Reservation System
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to store bus information
struct Bus{
    int busNumber;
    char source[50];
    char destination[50];
    int totalSeats;
    int availableSeats;
    float fare;
};

// Define a structure to store user login information
struct User{
    char username[50];
    char password[50];
};

// Function to display the main menu
void displayMainMenu(){
    printf("\n=== Main Menu ===\n");
    printf("1. Login\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
}

// Function to display the user menu
void displayUserMenu(){
    printf("\n=== User Menu ===\n");
    printf("1. Book a Ticket\n");
    printf("2. Cancel a Ticket\n");
    printf("3. Check Bus Status\n");
    printf("4. Logout\n");
    printf("Enter your choice: ");
}

// Function to perform user login
int loginUser(struct User users[], int numUsers, char username[], char password[])

{
    for (int i = 0; i < numUsers; i++){
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0){
            return i; // Return the index of the logged-in user
        }
    }
    return -1; // Return -1 if login fails
}

// Function to book tickets
void bookTicket(struct Bus buses[], int numBuses){
    printf("\nEnter Bus Number: ");
    int busNumber;
    scanf("%d", &busNumber);

    // Find the bus with the given busNumber
    int busIndex = -1;
    for (int i = 0; i < numBuses; i++){
        if (buses[i].busNumber == busNumber){
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1){
        printf("Bus with Bus Number %d not found.\n", busNumber);
    }
    else{
        printf("Enter Number of Seats: ");
        int seatsToBook;
        scanf("%d", &seatsToBook);

        if (buses[busIndex].availableSeats < seatsToBook){
            printf("Sorry, only %d seats are available.\n", buses[busIndex].availableSeats);
        }
        else{
            buses[busIndex].availableSeats -= seatsToBook;
            printf("Booking successful! %d seats booked on Bus Number %d.\n", seatsToBook, busNumber);
        }
    }
}

// Function to cancel tickets
void cancelTicket(struct Bus buses[], int numBuses){
    printf("\nEnter Bus Number: ");
    int busNumber;
    scanf("%d", &busNumber);

    // Find the bus with the given busNumber
    int busIndex = -1;
    for (int i = 0; i < numBuses; i++){
        if (buses[i].busNumber == busNumber){
            busIndex = i;
            break;
        }
    }

    if (busIndex == -1){
        printf("Bus with Bus Number %d not found.\n", busNumber);
    }
    else{
        printf("Enter Number of Seats to Cancel: ");
        int seatsToCancel;
        scanf("%d", &seatsToCancel);

        if (seatsToCancel > (buses[busIndex].totalSeats - buses[busIndex].availableSeats)){
            printf("Error: You can't cancel more seats than were booked.\n");
        }
        else{
            buses[busIndex].availableSeats += seatsToCancel;
            printf("Cancellation successful! %d seats canceled on Bus Number %d.\n", seatsToCancel,
                   busNumber);
        }
    }
}

// Function to check bus status
void checkBusStatus(struct Bus buses[], int numBuses){
    printf("\nEnter Bus Number: ");
    int busNumber;
    scanf("%d", &busNumber);

    // Find the bus with the given busNumber
    int busIndex = -1;
    for (int i = 0; i < numBuses; i++){
        if (buses[i].busNumber == busNumber){
            busIndex = i;
            break;
        }
    }

    if (busIndex != -1){
        printf("\nBus Number: %d\n", buses[busIndex].busNumber);
        printf("Source: %s\n", buses[busIndex].source);
        printf("Destination: %s\n", buses[busIndex].destination);
        printf("Total Seats: %d\n", buses[busIndex].totalSeats);
        printf("Available Seats: %d\n", buses[busIndex].availableSeats);
        printf("Fare: %.2f\n", buses[busIndex].fare);
    }
    else{
        printf("Bus with Bus Number %d not found.\n", busNumber);
    }
}

int main(){
    // Initialize user data
    struct User users[5] = {
        {"user1", "pass1"}, {"user2", "pass2"}, {"user3", "pass3"}, {"user4", "pass4"}, {"user5", "pass5"},
    };
    int numUsers = 5;

    // Initialize bus data
    struct Bus buses[3] = {
        {101, "City A", "City B", 50, 50, 500.0},
        {102, "City C", "City D", 40, 40, 400.0},
        {103, "City E", "City F", 30, 30, 300.0},
    };
    int numBuses = 3;

    int loggedInUserId = -1; // Index of the logged-in user

    while (1){
        if (loggedInUserId == -1){
            displayMainMenu();
            int choice;
            scanf("%d", &choice);

            if (choice == 1){
                char username[50];
                char password[50];

                printf("Enter Username: ");
                scanf("%s", username);
                printf("Enter Password: ");
                scanf("%s", password);

                loggedInUserId = loginUser(users, numUsers, username, password);
                if (loggedInUserId == -1){
                    printf("Login failed. Please check your username and password.\n");
                }
                else{
                    printf("Login successful. Welcome, %s!\n", username);
                }
            }
            else if (choice == 2){
                printf("Exiting the program.\n");
                break;
            }
            else{
                printf("Invalid choice. Please try again.\n");
            }
        }
        else{
            displayUserMenu();
            int userChoice;
            scanf("%d", &userChoice);

            switch (userChoice){
            case 1:
                bookTicket(buses, numBuses);
                break;
            case 2:
                cancelTicket(buses, numBuses);
                break;
            case 3:
                checkBusStatus(buses, numBuses);
                break;
            case 4:
                printf("Logging out.\n");
                loggedInUserId = -1;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
>>>>>>> f1f40cdfe88b44edfe2284a9c382e5957a92c4aa
            }
        }
    }

    return 0;
}
