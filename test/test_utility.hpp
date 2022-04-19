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

#ifndef THIS_IS_A_REALLY_COOL_TESTER_HPP
# define THIS_IS_A_REALLY_COOL_TESTER_HPP

# include <iostream>
# include <iomanip>
# include <string>
# include <sys/time.h>
# include <stdlib.h>
# include <vector>
# include <utility>
# include <stdlib.h>

///////////////////
// COLOR DEFINES //
///////////////////

	# define COLOR_RED		"\033[31m"
	# define COLOR_GREEN	"\033[32m"
	# define COLOR_YELLOW	"\033[33m"

	# define COLOR_BLU 		"\033[38;5;31m"
	# define COLOR_LBLUE 	"\033[38;5;51m"
	# define COLOR_ORANGE	"\033[38;5;214m"
	# define COLOR_PURPLE	"\033[38;5;98m"
	# define COLOR_OYELLOW	"\033[38;5;220m"
	# define COLOR_PINK		"\033[38;5;205m"
	# define COLOR_YOS		"\033[38;5;226"

	# define COLOR_RESET	"\033[0m"

//////////////
// Messages //
//////////////

	# define TEST_SUCCESS "[" COLOR_GREEN "OK" COLOR_RESET "] "
	# define TEST_FAILURE "[" COLOR_RED	"KO" COLOR_RESET "] "


	# define MILISECOND 1000

/////////////
// Utility //
/////////////

	void		print_header(std::string header);

	template < class ft_container, class std_container, class T >
		void	insert_amount(ft_container& ft_con, std_container& std_con, T val, size_t n = 420)
	{
		for (size_t i = 0; i < n; ++i) {
			ft_con.insert(val);
			std_con.insert(val);
		}
	}


	template < class ft_container, class std_container >
		void	push_back_increment(ft_container& ft_con, std_container& std_con, size_t n = 420)
	{
		for (size_t i = 0; i < n; ++i) {
			ft_con.push_back(i);
			std_con.push_back(i);
		}
	}

	template < class ft_container, class std_container >
		void	insert_increment(ft_container& ft_con, std_container& std_con, size_t n = 420)
	{
		for (size_t i = 0; i < n; ++i) {
			ft_con.insert(i);
			std_con.insert(i);
		}
	}

	template < class ft_container, class std_container, class T >
		void	push_back_amount(ft_container& ft_con, std_container& std_con, T val, size_t n = 420)
	{
		for (size_t i = 0; i < n; ++i) {
			ft_con.push_back(val);
			std_con.push_back(val);
		}
	}

	void		start_test(std::string name, void(*func)());

/////////////////////
// Compare utility //
/////////////////////

	template < class T1, class T2 >
		void	print_difference(T1 expected, T2 received)
	{
		std::cout	<< "expected value: " << expected << std::endl\
					<< "received value: " << received << std::endl;
	}

	template < class ft_val, class std_val >
		void	compare(ft_val& ft_con, std_val& std_con, bool(*comp)(ft_val&, std_val&), const char* test)
	{
		if (comp(ft_con, std_con) == true)
			std::cout << TEST_SUCCESS;
		else {
			std::cout << TEST_FAILURE;
			std::cout << "test: " << test << std::endl;
		}
	}

	template < class ft_val, class ft_itr, class std_val, class std_itr >
		void	compare(ft_val& ft_con, ft_itr ft_i, std_val& std_con, std_itr std_i, bool(*comp)(ft_val&, ft_itr, std_val&, std_itr), const char* test)
	{
		if (comp(ft_con, ft_i, std_con, std_i) == true)
			std::cout << TEST_SUCCESS;
		else {
			std::cout << TEST_FAILURE;
			std::cout << "test: " << test << std::endl;
		}
	}

	template <class ft_itr, class std_itr>
		bool	compare_these_iterators_yo(ft_itr& ft, std_itr& std)
	{
		if (*ft != *std) {
			print_difference(*std, *ft);
			return false;
		}
		return (true);
	}

	template <class ft_itr, class std_itr>
		bool	compare_these_map_iterators_yo(ft_itr& ft, std_itr& std)
	{
		if ((*ft).first != (*std).first) {
			std::cout << "\ndifference in first value:\n";
			print_difference((*std).first, (*ft).first);
			return false;
		}
		if ((*ft).second != (*std).second) {
			std::cout << "\ndifference in second value\n";
			print_difference((*std).second, (*ft).second);
			return false;
		}
		return (true);
	}

	template < class ft_pair, class std_pair >
		bool	compare_these_pairs_yo(ft_pair& ft_pr, std_pair& std_pr)
	{
		if (compare_these_map_iterators_yo(ft_pr.first, std_pr.first) == false) {
			std::cout << "Difference in key\n";
			return (false);
		}
		if (compare_these_map_iterators_yo(ft_pr.second, std_pr.second) == false) {
			std::cout << "Difference in mapped type\n";
			return false;
		}
		return (true);
	}

	template <class ft_val, class std_val>
		bool	compare_these_values_yo(ft_val& ft, std_val& std)
	{
		if (ft != std) {
			print_difference(std, ft);
			return false;
		}
		return (true);
	}


	template < class ft_pair, class std_pair >
		bool	compare_these_iterator_pairs_yo(ft_pair& ft_pr, std_pair& std_pr)
	{
		if (compare_these_values_yo(*(ft_pr.first), *(std_pr.first)) == false) {
			std::cout << "Difference in key\n";
			return (false);
		}
		if (compare_these_values_yo(*(ft_pr.second), *(std_pr.second)) == false) {
			std::cout << "Difference in mapped type\n";
			return false;
		}
		return (true);
	}


	bool		compare_exceptions(std::string& ft_exc, std::string& std_exc);

////////////////////////
// Leaky bois utility //
////////////////////////
template < class T >
	void run_leaks(T argc, char** argv)
{
	(void)argc;
	#ifndef DEBUG
		std::cout << std::endl;
		std::string name(argv[0]);
		name.erase(0, name.rfind("/") + 1);
		std::string leaks(std::string("leaks ") + name + " | grep 'leaks for'");
		system(leaks.c_str());
	#endif
}

///////////////////
// Class utility //
///////////////////

	class Timer
	{
		private:
			struct timeval	_time;
			size_t			_duration;
			size_t			_total_time;
			size_t			_started_time;

		public:
			Timer();
			~Timer(){}
			
			void		reset_timer();
			void		start_timer();
			size_t		end_timer();
			size_t		end_reset();
			size_t		get_total_time();
			void		end_and_print(const char* msg);
			std::string	end_and_format(const char* msg);
			std::string	format_time(size_t& time, const char * msg);

	}; /* end of timer class */
	
	struct test
	{
		private: 
			int			_val;
			std::string	_name;

		public:
			test(int val = 0, std::string name = "unknown");
			~test() {}

			bool	operator == (const test&x) {return (this->_val == x._val && this->_name == x._name);}

	}; /* end of test class */

///////////////////////
// Benchmark headers //
///////////////////////

void	print_benchmark_header(std::string prefix, std::string type);
void	print_benchmark_result(double&	ft_dur, double& std_dur, const char* type);
void	format_benchmark_result(std::vector< std::pair< std::string, size_t> >& ft_rs,\
								std::vector< std::pair< std::string, size_t> >& std_rs,\
								std::string container);


/////////////////////
// Test Prototypes //
/////////////////////

	void	vector_unit();
	void	vector_benchmark();
	void	deqtor_unit();
	void	deqtor_benchmark();
	void	map_unit();
	void	map_benchmark();
	void	set_unit();
	void	set_benchmark();

#endif
