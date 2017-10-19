#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class bool_ext
{
private:
	bool value;
public:
	bool_ext()
	{
		value = 0;
	}
	bool_ext(const bool_ext &c)
	{
		value = c.value;
	}
	bool_ext(bool a) : value(a)
	{}

	//unary
	friend const bool_ext operator -(const bool_ext& a);

	//binary
	friend const bool_ext operator +(const bool_ext, const bool_ext right); // +
	friend const bool_ext operator ^(const bool_ext& left, const bool_ext& right); // xor
	friend const bool_ext operator /(const bool_ext& left, const bool_ext& right); // Шеффер
	friend const bool_ext operator *(const bool_ext& left, const bool_ext& right); // 
	friend const bool_ext operator |(const bool_ext& left, const bool_ext& right); // PEIRCE
	friend const bool_ext operator >(const bool_ext& left, const bool_ext& right); // Импликация
	friend bool operator==(const bool_ext& left, const bool_ext& right);
	friend ostream & operator << (ostream & out, const bool_ext & a);
	// stream

	friend ostream & operator << (ostream & out, const bool_ext & a)
	{
		out << a.value;
		return out;
	}



	// =============	
	friend const bool_ext operator -(const bool_ext& a)
	{
		return  !a.value;
	}
	// =============
	const bool_ext& operator =(const bool_ext &a)
	{
		value = a.value;
		return (*this);
	}
	friend bool operator==(const bool_ext& left, const bool_ext& right)
	{
		return left.value == right.value;
	}
	friend const bool_ext operator *(const bool_ext& left, const bool_ext& right)
	{
		return left.value&&right.value;
	}
	friend const  bool_ext operator +(const bool_ext left, const bool_ext right)
	{
		return left.value || right.value;
	}
	friend const bool_ext operator ^(const bool_ext& left, const bool_ext& right) // XOR
	{
		return left.value^right.value;
	}
	friend const bool_ext operator /(const bool_ext& left, const bool_ext& right) // Шеффер 
	{
		return !left.value || !right.value;
	}
	friend const bool_ext operator |(const bool_ext& left, const bool_ext& right) // Пирс
	{
		return !left.value && !right.value;
	}
	friend const bool_ext operator >(const bool_ext& left, const bool_ext& right)
	{
		return !left.value || right.value;
	}
	friend const bool_ext operator <(const bool_ext& left, const bool_ext& right)
	{
		return (left.value || !right.value);
	}
};