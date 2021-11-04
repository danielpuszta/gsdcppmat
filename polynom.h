#ifndef POLYNOM__H
#define POLYNOM__H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template<typename T>
class Polynom {

public:
	Polynom(std::vector<T>v = {});
	Polynom(const Polynom<T>& rhs) {
		_v = rhs.getVector();
	}

	std::string to_string();
	T eval(T t);
	size_t deg() const { return _v.size() > 0 ?_v.size() - 1 : 0; }
	T coeff(size_t i) const;
	std::string operator()(T t);
	std::ostream& operator<<(const Polynom& p);
	void push_back(T t)  { _v.push_back(t); }
	T& operator []   (const size_t idx)   {  return _v[idx]; } // for lvalue operand
	const T& operator []  (const size_t idx) const { return _v[idx]; } // for rvalue operand
	std::vector<T> getVector() const{ return _v; }

	

private:
	std::vector<T> _v;
	std::string coefficent(T n, int idx, size_t size);
	std::string coeffSigned(T n, int idx);
};

template<typename T>
Polynom<T>::Polynom(std::vector<T> v) : _v(v) {}

template<typename T>
std::string Polynom<T>::to_string() {
	size_t siz = _v.size();
	if (_v.empty() || 1 == siz && 0 == _v[0]) {
		return "0";
	}
	std::string res = "";
	for (size_t i = siz - 1; i > 0; --i) {
		if (_v[i] != 0) {
			res += coefficent(_v[i], i, siz);
		}
	}

	res += _v[0] > 0 ? ("+" + std::to_string(_v[0])) : std::to_string(_v[0]);
	return res;
}

template<typename T>
std::string Polynom<T>::coeffSigned(T t, int idx) {
	if (t > 0) {
		return "+" + std::to_string(t) + "X^" + std::to_string(idx);
	}
	else {
		return "-" + std::to_string(-t) + "X^" + std::to_string(idx);
	}
}

template<typename T>
std::string Polynom<T>::coefficent(T t, int idx, size_t size) {
	// X instead of X^1
	if (1 == idx) {
		return t > 0 ? "+" + std::to_string(t) + "X" : "-" + std::to_string(-t) + "X";
	}

	// first coefficient + is not needed
	if (size == 1 + idx && t > 0) {
		return std::to_string(t) + "X^" + std::to_string(idx);
	}
	return coeffSigned(t, idx);
}

template <typename T>
T Polynom<T>::eval(T t) {
	T res{ 0 };
	if (!_v.empty()) {

		for (size_t i = _v.size() - 1; i > 0; --i) {
			res += _v[i]; // ...+ai
			res *= t; // ...x*
		}
		res += _v[0];
	}
	return res;
}

template<typename T>
T Polynom<T>::coeff(size_t i) const{
	return _v[i];
}


template<typename T>
std::string Polynom<T>::operator()(T t) {
	return std::to_string(eval(t));
}

template<typename T>
std::ostream& Polynom<T>::operator<<(const Polynom& p){
	std::cout << to_string();	
	return *this;
}

template<typename T>
Polynom<T> operator+(const Polynom<T>& lhs, const Polynom<T>& rhs) {
	Polynom<T> tmp(lhs);
	size_t minSize = std::min(lhs.deg(), rhs.deg());
	for (size_t i = 0;i<minSize+1;++i){
		tmp[i] += rhs[i];
		
	}
	if (tmp.deg() > minSize) {
		// iterate remaining rhs
		for (size_t i = 1 + minSize; i < rhs.deg(); ++i) {
			tmp.push_back(rhs[i]);		
		}
	}
	return tmp;
}

template<typename T>
Polynom<T> operator-(const Polynom<T>& lhs, const Polynom<T>& rhs) {
	Polynom<T> tmp(lhs);
	size_t minSize = std::min(lhs.deg(), rhs.deg());
	for (size_t i = 0; i < minSize+1; ++i) {
		tmp[i] -= rhs[i];
	}
	if (tmp.size() > minSize) {
		// iterate remaining rhs
		for (size_t i = 1 + minSize; i < rhs.deg(); ++i) {
			tmp.push_back(rhs[i]);
		}
	}

	return tmp;
}



#endif // POLYNOM__H
