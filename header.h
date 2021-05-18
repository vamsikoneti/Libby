typedef struct user
{
    int id;
    char title[30];
    char author[30];
    struct user *down;
    int issued;
    
}usernode;
void printallbooks();
usernode *filetolist(usernode *head); //makes a linked list from a binary file
int randomid(struct user *u); //generates a random id for a new user
usernode *createuser(struct user *head); //creates a new user node 
usernode *searchbook(usernode *p); //searches for a book
void issuebook(int lno, int userid); //issues a book
void addbook(); //adds a new book to the book file
void returnbook(int lno, int userid); //returns a book back