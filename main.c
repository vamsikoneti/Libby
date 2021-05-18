#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "header.h"
int main()
{
    char choice;
    int number;
    int line = 0;
    usernode *p, *u;
    p = malloc(sizeof(struct user));
    //p=u;
    
    p = filetolist(p); //linked list from binary file users.dat

    printf("\t\tLIBRARY\t\t\n");
    do
    {
        printf("Enter your choice: \n1.Sign up\n2.Search for and issue/return a book\n3.Add a book\n4.Quit\n");
        scanf("%d", &choice);
        if (1 <= choice && choice <= 5)
        {
            switch (choice)
            {
            case 1:
                printf("\nNew User created, your ID is: "); //new user
                p=createuser(p);

                break;
            case 2:
                printallbooks();
                searchbook(p); //returns the line number so that it can be issued in issuebook function
                break;
            case 3:
                addbook();
                printf("\nBook added\n");
                break;
            default:
                if (choice != 4)
                    printf("Invalid choice, try again");
                break;
            }
        }
    } while (choice != 4);//loops until quit is chosen
    remove("users.dat");
}
