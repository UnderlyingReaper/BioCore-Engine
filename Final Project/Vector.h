#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

template <typename T>
class Vector
{
private:
	int _capacity;
	int _size;
	T* _pointer;

public:
	Vector() : _size(0), _capacity(0), _pointer(nullptr) {}
	Vector(int capacity) : _size(0), _capacity(capacity)
	{
		if (capacity < 0)
			throw "Vector capacity cannot be negative.";

		_pointer = new T[_capacity] {};
	}
	Vector(const Vector& other) : _size(other._size), _capacity(other._capacity)
	{
		_pointer = new T[_capacity];

		for (int i = 0; i < _size; i++)
			_pointer[i] = other._pointer[i];
	}

	Vector& operator= (const Vector& other)
	{
		if (this != &other)
		{
			if (_capacity < other._size)
			{
				delete[] _pointer;
				_capacity = other._capacity;
				_pointer = new T[_capacity];
			}

			_size = other._size;
			for (int i = 0; i < _size; i++)
				_pointer[i] = other._pointer[i];
		}

		return *this;
	}

	~Vector()
	{
		delete[] _pointer;
	}

	T& operator[](int index) { return _pointer[index]; }
	const T& operator[](int index) const { return _pointer[index]; }

	friend bool operator== (const Vector& a, const Vector& b)
	{
		if (a._size != b._size) return false;

		for (int i = 0; i < a._size; i++)
		{
			if (a._pointer[i] != b._pointer[i])
				return false;
		}

		return true;
	}
	friend bool operator!= (const Vector& a, const Vector& b) { return !(a == b); }
	friend bool operator< (const Vector& a, const Vector& b)
	{
		int minSize = (a._size < b._size) ? a._size : b._size;
		for (int i = 0; i < minSize; i++)
		{
			if (a._pointer[i] < b._pointer[i]) return true;
			if (a._pointer[i] > b._pointer[i]) return false;
		}
		return a._size < b._size;
	}
	friend bool operator<= (const Vector& a, const Vector& b) { return (a < b) || (a == b); }
	friend bool operator> (const Vector& a, const Vector& b) { return !(a <= b); }
	friend bool operator>= (const Vector& a, const Vector& b) { return !(a < b); }

	void Assign(int count, T value)
	{
		if (count < 0)
			throw "Cannot assign a negative number of elements.";

		Reserve(count);
		for (int i = 0; i < count; i++)
			_pointer[i] = value;
		_size = count;
	}
	void Reserve(int amt)
	{
		if (amt < 0)
			throw "Cannot reserve a negative capacity.";

		if (amt <= _capacity) return;

		T* newPointer = new T[amt];
		for (int i = 0; i < _size; i++)
			newPointer[i] = _pointer[i];

		delete[] _pointer;
		_pointer = newPointer;
		_capacity = amt;
	}

	void ShrinkToFit()
	{
		if (_size == 0)
		{
			_capacity = 0;
			delete[] _pointer;
			_pointer = nullptr;
			return;
		}
		if (_size == _capacity) return;

		T* newPointer = new T[_size];

		for (int i = 0; i < _size; i++)
			newPointer[i] = _pointer[i];

		delete[] _pointer;
		_pointer = newPointer;
		_capacity = _size;
	}
	void Clear() { _size = 0; }
	void Erase(int index)
	{
		if (index < 0 || index >= _size)
			throw "Index out of bounds.";

		for (int i = index; i < _size - 1; i++)
			_pointer[i] = _pointer[i + 1];
		_size--;
	}

	void PushBack(T val)
	{
		if (_capacity == _size)
		{
			int newCapacity = (_capacity == 0) ? 1 : _capacity * 2;
			Reserve(newCapacity);
		}

		_pointer[_size] = val;
		_size++;
	}
	void AppendRange(const Vector& other)
	{
		Reserve(_size + other._size);

		for (int i = 0; i < other._size; i++)
			_pointer[_size + i] = other._pointer[i];
		_size += other._size;
	}
	void PopBack()
	{
		if (_size == 0)
			throw "Cannot pop from an empty vector.";

		_size--;
	}
	void Resize(int amt)
	{
		if (amt < 0)
			throw "Cannot resize to a negative size.";

		if (amt > _size)
		{
			if (amt > _capacity) Reserve(amt);

			for (int i = _size; i < amt; i++)
				_pointer[i] = T();

			_size = amt;
		}
		else if (amt < _size)
			_size = amt;
	}
	void Swap(Vector& other)
	{
		int tempCapacity = _capacity;
		int tempSize = _size;
		T* tempPointer = _pointer;

		_capacity = other._capacity;
		_size = other._size;
		_pointer = other._pointer;

		other._capacity = tempCapacity;
		other._size = tempSize;
		other._pointer = tempPointer;
	}

	T At(int index) const
	{
		if (index < 0 || index >= _size)
			throw "Index out of bounds.";

		return _pointer[index];
	}

	T Front() const
	{
		if (_size == 0) throw "Vector is empty.";
		return _pointer[0];
	}
	T Back() const
	{
		if (_size == 0) "Vector::Back - Vector is empty.";
		return _pointer[_size - 1];
	}

	bool Empty() const { return _size == 0; }
	int Size() const { return _size; }
	int MaxSize() const { return _capacity; }
	int Capacity() const { return _capacity; }

	void Insert(int index, T val)
	{
		if (index < 0 || index > _size)
			throw "Index out of bounds.";

		if (_size == _capacity)
		{
			Reserve((_capacity == 0) ? 1 : _capacity * 2);
		}

		for (int i = _size; i > index; i--)
		{
			_pointer[i] = _pointer[i - 1];
		}

		_pointer[index] = val;
		_size++;
	}

	int Find(T val) const
	{
		for (int i = 0; i < _size; i++)
		{
			if (_pointer[i] == val)
				return i;
		}
		return -1;
	}
	bool Contains(T val) const
	{
		return Find(val) != -1;
	}

	T* Begin() { return _pointer; }
	T* End() { return _pointer + _size; }
	const T* Begin() const { return _pointer; }
	const T* End() const { return _pointer + _size; }
};

#endif // !VECTOR_H