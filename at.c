#include <stdio.h>

int  ft_atoi(char *c)
{
    int sin = 1;
    int ruslt = 0;
    int i = 0;

    while ((c[i] <= 13 && c[i] >= 9 ) || c[i] == ' ')
        i++;
    while (c[i] == '-' || c[i] == '+')
    {
        if (c[i] == '-')
            sin *= -1;
        i++;
    }
    while (c[i] >= '0' && c[i] <= '9')
    {
        ruslt = (ruslt * 10 ) + (c[i] - '0');
        i++;
    }
    return (ruslt * sin);
}

int main()
{
    char dx[] = " ---+--+1234ab567";
    printf("%d", ft_atoi(dx));
}