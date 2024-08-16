// TOWER OF HANOI 
// TOI is an application of stack
// We will take 3 tower and decreasing number of n disk in tower 1 
// main aim is to transfer all the disk into tower 3 using tower 2 i the same order as in tower 1
// condition... 1 only once disk can be removed at a time 2 order of the disk arranged should be decreasing.. i.e base with bigger follower by smaller at the top
// tower of hanoi using recursive approach  
#include<stdio.h>  
void towers(int, char, char, char);  
 int main()  
 {  
        int n;  
        printf ("Enter the number of disks : \n");  
        scanf ("%d", &n);  
        printf ("The sequence of moves involved in the Tower of Hanoi are :\n");  
        towers (n, 'A','B','C');  
        return 0;  
   
}  
     void towers( int n, char BEG, char MID, char END){
        if(n<=0)
        {
            printf("ILLEGAL ENTRY");
        }
        else if (n == 1)
        {
           printf ("\n Move disk 1 from tower %c to tower %c", BEG, END);  
           return;  
        }  
    towers (n - 1, BEG, MID, END);  
    printf ("\n Move disk %d from tower %c to tower %c", n, BEG, END);  
    towers (n - 1, MID, END, BEG);  
 }
