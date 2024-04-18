#ifndef CANVAS_H
#define CANVAS_H

#define SIZE 20
#define SSIZE 3

typedef struct Object
{
    int cordX;
    int cordY;
    int rota;
    char type[SSIZE][SSIZE];
} Object;

void makeCanvas(char canvas[][SIZE], int size);

void refresh(char canvas[][SIZE]);

void makeMatrix(char canvas[][SIZE], Object *obj, int numObj, int *shouldStop);

void initializeGrid(Object *obj, char grid[][SSIZE]);

void rotate90Clockwise(Object *obj);

void setObjectToCanvas(char canvas[][SIZE], Object *obj);

int checkIfScore(char canvas[][SIZE]);

#endif /* CANVAS_H */