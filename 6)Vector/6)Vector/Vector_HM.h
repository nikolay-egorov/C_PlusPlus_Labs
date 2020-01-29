#pragma once
#include <stdexcept> 

using namespace std;
template <class T>
class  Vector_HM {
public:

	typedef const T* const_iterator;
	typedef T* iterator;
	Vector_HM();
	Vector_HM(size_t size);
	Vector_HM(size_t size, const T  initial);
	Vector_HM( Vector_HM<T>const & v ); // copy
	Vector_HM( Vector_HM<T>&& v) noexcept; //move

	~Vector_HM();

	inline	size_t capacity() const
	{
		return _capacity;
	}
	inline size_t size() const
	{
		return _size;
	}
	inline	bool empty() const {
		return _size == 0;
	}
	const_iterator begin() const;
	const_iterator end() const;
	T& front() const;
	T& back() const;
	iterator emplace(const_iterator position, T&& value);

	void push_back(const T& value);
	void pop_back();
	T & at(size_t pos);
	void reserve(size_t capacity);
	void resize(size_t size);

	T & operator[](size_t index);
	Vector_HM<T> & operator = (const Vector_HM<T> &);
	Vector_HM<T> & operator = ( Vector_HM<T> &&) noexcept;

	void clear();

	void swap( Vector_HM  & b);

	void emplace_back(T&& value);

private:
	size_t _size;
	
	size_t _capacity;
	
	size_t Log;
	T* buffer; //would it be a char ??
};

template<class T>
Vector_HM<T>::Vector_HM()
	: _size(0)
	, _capacity(0)
	, Log(0)
	, buffer(0)          
{}

template<class T>
Vector_HM<T>::Vector_HM( Vector_HM<T> const& v) {
	_size = v._size;
	Log = v.Log;
	_capacity = v._capacity;
	buffer = new T[_capacity];
	for (size_t i = 0; i < _capacity; i++)
		buffer[i] = v.buffer[i];
}
 
template<class T>
inline Vector_HM<T>::Vector_HM( Vector_HM<T>&& v) noexcept
	: _size(move(v._size))
	, _capacity(move(v._capacity))
	,Log(move(v.Log))
	,buffer(move(v.buffer))
{
	v.clear();

}

template<class T>
Vector_HM<T>::Vector_HM(size_t size) 
	: _size(size)
{	
	Log = ceil(log((double)size) / 0.301029996);
	_capacity = 1 << Log;
	buffer = new T[_capacity];
}

 
template<class T>
Vector_HM<T>::Vector_HM(size_t size, const T initial) {
	_size = size;
	Log = ceil(log((double)size) / 0.301029996);
	_capacity = 1 << Log;
	buffer = new T[_capacity];
	for (size_t i = 0; i < size; i++)
		buffer[i] = initial;
}

//UPD. exception questions solved
template<class T>
Vector_HM<T>& Vector_HM<T>::operator = ( Vector_HM<T> const& v) {
	if (this != &v)
	{
		Vector_HM<T> tmp(v);

		tmp.swap(*this);
		tmp.clear();
		/*
		delete[] buffer;
		_size = v._size;
		Log = v.Log;
		_capacity = v._capacity;
		buffer = new T[_capacity];
		for (size_t i = 0; i < _size; i++)
			buffer[i] = v.buffer[i];

			*/

	}
	return *this;
}

template<class T>
inline Vector_HM<T>& Vector_HM<T>::operator=( Vector_HM<T>&& v) noexcept
{
	v.swap(*this);
	return *this;
}

template<class T>
typename Vector_HM<T>::const_iterator Vector_HM<T>:: Vector_HM<T>::begin() const {
	return buffer;
}

template<class T>
typename Vector_HM<T>::const_iterator Vector_HM<T>::  Vector_HM<T>::end() const {
	return buffer + size();
}

template<class T>
T& Vector_HM<T>::front()  const {
	return buffer[0];
}

template<class T>
T& Vector_HM<T>::back() const {
	return buffer[_size - 1];
}

template<class T>
inline typename Vector_HM<T>::iterator Vector_HM<T>::emplace(const_iterator position, T && value)
{
	iterator iit = &buffer[position - buffer];
	if (_size >= _capacity) {
		reserve(1 << Log);
		Log++;
	}

	memmove(iit + 1, iit, (_size++ - (position - buffer)) * sizeof(T));
	(*iit) = std::move(std::forward<T>(value));

 
	return iit;
}

template<class T>
void Vector_HM<T>::push_back(const T & v) {
	
	if (_size >= _capacity) {
		reserve(1 << Log);
		Log++;
	}
	buffer[_size++] = v;
}

template<class T>
void Vector_HM<T>::pop_back() {
	if (!empty()) {

		(reinterpret_cast<T*>(buffer)[_size - 1]).~T();
		_size--;
	}
	else
		throw std::out_of_range("Empty inside");
}

template<class T>
inline T & Vector_HM<T>::at(size_t pos)
{
	if (pos >= _size)
		throw std::out_of_range("Out of order");
	return buffer[pos];
}

template<class T>
void Vector_HM<T>::reserve(size_t capacity) {
	T * newBuffer = new T[capacity];

	for (size_t i = 0; i < _size; i++)
		newBuffer[i] = buffer[i];

	_capacity = capacity;
	delete[] buffer;
	buffer = newBuffer;
}


template<class T>
void Vector_HM<T>::resize(size_t size) {
	Log = ceil(log((double)size) / 0.301029996);
	reserve(1 << Log);
	_size = size;
}

template<class T>
T& Vector_HM<T>::operator[](size_t index) {
	return buffer[index];
}



template<class T>
Vector_HM<T>::~Vector_HM() {
	delete[] buffer;
}

template <class T>
void Vector_HM<T>::clear() {
	
	for (size_t i = 0; i < _size-1; i++)
	{
		(reinterpret_cast<T*>(buffer)[i ]).~T();
	}
	_capacity = 0;
	_size = 0;
	buffer = 0;
	Log = 0;
}

template<class T>
inline void Vector_HM<T>::swap( Vector_HM  & b)
{
	 
	std::swap( this->_size, b._size);
	std::swap(this->_capacity, b._capacity);
	std::swap(this->Log, b.Log);
	std::swap(this->buffer, b.buffer);

	 
}

template<class T>
inline void Vector_HM<T>::emplace_back(T && value)
{
	if (_size >= _capacity) {
		reserve(1 << Log);
		Log++;
	}

  
	buffer[_size++] = move(std::forward<T>(value));

}
