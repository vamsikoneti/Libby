#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <errno.h>
#define max 99999
#define min 10000

void printallbooks()
{
    FILE *myfile = fopen ( "f.txt", "r" );
    if (!myfile)
	{
	    printf(" File not found or unable to open the input file!!\n");
        return NULL;
    }
    char line[128];
    char *value0;
    char *value1;
    printf("\n\t\tBOOKS\n");
    printf("[Title, Author]\n");
    while(fgets(line, sizeof(line), myfile)){
        //load title
        value0 = strtok(line, ",");
        //load author
        value1 = strtok(NULL, ",");
        printf("%s, %s\n", value0, value1);
    }
    fclose(myfile);
}

usernode *filetolist(usernode *head)
{
    FILE *fp = fopen("users.dat", "r+");
    usernode *curr;
    head = curr = NULL;
    usernode node; //only structures can be read and written into a .dat
    while (fread(&node, sizeof(struct user), 1, fp))
    {
        if (head == NULL)
        {
            head = (struct user *)malloc(sizeof(usernode));
            head->id = node.id;
            strcpy(head->title, node.title);   //copying read title to the head node
            strcpy(head->author, node.author); //copying read author to the head node
            curr = head;
        }
        else
        {
            curr->id = node.id;
            strcpy(curr->title, node.title);
            strcpy(curr->author, node.author);
        }
        curr->down = (struct user *)malloc(sizeof(usernode)); //allocate memory for curr down because it might not exist
        curr = curr->down;
        //printf("1");
    }
    curr = NULL;
    fclose(fp);
    return head;
}
int randomid(usernode *u)
{
    usernode *temp = u;
    int randint = 1;
    while (randint >= max || randint <= min)
        randint = rand(); //keeps giving random numbers until it is a 5 digit number (id)
    /*for(;temp->down;temp=temp->down)
    {   
        
        if(randint == temp->id)
            return randomid(u); //if the randint has been used as an id before, call the function to make a new randint
    } */
    return randint;
}
usernode *createuser(usernode *head)
{
    usernode *User = (usernode *)malloc(sizeof(usernode));
    usernode *newuser = head;
    User->id = randomid(head); //creates new id
    //printf("%d\n",User->id);
    User->down = NULL;
    strcpy(User->title, "NA"); //starting off with making title and author "NA"
    strcpy(User->author, "NA");
    //printf("%s ", User->author);
    if (head == NULL)
    {
        head = User;
        printf("%d\n", head->id);
    }
    else
    {
        while (newuser->down != NULL)
            newuser = newuser->down;
        newuser->down = User;
        printf("%d\n", User->id);
    }

    return head;
}

void addbook()
{
    FILE *f = fopen("f.txt", "a");

    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    char title[30];
    char author[30];
    char zeros[5] = "00000"; //writes 00000 in place of id
    int issue = 0;           //writes 0 in place of issued
    printf("\nEnter the title of the book: ");
    getchar();
    gets(title);
    printf("\nEnter the author of the book: ");
    gets(author);
    fprintf(f, "%s,", title);
    fprintf(f, "%s,", author);
    fprintf(f, "%d,", issue);
    fprintf(f, "%s\n", zeros);
    fclose(f);
}
void printusers(struct user *head)
{
    printf("file opened for writing");
    FILE *fp;
    if ((fp = fopen("users.dat", "wb")) == NULL)
    {
        printf("error opening file");
        exit(1);
    }
    while (head != NULL)
    {
        fwrite(head, sizeof(usernode), 1, fp);
        //printf("%d %s %s", head->id, head->title, head->title);
        head = head->down;
    }
    fclose(fp);
}