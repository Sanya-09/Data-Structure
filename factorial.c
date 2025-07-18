#include<stdio.h>
int fact(int);
int main()
{
    int num;
    printf("Enter a number");
    scanf("%d", &num);
    int factorial = fact(num);
    printf("Factorial of %d = %ld", num , factorial);
    return 0;
}
int fact(int num)
{
    int i ;
    int factorial= 1;
    for (i=1 ; i<=num ; i++)
    factorial = factorial * i ;
    return (factorial);

}
