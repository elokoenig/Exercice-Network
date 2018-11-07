#include "network.h"
#include "random.h"

void Network::resize(const size_t& newsize)
{
	values.clear();
	values.resize(newsize);
	RNG.normal(values);
}
    

bool Network::add_link(const size_t& a, const size_t& b)
{
	if ( a >= this->size() or b >= this->size() or a == b or (links.find(a)->first == a and links.find(b)->second == b) or (links.find(b)->first == b and links.find(b)->second == b) ) {
		return false;
	} else {
		links.insert({a,b});
		links.insert({b,a});
		return true;
	}
}


size_t Network::random_connect(const double& mean)
{
	for ( auto it = links.begin(); it != links.end(); ) {
		it = links.erase(it);
	}
	
	size_t i(0);
	for ( size_t n=0; n < this->size(); ++n ) {
		std::vector< int > links(RNG.poisson(mean));
		RNG.uniform_int(links, 0, this->size()-1);
		for ( auto other_n : links ) {
			if (add_link(n, other_n)); {
				++i;
			}
		}
	}
	return i;
}


size_t Network::set_values(const std::vector<double>& newvalues)
{
	size_t t = newvalues.size();
	size_t n(0);
	if ( t <= this->size() ) {
		for ( size_t i=0; i<t; ++i ) {
			values[i] = newvalues[i];
			++n;
		}
	} else {
		for ( size_t i=0; i<this->size(); ++i ) {
			values[i] = newvalues[i];
			++n;
		}
	}
	return n;
}


size_t Network::size() const
{
	return values.size();
}


size_t Network::degree(const size_t &_n) const
{
	size_t i(0);
	if ( _n < this->size() ) {
		for ( auto it : links ) {
			if ( it.first == _n ) {
				++i;
			}
		}
	}
	return i;
}


double Network::value(const size_t &_n) const
{
	if ( _n < this->size() ) {
		return values[_n];
	} else {
		return 0;
	}
}


std::vector<double> Network::sorted_values() const
{
	std::vector<double> valuestored = values;
	std::sort(valuestored.begin(), valuestored.end(), std::greater<double>());
    return valuestored;
}


std::vector<size_t> Network::neighbors(const size_t& n) const
{
	std::vector<size_t> linked_nodes;
	for ( auto it : links ) {
		if ( it.first == n ) {
			linked_nodes.push_back(it.second);
		}
	}
	return linked_nodes;
}




