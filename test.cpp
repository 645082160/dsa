#include <stdio.h>
#include <stdlib.h>

void overflow()
{
        long i;
        printf("%p\n", &i);
        overflow();
        return;
}

int main()
{
        overflow();
        return 0;
}