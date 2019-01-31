#include <stdlib.h>
#include <stdio.h>

int main()
{
    int order;
    double coefficients[11];
    do
    {
        printf("Insert the polynomial order: ");
        scanf("%d", &order);
    } while (order < 0 && order > 10);
    for (int i = order; i >= 0; i--)
    {
        switch (i)
        {
        case 0:
            printf("%c = ", 'a' + order);
            break;
        case 1:
            printf("%cx = ", 'a' - i + order);
            break;
        default:
            printf("%cx^%d = ", 'a' - i + order, i);
            break;
        }
        scanf("%lf", &coefficients[i]);
    }
    FILE *f = fopen("func.dat", "w");
    fprintf(f, "%d", order);
    for (int i = 0; i <= order; i++)
    {
        fprintf(f, "\n%lf", coefficients[i]);
    }
    fprintf(f, "\n");
    fclose(f);
}