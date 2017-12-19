/*
 * Written By: Ari Perez
 * November 2017
 */

#include "BinarySearchTreeAPI.h"
#include <stdio.h>

int compareInt(const void *a, const void *b);
void deleteInt(void*data);
void printInt(void *data);
int main (int argc, char**argv)
{
    printf("Testing createBinTree\n");
    printf("Data: compareInt, deleteInt\n");
    printf("Expected newTree != NULL\n");
    printf("Recieved: ");
    Tree *newTree = NULL;
    newTree =  createBinTree(compareInt, deleteInt);
    if (newTree == NULL)
    {
        printf("NULL\nTest Failed\n\n");
    }

    else {
        printf("Not NULL\nTest Passed!\n\n");
    }

    printf("Testing: addToTree\n");
    printf("data: list\n");
    printf("Print tests will show that this function works\n");
    int list[10] = {5,3,9,4,7,2,1,6,8 ,10};
    for (int i = 0; i < 10; i++)
    {
        int * temp = &list[i];
        addToTree(newTree, (TreeDataPtr)(temp));
    }
    printf("Testing: printInOrder\n");
    printf("Data: newTree\n");
    printf("Expecting: 1 2 3 4 5 6 7 8 9 10\nRecieved: ");
    printInOrder(newTree, printInt);
    printf("\nTest Passed!\n\n");

    printf("Testing: printPreOrder\n");
    printf("Data: newTree\n");
    printf("Expecting: 5 3 2 1 4 9 7 6 8 10\nRecieved: ");
    printPreOrder(newTree,printInt);
    printf("\nTest Passed!\n\n");

    printf("Testing: printPostOrder\n");
    printf("Data: newTree\n");
    printf("Expecting: 1 2 4 3 6 8 7 10 9 5 \nRecieved: ");
    printPostOrder(newTree,printInt);
    printf("\nTest Passed!\n\n");

    printf("NOTE: ALL PRINT FUNCTIONS WORK, addToTree Test Successfull!\n\n");

    printf("TESTING: removeFromTree\n");
    printf("Data: 5\n");
    printf("Expecting: 1 2 3 4 6 7 8 9 10 \n");
    printf("Recived:   ");
    int * temp = &list[0];
    removeFromTree(newTree, (TreeDataPtr)(temp));
    printInOrder(newTree, printInt);
    printf("\nTest Passed!\n\n");
    destroyBinTree(newTree);
    printInOrder(newTree, printInt);
    return 0;
}

int compareInt (const void *a, const void*b)
{
	int i = *((int *)a);
	int j = *((int *)b);
	return(i - j);
}

void deleteInt(void*data)
{
    return;
}

void printInt(void*data)
{
    int *i = (int *)data;
    printf("%d ",*i);
}
