#include <stdio.h>
#include <stdlib.h>


float larp(float start, float end, float value)
{
    //printf("Larping %.2f and %.2f of %.2f\n", start, end, value);
    return end * value + start* (1 - value);
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <GRIDSIZE> <SCALE> <SEED>\n", argv[0]);
        return 1;
    }

    int GRIDSIZE = atoi(argv[1]);
    int POINTSIZE = atoi(argv[2]);

    float SCALING = GRIDSIZE / POINTSIZE;
    srand(atoi(argv[3]));

    float **points = malloc(sizeof(float*) * POINTSIZE + 1);
    for (int i = 0; i <= POINTSIZE; i++)
        points[i] = malloc(sizeof(float) * POINTSIZE + 1);

    for (int i = 0; i <= POINTSIZE; i++)
    {
        for (int j = 0; j <= POINTSIZE; j++)
        {
            points[i][j] = (rand() % 100) / 100.0f;
            //printf("Rand value: %.2f\n", points[i][j]);
        }
    }

    float **grid = malloc(sizeof(float*) * GRIDSIZE);
    for (int i = 0; i <  GRIDSIZE; i++) 
        grid[i] = malloc(sizeof(float) * GRIDSIZE);


    for (int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            float x = j / SCALING, y = i / SCALING; 
            int x0 = x;
            int y0 = y;

            float top = larp(points[y0][x0], points[y0][x0 + 1], x - x0);
            float bottom = larp(points[y0 + 1][x0], points[y0 + 1][x0 + 1], x - x0);

            grid[i][j] = larp(top, bottom, y - y0);

            //printf("%.2f %.2f\n", x - x0, y - y0);
            
        }
    }

    /*
    for (int i = 0; i <= POINTSIZE; i++)
    {
        for (int j = 0; j <= POINTSIZE; j++)
        {
            int shade = (points[i][j] * 12);
            if (shade < 0) shade = 0;
            if (shade > 11) shade = 11;
            char c = ".,-~:;=!*#$@"[shade];
            putchar(c);
        }
        putchar('\n');
    }
    */

    for (int i = 0; i < GRIDSIZE; i++)
    {
        for (int j = 0; j < GRIDSIZE; j++)
        {
            int shade = (grid[i][j] * 13);
            if (shade < 0) shade = 0;
            if (shade > 11) shade = 12;
            char c = " .,-~:;=!*#$&@"[shade];
            putchar(c);
        }
        putchar('\n');
    }


    for (int i = 0; i < GRIDSIZE; i++)
        free(grid[i]);

    for (int i = 0; i < POINTSIZE; i++)
        free(points[i]);

    free(points);
    free(grid);

    return 0;
}
