#ifndef TREE
#define TREE

#include <iostream>
#include <memory>
#include <string>
#include <queue>
#include "algorithm.hpp"
#include "utility.hpp"
#define CBLACK 1;
#define CRED 0;

namespace ft
{
    template<class T>
    struct node
    {
        int color;
        node *parent;
        node *left;
        node *right;
        T item;

        node(const T & data) : item(data.first, data.second)
        {
            parent = NULL;
            left = NULL;
            right = NULL;
            color = CBLACK;
        }

        bool 
        is_nil(void) const
        {
            if (this->parent == this)
                return true;
            return false;
        }
    };

    template <class Key, class T, class keyCompare = std::less<Key>, class valueCompare = std::less<T>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    class rb_tree
    {
        public:
		typedef ft::pair<const Key, T> value_type;
        typedef Key key_type;
        typedef T mapped_type;
        typedef keyCompare key_compare;
		typedef valueCompare value_compare;
		typedef typename Alloc::template rebind<node<value_type> >::other allocator_type;
		typedef std::size_t size_type;
		typedef node<value_type> node;

        rb_tree(void) :
        _alloc(allocator_type()),
        _cmp(key_compare())
        {
            _nil = _alloc.allocate(1);
            construct_node(_nil);
            _nil->parent = _nil;
            _nil->color = CBLACK;
        }

        ~rb_tree(void)
		{
			_alloc.destroy(_nil);
			_alloc.deallocate(_nil, 1);
		}

        void
        insert_node(const value_type &value)
        {
            node *new_node = _alloc.allocate(1);
            construct_node(new_node, value);
            if (_nil->right == _nil)
            {
                _nil->right = new_node;
                new_node->parent = _nil;
            }
            else
            {
                node *new_parent = insertion_destination(_nil->right, new_node);
                if (_cmp(new_parent->item.first, new_node->item.first))
                    new_parent->right = new_node;
                else
                    new_parent->left = new_node;
                new_node->parent = new_parent;
                new_node->color = CRED;
            }
            insert_fix(new_node);
        }

        node
		*search(const key_type & n) const
		{
			return search_helper(_nil->right, n);
		}

        void delete_by_key(const key_type &key)
        {
            delete_node_helper(key);
        }

        void printTree()
        {
            if (_nil->right)
                printHelper(_nil->right, "", true);
        }

		node *
		left_most(void) const
		{
            node *tmp = _nil->right;
            
            while (tmp->left != _nil) {
                tmp = tmp->left;
            }
            return tmp;
		}

		node *
		right_most(void) const
		{
            node *tmp = _nil->right;
            
            while (tmp->right != _nil)
                tmp = tmp->right;
            return tmp;
		}

		node*
		get_next_node(const key_type & n) const
		{
			node* tmp = _nil->right;

			while (tmp != _nil)
			{
				if (_cmp(n, tmp->item.first))
					tmp = tmp->left;
				else if (_cmp(tmp->item.first, n))
					tmp = tmp->right;
			}
			return tmp;
		}

		node *
		get_nil_node(void) const
		{
			return _nil;
		}

		void
		swap_root(rb_tree &x)
		{
			ft::swap(_nil, x._nil);
		}

		allocator_type
		get_allocator(void) const
		{
			return _alloc;
		}

        private:

        node *_nil;
        allocator_type _alloc;
        key_compare _cmp;

        void
        construct_node(node *ptr, value_type val = value_type())
        {
            node tmp(val);
            _alloc.construct(ptr, tmp);
            ptr->left = _nil;
            ptr->right = _nil;
        }

        node *search_helper(node *current, const key_type &key) const
        {
            if (current == _nil || equal(key, current->item.first))
                return current;
            
            if (_cmp(key, current->item.first))
                return search_helper(current->left, key);
            return search_helper(current->right, key);
        }

        void delete_node_helper(const key_type &key)
        {
            node *z = search(key);
            node *x;//delete fix (double black)대상
            node *y;//delete 할 노드 선정

            if (!z)
                return;
            y = z;
            int original_color = y->color;
            if (z->left == _nil)
            {
                x = z->right;
                transplant(z, z->right);
            }
            else if (z->right == _nil)
            {
                x = z->left;
                transplant(z, z->left);
            }
            else
            {
                y = minimum(z->right);
                original_color = y->color;
                x = y->right;
                if (y->parent == z)
                {
                    if (x)
                        x->parent = y;
                }
                else
                {
                    transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
			_alloc.destroy(z);
			_alloc.deallocate(z, 1);
            if (original_color == 1)
                delete_fix(x);
            _nil->parent = _nil;
        }

        void delete_fix(node *x)
        {
            node *s;
            while (x != _nil->right && x->color == 1)
            {
                if (x == x->parent->left)
                {
                    s = x->parent->right;
                    //case1
                    if (s->color == 0)
                    {
                        s->color = 1;
                        x->parent->color = 0;
                        left_rotate(x->parent);
                        s = x->parent->right;
                    }
                    //case2
                    if (s->left->color == 1 && s->right->color == 1)
                    {
                        s->color = 0;
                        x = x->parent;
                    }
                    else
                    {
                        // case3
                        if (s->right->color == 1)
                        {
                            s->left->color = 1;
                            s->color = 0;
                            right_rotate(s);
                            s = x->parent->right;
                        }
                        //case4
                        s->color = x->parent->color;
                        x->parent->color = 1;
                        s->right->color = 1;
                        left_rotate(x->parent);
                        x = _nil->right;
                    }
                }
                else
                {
                    s = x->parent->left;
                    if (s->color == 0)
                    {
                        s->color = 1;
                        x->parent->color = 0;
                        right_rotate(x->parent);
                        s = x->parent->right;
                    }
                    if (s->right->color == 1)
                    {
                        s->color = 0;
                        x = x->parent;
                    }
                    else
                    {
                        if (s->left->color == 1)
                        {
                            s->right->color = 1;
                            s->color = 0;
                            left_rotate(s);
                            s = x->parent->right;
                        }

                        s->color = x->parent->color;
                        x->parent->color = 1;
                        s->left->color = 1;
                        right_rotate(x->parent);
                        x = _nil->right;
                    }
                }
            }
            x->color = 1;
        }

        void transplant(node *u, node *v)
        {
            if (u->parent == NULL)
                _nil->right = v;
            else if (u == u->parent->left)
                u->parent->left = v;
            else
                u->parent->right = v;
            if (v && u)
                v->parent = u->parent;
        }

        node *minimum(node *node)
        {
            while (node->left != _nil)
                node = node->left;
            return node;
        }

        node *maximum(node *node)
        {
            while (node->right != _nil)
                node = node->right;
            return node;
        }

        void left_rotate(node *x)
        {
            node *y = x->right;
            x->right = y->left;
            if (y->left != _nil)
                y->left->parent = x;
            y->parent = x->parent;
            if (x->parent == NULL)
                _nil->right = y;
            else if (x == x->parent->left)
                x->parent->left = y;
            else
                x->parent->right = y;
            y->left = x;
            x->parent = y;
        }

        void right_rotate(node *x)
        {
            node *y = x->left;
            x->left = y->right;
            if (y->right != _nil)
                y->right->parent = x;
            y->parent = x->parent;
            if (x->parent == NULL)
                _nil->right = y;
            else if (x == x->parent->right)
                x->parent->right = y;
            else
                x->parent->left = y;
            y->right = x;
            x->parent = y;
        }

        void insert_fix(node *z)
        {
            // red = 0 black = 1
            node *uncle;
            while (z->parent->color == 0)
            {
                if (z->parent == z->parent->parent->right)
                {
                    uncle = z->parent->parent->left;
                    if (uncle->color == 0)
                    {
                        uncle->color = 1;
                        z->parent->color = 1;
                        z->parent->parent->color = 0;
                        z = z->parent->parent;
                    }
                    else
                    {
                        if (z == z->parent->left)
                        {
                            z = z->parent;
                            right_rotate(z);
                        }
                        z->parent->color = 1;
                        z->parent->parent->color = 0;
                        left_rotate(z->parent->parent);
                    }
                }
                else
                {
                    uncle = z->parent->parent->right;
                    //case1
                    if (uncle->color == 0)
                    {
                        uncle->color = 1;
                        z->parent->color = 1;
                        z->parent->parent->color = 0;
                        z = z->parent->parent;
                    }
                    else
                    {
                        //case2
                        if (z == z->parent->right)
                        {
                            z = z->parent;
                            left_rotate(z);
                        }
                        //cas3
                        z->parent->color = 1;
                        z->parent->parent->color = 0;
                        right_rotate(z->parent->parent);
                    }
                }
                if (z == _nil->right)
                    break;
            }
            _nil->right->color = 1;
        }

        node *insertion_destination(node *position, node *new_node)
        {
            while (position != _nil)
            {
                if (_cmp(position->item.first, new_node->item.first))
                {
                    if (position->right == _nil)
                        return position;
                    position = position->right;
                }
                else
                {
                    if (position->left == _nil)
                        return position;
                    position = position->left;
                }
            }
            return position;
        }

		bool
		equal(key_type a, key_type b) const
		{
			return (!_cmp(a, b) && !_cmp(b, a));
		}

        void printHelper(node *root, std::string indent, bool last)
        {
            if (root != _nil)
            {
                std::cout << indent;
                if (last)
                {
                    std::cout << "R----";
                    indent += "   ";
                }
                else
                {
                    std::cout << "L----";
                    indent += "|  ";
                }
                std::string sColor;
                if (root->color == 1)
                    sColor = "BLACK";
                else
                    sColor = "RED";
                std::cout << root->item.first << "(" << sColor << ")" << std::endl;
                printHelper(root->left, indent, false);
                printHelper(root->right, indent, true);
            }
        }
    };

}

#endif