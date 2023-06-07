#include "main.h"

int main(int ac, char **av)
{
    t_var	var;

	if (ac - 1 == 4 || ac - 1 == 5)
	{
		if (check_valid_input(ac, av))
			return (1);
		fill_struct(ac, av, &var);
		initiate_struct(&var);
		start_simulation(&var);
	}
	else
		printf("Usage: ./philo <# philosophers> <time to die> <time to eat>\
				<time to sleep> [# times each philosopher must eat]\n");
	return (0);
}