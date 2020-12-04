#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INPUT_FILE "sample_input"

void matrixPrint(int *x, int r, int c)
{
    for (int i = 0; i < r; i += 1)
    {
        for (int j = 0; j < c; j += 1)
            printf("%d ", *(x + i * c + j));
        printf("\n");
    }
}

int *copy(int *x, int r, int c)
{
    int *temp = (int *)calloc(r * c, sizeof(int));
    for (int i = 0; i < r; i += 1)
        for (int j = 0; j < c; j += 1)
            *(temp + i * c + j) = *(x + i * c + j);
    return temp;
}

int *getSafeState(int *rem, int *alloc, int *avail, int n, int m)
{
    int *safeSeq = (int *)calloc(n, sizeof(int));

    // Making Copies to use
    int *r = copy(rem, n, m);
    int *a = copy(alloc, n, m);
    int *av = copy(avail, 1, m);

    int safeProc, i, j, k, safe;
    for (k = 0; k < n; k += 1)
    {
        safeProc = -1;
        for (i = 0; i < n; i += 1)
        {
            safe = 1;
            for (j = 0; j < m; j += 1)
            {
                if (*(r + i * m + j) > av[j])
                {
                    safe = 0;
                    break;
                }
            }
            if (safe == 1)
            {
                safeProc = i;
                break;
            }
        }
        if (safeProc != -1)
        {
            safeSeq[k] = safeProc + 1;
            for (j = 0; j < m; j += 1)
            {
                av[j] += *(a + safeProc * m + j) + *(r + safeProc * m + j);
                *(r + safeProc * m + j) = INT_MAX;
                *(a + safeProc * m + j) = -1;
            }
        }
        else
        {
            for (int p = 0; p < n; p += 1)
                safeSeq[i] = -1;
        }
    }
    free(a);
    free(r);
    free(av);
    return safeSeq;
}

int checkSafe(int *seq, int *rem, int *alloc, int *avail, int n, int m)
{
    int *r = copy(rem, n, m);
    int *a = copy(alloc, n, m);
    int *av = copy(avail, 1, m);

    int safe, i, j, k;

    for (i = 0; i < n; i += 1)
    {
        k = seq[i];
        for (j = 0; j < m; j += 1)
        {
            if (*(r + k * m + j) > av[j])
            {
                free(a);
                free(r);
                free(av);
                return 0;
            }
        }
        for (j = 0; j < m; j += 1)
        {
            av[j] += *(a + k * m + j) + *(r + k * m + j);
            *(r + k * m + j) = INT_MAX;
            *(a + k * m + j) = -1;
        }
    }

    free(a);
    free(r);
    free(av);
    return 1;
}

int main()
{
    FILE *f;

    int n, m, i, j, flag;

    f = fopen(INPUT_FILE, "r");

    printf("number of processes n read from input file : ");
    fscanf(f, "%d", &n);
    printf("%d \n", n);
    printf("number of resources m read from input file : ");
    fscanf(f, "%d", &m);
    printf("%d \n", m);

    printf("\n");


    int *allocTable = (int *)calloc(n * m, sizeof(int));
    int *maxTable = (int *)calloc(n * m, sizeof(int));
    int *needTable = (int *)calloc(n * m, sizeof(int));
    int *avail = (int *)calloc(m, sizeof(int));
    int *inputSequence = (int *)calloc(n, sizeof(int));
    int *request = (int *)calloc(m, sizeof(int));
    int *res;

    // read Available Resources
    printf("Available Resources read from input file ...\n");
    for (i = 0; i < m; i += 1)
        fscanf(f, "%d", avail + i);

    // read Alloc table
    printf("Alloc Table read from input file ...\n");
    for (i = 0; i < n; i += 1)
        for (j = 0; j < m; j += 1)
            fscanf(f, "%d", allocTable + i * m + j);

    // read Max Table
    printf("Max Table read from input file ...\n");
    for (i = 0; i < n; i += 1)
        for (j = 0; j < m; j += 1)
            fscanf(f, "%d", maxTable + i * m + j);

    // needTable
    for (i = 0; i < n; i += 1)
        for (j = 0; j < m; j += 1)
            *(needTable + i * m + j) = *(maxTable + i * m + j) - *(allocTable + i * m + j);

    // Calculate Remaining Resources
    for (i = 0; i < n; i += 1)
        for (j = 0; j < m; j += 1)
            avail[j] -= *(allocTable + i * m + j);

    printf("\n");
    printf("Available Resources \n");
    matrixPrint(avail, 1, m);
    printf("\n");
    printf("Max Table \n");
    matrixPrint(maxTable, n, m);
    printf("\n");
    printf("Alloc Table \n");
    matrixPrint(allocTable, n, m);
    printf("\n");
    printf("Need Table \n");
    matrixPrint(needTable, n, m);
    printf("\n");

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

    printf("\n\n");

    char ch = 'y';
    while (ch != 't' || ch == 'T')
    {
        fscanf(f, "%c", &ch);
        switch (ch)
        {
        case 'a':
            res = getSafeState(needTable, allocTable, avail, n, m);
            printf("Following is a Safe Sequence \n");
            for (i = 0; i < n; i += 1)
                printf("%d ", res[i]);
            printf("\n");
            printf("\n");
            break;

        case 'b':
            printf("input sequence read from input file \n");
            printf("Input Sequence : ");
            for (i = 0; i < n; i += 1)
            {
                fscanf(f, "%d", inputSequence + i);
                printf("%d ", *(inputSequence + i));
                inputSequence[i] -= 1;
            }
            printf("\n");
            if (checkSafe(inputSequence, needTable, allocTable, avail, n, m))
                printf("State is SAFE\n");
            else
                printf("State is NOT SAFE\n");
            printf("\n");
            break;

        case 'c':
            printf("input request read from input file \n \n");
            printf("Request  ");
            for (i = 0; i < m; i += 1)
            {
                fscanf(f, "%d", request + i);
                printf("%d ", *(request + i));
            }
            printf("\n");
            flag = 1;
            for (j = 0; j < m; j += 1)
            {
                if (avail[j] < request[j])
                {
                    flag = 0;
                    break;
                }
            }
            if (flag == 1)
                printf("REQUEST CAN BE GRANTED\n");
            else
                printf("REQUEST CANNOT BE GRANTED\n");
            printf("\n");
            break;

        default:
            break;
        }
    }
}