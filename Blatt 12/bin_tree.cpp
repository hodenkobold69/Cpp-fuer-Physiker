#include <iostream>
#include <cstdlib>
//using namespace std ;	//don't make me laugh...

class Node {

private:
    double value ;  // node value
    Node* left ;    // left node pointer
    Node* right ;   // right node pointer

public:
	Node(double init): value(init){left = NULL; right = NULL;};
	~Node();
	void insert(double x);
	double min();
	friend std::ostream &operator<< (std::ostream &str, const Node &n);
};

void Node::insert(double x)	{

	if(x <= value)	{

		if(!left)
			left=new Node(x);
		else
			left->insert(x);

	} else	{

		if(!right)
			right=new Node(x);
		else
			right->insert(x);
	}
}

Node::~Node()	{

	//remember: delete calls destructor of object --> recursively destructs alls nodes
    if(left)
		delete(left);
    if(right) 
		delete(right);
}

double Node::min()	{

	if(!left)
		return value;
	else return left->min();
}

std::ostream &operator<< (std::ostream &str, const Node &n)	{

    if (0 != n.left)
		str << *(n.left) ;

	str << n.value << " " ;

	if (0 != n.right)
		str << *(n.right) ;

	return str ;
}

int main()	{

    srand ((unsigned int)time(0)) ;

    Node tree(1.0) ;        //root node

    for(int i=0; i<10; i++)	{

		double x = 2.0*double(rand())/RAND_MAX ;
		std::cout << "Adding: " << x << std::endl ;
		tree.insert(x) ;
    }

    std::cout << "Minimum value: " << tree.min() << std::endl ;
    std::cout << "Sorted tree output: " << std::endl << "  " << tree << std::endl ;
}
