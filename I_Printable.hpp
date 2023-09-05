#pragma once
#include <iostream>
#include <vector>

class I_Printable {
	friend std::ostream& operator<<(std::ostream& os, const I_Printable& rhs);
public:
	virtual void print(std::ostream& os) const = 0;
	virtual void show(const std::vector<I_Printable>&) const = 0;
	virtual void show(const std::vector<I_Printable>&, std::string) const = 0;
	virtual std::string get_group() const = 0;

	// comment
};