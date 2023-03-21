#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AdptArray.h"

typedef struct AdptArray_
{
    int ArrSize;
    PElement *pElemArr;
    DEL_FUNC delfunc;
    COPY_FUNC copyfunc;
    PRINT_FUNC printfunc;
}*PAdptArray;

/*  Creat a new AdpyArray */
PAdptArray CreateAdptArray(COPY_FUNC copyfunc , DEL_FUNC delfunc,PRINT_FUNC printfunc)
{
    PAdptArray new = (PAdptArray)malloc(sizeof(struct AdptArray_));
    if(!new)
        return NULL;

    new -> ArrSize = 0;
    new -> pElemArr = NULL;
    new -> delfunc = delfunc;
    new -> copyfunc = copyfunc;
    new -> printfunc = printfunc;

    return new;
}

/*  Delete an AdptArray */
void DeleteAdptArray(PAdptArray pArray)
{
    if(pArray == NULL)
        return;
    
    else if(pArray -> pElemArr)
    {
        for( int i=0; i< pArray -> ArrSize; i++)
        {
            if(pArray ->pElemArr[i])
            {
                pArray -> delfunc(pArray -> pElemArr[i]);
            }
        }
        free(pArray -> pElemArr);
    }
    free(pArray);
}

/*  set the element at the index "spot"  */
Result SetAdptArrayAt(PAdptArray pArray, int index, PElement pNewElement)
{
    if( pArray == NULL)
        return FAIL;

    if( index < pArray -> ArrSize )
    {
        if ((pArray -> pElemArr)[index])
        {
            pArray -> delfunc((pArray -> pElemArr)[index]);
        }
        (pArray -> pElemArr)[index] = pArray->copyfunc(pNewElement);
    }

    else
    {
        PElement *newpElemArr = (PElement*)calloc((index+1), sizeof(PElement));
        if (!newpElemArr)
            return FAIL;

        memcpy(newpElemArr,pArray->pElemArr,pArray->ArrSize*sizeof(PElement));
        free (pArray -> pElemArr);
        pArray -> pElemArr = newpElemArr;
        (pArray -> pElemArr)[index]== pArray->copyfunc(pNewElement);
    }

    if( index >= pArray -> ArrSize)
    {
        pArray -> ArrSize = index +1;
    }

    return SUCCESS;
}

/*  get an index and return copy of the element in this index  */
PElement GetAdptArrayAt(PAdptArray pArray, int index)
{
    if( pArray == NULL)
        return NULL;
    if(pArray -> ArrSize <= index)
        return NULL;
    if(pArray->pElemArr[index] == NULL)
        return NULL;
    
    return (pArray -> copyfunc((pArray -> pElemArr)[index]));
}

/*  return the size of array  */
int GetAdptArraySize(PAdptArray pArray)
{
    if (pArray == NULL)
        return -1;

    return pArray->ArrSize;
}

/*  print the elemants  */
void PrintDB(PAdptArray pArray)
{
    if( pArray == NULL)
        return;

    for(int i=0; i<pArray -> ArrSize; i++)
    {
        if(pArray -> pElemArr[i])
        {
            pArray -> printfunc(pArray -> pElemArr[i]);
        }
    }
}


