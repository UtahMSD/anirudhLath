#include <stdio.h>

long fib( long num )
{
    if( num == 1 ) {
        return 0;
    }
    else if( num == 2 ) {
        return 1;
    }
    return fib( num - 1 ) + fib( num - 2 );
}

int main() {
    printf("%d", fib(6));
    return 0;
}
