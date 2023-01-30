#include <stdio.h>

int fatorial(int n)
{
    int f = 1;

    while( n > 0 )
        f *= n--;

    return f;
}

int main(){
    printf("%d\n",fatorial(5));
    return 0;
}