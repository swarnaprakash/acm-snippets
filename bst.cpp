/********************************************************************************************************************************

						STATIC BINARY SEARCH TREE
							written by U.Swarnaprakash
						
						BST<Type>
						Duplicate Elements allowed
						For user defined data types overload  the operator <  

************************************************************************************************************************************/

//Most member functions in this implementation use double pointers.Single pointers won't work !

#include<iostream>
#include<cstdio>
#include<string>

using namespace std;

#define DB(x) cout<<#x" : "<<x<<endl;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
class node
{
	public:
	Type key;
	node *left;
	node *right;
	node()
	{
		left=NULL;
		right=NULL;
	}
};

template<class Type>
class BST
{
	node<Type> *root;
	void clear(node<Type> **);
	void erase(node<Type> **);
	void inorder(node<Type> *);
		
	public:
	BST();
	node<Type>* insert(const Type &);
	node<Type>* find(const Type &);
	node<Type>* max();
	node<Type>* min();
	Type pop_max();
	Type pop_min();
	bool erase(const Type &);
	void inorder();
	void clear();
	~BST();
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
BST<Type>::BST()
{
	root=NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
node<Type>* BST<Type>::insert(const Type &item)
{
	node<Type>* new_node=new node<Type>;
	new_node->key=item;
	node<Type>** ptr=&root;
	while(*ptr!=NULL)
	{
		if(item<(*ptr)->key)
			ptr=&(*ptr)->left;
		else
			ptr=&(*ptr)->right;
	}
	
	return *ptr=new_node;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
node<Type>* BST<Type>::find(const Type &item)
{
	node<Type>* ptr=root;
	while(ptr!=NULL)
	{
		if(ptr->key==item)
			return ptr;
		else if(item<ptr->key)
			ptr=ptr->left;
		else
			ptr=ptr->right;
	}
	return NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
node<Type>* BST<Type>::max()
{
	node<Type> *ptr=root;
	if(ptr==NULL)
		return NULL;
	while(ptr->right!=NULL)
		ptr=ptr->right;
	return ptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
node<Type>* BST<Type>::min()
{
	node<Type> *ptr=root;
	if(ptr==NULL)
		return NULL;
	while(ptr->left!=NULL)
		ptr=ptr->left;
	return ptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
Type BST<Type>::pop_max()
{
	node<Type> **ptr=&root;
	while((*ptr)->right!=NULL)
		ptr=&(*ptr)->right;
		
	Type ret=(*ptr)->key;
	erase(ptr);
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
Type BST<Type>::pop_min()
{
	node<Type> **ptr=&root;
	while((*ptr)->left!=NULL)
		ptr=&(*ptr)->left;
		
	Type ret=(*ptr)->key;
	erase(ptr);
	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void BST<Type>::erase(node<Type> **ptr)	//private member function
{
	if((*ptr)->left==NULL)
	{
		
		node<Type> *tmp=*ptr;
		*ptr=(*ptr)->right;
		delete tmp;
		
	}
	else if((*ptr)->right==NULL)
	{
		node<Type> *tmp=*ptr;
		*ptr=(*ptr)->left;
		delete tmp;
	}
	else
	{
		 // In-order successor (leftmost child of right subtree)
		node<Type> **tmp=&(*ptr)->right;
		while((*tmp)->left!=NULL)
			tmp=&(*tmp)->left;
		(*ptr)->key=(*tmp)->key;
		erase(tmp);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
bool BST<Type>::erase(const Type &item)
{
	node<Type>** ptr=&root;
	while(*ptr!=NULL)
	{
		if((*ptr)->key==item)
			break;
		else if(item<(*ptr)->key)
			ptr=&(*ptr)->left;
		else
			ptr=&(*ptr)->right;
	}
	if(*ptr==NULL)
		return false;
		
	erase(ptr);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void BST<Type>::inorder(node<Type> *ptr)	//private member function
{
	if(ptr==NULL)
		return;
	inorder(ptr->left);
	cout<<endl<<"Node details"<<endl;
	DB(ptr);
	DB(ptr->key);
	DB(ptr->left);
	DB(ptr->right);
	inorder(ptr->right);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void BST<Type>::inorder()
{
	puts("");
	inorder(root);
	puts("");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void BST<Type>::clear(node<Type> **ptr)	//private member function
{
	if(*ptr==NULL)
		return;
	clear(&(*ptr)->left);
	clear(&(*ptr)->right);
	delete *ptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void BST<Type>::clear()
{
	clear(&root);
	root=NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
BST<Type>::~BST()
{
	clear(&root);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	string op;
	int n;
	BST<int> bst;
	while(cin>>op>>n)
	{
		//printf("%p\n",bst.root);
		if(op=="insert")
			bst.insert(n);
		else if(op=="find")
		{
			node<int> *ptr=bst.find(n);
			if(ptr==NULL)
				puts("Not Found");
			else
				printf("%d\n",ptr->key);
				
		}
		else if(op=="erase")
		{
			cout<<bst.erase(n)<<endl;
		}
		else if(op=="max")
		{
			cout<<bst.max()->key<<endl;
		}
		else if(op=="min")
		{
			cout<<bst.min()->key<<endl;
		}
		else if(op=="clear")
		{
			cout<<"cleared";
			bst.clear();
		}
		else if(op=="pop_max")
		{
			cout<<bst.pop_max()<<endl;
		}
		else if(op=="pop_min")
		{
			cout<<bst.pop_min()<<endl;
		}
		bst.inorder();
	}
	puts("");
	//bst.clear(&bst.root);
	system("pause");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
