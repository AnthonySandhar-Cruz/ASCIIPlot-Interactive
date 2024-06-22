#include "ascii_plot.h"
#include <math.h>
#include <string.h>
#include "tinyexpr.h"
#include <stdio.h>
#include <time.h>

size_t double_length(double number)
{
    // Determine the length of the string representation of a double
    char buffer[50];
    sprintf(buffer, "%lf", number);
    return strlen(buffer);
}

double find_range_len(double min, double max)
{
    // Find the larger of the two bounds and returns size of the range
    if (fabs(min) > fabs(max))
    {
        return 2 * fabs(min);
    }
    else
    {
        return 2 * fabs(max);
    }
}

// create a functiin that returns a matrix
void initialize_cartesian(int w, int h, char matrix[h][w], int x_mid, int y_mid)
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (i == y_mid && j == x_mid)
            {
                matrix[i][j] = '+';
            }
            else if (i == y_mid)
            {
                matrix[i][j] = '-';
            }
            else if (j == x_mid)
            {
                matrix[i][j] = '|';
            }
            else if (i == 0 || i == h - 1)
            {
                matrix[i][j] = '-';
            }
            else if (j == 0 || j == w - 1)
            {
                matrix[i][j] = '|';
            }
            else
            {
                matrix[i][j] = ' ';
            }
        }
    }
}

void find_plot_points(int w, int h, char matrix[h][w], int x_mid, int y_mid, double dx, double dy, double x[w], double y[w], char marker)
{
    int x_pos;
    int y_pos;

    for (int i = 0; i < w - 2; i++)
    {
        if (y[i] > 0)
        {
            y_pos = y_mid - (int)(fabs(y[i]) / dy);
        }
        else
        {
            y_pos = y_mid + (int)(fabs(y[i]) / dy);
        }

        if (x[i] > 0)
        {
            x_pos = x_mid + (int)(fabs(x[i]) / dx);
        }
        else
        {
            x_pos = x_mid - (int)(fabs(x[i]) / dx);
        }
        matrix[y_pos][x_pos] = marker;
    }
}

void make_plot(int w, int h, double x_min, double x_max, char function[30], char matrix[h][w], char marker, int startx, int starty)
{
    int x_mid = w / 2;
    int y_mid = h / 2;
    double x_len;
    double y_len;
    double dx;
    double dy;
    double y_min;
    double y_max;
    double x[w];
    double y[w];
    int y_pos;
    int x_pos;

    x_len = find_range_len(x_min, x_max);
    dx = x_len / (w - 2);

    // compute x and y arrays
    for (int i = 0; i < w - 2; i++)
    {
        x[i] = (-1 * (x_len / 2)) + i * dx;
        te_variable vars[] = {{"x", &x[i]}};
        int err;
        te_expr *expr = te_compile(function, vars, 1, &err);
        y[i] = te_eval(expr);
        te_free(expr);
    }

    // find y_min and y_max
    y_min = y[0];
    y_max = y[0];
    for (int i = 1; i < w - 2; i++)
    {
        if (y[i] < y_min)
        {
            y_min = y[i];
        }
        else if (y[i] > y_max)
        {
            y_max = y[i];
        }
    }

    y_len = find_range_len(y_min, y_max);
    dy = y_len / (h - 2);

    // initialize matrix (cartesian plane)
    initialize_cartesian(w, h, matrix, x_mid, y_mid);

    // find plot points and add them to matrix
    find_plot_points(w, h, matrix, x_mid, y_mid, dx, dy, x, y, marker);

    // plot the matrix with y-axis scale
    for (int i = 0; i < h; i++)
    {
        move(starty, startx);
        if (i % 5 == 0)
        {
            printw(" %6.2f ", y_mid - i > 0 ? (y_mid - i) * dy : (i - y_mid) * dy);
        }
        else
        {
            printw("        ");
        }
        move(starty, startx + 8);
        for (int j = 0; j < w; j++)
        {
            printw("%c", matrix[i][j]);
        }
        starty++;
    }

    // plot the x-axis scale
    move(starty, startx);
    printw("       ");
    for (int i = 0; i < w; i++)
    {
        if (i == 0)
        {
            printw("%6.2f", x_min);
        }
        else if (i == (x_mid - double_length(x_min) - 1))
        {
            printw("%6.2f", 0.0);
        }
        else if (i == (w - 1 - double_length(x_min) - double_length(0.0) - 2))
        {
            printw("%6.2f", x_max);
            break;
        }
        else
        {
            printw(" ");
        }
    }
}

// Function to get current timestamp
void get_timestamp(char *buffer, size_t size)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y%m%d%H%M%S", t);
}

// Function to save the plot to a file
void save_plot_to_file(int w, int h, double x_min, double x_max, char function[30], char matrix[h][w])
{
    int y_mid = h / 2;
    int x_mid = w / 2;

    int x_len = find_range_len(x_min, x_max);
    double dx = x_len / (w - 2);

    // compute x and y arrays
    double x[w];
    double y[w];
    for (int i = 0; i < w - 2; i++)
    {
        x[i] = (-1 * (x_len / 2)) + i * dx;
        te_variable vars[] = {{"x", &x[i]}};
        int err;
        te_expr *expr = te_compile(function, vars, 1, &err);
        y[i] = te_eval(expr);
        te_free(expr);
    }

    // find y_min and y_max
    double y_min = y[0];
    double y_max = y[0];
    for (int i = 1; i < w - 2; i++)
    {
        if (y[i] < y_min)
        {
            y_min = y[i];
        }
        else if (y[i] > y_max)
        {
            y_max = y[i];
        }
    }

    int y_len = find_range_len(y_min, y_max);
    double dy = y_len / (h - 2);

    char filename[100];
    get_timestamp(filename, sizeof(filename));
    strcat(filename, ".txt");

    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }

    // Save the matrix with y-axis scale
    for (int i = 0; i < h; i++)
    {
        if (i % 5 == 0)
        {
            fprintf(file, " %6.2f ", y_mid - i > 0 ? (y_mid - i) * dy : (i - y_mid) * dy);
        }
        else
        {
            fprintf(file, "        ");
        }
        for (int j = 0; j < w; j++)
        {
            fputc(matrix[i][j], file);
        }
        fputc('\n', file);
    }

    // Save the x-axis scale
    fprintf(file, "       ");
    for (int i = 0; i < w; i++)
    {
        if (i == 0)
        {
            fprintf(file, "%6.2f", x_min);
        }
        else if (i == (x_mid - double_length(x_min) - 1))
        {
            fprintf(file, "%6.2f", 0.0);
        }
        else if (i == (w - 1 - double_length(x_min) - double_length(0.0) - 2))
        {
            fprintf(file, "%6.2f", x_max);
            break;
        }
        else
        {
            fputc(' ', file);
        }
    }

    fclose(file);
}