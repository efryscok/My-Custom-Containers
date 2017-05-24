#pragma once

#include <functional>

namespace ef {
	// Node class
	template <typename _Kty>
	class _list_node {

	public: // Type definitions

		using value_type = _Kty;
		using pointer = _list_node<_Kty>*;

	public: // Member data

		pointer _Prev;
		pointer _Next;
		value_type _Value;

	public: // Constructors

		// Default constructor
		_list_node() : _Prev(nullptr), _Next(nullptr) {}

		// Copy constructor
		_list_node(_list_node<value_type> const& rhs) : _Prev(rhs._Prev), _Next(rhs._Next), _Value(rhs._Value) {}

		// Rvalue copy constructor
		_list_node(_list_node<value_type> && rhs) : _Prev(std::move(rhs._Prev)), _Next(std::move(rhs._Next)), _Value(std::move(rhs._value)) {}

		// Value constructor
		_list_node(value_type const& value) : _Prev(nullptr), _Next(nullptr), _Value(value) {}

		// Rvalue value constructor
		_list_node(value_type && value) : _Prev(nullptr), _Next(nullptr), _Value(std::move(value)) {}

	public: // Deconstructor

		~_list_node() {}

	public: // Member functions

		// Test if the current node has a next node
		bool hasNext() const { return _Next != nullptr; }

		// Test if the current node has a previous node
		bool hasPrev() const { return _Prev != nullptr; }

	public: // Operator overloads

		// Relational operators
		bool operator ==(_list_node<value_type> const& rhs) { return _Value == rhs._Value; }
		bool operator <(_list_node<value_type> const& rhs) { return _Value < rhs._Value; }
		bool operator !=(_list_node<value_type> const& rhs) { return _Value != rhs._Value; }
		bool operator >(_list_node<value_type> const& rhs) { return _Value > rhs._Value; }
		bool operator <=(_list_node<value_type> const& rhs) { return _Value <= rhs._Value; }
		bool operator >=(_list_node<value_type> const& rhs) { return _Value >= rhs._Value; }
	};

	// Iterator class
	template <typename _Kty>
	class _list_iterator {

	public: // Type definitions

		using value_type = _Kty;
		using node_type = _list_node<_Kty>*;

	public: // Member data

		node_type _Nodeptr;

	public: // Constructors

		_list_iterator(node_type node) : _Nodeptr(node) {}

	public: // Destructor

		~_list_iterator() {}

	public: // Operator overloads

		// Pre-increment
		_list_iterator& operator ++() {
			_Nodeptr = _Nodeptr->_Next;
			return *this;
		}

		// Post-increment
		_list_iterator operator ++(int) {
			_list_iterator<value_type> beforeIT(_Nodeptr);
			_Nodeptr = _Nodeptr->_Next;
			return beforeIT;
		}

		// Pre-decrement
		_list_iterator& operator --() {
			_Nodeptr = _Nodeptr->_Prev;
			return *this;
		}

		// Post-decrement
		_list_iterator operator --(int) {
			_list_iterator<value_type> beforeIT(_Nodeptr);
			_Nodeptr = _Nodeptr->_Prev;
			return beforeIT;
		}

		// Dereference
		value_type operator *() { return _Nodeptr->_Value; }

		// Member access
		value_type* operator ->() { return &(_Nodeptr->_Value); }

		// Relational operators
		bool operator ==(_list_iterator<value_type> const& rhs) { return _Nodeptr == rhs._Nodeptr; }
		bool operator <(_list_iterator<value_type> const& rhs) { return _Nodeptr < rhs._Nodeptr; }
		bool operator !=(_list_iterator<value_type> const& rhs) { return _Nodeptr != rhs._Nodeptr; }
		bool operator >(_list_iterator<value_type> const& rhs) { return rhs._Nodeptr < _Nodeptr; }
		bool operator <=(_list_iterator<value_type> const& rhs) { return _Nodeptr <= rhs._Nodeptr; }
		bool operator >=(_list_iterator<value_type> const& rhs) { return _Nodeptr >= rhs._Nodeptr; }
	};

	// Reverse iterator class
	template <typename _Kty>
	class _list_reverse_iterator {

	public: // Type definitions

		using value_type = _Kty;
		using node_type = _list_node<_Kty>*;

	public: // Member data

		node_type _Nodeptr;

	public: // Constructors

		_list_reverse_iterator(node_type const& node) : _Nodeptr(node) {}

	public: // Deconstructors

		~_list_reverse_iterator() {}

	public: // Operator overloads

		// Pre-incrememnt
		_list_reverse_iterator& operator ++() {
			_Nodeptr = _Nodeptr->_Prev;
			return *this;
		}

		// Post-increment
		_list_reverse_iterator operator ++(int) {
			_list_reverse_iterator<value_type> before(_Nodeptr);
			_Nodeptr = _Nodeptr->_Prev;
			return before;
		}

		// Pre-decrement
		_list_reverse_iterator& operator --() {
			_Nodeptr = _Nodeptr->_Next;
			return *this;
		}

		// Post-decrement
		_list_reverse_iterator operator --(int) {
			_list_reverse_iterator<value_type> before(_Nodeptr);
			_Nodeptr = _Nodeptr->_Next;
			return before;
		}

		// Dereference
		value_type operator *() { return _Nodeptr->_Value; }

		// Member access
		value_type operator ->() { return &(_Nodeptr->_Value); }

		// Relational operators
		bool operator ==(_list_reverse_iterator<value_type> const& rhs) { return _Nodeptr == rhs._Nodeptr; }
		bool operator <(_list_reverse_iterator<value_type> const& rhs) { return _Nodeptr > rhs._Nodeptr; }
		bool operator !=(_list_reverse_iterator<value_type> const& rhs) { return _Nodeptr != rhs._Nodeptr; }
		bool operator >(_list_reverse_iterator<value_type> const& rhs) { return _Nodeptr < rhs._Nodeptr; }
		bool operator <=(_list_reverse_iterator<value_type> const& rhs) { return _Nodeptr >= rhs._Nodeptr; }
		bool operator >=(_list_reverse_iterator<value_type> const& rhs) { return _Nodeptr <= rhs._Nodeptr; }
	};
	
	// List class
	template <typename _Kty, typename _Pr = std::less<_Kty>>
	class list {

	public: // Type definitions

		using value_type = _Kty;
		using key_compare = _Pr;
		using size_type = size_t;
		using difference_type = ptrdiff_t;
		using const_reference = const _Kty&;
		using pointer = _list_node<_Kty>*;
		using const_pointer = _list_node<_Kty>* const;
		using iterator = _list_iterator<_Kty>;
		using const_iterator = iterator const;
		using reverse_iterator = _list_reverse_iterator<_Kty>;
		using const_reverse_iterator = reverse_iterator const;

	private: // Member data

		pointer _Begin;
		pointer _End;
		size_type _Size;
		key_compare _Cmp;

	public: // Constructors

		// Default constructor
		list(key_compare const& cmp = key_compare()) : _Begin(nullptr), _End(nullptr), _Size(0), _Cmp(cmp) {}

		// Copy constructor
		list(list<value_type> const& rhs, key_compare const& cmp = key_compare()) : _Begin(nullptr), _End(nullptr), _Size(0), _Cmp(cmp) {
			copy(rhs);
		}

		// Rvalue copy constructor
		list(list<value_type> && rhs, key_compare const& cmp = key_compare()) : _Begin(nullptr), _End(nullptr), _Size(0), _Cmp(cmp) {
			copy(std::move(rhs));
			rhs.clear();
		}

		// Initializer list constructor
		list(std::initializer_list<value_type> init, key_compare const& cmp = key_compare()) : _Begin(nullptr), _End(nullptr), _Size(0), _Cmp(cmp) {
			insert(init.begin(), init.end());
		}

		// Iterator constructor
		template <typename IT>
		list(IT first, IT last, key_compare const& cmp = key_compare()) : _Begin(nullptr), _End(nullptr), _Size(0), _Cmp(cmp) {
			insert(first, last);
		}

	public: // Destructor

		~list() { destroyList(); }

	public: // Member functions

		// Iterators
		iterator begin() { return iterator((_Begin != nullptr && _Begin->_Next) ? _Begin->_Next : _Begin); }
		iterator end() { return iterator(_End); }
		const_iterator begin() const { return const_iterator((_Begin != nullptr && _Begin->_Next) ? _Begin->_Next : _Begin); }
		const_iterator end() const { return const_iterator(_End); }
		reverse_iterator rbegin() { return reverse_iterator((_End != nullptr && _End->_Prev) ? _End->_Prev : _End); }
		reverse_iterator rend() { return reverse_iterator(_Begin); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator((_End != nullptr && _End->_Prev) ? _End->_Prev : _End); }
		const_reverse_iterator rend() const { return const_reverse_iterator(_Begin); }
		const_iterator cbegin() const { return const_iterator((_Begin != nullptr && _Begin->_Next) ? _Begin->_Next : _Begin); }
		const_iterator cend() const { return const_iterator(_End); }
		const_reverse_iterator crbegin() const { return const_reverse_iterator((_End != nullptr && _End->_Prev) ? _End->_Prev : _End); }
		const_reverse_iterator crend() const { return const_reverse_iterator(_Begin); }

		// Capacity
		bool empty() const { return begin() == end(); }
		size_type size() const { return _Size; }
		size_type count(value_type const& value) {
			iterator valueIT = find(value);
			size_type count = 0;
			if (valueIT == end()) {
				return count;
			}
			while (*valueIT == value) {
				++count;
				++valueIT;
			}
			return count;
		}

		// Accessors
		const_reference front() const { return begin()->_Next->_Value; }
		const_reference back() const { return end()->_Prev->_Value; }
		iterator find(value_type const& value) {
			// Empty
			if (begin() == nullptr) {
				return iterator(_End);
			}

			// Value less than first node
			pointer searchNode = _Begin;
			if (_Cmp(value, searchNode->_Value)) {
				return end();
			}
			else if (value == searchNode->_Value) {
				return iterator(searchNode);
			}
			else { // Value is > node value
				while (searchNode != _End && searchNode->_Next != nullptr && _Cmp(searchNode->_Value, value)) {
					searchNode = searchNode->_Next;
				}

				if (_Cmp(value, searchNode->_Value)) {
					return end();
				}

				if (value == searchNode->_Value) {
					return iterator(searchNode);
				}

				return end(); // Value not found
			}
		}
		std::pair<iterator, iterator> equal_range(value_type const& value) {
			iterator first = find(value);
			if (first == end()) {
				return std::make_pair(end(), end());
			}
			iterator second = first;
			while (*second == value) {
				second++;
			}
			return std::make_pair(first, second);
		}

		// Mutators
		template <typename IT>
		void insert(IT first, IT last) {
			while (first != last) {
				insert((value_type)*first++);
			}
		}
		void insert(value_type const& value) {
			pointer newNode = new _list_node<value_type>(value);

			// Empty - new node is the beginning
			if (_Begin == _End) {
				_Begin = new _list_node<value_type>();
				_End = new _list_node<value_type>();
				_Begin->_Next = newNode;
				newNode->_Prev = _Begin;
				newNode->_Next = _End;
				_End->_Prev = newNode;
				++_Size;
				return;
			}

			// Replace first node - new node is the beginning
			pointer it = _Begin->_Next;
			if (_Cmp(newNode->_Value, it->_Value)) {
				it->_Prev = newNode;
				newNode->_Next = it;
				_Begin->_Next = newNode;
				newNode->_Prev = _Begin;
				it = newNode;
				++_Size;
				return;
			}

			// Traverse nodes - find insertion point
			while (it->hasNext() && !(_Cmp(newNode->_Value, it->_Next->_Value)) && it->_Next != _End) {
				it = it->_Next;
			}

			// Found a following node
			if (it->hasNext()) {
				newNode->_Next = it->_Next;
				(it->_Next)->_Prev = newNode;
			}

			// Place new node in list
			newNode->_Prev = it;
			it->_Next = newNode;
			++_Size;
			return;
		}
		void insert(value_type && value) {
			pointer newNode = new _list_node<value_type>(std::move(value));

			// Empty - new node is the beginning
			if (_Begin == _End) {
				_Begin = new _list_node<value_type>();
				_End = new _list_node<value_type>();
				_Begin->_Next = newNode;
				newNode->_Prev = _Begin;
				newNode->_Next = _End;
				_End->_Prev = newNode;
				++_Size;
				return;
			}

			// Replace first node - new node is the beginning
			pointer it = _Begin->_Next;
			if (_Cmp(newNode->_Value, it->_Value)) {
				it->_Prev = newNode;
				newNode->_Next = it;
				_Begin->_Next = newNode;
				newNode->_Prev = _Begin;
				it = newNode;
				++_Size;
				return;
			}

			// Traverse nodes - find insertion point
			while (it->hasNext() && !(_Cmp(newNode->_Value, it->_Next->_Value)) && it->_Next != _End) {
				it = it->_Next;
			}

			// Found a following node
			if (it->hasNext()) {
				newNode->_Next = it->_Next;
				(it->_Next)->_Prev = newNode;
			}

			// Place new node in list
			newNode->_Prev = it;
			it->_Next = newNode;
			++_Size;
			return;
		}
		void insert(std::initializer_list<value_type> const& init) {
			insert(init.begin(), init.end());
		}
		void erase(const_iterator location) {
			pointer erased = location._Nodeptr;
			pointer pulledNode = erased->_Next;

			// Erasing end Node
			if (pulledNode == _End && erased->_Prev == _Begin) {
				clear();
				return;
			}
			else {
				value_type nValue = erased->_Value;
				pointer it = _Begin->_Next;

				// Determine which node has the value
				iterator searchIT = find(nValue);
				while (*searchIT == nValue) {
					// Found node in list
					if (searchIT._Nodeptr == erased) {
						searchIT = nullptr;
						break;
					}
					++searchIT;
				}
			}

			// Check for previous node to reference the pulled node
			if (erased->_Prev != nullptr) {
				erased->_Prev->_Next = pulledNode;
				pulledNode->_Prev = erased->_Prev;
			}

			// Clean up the erased node
			delete erased;
			--_Size;
		}
		iterator erase(const_iterator first, const_iterator last) {
			iterator it = first;
			iterator helperNode = it;
			while (it != last) {
				++helperNode;
				erase(it);
				it = helperNode;
			}
			return last;
		}
		size_type erase(value_type const& value) {
			iterator beginIterator = find(value);
			size_type returnCount = 0;
			if (beginIterator._Nodeptr == _End) {
				return returnCount;
			}
			while (*beginIterator == value) {
				iterator deletedIT = beginIterator++;
				erase(deletedIT);
				++returnCount;
			}
			return returnCount;
		}
		list<value_type>& swap(list<value_type>& rhs) {
			list<value_type> temp;

			// Begin
			temp._Begin = std::move(rhs._Begin);
			rhs._Begin = std::move(_Begin);
			_Begin = std::move(temp._Begin);

			// End
			temp._End = std::move(rhs._End);
			rhs._End = std::move(_End);
			_End = std::move(temp._End);

			// Count
			temp._Size = std::move(rhs._Size);
			rhs._Size = std::move(_Size);
			_Size = std::move(temp._Size);

			// Comparator
			temp._Cmp = std::move(rhs._Cmp);
			rhs._Cmp = std::move(_Cmp);
			_Cmp = std::move(temp._Cmp);

			return *this;
		}
		list<value_type>& copy(list<value_type> const& item) {
			clear();
			insert(item.begin(), item.end());
			return *this;
		}
		void clear() {
			if (_Begin != _End) {
				destroyList();
			}
			_Begin = _End = nullptr;
			_Size = 0;
		}

		// Operators
		list<value_type>& operator =(list<value_type> const& rhs) {
			clear();
			copy(rhs);
			return *this;
		}
		list<value_type>& operator = (list<value_type> && rhs) {
			clear();
			swap(rhs);
			rhs.clear();
			return *this;
		}
		list<value_type>& operator =(std::initializer_list<value_type> const& init) {
			clear();
			insert(init.begin(), init.end());
			return *this;
		}
		bool operator ==(list<value_type> const& rhs) {
			if (size() != rhs.size()) {
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
		bool operator <(list<value_type> const& rhs) {
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
		bool operator !=(list<value_type> const& rhs) {
			return !(this == rhs);
		}
		bool operator >(list<value_type> const& rhs) {
			return rhs < this;
		}
		bool operator <=(list<value_type> const& rhs) {
			return !(this > rhs);
		}
		bool operator >=(list<value_type> const& rhs) {
			return !(this < rhs);
		}

	private: // Destructor

		void destroyList() {
			pointer eraser = _Begin;
			pointer temp = nullptr;
			while (eraser != nullptr && eraser->hasNext() && eraser != _End) {
				temp = eraser->_Next;
				delete eraser;
				eraser = temp;
				temp = nullptr;
			}
			delete eraser;
		}

	};
}