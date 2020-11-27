#include <iostream>
#include <string>
using namespace std;
template <class T> class Node {
public:
	T data;
	int height;
	Node<T>* left = NULL;
	Node<T>* right = NULL;
};
template <class T> class Binary_tree {
private:
	void _insert(Node<T>* _node, T _data) {
		if (_data < _node->data) {
			if (_node->left == NULL) {				
				_node->left = new Node<T>;
				_node->left->data = _data;
				_node->left->left = _node->left->right = NULL;
			}
			else {
				_insert(_node->left, _data);
			}
		}
		else {
			if (_node->right == NULL) {
				_node->right = new Node<T>;
				_node->right->data = _data;
				_node->right->left = _node->right->right = NULL;
			}
			else {
				_insert(_node->right, _data);
			}
		}
	}
	T findPredecessor(Node<T>* _node) {
		if (_node->right != NULL) {
			return findPredecessor(_node->right);
		}
		return _node->data;

	}
	Node<T>* _deletr_element(Node<T>* _node, T _data) {
		if (_node == NULL) {
			cout << "The data isn't in the tree.\n";
		}
		else if (_data < _node->data) {
			_node->left = _deletr_element(_node->left, _data);
		}
		else if(_data > _node->data){
			_node->right = _deletr_element(_node->right, _data);
		}
		else if (_node->left != NULL && _node->right != NULL) {
			_node->data = findPredecessor(_node->left);
			_node->left = _deletr_element(_node->left, _node->data);
		}
		else{
			Node<T>* temp = _node;
			if (_node->left != NULL) {
				_node = _node->left;
			}
			else {
				_node = _node->right;
			}
			delete temp;
			temp = NULL;
		}
		return _node;
	}
	void _print_all(Node<T>* _node, bool& b) {
		if (_node) {
			
			_print_all(_node->left, b);		
			_print_all(_node->right, b);
			if (b) {
				cout << _node->data;
				b = false;
			}
			else {
				cout << ' ' << _node->data;
			}
		}
	}
	void _print_top(Node<T>* _node, bool& b, int height) {
		if (_node) {
			_print_top(_node->left, b, height);
			if (_node->height <= height) {
				if (b) {
					cout << _node->data;
					b = false;
				}
				else {
					cout << ' ' << _node->data;
				}
			}
			_print_top(_node->right, b, height);
		}
	}
	void _print_down(Node<T>* _node, bool& b, int height) {
		if (_node) {
			if (_node->height >= height) {
				if (b) {
					cout << _node->data;
					b = false;
				}
				else {
					cout << ' ' << _node->data;
				}
			}
			_print_down(_node->left, b, height);			
			_print_down(_node->right, b, height);
		}
	}
	void _height(Node<T>* _node, int level, int& big) {
		if (_node) {
			_node->height = level;
			if (level > big) big = level;
			_height(_node->left, level + 1, big);
			_height(_node->right, level + 1, big);
		}
	}
	void _getHeightNumber(Node<T>* _node, int _height , int& number) {
		if (_node) {
			if (_node->height == _height) { number++; return; }
			_getHeightNumber(_node->left, _height, number);
			_getHeightNumber(_node->right, _height, number);
		}
	}

public:
	Node<T>* root = NULL;
	void insert(T _data) {
		if (root == NULL) {
			root = new Node<T>;
			root->data = _data;
			root->left = root->right = NULL;
		}
		else {
			_insert(root, _data);
		}
	}
	void delete_element(T _data) {
		root = _deletr_element(root, _data);
	}
	void print_all() {
		if (root == NULL) {
			cout << "The tree is empty.\n";
		}
		else {
			bool boo = true;
			_print_all(root, boo);
		}		
	}
	void print_top(int height) {
		if (root == NULL) {
			cout << "The tree is empty.\n";
		}
		else {
			bool boo = true;
			_print_top(root, boo, height);
		}
	}
	void print_down(int height) {
		if (root == NULL) {
			cout << "The tree is empty.\n";
		}
		else {
			bool boo = true;
			_print_down(root, boo, height);
		}
	}
	int height() {
		int big = 0;
		_height(root, 1, big);
		return big;
	}
	int getHeightNumber(int height) {
		int number = 0;
		_getHeightNumber(root, height, number);
		return number;
	}
};
int main(void) {
	string str;
	int num = 0;
	Binary_tree<int> Tree;
	getline(cin, str);
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == ' ') {
			Tree.insert(num);
			num = 0;
		}
		else {
			num *= 10;
			num += str[i] - '0';
		}
	}
	Tree.insert(num);
	num = 0;
	Tree.print_all();
	printf("\n");
	getline(cin, str);
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == ' ') {
			Tree.delete_element(num);
			num = 0;
		}
		else {
			num *= 10;
			num += str[i] - '0';
		}
	}
	Tree.delete_element(num);
	int height = Tree.height();
	int n = 1;
	int top = Tree.getHeightNumber(n);
	int down = Tree.getHeightNumber(height);
	
	while ((height - n) > 1) {
		if (top < down) {
			n++;
			top += Tree.getHeightNumber(n);
		}
		else if (top > down) {
			height--;
			down += Tree.getHeightNumber(height);
		}
		else {
			if (Tree.getHeightNumber(n + 1) > Tree.getHeightNumber(height - 1)) {
				height--;
				down += Tree.getHeightNumber(height);
			}
			else {
				n++;
				top += Tree.getHeightNumber(n);
			}
		}
	}
	Tree.print_top(height - 1);
	printf("\n");
	Tree.print_down(height);
}