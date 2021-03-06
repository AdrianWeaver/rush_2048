/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */ /*                                                    +:+ +:+         +:+     */
/*   By: aweaver <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 09:35:55 by aweaver           #+#    #+#             */
/*   Updated: 2022/03/20 16:25:06 by aweaver          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_2048.h"

void	ft_destroy_board(void *window, void **board, int size)
{
	int	i;

	i = 0;
	while (i < size + 1)
	{
		delwin(board[i]);
		i++;
	}
	delwin(window);
}

void	ft_color_border(t_block *board_values, void **board, int tile_nb)
{
	if (board_values[tile_nb].number == 2)
		wattron(board[tile_nb], COLOR_PAIR(1));
	if (board_values[tile_nb].number == 4)
		wattron(board[tile_nb], COLOR_PAIR(2));
	if (board_values[tile_nb].number == 8)
		wattron(board[tile_nb], COLOR_PAIR(3));
	if (board_values[tile_nb].number == 16)
		wattron(board[tile_nb], COLOR_PAIR(4));
	if (board_values[tile_nb].number == 32)
		wattron(board[tile_nb], COLOR_PAIR(5));
	if (board_values[tile_nb].number == 64)
		wattron(board[tile_nb], COLOR_PAIR(6));
	if (board_values[tile_nb].number == 128)
		wattron(board[tile_nb], COLOR_PAIR(7));
	if (board_values[tile_nb].number == 256)
		wattron(board[tile_nb], COLOR_PAIR(8));
	if (board_values[tile_nb].number == 512)
		wattron(board[tile_nb], COLOR_PAIR(9));
	if (board_values[tile_nb].number == 1024)
		wattron(board[tile_nb], COLOR_PAIR(10));
	if (board_values[tile_nb].number == 2048)
		wattron(board[tile_nb], COLOR_PAIR(11));
}

void	ft_color_letters(t_block *board_values, void **board, int tile_nb)
{
	if (board_values[tile_nb].number == 2)
		wattron(board[tile_nb], COLOR_PAIR(1));
	if (board_values[tile_nb].number == 4 || board_values[tile_nb].number == 128)
		wattron(board[tile_nb], COLOR_PAIR(2));
	if (board_values[tile_nb].number == 8 || board_values[tile_nb].number == 256)
		wattron(board[tile_nb], COLOR_PAIR(3));
	if (board_values[tile_nb].number == 16 || board_values[tile_nb].number == 512)
		wattron(board[tile_nb], COLOR_PAIR(4));
	if (board_values[tile_nb].number == 32 || board_values[tile_nb].number == 1024)
		wattron(board[tile_nb], COLOR_PAIR(5));
	if (board_values[tile_nb].number == 64 || board_values[tile_nb].number == 2048)
		wattron(board[tile_nb], COLOR_PAIR(6));
}

void	**ft_create_box(void **board, void *window, int size, t_block *board_values, int score, int won)
{
	int		tile_nb;
	int		i;
	int		j;
	int		tile_length;
	int		tile_height;

	i = 0;
	tile_nb = 0;
	tile_length = (COLS - 4) / size;
	tile_height = (LINES - 5) / size;
	wresize(window, 5 + (size * tile_height), 4 + (size * tile_length));
	wborder(window, 0, 0, 0, 0, 0, 0, 0, 0);
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			board[tile_nb] = subwin(window, tile_height, tile_length , 1 + (j * tile_height), 2 + (i *tile_length));
			ft_color_border(board_values, board, tile_nb);
			wborder(board[tile_nb], 0, 0, 0, 0, 0, 0, 0, 0);
			ft_color_letters(board_values, board, tile_nb);
			if (board_values[tile_nb].number != 0)
				mvwprintw(board[tile_nb],
					(tile_height / 2), (tile_length /2), "%d", board_values[tile_nb].number);
			else
				wattron(board[tile_nb], COLOR_PAIR(1));
			tile_nb++;
			j++;
		}
		i++;
	}
	board[tile_nb] = subwin(window, 3, (size * tile_length), 1 + (j * tile_height), 2);
	wborder(board[tile_nb], 0, 0, 0, 0, 0, 0, 0, 0);
	if (won == 1)
		mvwprintw(board[tile_nb], 1, 1, "%s%*d", "GG! CURRENT SCORE:", (size * tile_length) - 20, score);
	else
		mvwprintw(board[tile_nb], 1, 1, "%s%*d", "CURRENT SCORE:", (size * tile_length) - 16, score);
	return (board);
}

void	**ft_create_toosmall(void *window)
{ wresize(window, LINES, COLS); mvwprintw(window, LINES / 2, COLS / 2, "%s", "Too small");
	return (NULL);
}

void	**ft_redraw(void *window, int size, void **board, t_block *board_values, int score, int won)
{
	ft_destroy_board(window, board, size);
	if (COLS >= (4 + (6 * size)) && LINES >= (5 + (3 * size)))
		return (ft_create_box(board, window, size, board_values, score, won));
	else
		return (ft_create_toosmall(window));
}

int	ft_init_color(void)
{
	start_color();
	if (start_color())
		return (1);
	init_pair(1, COLOR_WHITE, COLOR_BLACK);		//2 
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);	//4		|| 128
	init_pair(3, COLOR_RED, COLOR_BLACK);		//8		|| 256
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);	//16	|| 512
	init_pair(5, COLOR_CYAN, COLOR_BLACK);		//32	|| 1024
	init_pair(6, COLOR_GREEN, COLOR_BLACK);		//64	|| 2048
	init_pair(7, COLOR_YELLOW, COLOR_YELLOW);	//128 border
	init_pair(8, COLOR_RED, COLOR_RED);			//256 border
	init_pair(9, COLOR_MAGENTA, COLOR_MAGENTA);	//512 border
	init_pair(10, COLOR_CYAN, COLOR_CYAN);		//1024 border
	init_pair(11, COLOR_GREEN, COLOR_GREEN);	//2048 border
	return (0);
}
int	ft_menu(void *window, int key)
{
	int	size;

	mvwprintw(window, LINES / 2, COLS / 2, "%s", "Choose a size between 4 and 9 included");
	while (1)
	{
		key = wgetch(window);
		if (key == KEY_FOUR) 
		{
			size = 4;
			break ;
		}
		if (key == KEY_FIVE) 
		{
			size = 5;
			break ;
		}
		if (key == KEY_SIX) 
		{
			size = 6;
			break ;
		}
		if (key == KEY_SEVEN) 
		{
			size = 7;
			break ;
		}
		if (key == KEY_EIGHT) 
		{
			size = 8;
			break ;
		}
		if (key == KEY_NINE) 
		{
			size = 9;
			break ;
		}
		if (key == KEY_ESC) 
		{
			size = 0;
			break ;
		}
		if (key == KEY_RESIZE)
		{
			clear();
			refresh();
			if (COLS > 1 && LINES >= 2)
			{
				mvwprintw(window, 1, 1, "%s", "Welcome to our Awesome Menu!");
				mvwprintw(window, LINES / 2, 1, "%s", "Choose a size between 4 and 9 included");
			}
		}
	}
	clear();
	refresh();
	return (size);
}

int	main(void)
{
	t_block	*board_values;
	int		size;
	void	*window;
	int		key;
	int		win;
	int		won;
	int		score;
	int		save;

	key = 0;
	size = 4;
	win = 0;
	save = 1;
	if (WIN_VALUE == 2)
		win = 1;
	won = 0;
	window = initscr();
	if (window == NULL)
		return (1);
	curs_set(0);
	if (ft_init_color() || raw() || noecho() || keypad(window, TRUE) || nodelay(window, TRUE))
	{
		endwin();
		delscreen(window);
		return (1);
	}
	score = 0;
	size = ft_menu(window, key);
	void	*board[size * size];
	if (size == 0)
	{
		endwin();
		delscreen(window);
		return (1);
	}
	board_values = initialisation(size);
	if (board_values == NULL)
	{
		endwin();
		delscreen(window);
		free(board_values);
		return (1);
	}
	ft_create_box(board, window, size, board_values, score, won);
	while (1)
	{
		key = wgetch(window);
		if (key == KEY_UP || key == KEY_DOWN || key == KEY_RIGHT || key == KEY_LEFT)
		{
			win = movement(key, board_values, size, win, &score);
			clear();
			refresh();
			ft_redraw(window, size, board, board_values, score, won);
		}
		if (key == KEY_RESIZE)
		{
			clear();
			refresh();
			ft_redraw(window, size, board, board_values, score, won);
		}
		if (key == KEY_ESC || key == 3)
		{
			save = 0;
			break ;
		}
		refresh();
		if (win == 1 && won == 0)
		{
			ft_redraw(window, size, board, board_values, score, won);
			won = 1;
		}
		if (win == 3)
		{
			won = 2;
			break;
		}
		if (win == 2)
			break ;
	}
	ft_destroy_board(window, board, size);
	clear();
	endwin();
	delscreen(window);
	free(board_values);
	if (win == 2 && won == 0)
		ft_printf("You lost I'm afraid, final score: %d\n", score);
	if (won == 1)
		ft_printf("You are one of the few, good job. final score: %d\n", score);
	else if (won == 2)
		ft_printf("You bested the game, congratz! score : %d\n", score);
	if (save == 1)
	{
		ft_printf("Please enter 3 letters to save highscore\n");
		//new_score(score, get_next_line(0)); disabled to prevent a leak
	}
	return (0);
}
