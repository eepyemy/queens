#include <unistd.h>

#define CANNOT -1
#define CAN 1
#define NOT_FOUND -1
#define FOUND 1

int	can_place(int col, int row, int *queens)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if ((i == col || queens[i] == row) && queens[i] != -1)
			return (CANNOT);
		if (col + row + 1 == i + queens[i] + 1 && queens[i] != -1)
			return (CANNOT);
		if (col + 10 - row == i + 10 - queens[i] && queens[i] != -1)
			return (CANNOT);
		i++;
	}
	return (CAN);
}

int	solution_found(int placed)
{
	if (placed >= 10)
		return (FOUND);
	else
		return (NOT_FOUND);
}

void	solution_print(int *queens)
{
	int		i;
	char	output;

	i = 0;
	while (i < 10)
	{
		output = queens[i] + '0';
		write(1, &output, 1);
		i++;
	}
	write(1, "\n", 1);
}

void	next_queen(int col, int *queens, int placed, int *solutions_count)
{
	int	new_col;
	int	i;

	if (solution_found(placed) == FOUND)
	{
		*solutions_count += 1;
		solution_print(queens);
		return ;
	}
	i = 0;
	while (i < 10)
	{
		if (can_place(col, i, queens) == CAN)
		{
			queens[col] = i;
			new_col = (col + 1) % 10;
			next_queen(new_col, queens, placed + 1, solutions_count);
			queens[col] = -1;
		}
		i++;
	}
}

int	ft_ten_queens_puzzle(void)
{
	int		count;
	int		*count_p;
	int		queens[10];

	count_p = &count;
	*count_p = 0;
	while (*count_p < 10)
	{
		queens[*count_p] = -1;
		*count_p = *count_p + 1;
	}
	*count_p = 0;
	next_queen(0, queens, 0, count_p);
	return (*count_p);
}
