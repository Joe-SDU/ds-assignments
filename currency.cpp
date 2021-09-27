#include <iostream>
#include "currency.h"
#include "exception_class.h"

currency::currency(signType theSign, unsigned long theDollars, unsigned int theCents)
{
	setValue(theSign, theDollars, theCents);
}

void currency::setValue(signType theSign, unsigned long theDollars, unsigned int theCents)
{
	if (theCents > 99) throw illegalParameterValue("cents should be < 100");
	sign = theSign;
	dollars = theDollars;
	cents = theCents;
}

void currency::setValue(double theAmount)
{
	if (theAmount < 0)
	{
		sign = minus;
		theAmount = -theAmount;
	}

	dollars = static_cast<unsigned long>(theAmount);
	cents = static_cast<unsigned int>((theAmount + 0.001 - dollars) * 100);
}

currency currency::add(const currency& x) const
{
	long a1, a2, a3; // 此处为何要用long?

	a1 = dollars * 100 + cents;
	if (sign == minus) a1 = -a1;

	a2 = x.dollars * 100 + x.cents;
	if (x.sign == minus) a2 = -a2;

	a3 = a1 + a2;
	
	currency res;
	
	if (a3 < 0)
	{
		res.sign = minus;
		a3 = -a3;
	}
	res.dollars = a3 / 100;
	res.cents = a3 - res.dollars * 100;

	return res;
}

currency& currency::increment(const currency& x)
{
	*this = add(x);
	return *this;
}

std::ostream& currency::output(std::ostream& os) const &
{
	if (sign == minus) os << '-';
	os << dollars << '.';
	if (cents < 10) os << '0';
	os << cents;
	return os;
}

void currency::input(std::istream& is)
{
	double x;
	is >> x;
	setValue(x);
}

currency currency::subtract(const currency& x) const
{
	return add(x.multiply(-1));
}

currency currency::percent(double x) const
{
	return multiply(x / 100);
}

currency currency::multiply(double x) const
{
	double money = dollars + static_cast<double>(cents) / 100;
	currency res;
	res.setValue(money * x);
	return res;
}

currency currency::divide(double x) const
{
	double tmp = 1.0 / x;
	return multiply(tmp);
}