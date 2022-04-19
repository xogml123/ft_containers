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
# include <map.hpp>
# include <map>
# include <Benchmark.hpp>

template < class Container, class p>
	static void	bench_fill_container(Container& con, p(*mp)(size_t, test))
{
	for (size_t i = 0; i < 5000; i++)
		con.insert(mp(i, test(420, "data")));
}


template < class Container, class p>
	static void	bench_insert(Container& con, p(*mp)(size_t, test))
{
	for (size_t i = 0; i < 420690; i++)
		con.insert(mp(i, test(420, "data")));
}

template < class Container>
	static void	bench_erase(Container& con)
{
	while (con.size() > 1337)
		con.erase(con.begin());
}

template < class Container>
	static void	bench_value_erase(Container& con)
{
	for (size_t i = con.size(); i > 0; i--)
		con.erase(i);
}

template < class Container>
	static void	bench_range_erase(Container& con)
{
	con.erase(con.begin(), --con.end());
}

template < class Container >
	static void	bench_elem_access(Container& con)
{
	for (size_t i = 0; i < 420690; i++)
		con[i] = test(i);
}

template < class Container >
	static void	bench_elem_access_new_val(Container& con)
{
	for (size_t i = 0; i < 420690; i++)
		con[i] = test(i);
}

template < class Container >
	static void	bench_clear(Container& con)
{
	con.clear();
}

template < class Container >
	static void	bench_assignation(Container& con, Container& con_tba)
{
	con_tba = con;
}

template < class Container, class p>
	static void	bench_hint_insert(Container& con, p(*mp)(size_t, test))
{
	con.insert(mp(0, test(1, "first")));
	for (size_t i = 1; i < 500000; i++)
		con.insert(--con.end(), mp(i, test(69, "hint")));
}

template < class Container, class p>
	static void	bench_wrong_hint_insert(Container& con, p(*mp)(size_t, test))
{
	con.insert(mp(0, test(1, "first")));
	for (size_t i = 1; i < 500000; i++)
		con.insert(con.begin(), mp(i, test(69, "hint")));
}

template < class Bench, class p>
	static void bench_tests(Bench& bench, p(*mp)(size_t, test))
{
	bench.run_test(bench_insert, mp, "insert");
	
	bench.run_test(bench_insert, mp, "(ek) insert");
	bench.run_test(bench_erase, "erase");

	for (size_t i = 0; i < 420; i++)
		bench.run_test(bench_assignation, "assignation operator");

	bench.run_test(bench_elem_access, "operator []");
	bench.run_test(bench_elem_access, "(ek) operator []");

	for (size_t i = 0; i < 250; ++i) {
		bench_fill_container(bench.get_container(), mp);
		bench.run_test(bench_clear, "clear");
	}

	bench.run_test(bench_hint_insert, mp, "hint insert");
	bench.run_test(bench_value_erase, "value erase");
	bench.run_test(bench_wrong_hint_insert, mp, "insert wrong hint");
	bench.run_test(bench_range_erase, "range erase");
}

void map_benchmark()
{
	Benchmark< ft::map<size_t, test> >	ft_bench;
	Benchmark< std::map<size_t, test> >	std_bench;

	bench_tests(ft_bench, ft::make_pair<size_t, test>);
	bench_tests(std_bench, std::make_pair<size_t, test>);

	std::map< std::string, size_t >	ft_result = ft_bench.get_result();
	std::map< std::string, size_t >	std_result = std_bench.get_result();

	format_benchmark_result(ft_result, std_result, "map");
	print_benchmark_result(ft_bench.get_total_time(), std_bench.get_total_time(), "map");
}
