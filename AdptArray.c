#include <stdio.h>
#include <stdlib.h>
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
        return NULL;
    
    else if(pArray -> pElemArr)
    {
        for( int i=0; i< pArray -> ArrSize; i++)
        {
            if(pArray ->pElemArr[i])
            {
                pArray -> delfund(pArray -> pElemArr[i]);
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
        PElement oldElemArr = pArray -> pElemArr[index];
        if (oldElemArr)
        {
            pArray -> delfunc(oldElemArr);
        }
        pArray -> pElemArr[index] = pArray->copyfunc(pNewElement);
    }

    else
    {
        PElement *newpElemArr = (PElement*)calloc((index+1), sizeof(Pelement));
        if (!newpElemArr)
            return FAIL;

        if(pArray -> pElemArr)
        {
            for (int i=0; i< pArray -> ArrSize; i++)
            {
                if(pArray -> pElemArr[i] != NULL)
                {
                    newpElemArr[i] = pArray -> copyfunc(pArray -> pElemArr[i]);
                    pArray -> delfunc(pArray -> pElemArr[i]);
                }
            }
        }
         free (pArray -> pElemArr);
         pArray -> pElemArr = newpElemArr;
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
    if(index < 0 || pArray -> ArrSize <= index || adptArray->arr[index] == NULL)
        return NULL;
    
    return (pArray -> copyfunc(pArray -> pElemArr[index]));
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


