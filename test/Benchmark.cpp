/* ************************************************************************** */
/*                                                                            */
/*        ,--,  .---.  .-. .-. _______  .--.  ,-..-. .-.,---.  ,---.          */
/*      .' .') / .-. ) |  \| ||__   __|/ /\ \ |(||  \| || .-'  | .-.\         */
/*      |  |(_)| | |(_)|   | |  )| |  / /__\ \(_)|   | || `-.  | `-'/         */
/*      \  \   | | | | | |\  | (_) |  |  __  || || |\  || .-'  |   (          */
/*       \  `-.\ `-' / | | |)|   | |  | |  |)|| || | |)||  `--.| |\ \         */
/*        \____\)---'  /(  (_)   `-'  |_|  (_)`-'/(  (_)/( __.'|_| \)\        */
/*             (_)    (__)                      (__)   (__)        (__)       */
/*              _______ ,---.     .---.  _______ ,---.  ,---.                 */
/*             |__   __|| .-'    ( .-._)|__   __|| .-'  | .-.\                */
/*               )| |   | `-.   (_) \     )| |   | `-.  | `-'/                */
/*              (_) |   | .-'   _  \ \   (_) |   | .-'  |   (                 */
/*                | |   |  `--.( `-'  )    | |   |  `--.| |\ \                */
/*                `-'   /( __.' `----'     `-'   /( __.'|_| \)\               */
/*                     (__)                     (__)        (__)              */
/*                                                                            */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

# include <test_utility.hpp>
# include <map>

void	print_benchmark_container(std::string prefix, std::string type)
{
	std::cout << COLOR_GREEN << prefix;
	std::cout << COLOR_RESET << "::" << COLOR_ORANGE << type << COLOR_RESET << std::setw(12) << std::left << std::setfill('-') << "";
}

static size_t my_diff(size_t& first, size_t& second)
{
	if (first > second)
		return (first - second);
	return (second - first);
}

static void		set_performance_color(size_t ft_t, size_t std_t)
{
	/* if the diffrence is less than 10% */
	if ((double)my_diff(ft_t, std_t) < (double)std_t * (double)0.1)
		std::cout << COLOR_ORANGE;
	else if (ft_t > std_t)
		std::cout << COLOR_RED;
	else
		std::cout << COLOR_GREEN;
}

void	format_benchmark_result(std::map< std::string, size_t >	& ft_rs,
								std::map< std::string, size_t >	& std_rs,
								std::string container)
{
	print_header(std::string("Benchmark results for ft::") + container);

	std::map< std::string, size_t >::iterator ft_itr = ft_rs.begin();
	std::map< std::string, size_t >::iterator std_itr = std_rs.begin();

	size_t ft_time, std_time;
	std::string ft_con, std_con;
	ft_con = std::string(COLOR_GREEN) + "ft" + COLOR_RESET + "::" + COLOR_ORANGE + container;
	std_con = std::string(COLOR_GREEN) + "std" + COLOR_RESET + "::" + COLOR_ORANGE + container + "\n";
	std::cout << std::setw(73) << ft_con << std::setw(47) << std_con << std::endl; 
	while (ft_itr != ft_rs.end())
	{
		ft_time = (*ft_itr).second;
		std_time = (*std_itr).second;

		/* test name */
		std::cout	<< COLOR_PINK << std::setw(20) << std::right << (*ft_itr).first << COLOR_RESET  << " took: ";
	
		/* ft result */
		set_performance_color(ft_time, std_time);
		std::cout << std::setw(24) << std::right << ft_time << COLOR_BLU << "µs";

		/* std result */
		std::cout << COLOR_LBLUE << std::setw(24) << std::right << std_time << COLOR_BLU << "µs\n" << COLOR_RESET;

		++ft_itr;
		++std_itr;
	}
}

void	print_benchmark_result(double ft_dur, double std_dur, const char* type)
{
	double result = (ft_dur - std_dur) / ft_dur * 100;

	std::cout << COLOR_GREEN << "\nft" << COLOR_RESET;
	std::cout << "::" << COLOR_ORANGE << type << COLOR_RESET;
	std::cout << std::fixed << std::setprecision(2);
	std::cout << " was ";
	if (result >= (double)-5 && result <= (double)5) {
		if  (result >= (double)0)
			std::cout << COLOR_ORANGE << result << COLOR_RESET << "% slower";
		else 
			std::cout << COLOR_ORANGE << -result << COLOR_RESET << "% faster";
		std::cout << COLOR_LBLUE << " (￢_￢;)\n";
	}
	else if (result < (double)-5) {
		std::cout << COLOR_GREEN << -result << COLOR_RESET << "% ";
		std::cout << "faster " << COLOR_YELLOW << "ヽ(o＾▽＾o)ノ\n";
	}
	else {
		std::cout << COLOR_RED << result << COLOR_RESET << "% ";
		std::cout << "slower " << COLOR_BLU << "(っ˘̩╭╮˘̩)っ\n";
	}
	std::cout << COLOR_RESET;
}
