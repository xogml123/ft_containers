/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_benchmark.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takim <takim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by  |_|  (_)`-       #+#    #+#             */
/*   Updated: 2022/04/19 19:22:44 by takim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*              (_) |   | .-'   _  \ \   (_) |   | .-'  |   (                 */
/*                | |   |  `--.( `-'  )    | |   |  `--.| |\ \                */
/*                `-'   /( __.' `----'     `-'   /( __.'|_| \)\               */
/*                     (__)                     (__)        (__)              */
/*                                                                            */
/*                   Kingmar  |  https://github.com/K1ngmar                   */
/*                                                                            */
/* ************************************************************************** */

# include <test_utility.hpp>
# include <vector.hpp>
# include <vector>
# include <Benchmark.hpp>
template < class Container >
	static void	fill_container(Container& con)
{
	con.insert(con.begin(), 25000, test(420, "data"));
}

template < class Container >
	static	void bench_push_back(Container& con)
{
	for (size_t i = 0; i < 500000; ++i)
		con.push_back(test(i));
}

template < class Container >
	static void	bench_fill_insert(Container& con)
{
	for (size_t i = 0; i < 50; ++i)
		con.insert(con.begin(), 250, test(1, "insert"));
}

template < class Container >
	static void bench_pop_back(Container& con)
{
	while (con.size() > 1337)
		con.pop_back();
}

template < class Container >
	static void bench_swap(Container& con, Container& vec)
{
	for (size_t i = 0; i < 42069; ++i)
		vec.swap(con);
}

template < class Container >
	static void bench_erase(Container& con)
{
	con.erase(con.begin(), con.end() - 2500);
}

template < class Container >
	static void bench_clear(Container& con)
{
	con.clear();
}

template < class Container >
	static void bench_reserve(Container& con)
{
	for (size_t i = 0; i < 500; ++i) {
		con.reserve(250);
		con.reserve(500000);
		con.clear();
	}
}

template < class Container >
	static void bench_resize(Container& con)
{
	for (size_t i = 0; i < 500; ++i) {
		con.resize(25000);
		con.resize(1337);
	}
}

template < class Container >
	static void bench_assign(Container& con)
{
	for (size_t i = 0; i < 50; ++i) {
		con.assign(420, test(69));
		con.assign(200000, test(69));
	}
}

template < class Container >
	static void bench_assign_operator(Container& con, Container& con_too)
{
	for (size_t i = 0; i < 5000; ++i) {
		con = con_too;
		con_too = con;
	}
}

template < class Bench >
	static void bench_tests(Bench& bench)
{
	bench.run_test(bench_push_back, "push back");
	bench.run_test(bench_fill_insert, "fill insert");
	bench.run_test(bench_pop_back, "pop back");

	fill_container(bench.get_container());
	bench.run_test(bench_swap, "swap");

	for (size_t i = 0; i < 250; ++i) {
		fill_container(bench.get_container());
		bench.run_test(bench_erase, "erease");
	}

	for (size_t i = 0; i < 250; ++i) {
		fill_container(bench.get_container());
		bench.run_test(bench_clear, "clear");
	}

	bench.run_test(bench_reserve, "reserve");
	fill_container(bench.get_container());
	bench.run_test(bench_resize, "resize");
	bench.run_test(bench_assign, "assign");
	bench.run_test(bench_assign_operator, "assign opr");
}

void vector_benchmark()
{
	Benchmark< ft::vector<test> >	ft_bench;
	Benchmark< std::vector<test> >	std_bench;

	bench_tests(ft_bench);
	bench_tests(std_bench);

	std::map< std::string, size_t >	ft_result = ft_bench.get_result();
	std::map< std::string, size_t >	std_result = std_bench.get_result();

	format_benchmark_result(ft_result, std_result, "vector");
	print_benchmark_result(ft_bench.get_total_time(), std_bench.get_total_time(), "vector");
}
