#pragma once

#include <algorithm>

namespace ef {
	template <typename _Kty>
	class _map_node {

	public: // Type definitions

		using size_type = size_t;
		using value_type = _Kty;
		using value_ptr = value_type*;
		using node_ptr = _map_node<_Kty>*;

	public: // Member data

		int _Balance;
		size_type _Height;
		value_ptr _Valueptr;
		node_ptr _Parent;
		node_ptr _Left;
		node_ptr _Right;

	public: // Constructors

		// Default constructor
		_map_node() : _Valueptr(nullptr), _Parent(nullptr), _Left(nullptr), _Right(nullptr), _Height(1), _Balance(0) {}

		// Initialize constructor
		_map_node(value_type &v, _map_node &p, _map_node &l, _map_node &r) : _Valueptr(v), _Parent(p), _Left(l), _Right(r) {
			updateBalance();
		}

	public: // Member functions

		size_t leftHeight() {
			if (_Left != nullptr) {
				return _Left->_Height;
			}
			else {
				return 0;
			}
		}
		size_t rightHeight() {
			if (_Right != nullptr) {
				return _Right->_Height;
			}
			else {
				return 0;
			}
		}
		void updateBalance() {
			size_type lh = 0;
			size_type rh = 0;
			if (_Left != nullptr) {
				lh = _Left->_Height;
			}
			if (_Right != nullptr) {
				rh = _Right->_Height;
			}
			_Height = std::max(lh, rh) + 1;
			_Balance = (int)(lh - rh);
		}

	public: // Destructor

		~_map_node() {
			if (_Valueptr != nullptr) {
				delete _Valueptr;
			}
		}

	};

	template <typename _Kty>
	class _map_iterator {

	public: // Type definitions

		using value_type = _Kty;
		using value_ptr = _Kty*;
		using node_ptr = _map_node<_Kty>*;

	public: // Member data

		node_ptr _Nodeptr;

	public: // Constructors

		// Default constructor
		_map_iterator() :_Nodeptr(nullptr) {}

		// Value constructor
		_map_iterator(node_ptr node) :_Nodeptr(node) {}

		// Copy contructor
		_map_iterator(_map_iterator const& it) {
			_Nodeptr = it._Nodeptr;
		}

	public: // Destructor

		~_map_iterator() {}

	public: // Operator overloads

		_map_iterator& operator =(_map_iterator const& it) {
			_Nodeptr = it._Nodeptr;
			return *this;
		}
		
		// Pre-increment
		_map_iterator& operator ++() {
			if (_Nodeptr->_Right != nullptr) {
				_Nodeptr = _Nodeptr->_Right;
				while (_Nodeptr->_Left != nullptr) {
					_Nodeptr = _Nodeptr->_Left;
				}
			}
			else {
				node_ptr prevNode;
				do {
					prevNode = _Nodeptr;
					_Nodeptr = _Nodeptr->_Parent;
					if (_Nodeptr != nullptr && _Nodeptr->_Left == prevNode) {
						break;
					}
				} while (_Nodeptr->_Parent != nullptr);
			}
			return *this;
		}
		
		// Post-increment
		_map_iterator operator ++(int) {
			_map_iterator beforeIT = *this;
			if (_Nodeptr->_Right != nullptr) {
				_Nodeptr = _Nodeptr->_Right;
				while (_Nodeptr->_Left != nullptr) {
					_Nodeptr = _Nodeptr->_Left;
				}
			}
			else {
				node_ptr prevNode;
				do {
					prevNode = _Nodeptr;
					_Nodeptr = _Nodeptr->_Parent;
					if (_Nodeptr != nullptr && _Nodeptr->_Left == prevNode) {
						break;
					}
				} while (_Nodeptr->_Parent != nullptr);
			}
			return beforeIT;
		}

		// Pre-decrement
		_map_iterator& operator --() {
			if (_Nodeptr->_Left != nullptr) {
				_Nodeptr = _Nodeptr->_Left;
				while (_Nodeptr->_Right != nullptr) {
					_Nodeptr = _Nodeptr->_Right;
				}
			}
			else {
				node_ptr prevNode;
				do {
					prevNode = _Nodeptr;
					_Nodeptr = _Nodeptr->_Parent;
					if (_Nodeptr != nullptr && _Nodeptr->_Right == prevNode) {
						break;
					}
				} while (_Nodeptr->_Parent != nullptr && _Nodeptr == _Nodeptr->_Parent->_Left);
			}
			return *this;
		}

		// Post-decrement
		_map_iterator operator --(int) {
			_map_iterator beforeIT = *this;
			if (_Nodeptr->_Left != nullptr) {
				_Nodeptr = _Nodeptr->_Left;
				while (_Nodeptr->_Right != nullptr) {
					_Nodeptr = _Nodeptr->_Right;
				}
			}
			else {
				node_ptr prevNode;
				do {
					prevNode = _Nodeptr;
					_Nodeptr = _Nodeptr->_Parent;
					if (_Nodeptr != nullptr && _Nodeptr->_Right == prevNode) {
						break;
					}
				} while (_Nodeptr->_Parent != nullptr && _Nodeptr == _Nodeptr->_Parent->_Left);
			}
			return beforeIT;
		}

		// Dereference
		value_type operator *() const {
			return *(_Nodeptr->_Valueptr);
		}

		// Member access
		value_ptr operator ->() const {
			return _Nodeptr->_Valueptr;
		}

		// Relational operators
		bool operator ==(_map_iterator const& it) const {
			return _Nodeptr == it._Nodeptr;
		}
		bool operator !=(_map_iterator const& it) const {
			return _Nodeptr != it._Nodeptr;
		}
	};

	template <typename _Kty>
	class _map_reverse_iterator {

	public: // Type definitions

		using value_type = _Kty;
		using value_ptr = _Kty*;
		using node_ptr = _map_node<_Kty>*;

	public: // Member data

		node_ptr _Nodeptr;

	public: // Constructors

		// Default constructor
		_map_reverse_iterator() : _Nodeptr(0) {}

		// Value constructor
		_map_reverse_iterator(node_ptr node) : _Nodeptr(node) {}

		// Copy constructor
		_map_reverse_iterator(_map_reverse_iterator const& it) {
			_Nodeptr = it._Nodeptr;
		}

	public: // Destructor

		~_map_reverse_iterator() {}

	public: // Operator overloads

		_map_reverse_iterator& operator =(_map_reverse_iterator const& it) {
			_Nodeptr = it._Nodeptr;
			return *this;
		}

		// Pre-increment
		_map_reverse_iterator& operator ++() {
			if (_Nodeptr->_Left != nullptr) {
				_Nodeptr = _Nodeptr->_Left;
				while (_Nodeptr->_Right != nullptr) {
					_Nodeptr = _Nodeptr->_Right;
				}
			}
			else {
				node_ptr prevNode;
				do {
					prevNode = _Nodeptr;
					_Nodeptr = _Nodeptr->_Parent;
					if (_Nodeptr != nullptr && _Nodeptr->_Right == prevNode) {
						break;
					}
				} while (_Nodeptr->_Parent != nullptr);
			}
			return *this;
		}

		// Post-increment
		_map_reverse_iterator operator ++(int) {
			_map_reverse_iterator beforeIT = *this;
			if (_Nodeptr->_Left != nullptr) {
				_Nodeptr = _Nodeptr->_Left;
				while (_Nodeptr->_Right != nullptr) {
					_Nodeptr = _Nodeptr->_Right;
				}
			}
			else {
				node_ptr prevNode;
				do {
					prevNode = _Nodeptr;
					_Nodeptr = _Nodeptr->_Parent;
					if (_Nodeptr != nullptr && _Nodeptr->_Right == prevNode) {
						break;
					}
				} while (_Nodeptr->_Parent != nullptr);
			}
			return beforeIT;
		}

		// Pre-decrement
		_map_reverse_iterator& operator --() {
			if (_Nodeptr->_Right != nullptr) {
				_Nodeptr = _Nodeptr->_Right;
				while (_Nodeptr->_Left != nullptr) {
					_Nodeptr = _Nodeptr->_Left;
				}
			}
			else {
				node_ptr prevNode;
				do {
					prevNode = _Nodeptr;
					_Nodeptr = _Nodeptr->_Parent;
					if (_Nodeptr != nullptr && _Nodeptr->_Left == prevNode) {
						break;
					}
				} while (_Nodeptr->_Parent != nullptr && _Nodeptr == _Nodeptr->_Parent->_Right);
			}
			return *this;
		}

		// Post-decrement
		_map_reverse_iterator operator --(int) {
			_map_reverse_iterator beforeIT = *this;
			if (_Nodeptr->_Right != nullptr) {
				_Nodeptr = _Nodeptr->_Right;
				while (_Nodeptr->_Left != nullptr) {
					_Nodeptr = _Nodeptr->_Left;
				}
			}
			else {
				node_ptr prevNode;
				do {
					prevNode = _Nodeptr;
					_Nodeptr = _Nodeptr->_Parent;
					if (_Nodeptr != nullptr && _Nodeptr->_Left == prevNode) {
						break;
					}
				} while (_Nodeptr->_Parent != nullptr && _Nodeptr == _Nodeptr->_Parent->_Right);
			}
			return beforeIT;
		}

		// Dereference
		value_type operator *() const {
			return *(_Nodeptr->_Valueptr);
		}

		// Member access
		value_ptr operator ->() const {
			return _Nodeptr->_Valueptr;
		}

		// Relational operators
		bool operator ==(_map_reverse_iterator const& it) const {
			return _Nodeptr == it._Nodeptr;
		}
		bool operator !=(_map_reverse_iterator const& it) const {
			return _Nodeptr != it._Nodeptr;
		}
	};

	template <typename _Kty, typename _Ty, typename _Pr = std::less<_Kty>>
	class map {

	public: // Type definitions

		using key_type = _Kty;
		using mapped_type = _Ty;
		using reference = _Ty&;
		using const_reference = _Ty const&;
		using key_compare = _Pr;
		using size_type = size_t;
		using value_type = std::pair<const _Kty, _Ty>;
		using pointer = std::pair<const _Kty, _Ty>*;
		using const_pointer = std::pair<const _Kty, _Ty>* const;
		using node_type = _map_node<value_type>;
		using node_ptr = _map_node<value_type>*;
		using iterator = _map_iterator<value_type>;
		using const_iterator = iterator const;
		using reverse_iterator = _map_reverse_iterator<value_type>;
		using const_reverse_iterator = reverse_iterator const;

	private: // Member data

		size_type _Count;
		key_compare _Cmp;
		node_ptr _Root;
		node_ptr _Min;
		node_ptr _Max;
		node_ptr _Left;
		node_ptr _Right;

	public: // Constructors

		// Default constructor
		map(key_compare const& cmp = key_compare()) : _Cmp(cmp), _Count(0) {
			_init();
		}

		// Copy constructor
		map(map<key_type, value_type> const& rhs, key_compare const& cmp = key_compare()) : _Cmp(cmp), _Count(0) {
			_init();
			insert(rhs.begin(), rhs.end());
		}

		// Rvalue copy constructor
		map(map<key_type, value_type> && rhs, key_compare const& cmp = key_compare()) : _Cmp(cmp), _Count(0) {
			copy(std::move(rhs));
			rhs.clear();
		}

		// Initializer list constructor
		map(std::initializer_list<value_type> init, key_compare const& cmp = key_compare()) : _Cmp(cmp), _Count(0) {
			_init();
			insert(init.begin(), init.end());
		}

		// Iterator constructor
		template <typename IT>
		map(IT first, IT last, key_compare const& cmp = key_compare()) : _Cmp(cmp), _Count(0) {
			_init();
			insert(first, last);
		}

	public: // Destructor

		~map() { _removeTree(_Root); }

	public: // Member functions
		
		// Iterators
		iterator begin() {
			return iterator(_Min);
		}
		iterator end() {
			return iterator(_Right);
		}
		reverse_iterator rbegin() {
			return reverse_iterator(_Max);
		}
		reverse_iterator rend() {
			return reverse_iterator(_Left);
		}
		const_iterator begin() const {
			return const_iterator(_Min);
		}
		const_iterator end() const {
			return const_iterator(_Right);
		}
		const_reverse_iterator rbegin() const {
			return const_reverse_iterator(_Max);
		}
		const_reverse_iterator rend() const {
			return const_reverse_iterator(_Left);
		}
		const_iterator cbegin() const {
			return const_iterator(_Min);
		}
		const_iterator cend() const {
			return const_iterator(_Right);
		}
		const_reverse_iterator crbegin() const {
			return const_reverse_iterator(_Max);
		}
		const_reverse_iterator crend() const {
			return const_reverse_iterator(_Left);
		}

		// Capacity
		bool empty() const {
			return _Count == 0;
		}
		size_type size() const {
			return _Count;
		}
		size_type count(key_type const& key) const {
			iterator keyIT = find(key);
			return keyIT == end() ? 0 : 1;
		}

		// Accessors
		mapped_type at(key_type const& key) {
			iterator keyIT = find(key);
			if (keyIT == end()) {
				return mapped_type();
			}
			return keyIT._Nodeptr->_Valueptr->second;
		}
		iterator find(key_type const& key) {
			iterator searchIT = lowerBound(key);
			return (searchIT == end() || _Cmp(key, searchIT->first)) ? end() : searchIT;
		}
		std::pair<iterator, iterator> equal_range(key_type const& key) {
			iterator firstIT = begin();
			iterator secondIT = end();
			while (firstIT != nullptr) {
				if (_Cmp(firstIT->first, key)) {
					firstIT = firstIT._Nodeptr->_Right;
				}
				else if (_Cmp(k, firstIT->first)) {
					secondIT = firstIT;
					firstIT = firstIT._Nodeptr->_Left;
				}
				else {
					iterator thirdIT(firstIT._Nodeptr->_Right);
					iterator fourthIT(secondIT);
					secondIT = firstIT;
					firstIT = firstIT._Nodeptr->_Left;
					return std::pair<iterator, iterator>(lower_bound(firstIT, secondIT, key), upper_bound(thirdIT, fourthIT, key));
				}
			}
			return std::pair<iterator, iterator>(iterator(secondIT),
				iterator(secondIT));
		}
		iterator lowerBound(key_type const& key) {
			if (_Count == 0) {
				return end();
			}
			node_ptr firstNode = _Root;
			node_ptr secondNode = end()._Nodeptr;
			while (firstNode != nullptr && firstNode != _Left && firstNode != _Right) {
				if (_Cmp(firstNode->_Valueptr->first, key)) {
					firstNode = firstNode->_Right;
				}
				else {
					secondNode = firstNode, firstNode = firstNode->_Left;
				}
			}
			return iterator(secondNode);
		}
		iterator upperBound(key_type const& key) {
			if (_Count == 0) {
				return end();
			}
			node_ptr firstNode = _Root;
			node_ptr secondNode = end()._Nodeptr;
			while (firstNode != nullptr && firstNode != _Right && firstNode != _Left) {
				if (_Cmp(key, firstNode->_Valueptr->first)) {
					secondNode = firstNode, firstNode = firstNode->_Left;
				}
				else {
					firstNode = firstNode->_Right;
				}
			}
			return iterator(secondNode);
		}

		// Mutators
		template <typename IT>
		void insert(IT first, IT last) {
			while (first != last) {
				insert((value_type)*first++);
			}
		}
		iterator insert(value_type const& value) {
			_removeBarrier();
			iterator insertPos = _getInsertPos(value.first);

			if (insertPos != end()) {
				iterator valueIT = iterator(_insert(insertPos._Nodeptr, value));
				_addBarrier();
				return valueIT;
			}
			_addBarrier();
			return insertPos;
		}
		void erase(iterator location) {
			node_ptr eraseNode = location._Nodeptr;
			if (eraseNode->_Left != nullptr) {
				--location;
				node_ptr leftNode = location._Nodeptr;
				value_type* eraseValue = eraseNode->_Valueptr;
				eraseNode->_Valueptr = leftNode->_Valueptr;
				leftNode->_Valueptr = eraseValue;
				node_ptr _Parent = leftNode->_Parent;
				if (_Parent->_Left == leftNode) {
					_Parent->_Left = nullptr;
				}
				else {
					_Parent->_Right = nullptr;
				}
				leftNode->_Parent = nullptr;
				delete leftNode;
				--_Count;
				_rebalance(_Parent);
			}
			else if (eraseNode->_Right != nullptr) {
				++location;
				node_ptr rightNode = location._Nodeptr;
				value_type* eraseValue = eraseNode->_Valueptr;
				eraseNode->_Valueptr = rightNode->_Valueptr;
				rightNode->_Valueptr = eraseValue;
				node_ptr _Parent = rightNode->_Parent;
				if (_Parent->_Left == rightNode) {
					_Parent->_Left = nullptr;
				}
				else {
					_Parent->_Right = nullptr;
				}
				rightNode->_Parent = nullptr;
				delete rightNode;
				--_Count;
				_rebalance(_Parent);
			}
			else {
				node_ptr _Parent = eraseNode->_Parent;
				if (_Parent->_Left == eraseNode) {
					_Parent->_Left = nullptr;
				}
				else {
					_Parent->_Right = nullptr;
				}
				eraseNode->_Parent = nullptr;
				delete eraseNode;
				--_Count;
				_rebalance(_Parent);
			}
		}
		size_type erase(key_type const& key) {
			iterator searchIT = find(key);
			if (searchIT == end()) {
				return 0;
			}
			erase(searchIT);
			return 1;
		}
		void clear() {
			_Count = 0;
			_removeTree(_Root);
			_init();
		}
		map<key_type, value_type>& copy(map<key_type, value_type> const& item) {
			clear();
			insert(item.begin(), item.end());
			return *this;
		}
		map<key_type, value_type>& swap(map<key_type, value_type>& rhs) {
			map<key_type, mapped_type> temp;

			// Count
			temp._Count = std::move(rhs._Count);
			rhs._Count = std::move(_Count);
			_Count = std::move(temp._Count);

			// Comparator
			temp._Cmp = std::move(rhs._Cmp);
			rhs._Cmp = std::move(_Cmp);
			_Cmp = std::move(temp._Cmp);

			// Root
			temp._Root = std::move(rhs._Root);
			rhs._Root = std::move(_Root);
			_Root = std::move(temp._Root);

			// Min
			temp._Min = std::move(rhs._Min);
			rhs._Min = std::move(_Min);
			_Min = std::move(temp._Min);

			// Max
			temp._Max = std::move(rhs._Max);
			rhs._Max = std::move(_Max);
			_Max = std::move(temp._Max);

			// Left
			temp._Left = std::move(rhs._Left);
			rhs._Left = std::move(_Left);
			_Left = std::move(temp._Left);

			// Right
			temp._Right = std::move(rhs._Right);
			rhs._Right = std::move(_Right);
			_Right = std::move(temp._Right);
		}

	public: // Operator overloads

		map& operator =(map const& rhs) {
			clear();
			for (iterator it = rhs.begin(); it != rhs.end(); ++it) {
				insert(*it);
			}
			return *this;
		}
		mapped_type& operator [](key_type const& key) {
			iterator searchIT = lowerBound(key);
			if (searchIT == end() || _Cmp(key, searchIT->first)) {
				searchIT = insert(value_type(key, mapped_type()));
			}
			return searchIT->second;
		}

		// Relational operators
		bool operator ==(map const& rhs) {
			if (size() != rhs.size()) {
				return false;
			}
			else {
				if (size() == 0) {
					return true;
				}
				iterator lhsIT = begin();
				iterator rhsIT = rhs.begin();
				while (lhsIT != end() && rhsIT != rhs.end()) {
					if ((*lhsIT) != (*rhsIT)) return false;
					++lhsIT;
					++rhsIT;
				}
				return true;
			}
		}
		bool operator !=(map const& rhs) {
			if (size() != rhs.size()) {
				return true;
			}
			else {
				if (size() == 0) {
					return false;
				}
				iterator lhsIT = begin();
				const_iterator rhsIT = rhs.begin();
				while (lhsIT != end() && rhsIT != rhs.end()) {
					if ((*lhsIT) != (*rhsIT)) {
						return true;
					}
					++lhsIT;
					++rhsIT;
				}
				return false;
			}
		}
		bool operator <(map const& rhs) {
			if (size() == 0) {
				return false;
			}
			iterator lhsIT = begin();
			iterator rhsIT = rhs.begin();
			while (lhsIT != end() && rhsIT != rhs.end()) {
				if ((*lhsIT) < (*rhsIT)) {
					return true;
				}
				else if ((*lhsIT) > (*rhsIT)) {
					return false;
				}
				++lhsIT;
				++rhsIT;
			}
			if (lhsIT == end()) {
				if (rhsIT == rhs.end()) {
					return false;
				}
				else {
					return true;
				}
			}
			else {
				return false;
			}
		}
		bool operator <=(map const& rhs) {
			if (size() == 0) {
				return false;
			}
			iterator lhsIT = begin();
			iterator rhsIT = rhs.begin();
			while (lhsIT != end() && rhsIT != rhs.end()) {
				if ((*lhsIT) < (*rhsIT)) {
					return true;
				}
				else if ((*lhsIT) > (*rhsIT)) {
					return false;
				}
				++lhsIT;
				++rhsIT;
			}
			if (lhsIT == end()) {
				if (rhsIT == rhs.end()) {
					return true;
				}
				else {
					return true;
				}
			}
			else {
				return false;
			}
		}
		bool operator >(map const& rhs) {
			if (size() == 0) {
				return false;
			}
			iterator lhsIT = begin();
			const_iterator rhsIT = rhs.begin();
			while (lhsIT != end() && rhsIT != rhs.end()) {
				if ((*lhsIT) < (*rhsIT)) {
					return false;
				}
				else if ((*lhsIT) > (*rhsIT)) {
					return true;
				}
				++lhsIT;
				++rhsIT;
			}
			if (lhsIT == end()) {
				if (rhsIT == rhs.end()) {
					return false;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
		}
		bool operator >=(map const& rhs) {
			if (size() == 0) {
				return false;
			}
			iterator lhsIT = begin();
			iterator rhsIT = rhs.begin();
			while (lhsIT != end() && rhsIT != rhs.end()) {
				if ((*lhsIT) < (*rhsIT)) {
					return false;
				}
				else if ((*lhsIT) > (*rhsIT)) {
					return true;
				}
				++lhsIT;
				++rhsIT;
			}
			if (lhsIT == end()) {
				if (rhsIT == rhs.end()) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return true;
			}
		}

	private: // Helper functions

		void _init() {
			_Root = new node_type();
			_Min = nullptr;
			_Max = nullptr;
			_Left = new node_type();
			_Left->_Height = 0;
			_Left->_Parent = _Root;
			_Right = new node_type();
			_Right->_Height = 0;
			_Root->_Left = _Left;
			_Root->_Right = _Right;
			_Root->_Height = 0;
			_Right->_Parent = _Root;
		}
		void _removeTree(node_ptr _Nodeptr) {
			if (_Nodeptr != nullptr && _Nodeptr->_Left != nullptr) {
				_removeTree(_Nodeptr->_Left);
			}
			if (_Nodeptr != nullptr && _Nodeptr->_Right != nullptr) {
				_removeTree(_Nodeptr->_Right);
			}
			if (_Nodeptr != nullptr) {
				delete _Nodeptr;
			}
		}
		void _removeBarrier() {
			if (size() > 0) {
				_Min->_Left = nullptr;
				_Left->_Parent = nullptr;
				_Max->_Right = nullptr;
				_Right->_Parent = nullptr;
			}
		}
		void _addBarrier() {
			if (size() > 0) {
				_Min->_Left = _Left;
				_Left->_Parent = _Min;
				_Max->_Right = _Right;
				_Right->_Parent = _Max;
			}
		}
		iterator _getInsertPos(key_type const& key) {
			if (size() == 0) {
				return iterator(_Root);
			}
			iterator searchNode = find(key);
			if (searchNode != end()) {
				return end();
			}
			iterator firstNode = _Root->_Parent;
			iterator secondNode = _Root;
			bool cmp = true;
			while (secondNode != nullptr) {
				firstNode = secondNode;
				cmp = _Cmp(key, secondNode._Nodeptr->_Valueptr->first);
				secondNode = cmp ? secondNode._Nodeptr->_Left : secondNode._Nodeptr->_Right;
			}
			return iterator(firstNode);
		}
		iterator _insert(node_ptr parent, value_type const& value) {
			value_type* newValue = new value_type(value.first, value.second);
			if (size() == 0) {
				_Root->_Valueptr = newValue;
				_Root->updateBalance();
				++_Count;
				_Min = _Root;
				_Max = _Root;
				return iterator(_Root);
			}
			else {
				node_ptr newNode = new node_type;
				newNode->_Valueptr = newValue;
				newNode->_Height = 1;
				if (parent->_Parent == nullptr) {
					newNode->_Parent = parent;
					if (_Cmp(newValue->first, parent->_Valueptr->first)) {
						parent->_Left = newNode;
					}
					else {
						parent->_Right = newNode;
					}
					parent->updateBalance();
				}
				else {
					bool insert_left = (parent == _Root || _Cmp(newValue->first, parent->_Valueptr->first));
					newNode->_Parent = parent;
					_rebalanceInsert(insert_left, newNode, parent);
				}

				++_Count;
				if (_Min == nullptr || _Min->_Valueptr->first > newNode->_Valueptr->first) {
					_Min = newNode;
				}

				if (_Max == nullptr || _Max->_Valueptr->first < newNode->_Valueptr->first) {
					_Max = newNode;
				}
				return iterator(newNode);
			}
		}
		node_ptr _rotateRight(node_ptr node) {
			node_ptr parent = node->_Parent;
			node_ptr leftNode = node->_Right;
			if (leftNode->leftHeight() < leftNode->rightHeight()) {
				// need single rotation
				if (_Root == node) {
					_Root = leftNode;
				}
				node_ptr leftLeftNode = leftNode->_Left;
				//restructure
				if (parent != nullptr) {
					bool is_left_child = (node == parent->_Left);
					if (is_left_child) {
						parent->_Left = leftNode;
					}
					else {
						parent->_Right = leftNode;
					}
				}
				leftNode->_Parent = parent;
				leftNode->_Left = node; node->_Parent = leftNode;
				node->_Right = leftLeftNode;
				if (leftLeftNode) {
					leftLeftNode->_Parent = node;
				}
				node->updateBalance();
				leftNode->updateBalance();
				return leftNode;
			}
			else {
				// need double rotation
				node_ptr leftLeftNode = leftNode->_Left;
				if (_Root == node) _Root = leftLeftNode;
				node_ptr left = leftLeftNode->_Left;
				node_ptr right = leftLeftNode->_Right;
				// restructure
				if (parent != nullptr) {
					bool is_left_child = (node == parent->_Left);
					if (is_left_child) parent->_Left = leftLeftNode; else parent->_Right = leftLeftNode;
				}
				leftLeftNode->_Parent = parent;
				leftLeftNode->_Left = node; node->_Parent = leftLeftNode;
				leftLeftNode->_Right = leftNode; leftNode->_Parent = leftLeftNode;
				node->_Right = left; if (left) left->_Parent = node;
				leftNode->_Left = right; if (right) right->_Parent = leftNode;
				leftNode->updateBalance();
				node->updateBalance();
				leftLeftNode->updateBalance();
				return leftLeftNode;
			}
		}
		node_ptr _rotateLeft(node_ptr node) {
			node_ptr parent = node->_Parent;
			node_ptr leftNode = node->_Left;
			if (leftNode->rightHeight() < leftNode->leftHeight()) {
				// need single rotation
				if (_Root == node) {
					_Root = leftNode;
				}
				node_ptr rightLeftNode = leftNode->_Right;
				// restructure
				if (parent != nullptr) {
					bool is_left_child = (node == parent->_Left);
					if (is_left_child) {
						parent->_Left = leftNode;
					}
					else {
						parent->_Right = leftNode;
					}
				}
				leftNode->_Parent = parent;
				leftNode->_Right = node; node->_Parent = leftNode;
				node->_Left = rightLeftNode;
				if (rightLeftNode) {
					rightLeftNode->_Parent = node;
				}
				node->updateBalance();
				leftNode->updateBalance();
				return leftNode;
			}
			else {
				// need double rotation
				node_ptr leftRightNode = leftNode->_Right;
				if (_Root == node) {
					_Root = leftRightNode;
				}
				node_ptr left = leftRightNode->_Left;
				node_ptr right = leftRightNode->_Right;
				if (parent != nullptr) {
					bool is_left_child = (node == parent->_Left);
					if (is_left_child) {
						parent->_Left = leftRightNode;
					}
					else {
						parent->_Right = leftRightNode;
					}
				}
				leftRightNode->_Parent = parent;
				leftRightNode->_Left = leftNode; leftNode->_Parent = leftRightNode;
				leftRightNode->_Right = node; node->_Parent = leftRightNode;
				leftNode->_Right = left;
				if (left) {
					left->_Parent = leftNode;
				}
				node->_Left = right;
				if (right) {
					right->_Parent = node;
				}
				node->updateBalance();
				leftNode->updateBalance();
				leftRightNode->updateBalance();
				return leftRightNode;
			}
		}
		void _rebalance(node_ptr parent) {
			while (parent != nullptr) {
				parent->updateBalance();
				if (parent->_Balance < -1) { // need right rotation
					parent = _rotateRight(parent);
				}
				else if (parent->_Balance > 1) { // need left rotation
					parent = _rotateLeft(parent);
				}
				parent = parent->_Parent;
			}
		}
		void _rebalanceInsertLeft(node_ptr node, node_ptr parent) {
			parent->_Left = node;
			_rebalance(parent);
		}
		void _rebalanceInsertRight(node_ptr node, node_ptr parent) {
			parent->_Right = node;
			_rebalance(parent);
		}
		void _rebalanceInsert(bool insertLeft, node_ptr node, node_ptr parent) {
			if (insertLeft) {
				_rebalanceInsertLeft(node, parent);
			}
			else {
				_rebalanceInsertRight(node, parent);
			}
		}
	};
}