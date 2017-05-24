#pragma once

#include <functional>

namespace ef {
	// Iterator class
	template <typename _Kty>
	class _vector_iterator {
		 
	public: // Type definitions

		using value_type = _Kty;
		using value_ptr = _Kty*;

	public: // Member data

		value_ptr _Valueptr;

	public: // Constructor

		_vector_iterator(value_ptr value) : _Valueptr(value) {}

	public: // Destructor

		~_vector_iterator() {}

	public: // Member functions

		// Pre-increment
		_vector_iterator& operator ++() {
			++_Valueptr;
			return *this;
		}

		// Post-increment
		_vector_iterator operator ++(int) {
			_vector_iterator<value_type> beforeIT(_Valueptr++);
			return beforeIT;
		}

		// Pre-decrement
		_vector_iterator& operator --() {
			--_Valueptr;
			return *this;
		}

		// Post-decrement
		_vector_iterator operator --(int) {
			_vector_iterator<value_type> beforeIT(_Valueptr--);
			return beforeIT;
		}

		// Dereference
		value_type operator *() {
			return *_Valueptr;
		}

		// Member access
		value_ptr operator ->() {
			return _Valueptr;
		}

		// Relational operators
		bool operator ==(_vector_iterator<value_type> const& rhs) { return _Valueptr == rhs._Valueptr; }
		bool operator <(_vector_iterator<value_type> const& rhs) { return _Valueptr < rhs._Valueptr; }
		bool operator !=(_vector_iterator<value_type> const& rhs) { return _Valueptr != rhs._Valueptr; }
		bool operator >(_vector_iterator<value_type> const& rhs) { return _Valueptr > rhs._Valueptr; }
		bool operator <=(_vector_iterator<value_type> const& rhs) { return _Valueptr <= rhs._Valueptr; }
		bool operator >=(_vector_iterator<value_type> const& rhs) { return _Valueptr >= rhs._Valueptr; }
	};

	// Reverse iterator class
	template <typename _Kty>
	class _vector_reverse_iterator {

	public: // Type definitions

		using value_type = _Kty;
		using value_ptr = _Kty*;

	public: // Member data

		value_ptr _Valueptr;

	public: // Constructor

		_vector_reverse_iterator(value_ptr value) : _Valueptr(value) {}

	public: // Destructor

		~_vector_reverse_iterator() {}

	public: // Operator overloads

		// Pre-increment
		_vector_reverse_iterator& operator ++() {
			--_Valueptr;
			return *this;
		}

		// Post-increment
		_vector_reverse_iterator operator ++(int) {
			_vector_reverse_iterator<value_type> beforeIT(_Valueptr--);
			return beforeIT;
		}

		// Pre-decrement
		_vector_reverse_iterator& operator --() {
			++_Valueptr;
			return *this;
		}

		// Post-decrement
		_vector_reverse_iterator operator --(int) {
			_vector_reverse_iterator<value_type> beforeIT(_Valueptr++);
			return beforeIT;
		}

		// Dereference
		value_type operator *() {
			return *_Valueptr;
		}

		// Member access
		value_ptr operator ->() {
			return _Valueptr;
		}

		// Relational operators
		bool operator ==(_vector_reverse_iterator<value_type> const& rhs) { return _Valueptr == rhs._Valueptr; }
		bool operator <(_vector_reverse_iterator<value_type> const& rhs) { return _Valueptr > rhs._Valueptr; }
		bool operator !=(_vector_reverse_iterator<value_type> const& rhs) { return _Valueptr != rhs._Valueptr; }
		bool operator >(_vector_reverse_iterator<value_type> const& rhs) { return _Valueptr < rhs._Valueptr; }
		bool operator <=(_vector_reverse_iterator<value_type> const& rhs) { return _Valueptr >= rhs._Valueptr; }
		bool operator >=(_vector_reverse_iterator<value_type> const& rhs) { return _Valueptr <= rhs._Valueptr; }
	};

	// Vector class
	template <typename _Kty, typename _Pr = std::less<_Kty>>
	class vector {

	public: // Type definitions

		using value_type = _Kty;
		using key_compare = _Pr;
		using size_type = size_t;
		using pointer = _Kty*;
		using const_reference = _Kty const&;
		using iterator = _vector_iterator<value_type>;
		using const_iterator = iterator const;
		using reverse_iterator = _vector_reverse_iterator<value_type>;
		using const_reverse_iterator = reverse_iterator const;

	private: // Member data

		pointer _Dataptr;
		size_type _Size;
		size_type _Cap;
		key_compare _Cmp;

	public: // Constructors

		// Default constructor
		vector(key_compare const& cmp = key_compare()) : _Dataptr(nullptr), _Size(0), _Cap(0), _Cmp(cmp) {}

		// Copy constructor
		vector(vector<value_type> const& rhs, key_compare const& cmp = key_compare()) : _Dataptr(nullptr), _Size(0), _Cap(0), _Cmp(cmp) {
			copy(rhs);
		}

		// Rvalue copy constructor
		vector(vector<value_type> && rhs, key_compare const& cmp = key_compare()) : _Dataptr(nullptr), _Size(0), _Cap(0), _Cmp(cmp) {
			copy(std::move(rhs));
			rhs.clear();
		}

		// Initializer list constructor
		vector(std::initializer_list<value_type> init, key_compare const& cmp = key_compare()) : _Dataptr(nullptr), _Size(0), _Cap(0), _Cmp(cmp) {
			push_back(init.begin(), init.end());
		}

		// Iterator constructor
		template <typename IT>
		vector(IT first, IT last, key_compare const& cmp = key_compare()) : _Dataptr(nullptr), _Size(0), _Cap(0), _Cmp(cmp) {
			push_back(first, last);
		}

	public: // Deconstructor

		~vector() { clear(); }

	public: // Member functions

		// Iterators
		iterator begin() { return iterator(_Dataptr); }
		iterator end() { return iterator(_Dataptr + _Size); }
		const_iterator begin() const { return const_iterator(_Dataptr); }
		const_iterator end() const { return const_iterator(_Dataptr + _Size); }
		reverse_iterator rbegin() { return reverse_iterator(_Dataptr + _Size - 1); }
		reverse_iterator rend() { return reverse_iterator(_Dataptr - 1); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(_Dataptr + _Size - 1); }
		const_reverse_iterator rend() const { return const_reverse_iterator(_Dataptr - 1); }
		const_iterator cbegin() const { return const_iterator(_Dataptr); }
		const_iterator cend() const { return const_iterator(_Dataptr + _Size); }
		const_reverse_iterator crbegin() const { return const_reverse_iterator(_Dataptr + _Size - 1); }
		const_reverse_iterator crend() const { return const_reverse_iterator(_Dataptr - 1); }

		// Capacity
		bool empty() const { return _Size == 0; }
		size_type size() const { return _Size; }
		size_type capacity() const { return _Cap; }

		// Accessors
		const_reference front() const { return *(_Dataptr); }
		const_reference back() const { return *(_Dataptr + _Size - 1); }
		iterator find(value_type const& value) {
			// Find the first instance of the value
			for (iterator it = begin(); it != end(); ++it) {
				if (*it == value) {
					return it;
				}
			}

			// Not found
			return iterator(_Dataptr + _Size);
		}
		value_type& at(size_type pos) {	return _Dataptr[pos]; }

		// Mutators
		template <typename IT>
		void push_back(IT first, IT last) {
			while (first != last) {
				push_back((value_type)*first++);
			}
		}
		void push_back(value_type value) {
			// Is the next index >= size of the data
			if (_Size >= _Cap) {
				size_type newSize = (_Cap == 0) ? 1 : _Cap * 2;
				_Reallocate(newSize);
			}

			// We have enough space, so "insert"
			_Dataptr[_Size] = value;

			// Set "next" location
			++_Size;
		}
		void clear() {
			if (_Dataptr != nullptr) {
				delete[] _Dataptr;
			}
			_Dataptr = nullptr;
			_Size = 0;
			_Cap = 0;
		}
		void sort() {
			std::sort(_Dataptr, _Dataptr + _Size);
		}
		vector<value_type>& copy(vector<value_type> const& item) {
			clear();
			_Reallocate(item.capacity());
			push_back(item.begin(), item.end());
			return *this;
		}
		vector<value_type>& swap(vector<value_type>& rhs) {
			vector<value_type> temp;

			// Dataptr
			temp._Dataptr = std::move(rhs._Dataptr);
			rhs._Dataptr = std::move(_Dataptr);
			_Dataptr = std::move(temp._Dataptr);

			// Size
			temp._Size = std::move(rhs._Size);
			rhs._Size = std::move(_Size);
			_Size = std::move(temp._Size);

			// Cap
			temp._Cap = std::move(rhs._Cap);
			rhs._Cap = std::move(_Cap);
			_Cap = std::move(temp._Cap);

			// Cmp
			temp._Cmp = std::move(rhs._Cmp);
			rhs._Cmp = std::move(_Cmp);
			_Cmp = std::move(temp._Cmp);

			return *this;

		}

		// Operator overloads
		vector<value_type>& operator =(vector<value_type> const& rhs) {
			clear();
			copy(rhs);
			return *this;
		}
		vector<value_type>& operator =(vector<value_type> && rhs) {
			clear();
			swap(rhs);
			rhs.clear();
			return *this;
		}
		vector<value_type>& operator =(std::initializer_list<value_type> const& init) {
			clear();
			push_back(init.begin(), init.end());
			return *this;
		}
		bool operator ==(vector<value_type> const& rhs) {
			if (_Size != rhs.size()) {
				return false;
			}

			iterator lhsIT = begin();
			iterator rhsIT = rhs.begin();
			while (lhsIT != end() && rhsIT != rhs.end()) {
				if ((*lhsIT++) != (*rhsIT++)) {
					return false;
				}
			}

			return true;
		}
		bool operator <(vector<value_type> const& rhs) {
			iterator lhsIT = begin();
			iterator rhsIT = rhs.begin();

			while (lhsIT != end() && rhsIT != rhs.end()) {
				if (*lhsIT < *rhsIT) {
					return true;
				}
				if (*lhsIT > *rhsIT) {
					return false;
				}
				++lhsIT;
				++rhsIT;
			}

			if (lhsIT == end() && rhsIT != rhs.end()) {
				return true;
			}

			return false;
		}
		bool operator !=(vector<value_type> const& rhs) {
			return !(this == rhs);
		}
		bool operator >(vector<value_type> const& rhs) {
			return rhs < this;
		}
		bool operator <=(vector<value_type> const& rhs) {
			return !(this > rhs);
		}
		bool operator >=(vector<value_type> const& rhs) {
			return !(this < rhs);
		}
		value_type& operator[] (size_type pos) { return at(pos); }
	private: 

		void _Reallocate(size_type newSize) {
			// Allocate new amount of data
			pointer newData = new value_type[newSize];

			// Copy old data to new location
			if (_Dataptr != nullptr) {
				for (int i = 0; i < _Cap; ++i) {
					newData[i] = _Dataptr[i];
				}

				// Delete old location (array)
				delete[] _Dataptr;

			}

			// Point the data pointer to new location
			_Dataptr = newData;

			// Clean up - how big things now are...
			_Cap = newSize;
		}
	};
}