/*
 * Written By: Ari Perez
 * November 2017
 */

#include "BinarySearchTreeAPI.h"
#include "ai.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Knowledge * createKnowledge(char*key, char*output)
{
    Knowledge *newKnow = malloc(sizeof(Knowledge));
    newKnow->key = malloc(sizeof(char) *(strlen(key) + 1));
    newKnow->output = malloc(sizeof(char) * (strlen(output) + 1)) ;
    strcpy(newKnow->key, key);
    strcpy(newKnow->output, output);
    newKnow->sysRate = 0.5;
    newKnow->userRate = 0;
    newKnow->learningRate = 0.05;
    newKnow->count = 0;
    return newKnow;
}

void setRate(Knowledge *toSet, double userRate)
{
    toSet->userRate = userRate;
}

void setLearning(Knowledge *toSet, double learningRate)
{
    toSet->learningRate = learningRate;
}

void setCount(Knowledge *toSet, int num)
{
    toSet->count+=num;
}

void setSystem(Knowledge*toSet, double newSysRate)
{
    toSet->sysRate = newSysRate;
}

char*getKey(Knowledge *toGet)
{
    return(toGet->key);
}

char*getOuput(Knowledge *toGet)
{
    return(toGet->output);
}

double getRating(Knowledge *toGet)
{
    return(toGet->userRate);
}

double getSystem(Knowledge *toGet)
{
    return(toGet->sysRate);
}

double getLearningRate(Knowledge *toGet)
{
    return(toGet->learningRate);
}

int getCount(Knowledge *toGet)
{
    return(toGet->count);
}

int compareKnowledge(const void *first, const void*second)
{
    Knowledge *a = ((Knowledge*)first);
    Knowledge *b = ((Knowledge*)second);

    return(strcmp(getKey(a), getKey(b)));

}

void printKnowledge(void *first)
{
    Knowledge *a = ((Knowledge*)first);
    printf("%s    Rating:%lf        System:%lf         Occurences:%d\n", getKey(a), getRating(a), getSystem(a), getCount(a));
}

void printOutput(void *first)
{
    Knowledge *a = ((Knowledge*)first);
    printf("%s\n", getOuput(a));
}

void deleteKnowledge(void*first)
{
    return;
}
