#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct bus{
	int busnumber;
	char source[50];
	char desination[50];
	int totalseats;
	int availableseats;
	float fare;
};


 struct user{
 	char username[50];
 	char password[50];
 };
 
 
void displayMainMenu() 
{
	printf("\n===Main Menu===\n");
	printf("1. Login\n");
	printf("1. Exit\n");
	printf("Enter your choice:");
}


void displayUserMenu()
{
printf("\n=== User Menu ===\n");
printf("1. Book a Ticket\n");
printf("2. Cancle a Ticket\n");
printf("3. Check Bus Status\n");
printf("4. Logout\n");
printf("Enter your choice:");
}

loginuser:
int loginUser(struct Userusers[10],int numUsers,char username[],char password[])
{
	for(int i=0;i<numUsers;i++)
	{
		if(strcmp(users[i].username,username)==0&&strcmp(users[i].password,password)==0)
		{
		return i;	
		}
		return -1;
	}
}
// Function to book tickets
void book Ticket(sztruct bus busses[],int numBuses)
{
     printf("\nEnter bus number:");
     int bus number;
     scanf("%d",&bus number:");
     
     
     
     // Find the bus with the given bus number
     int bus index=-1
     for(int i=0;i<num buses;i++)
     {
             if (buses[i].bus number == bus number)
             {
                              bus index=i;
                              break;
                              }
                              }
if(bus Index==-1)
{
printf("Bus with Bus number %d not found.\n",bus number);
}
else
{
    printf("Enter number of seats:");
    int seats to book;
    scanf("%d",&seats to book);
    if(buses[bus index].avilable seats<seats to book)
    {
    printf("Sorry,only %d seats are avilable.\n",buses[bus index].avilable seats);
}
else
{
    buses[bus index].avilable seats = seats to book;
    printf("Booking successful!%d seat booked on bus number %d.\n",seats to book,bus number);
}
}
}
