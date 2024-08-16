// MULTIPLE STACK CONCEPT 
#include<stdio.h>

#define max 6 // Maximum size of the stack

int stack[max]; // Array to store elements of both stacks
int topA=-1; // Top index of Stack  A
int topB=max-1; // Top index of Stack B

// Function to push an element into Stack A
void pushA (int val)  
{  
    if (topA == topB )  // Check if Stack A is full
    {
        printf("Overflow! cannot insert element in stack A\n");
        return;
    }   
    else   
    {  
    topA = topA +1;   
    stack[topA] = val;   
    }   
}

// Function to pop an element from Stack A
int popA()
{
    if(topA==-1)
    {
        printf("Underflow\n");  // Check if Stack A is empty
        return 0;  
    }
    else  
    {  
        printf("%d deleted.\n",stack[topA]);
        return stack[--topA];
    }
}

// Function to push an element into Stack B
void pushB (int val)  
{  
    if (topB == topA )  // Check if Stack B is full  
    {
        printf("Overflow! cannot insert element in stack B\n");
        return;
    }   
    else   
    {  
    topB = topB -1;   
    stack[topB] = val;   
    }   
}

// Function to pop an element from Stack B
int popB()
{
    if(topB==max)
    {
        printf("Underflow\n");  // Check if Stack B is empty
        return 0;  
    }
    else  
    {
        printf("Deleting top element.\n");
        printf("%d deleted.\n",stack[topB]);  
        return stack[++topB];   
    }
}

int main()
{
    int ch;
    int val,x,y;
    //Menu
    printf("*MENU*\n");
    printf("1.Push in stack A.\n");
    printf("2.Push in stack B.\n");
    printf("3.Pop from stack A.\n");
    printf("4.Pop from stack B.\n");
    printf("5.Display stack A.\n");
    printf("6.Display stack B.\n");
    printf("7.Exit menu.\n");
    //Menu loop
    do
    {
        printf("Enter your choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            printf("Enter element to be inserted in stack A.\n");
            scanf("%d",&val);
            pushA(val);
            break;

            case 2:
            printf("Enter element to be inserted in stack B.\n");
            scanf("%d",&val);
            pushB(val);
            break;

            case 3:
            popA();
            break;
            
            case 4:
            popB(); 
            break;

            case 5:                 // for displaying stack a
            printf("stack A\n");
            for(int i =topA; i>-1;i--)
            {
                printf("%d\t",stack[i]);
            }
            printf("\n");
            break;

            case 6:               // for displaying stack b
            printf("stack B\n");
            for(int i =topB; i<max-1;i++)
            {
                printf("%d\t",stack[i]);
            }
            printf("\n");
            break;

            case 7:
            printf("Exiting menu..\n");
            break;

            default:
            printf("Invalid choice.\n");
            break;
        }
    } while (ch != 7);   
}
