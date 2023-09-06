#pragma once
#include <iostream>
#include <vector>

class I_Printable {
	friend std::ostream& operator<<(std::ostream& os, const I_Printable& rhs);
public:
	virtual void print(std::ostream& os) const = 0;
	~I_Printable() = default;
};