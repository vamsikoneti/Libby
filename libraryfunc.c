#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include <errno.h>
#define max 99999
#define min 10000

void issuebook(int lno, int userid)
{
    int ctr = 0;
    char userid0[5];
    sprintf(userid0, "%d", userid); //user id in string
    FILE *fptr1, *fptr2;
    char str[256], temp[] = "temp.txt"; //temp .txt to write everything from f.txt to this with modifications
    fptr1 = fopen("f.txt", "r");
    if (!fptr1)
    {
        printf(" File not found or unable to open the input file!!\n");
        return;
    }
    fptr2 = fopen(temp, "w");
    if (!fptr2)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fptr1);
        return;
    }
    while (!feof(fptr1))
    {
        strcpy(str, "\0");
        fgets(str, 256, fptr1);
        if (!feof(fptr1))
        {
            ctr++;
            if (ctr != lno)
            {
                fprintf(fptr2, "%s", str);
            }
            else
            {
                int i = 0;
                int j = 0;
                for (i = 0, j = 0; str[i] != '\0'; i++) //loop to find where the 2nd comma is
                {
                    if (str[i] == ',')
                    {
                        j++;
                    }
                    if (j == 2)
                    {
                        str[i + 1] = '1'; //makes issued = 1
                        break;
                    }
                }
                i += 3;
                for (j = 0; j < 5; i++, j++)
                    str[i] = userid0[j]; //writes the user id into f.txt
                fprintf(fptr2, "%s", str);
            }
        }
    }
    fclose(fptr1);
    fclose(fptr2);
}
void returnbook(int lno, int userid)
{
    int ctr = 0;
    char userid0[5];
    sprintf(userid0, "%d", userid); //user id in string
    FILE *fptr1, *fptr2;
    char str[256], temp[] = "temp.txt"; //temp .txt to write everything from f.txt to this with modifications
    fptr1 = fopen("f.txt", "r");
    if (!fptr1)
    {
        printf(" File not found or unable to open the input file!!\n");
        return;
    }
    fptr2 = fopen(temp, "w");
    if (!fptr2)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fptr1);
        return;
    }
    while (!feof(fptr1))
    {
        strcpy(str, "\0");
        fgets(str, 256, fptr1);
        if (!feof(fptr1))
        {
            ctr++;
            if (ctr != lno)
            {
                fprintf(fptr2, "%s", str);
            }
            else
            {
                int i = 0;
                int j = 0;
                for (i = 0, j = 0; str[i] != '\0'; i++) //loop to find where the 2nd comma is
                {
                    if (str[i] == ',')
                    {
                        j++;
                    }
                    if (j == 2)
                    {
                        str[i + 1] = '0'; //makes issued = 1
                        break;
                    }
                }
                i += 3;
                for (j = 0; j < 5; i++, j++)
                    str[i] = '0'; //writes the user id into f.txt
                fprintf(fptr2, "%s", str);
            }
        }
    }
    fclose(fptr1);
    fclose(fptr2);
}

usernode *searchbook(usernode *p)
{
    FILE *myfile = fopen("f.txt", "r");
    if (!myfile)
    {
        printf(" File not found or unable to open the input file!!\n");
        return NULL;
    }
    int l = 0;
    char line[128];
    char *value0, *value1, *value2, *value3;
    char title[30], author[30];
    getchar(); //takes the stray \n so that scanf works properly instead of getting skipped
    printf("\nEnter the title: ");
    scanf("%[^\n]", title); //in case the title or author have multiple words
    printf("\nEnter the author: ");
    getchar();
    scanf("%[^\n]", author);
    getchar();
    while (fgets(line, sizeof(line), myfile))
    {
        value0 = strtok(line, ",");        //title
        value1 = strtok(NULL, ",");        //author
        value2 = strtok(NULL, ",");        //issued
        value3 = strtok(NULL, ",");        //id
        value3[strlen(value3) - 1] = '\0'; //removing the \n and making it \0
        l++;                               //increment to get the line number

        if (strcmp(title, value0) == 0 && strcmp(author, value1) == 0 && atoi(value2) == 0 && atoi(value3) == 0)
        {
            printf("\nfound\n");
            printf("Do you want to issue the book?[y/n]");
            if (getchar() == 'y')
            {
                int userid; //user id
                char userid0[5];
                printf("\nEnter your ID: ");
                scanf("%d", &userid);
                issuebook(l, userid);
                int flag = 0;
                for (; p != NULL; p = p->down)
                {
                    if (userid == p->id)
                    {
                        flag=1;
                        strcpy(p->title, title);
                        strcpy(p->author, author);
                    }
                }
                if(flag==1)
                    printf("\nBook Issued\n");
                else
                {
                    printf("\nInvalid User ID\n");
                    fclose(myfile);
                    return NULL;
                }
                
            }
            fclose(myfile);
            remove("f.txt");
            rename("temp.txt", "f.txt");
            return p;
        }
        else if (strcmp(title, value0) == 0 && strcmp(author, value1) == 0 && atoi(value2) == 1) //if the book has already been issued
        {
            printf("\nBook has already been issued\n");
            printf("Do you want to return the book?[y/n]");
            if (getchar() == 'y')
            {
                int userid; //user id
                char userid0[5];
                printf("\nEnter your ID: ");
                scanf("%d", &userid);
                returnbook(l, userid);
                int flag=0;
                for (; p != NULL; p = p->down)
                {
                    if (userid == p->id)
                    {
                        flag=1;
                        strcpy(p->title, "NA");
                        strcpy(p->author, "NA");
                    }
                }
                if(flag==1)
                    printf("\nBook Returned\n");
                else
                {
                    printf("\nInvalid User ID\n");
                    fclose(myfile);
                    return NULL;
                }
                
            }
            else
            {
                fclose(myfile);
                return NULL;
            }
            
            fclose(myfile);
            remove("f.txt");
            rename("temp.txt", "f.txt");
            return p;
        }
    }
    printf("\nSorry the requested book is not found.\n");
    fclose(myfile);

    return NULL;
}

