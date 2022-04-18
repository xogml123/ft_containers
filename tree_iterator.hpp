#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

namespace ft{

template<class Value>
struct Node{
	public:
	explicit Node(Value *srcval = 0) :	value(srcval),
										parent(0),
										left(0),
										right(0),
										is_black(false),
										is_nil(0){}
	
	Value	*value;
	Node*	parent;
	Node*	left;
	Node*	right;	
	bool	is_black;
	bool	is_nil;

	Node( Node const & other) {
		this->is_black = other.is_black;
		this->value = other.value;
		this->parent = other.parent;
		this->is_nil = other.is_nil;
		this->right = other.right;
		this->left = other.left;
	};

	Node& operator=(const Node& other){
		this->is_black = other.is_black;
		this->value = other.value;
		this->is_nil = other.is_nil;
		this->parent = other.parent;
		this->right = other.right;
		this->left = other.left;
		return *this;
	}	
	virtual ~Node(){}
};

template<typename T>
class tree_iterator {
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef typename ft::iterator_traits<T*>::value_type 		value_type;
		typedef typename ft::iterator_traits<T*>::reference 		reference;
		typedef typename ft::iterator_traits<T*>::pointer			pointer;
		typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
		typedef Node<typename ft::remove_const<value_type>::type >* node_pointer;

	private:
		node_pointer _node;

		node_pointer tree_min(node_pointer n) const {
			while(n->left != NULL && !n->left->is_nil)
				n = n->left;
			return n;
		}

		node_pointer tree_max(node_pointer n) const {
			while (n->right != NULL && !n->right->is_nil)
				n = n->right;
			return n;
		}

	public:
		tree_iterator() {}

		tree_iterator(void *node): _node(static_cast<node_pointer>(node)) {}

		tree_iterator(const tree_iterator<typename ft::remove_const<value_type>::type > & other)//: _node(other.node()) {}
		{
			*this = other;
		}

		tree_iterator& operator=(const tree_iterator<typename ft::remove_const<value_type>::type>& other) {
			this->_node = other.node();
			return *this;
		}

		reference operator*() const {
			return *(_node->value);
		}

		pointer operator->() const {
			return _node->value;
		}

		tree_iterator& operator++() {
			if (_node->right && !_node->right->is_nil) {
				_node = tree_min(_node->right);
			}
			else {
				node_pointer y = _node->parent;
				while (y != NULL && _node == y->right) {
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return *this;
		}

		tree_iterator operator++(int) {
			tree_iterator<value_type> temp = *this;
			if (!_node->right->is_nil) {
				_node = tree_min(_node->right);
			}
			else {
				node_pointer y = _node->parent;
				while (y != NULL && _node == y->right) {
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return temp;
		}

		tree_iterator& operator--() {
			if (_node->left && !_node->left->is_nil) {
				_node = tree_max(_node->left);
			}
			else {
				node_pointer y = _node->parent;
				while (y != NULL && _node == y->left) {
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return *this;
		}

		tree_iterator operator--(int) {
			tree_iterator<value_type> temp = *this;
			if (_node->left && !_node->left->is_nil) {
				_node = tree_max(_node->left);
			}
			else {
				node_pointer y = _node->parent;
				while (y != NULL && _node == y->left) {
					_node = y;
					y = y->parent;
				}
				_node = y;
			}
			return temp;
		}

		node_pointer node() const {
			return _node;
		}
	};	

template<typename A, typename B>
bool operator==(const tree_iterator<A> & lhs, const tree_iterator<B> & rhs){
		return (lhs.node() == rhs.node());
	}

template<typename A, typename B>
bool operator!=(const tree_iterator<A> & lhs, const tree_iterator<B> & rhs){
		return (lhs.node() != rhs.node());
	}

}
#endif