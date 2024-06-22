#include "ascii_plot.h"

WINDOW *create_newwin(int height, int width, int starty, int startax);
void destroy_win(WINDOW *local_win);

int main(int argc, char *argv[])
{
	// Initialize ncurses
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	start_color();
	refresh();

	WINDOW *options_win;
	WINDOW *plot_win;

	// Create option window
	int startx_opts, starty_opts, width_opts, height_opts;
	if ((COLS / 3) > 20)
	{
		startx_opts = 1, starty_opts = 1, width_opts = 20, height_opts = LINES - 3;
	}
	else
	{
		startx_opts = 1, starty_opts = 1, width_opts = COLS / 3, height_opts = LINES - 3;
	}
	options_win = create_newwin(height_opts, width_opts, starty_opts, startx_opts);

	// Create plot window
	int startx_plot = width_opts + 2, starty_plot = 1, width_plot = COLS - width_opts - 2, height_plot = LINES - 3;
	plot_win = create_newwin(height_plot, width_plot, starty_plot, startx_plot);

	// Show options
	mvwprintw(options_win, 2, 2, "(d) domain");
	mvwprintw(options_win, 5, 2, "(f) function");
	mvwprintw(options_win, 8, 2, "(m) marker");
	mvwprintw(options_win, 11, 2, "(c) colour");
	mvwprintw(options_win, height_opts - 6, 2, "(p) plot");
	mvwprintw(options_win, height_opts - 4, 2, "(s) save");
	mvwprintw(options_win, height_opts - 2, 2, "(x) exit");
	wrefresh(options_win);

	// Create colour options for marker
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);

	// Initialize plot params
	int startx_mat = width_opts + 3,
		starty_mat = 3, h_mat = height_plot - 4, w_mat = width_plot - 15;
	char matrix[h_mat][w_mat];

	// Input handling
	int ch;
	double domain = 5.0;
	char function[30];
	char marker = '*';
	char colour[10] = "red";
	int colour_pair = 1;
	while ((ch = getch()) != 'x')
	{
		switch (ch)
		{
		case 'd':
			mvwprintw(options_win, 3, 2, "          ");
			wmove(options_win, 3, 2);
			echo();
			wscanw(options_win, "%lf", &domain);
			noecho();
			mvwprintw(options_win, 3, 2, "          ");
			wmove(options_win, 3, 2);
			mvwprintw(options_win, 3, 2, "%lf", domain);
			wrefresh(options_win);
			break;
		case 'f':
			mvwprintw(options_win, 6, 2, "          ");
			wmove(options_win, 6, 2);
			echo();
			wgetnstr(options_win, function, sizeof(function) - 1);
			noecho();
			mvwprintw(options_win, 6, 2, "          ");
			wmove(options_win, 6, 2);
			mvwprintw(options_win, 6, 2, "%s", function);
			wrefresh(options_win);
			break;
		case 'm':
			mvwprintw(options_win, 9, 2, "          ");
			wmove(options_win, 9, 2);
			echo();
			wgetnstr(options_win, &marker, 1);
			noecho();
			mvwprintw(options_win, 9, 2, "          ");
			wmove(options_win, 9, 2);
			mvwprintw(options_win, 9, 2, "%c", marker);
			wrefresh(options_win);
			break;
		case 'c':
			mvwprintw(options_win, 12, 2, "          ");
			wmove(options_win, 12, 2);
			echo();
			wgetnstr(options_win, colour, sizeof(colour) - 1);
			noecho();
			mvwprintw(options_win, 12, 2, "          ");
			wmove(options_win, 12, 2);
			mvwprintw(options_win, 12, 2, "%s", colour);
			if (strcmp(colour, "red") == 0)
			{
				colour_pair = 1;
			}
			else if (strcmp(colour, "green") == 0)
			{
				colour_pair = 2;
			}
			else if (strcmp(colour, "blue") == 0)
			{
				colour_pair = 3;
			}
			wrefresh(options_win);
			break;
		case 'p':
			make_plot(w_mat, h_mat, -domain, domain, function, matrix, marker, startx_mat, starty_mat, colour_pair);
			break;
		case 's':
			save_plot_to_file(w_mat, h_mat, -domain, domain, function, matrix);
			break;
		}
	}

	// Clean up
	destroy_win(options_win);
	endwin();

	return 0;
}

WINDOW *create_newwin(int height, int width, int starty, int startx)
{
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	box(local_win, 0, 0);
	wrefresh(local_win);

	return local_win;
}

void destroy_win(WINDOW *local_win)
{
	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}
