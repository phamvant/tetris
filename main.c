#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 20
#define SSIZE 3

char allGrid[3][SSIZE][SSIZE] = {
    {{'0', '0', '0'}, {'0', '0', '0'}, {'0', '0', '0'}}, // grid3
    {{'.', '.', '.'}, {'.', '0', '.'}, {'0', '0', '0'}}, // grid1
    {{'.', '.', '.'}, {'0', '0', '0'}, {'.', '.', '.'}}, // grid2
};

typedef struct Object
{
    int cordX;
    int cordY;
    int rota;
    char type[SSIZE][SSIZE];
} Object;

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

void refresh(char canvas[][SIZE], int size)
{
    char *p;
    int count = 0;
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

void makeMatrix(char canvas[][SIZE], Object *obj)
{
    if (obj->cordY == SIZE - 1)
    {
        return;
    }

    int idx = 0;
    for (int i = obj->cordY; i < obj->cordY + SSIZE; i++)
    {
        int idx1 = 0;
        for (int j = obj->cordX; j < obj->cordX + SSIZE; j++)
        {
            canvas[i][j] = obj->type[idx][idx1];
            idx1++;
        }
        idx++;
    }
    obj->cordY++;
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

void initializeGrid(Object *obj, char grid[][SSIZE])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            obj->type[i][j] = grid[i][j];
        }
    }
    obj->cordY = 0;
    int start = rand() % (5 + 1);
    obj->cordX = 8;
}

int main()
{
    int size = SIZE;
    char canvas[size][size], *p;

    makeCanvas(canvas, size); // Pass canvas by reference
    Object obj1;

    initializeGrid(&obj1, allGrid[1]);

    while (1)
    {

        obj1.cordY++;
        makeMatrix(canvas, &obj1);
        // rotate90Clockwise(&obj1);
        refresh(canvas, size);
        usleep(100000);
        // system("clear");
        if (obj1.cordY > SIZE)
        {
            int objType = rand() % (2 + 1);
            initializeGrid(&obj1, allGrid[objType]);
        }
    }

    // for (p = &canvas[0][0]; p <= &canvas[SIZE - 1][SIZE - 1]; p++)
    // {
    //     printf("%d\n", *p);
    // }
}

