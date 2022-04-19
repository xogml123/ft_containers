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
# include <fadey.hpp>
# include <sstream>

void	print_header(std::string header)
{
	int width = 82;
	int padding = (width - header.length()) / 2;
	std::stringstream	hdr;

	hdr << "\n┌" << std::setw(width) << std::setfill('-') << "┐\n";
	hdr << "│" << std::setw(padding + header.length()) << std::setfill(' ') << header << std::setw(padding + (width - header.length()) % 2) << std::setfill(' ') << "│\n";
	hdr << "└" << std::setw(width) << std::setfill('-') << "┘\n";
	
	km::fadey << hdr.str() << "\n";
}

void	start_test(std::string name, void(*func)())
{
	std::cout << COLOR_YELLOW << std::right << std::setw(15) << name << COLOR_RESET << ": ";
	func();
	std::cout << "\n";
}

bool compare_exceptions(std::string& ft_exc, std::string& std_exc)
{
	if (ft_exc != std_exc) {
		print_difference(std_exc, ft_exc);
		return false;
	}
	else
		return true;
}

///////////
// Timer //
///////////
Timer::Timer() : _duration(0), _total_time(0), _started_time(0) {}

void Timer::reset_timer()
{
	_duration = 0;
}

void Timer::start_timer()
{
	gettimeofday(&_time, NULL);
	_started_time = (_time.tv_sec * 1000 * 1000) + _time.tv_usec;
}

size_t Timer::end_timer()
{
	gettimeofday(&_time, NULL);
	_duration += ((_time.tv_sec * 1000 * 1000) + _time.tv_usec) - _started_time;
	_total_time += _duration;
	return (_duration);
}

size_t Timer::end_reset()
{
	size_t duration = this->end_timer();
	this->reset_timer();
	return (duration);
}

size_t	Timer::get_total_time()
{
	return (_total_time);
}

////////////////
// Test class //
////////////////

test::test(int val, std::string name) 
	: _val(val), _name(name) 
{
}
