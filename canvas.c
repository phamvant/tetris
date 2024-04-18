#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "canvas.h"

void makeCanvas(char canvas[][SIZE], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            canvas[i][j] = '.';
        }
    }
}

int checkIfScore(char canvas[][SIZE])
{
    char *p;
    for (p = &canvas[SIZE - 1][0]; p <= &canvas[SIZE - 1][SIZE - 1]; p++)
    {
        if (*p != '0')
        {
            return 0;
        }
    }
    return 1;
}

void refresh(char canvas[][SIZE])
{
    char *p;
    int count = 0;

    int isScored = checkIfScore(canvas);
    printf("%d\n", isScored);

    for (p = &canvas[SIZE - 1][SIZE - 1]; p > &canvas[0][SIZE - 1]; p--)
    {
        if (isScored)
        {
            *p = *(p - SIZE);
        }
    }

    for (p = &canvas[0][0]; p <= &canvas[SIZE - 1][SIZE - 1]; p++)
    {
        printf("%c ", *p);
        count++;
        if (count == SIZE)
        {
            printf("\n");
            count = 0;
        }
    }

    for (p = &canvas[0][0]; p < &canvas[SIZE - 1][SIZE - 1]; p++)
    {
        *p = '.';
    }
}

void setObjectToCanvas(char canvas[][SIZE], Object *obj)
{
    int idx = 0;
    for (int i = obj->cordY; i < obj->cordY + SSIZE; i++)
    {
        // printf("%d \n", obj->cordY);
        int idx1 = 0;
        for (int j = obj->cordX; j < obj->cordX + SSIZE; j++)
        {
            // printf("%d", obj->cordY);
            if (obj->type[idx][idx1] == '0')
            {
                canvas[i][j] = obj->type[idx][idx1];
            }
            idx1++;
        }
        idx++;
    }
}

void makeMatrix(char canvas[][SIZE], Object *obj, int numObj, int *shouldStop)
{
    for (int k = 0; k < numObj - 1; k++)
    {
        setObjectToCanvas(canvas, obj);
        obj++;
    }

    int renderFlg = 0;
    int idx = 0;
    for (int i = obj->cordY; i < obj->cordY + SSIZE; i++)
    {
        int idx1 = 0;
        for (int j = obj->cordX; j < obj->cordX + SSIZE; j++)
        {
            if (((obj->type[idx][idx1] == '0') && ((canvas[i + 1][j] == '0') || i == SIZE - 1)))
            {
                *shouldStop = 1;
                renderFlg = 1;
            }
            idx1++;
        }
        idx++;
    }

    if (!renderFlg)
    {
        setObjectToCanvas(canvas, obj);
    }
}

void initializeGrid(Object *obj, char grid[][SSIZE])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            obj->type[i][j] = grid[i][j];
        }
    }

    obj->cordY = 2;
    obj->cordX = rand() % (17 + 1);
}

void rotate90Clockwise(Object *obj)
{
    for (int i = 0; i < SSIZE / 2; i++)
    {
        for (int j = i; j < SSIZE - i - 1; j++)
        {
            char temp = obj->type[i][j];
            obj->type[i][j] = obj->type[SSIZE - 1 - j][i];
            obj->type[SSIZE - 1 - j][i] = obj->type[SSIZE - 1 - i][SSIZE - 1 - j];
            obj->type[SSIZE - 1 - i][SSIZE - 1 - j] = obj->type[j][SSIZE - 1 - i];
            obj->type[j][SSIZE - 1 - i] = temp;
        }
    }
}
