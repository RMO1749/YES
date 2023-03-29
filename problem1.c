#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_int(const void *elem1, const void *elem2)
{
    int partA = *(int *)elem1;
    int partB = *(int *)elem2;

    // check whether the numbers are even or odd.
    if (partA % 2 == 0 && partB % 2 == 1)
    {
        return 1; // b comes before a
    }
    else if (partA % 2 == 1 && partB % 2 == 0)
    {
        return -1; // a comes before b 
    }
    else if (partA < partB)
    {
        return -1;       // a comes before b
    }
    else if(partA > partB)
    {
        return 1;   //b comes before a
    }
    else
    {
        return 0;
    }
}

int main()
{

    int i, integer;
    int *ptr; // this pointer will hold the base address of the block created

    printf("Enter an integer[size of an array]: ");
    scanf("%d", &integer);

    ptr = (int *)malloc(integer * sizeof(int));

    // check if the memory has been successfully allocated by malloc or not
    if (ptr == NULL)
    {
        printf("Memory not allocated.\n");
        exit(0);
    }
    else
    {

        for (i = 0; i < integer; i++)
        {
            printf("Enter values in the array: ");
            scanf("%d, ", &ptr[i]);
        }

        // Memory has successfully allocated using malloc.
        printf("Before sorting the list: ");
        for (i = 0; i < integer; i++)
        {
            printf(" %d, ", ptr[i]);
        }
    }

    qsort(ptr, integer, sizeof(int), compare_int);
    printf("\nAfter sorting the list: ");
    for (i = 0; i < integer; i++)
    {
        printf(" %d, ", ptr[i]);
    }

    free(ptr);

    return 0;
}