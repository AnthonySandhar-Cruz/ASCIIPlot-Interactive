#ifndef PLOT_FUNCTIONS_H
#define PLOT_FUNCTIONS_H

#include <stdio.h>
#include <ncurses.h>
#include <string.h>

void find_plot_points(int w, int h, char matrix[h][w], int x_mid, int y_mid, double dx, double dy, double x[w], double y[w], char marker);
void make_plot(int w, int h, double x_min, double x_max, char function[30], char matrix[h][w], char marker, int startx, int starty, int colour_pair);
size_t double_length(double number);
double find_range_len(double x_min, double x_max);
void initialize_cartesian(int w, int h, char matrix[h][w], int x_mid, int y_mid);
void get_timestamp(char *buffer, size_t size);
void save_plot_to_file(int w, int h, double x_min, double x_max, char function[30], char matrix[h][w]);

#endif
