#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <termios.h>
#include "canvas.h"

///////////// GLOBAL VARIABLES /////////////

char allGrid[4][SSIZE][SSIZE] = {
    {{'0', '0', '0'}, {'0', '0', '0'}, {'0', '0', '0'}}, // grid1
    {{'.', '.', '.'}, {'.', '0', '.'}, {'0', '0', '0'}}, // grid2
    {{'.', '.', '.'}, {'.', '.', '.'}, {'0', '0', '0'}}, // grid3
    {{'.', '.', '.'}, {'0', '0', '.'}, {'.', '0', '0'}}, // grid4
};

char keyboardInput;

///////////// GLOBAL VARIABLES /////////////

void navigate(Object *currentObject)
{
    switch (keyboardInput)
    {
    case 'a':
        currentObject->cordX--;
        break;

    case 'd':
        currentObject->cordX++;
        break;

    case ' ':
        rotate90Clockwise(currentObject);
        break;

    default:
        break;
    }

    keyboardInput = '\0';
}

void *readInputThread()
{
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char c;
    int i = 0;
    while (1)
    {
        if (read(STDIN_FILENO, &c, 1) > 0)
        {
            if (c == '\n' || i == 10)
            {
                keyboardInput = '\0';
                i = 0;
            }
            else
            {
                keyboardInput = c;
            }
        }
    }
}

void *renderThead()
{
    char canvas[SIZE][SIZE];
    makeCanvas(canvas, SIZE);

    Object *allObject;
    int numObj = 1;
    allObject = (Object *)malloc(sizeof(Object) * 1000);

    initializeGrid(allObject, allGrid[1]);

    Object *root;
    root = allObject;

    Object *currentObj;
    currentObj = allObject;

    int shoudStop = 0;

    while (1)
    {
        if (keyboardInput)
        {
            navigate(currentObj);
        }

        makeMatrix(canvas, root, numObj, &shoudStop);
        refresh(canvas);

        usleep(150000);
        system("clear");

        if (shoudStop)
        {
            printf("STOP");
            // GameOver - Free and create new Object
            if (currentObj->cordY < 1)
            {
                free(allObject);
                numObj = 1;
                allObject = (Object *)malloc(sizeof(Object) * 1000);
                initializeGrid(allObject, allGrid[1]);
                root = allObject;
                currentObj = allObject;
                shoudStop = 0;
                continue;
            }

            int objType = rand() % (3 + 1);
            currentObj++;
            numObj++;
            shoudStop = 0;
            initializeGrid(currentObj, allGrid[objType]);
            continue;
        }
        currentObj->cordY++;
    }
    return NULL;
}

int main()
{
    pthread_t readInputThreadId;
    pthread_t renderThreadId;

    pthread_create(&readInputThreadId, NULL, readInputThread, NULL);
    pthread_create(&renderThreadId, NULL, renderThead, NULL);
    pthread_join(readInputThreadId, NULL);
    pthread_join(renderThreadId, NULL);
}
