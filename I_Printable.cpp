#include "I_Printable.hpp"

std::ostream& operator<<(std::ostream& os, const I_Printable& rhs){
	rhs.print(os);
	return os;
}