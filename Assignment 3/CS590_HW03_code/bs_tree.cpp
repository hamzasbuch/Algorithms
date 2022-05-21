
#include "bs_tree.h"
#include <list>
#include <iostream>

using namespace std;

/*
 * constructor/destructor
 */
bs_tree::bs_tree()
{
    //create T_nil element
    T_nil = new bs_tree_node();
    T_nil->p = T_nil;
    T_nil->left = T_nil;
    T_nil->right = T_nil;
    
    //root of rb tree
    T_root = T_nil;
} 

bs_tree::~bs_tree()
{ 
    //delete nil element and all other allocated nodes
    remove_all(T_root);
    
    delete T_nil;
} 

void bs_tree::insert(int key, bs_tree_i_info& t_info)
{
    //Wrapper around insert
    //creates node with key
    //inserts node
    bs_tree_node* z;
    
    z = new bs_tree_node;
    z->key = key;
    
    insert(z, t_info);
    
}

void bs_tree::insert(bs_tree_node* z, bs_tree_i_info& t_info)
{
    //binary tree type insert
    //search position, insert new node
    bs_tree_node* x;
    bs_tree_node* y;
    
    y = T_nil;
    x = T_root;
    
    while (x != T_nil)
    {
        y = x;
        
        //Disallow duplicate values
        if(z->key == x->key)
        {
            t_info.i_duplicate++;
            return;
        }
        
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }
    
    z->p = y;
    if (y == T_nil)
        T_root = z;
    else
    {
        if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
    }
    
    z->left = T_nil;
    z->right = T_nil;
}

void bs_tree::inorder_output(bs_tree_node* x, int level, int* input_arr)
{
    //In order walk through binary tree
    if (x != T_nil)
    {
        inorder_output(x->left, level+1,input_arr);
        //cout << "(" << x->key << "," << level << ")" << endl;
        input_arr[index++] = x->key;
        inorder_output(x->right, level+1,input_arr);
    }
}	
//Modified inorder tree walk method to save the
//sorted numbers in the first argument: int* array.
//question 2
int bs_tree::convert(int* array, int n)
{
    index = 0;
    inorder_output(T_root, 1, array);
    return index;
}

void bs_tree::output(bs_tree_node* x, int r_level)
{ /*<<<*/
    /*
     * some structured output
     */
    list< pair<bs_tree_node*,int> > l_nodes;
    pair<bs_tree_node*,int> c_node;
    int c_level;
    
    c_level = r_level;
    l_nodes.insert(l_nodes.end(), pair<bs_tree_node*,int>(x, r_level));
    
    while (!l_nodes.empty())
    {
        c_node = *(l_nodes.begin());
        
        if (c_level < c_node.second)
        {
            cout << endl;
            c_level = c_node.second;
        }
        
        cout << "(" << c_node.first->key;
        
        if (c_node.first->p == T_nil)
            cout << ",ROOT) ";
        else
            cout << ",P:" << c_node.first->p->key << ") ";
        
        if (c_node.first->left != T_nil)
            l_nodes.insert(l_nodes.end(), pair<bs_tree_node*,int>(c_node.first->left,
                                                                  c_node.second+1));
        if (c_node.first->right != T_nil)
            l_nodes.insert(l_nodes.end(), pair<bs_tree_node*,int>(c_node.first->right,
                                                                  c_node.second+1));
        l_nodes.erase(l_nodes.begin());
    }
    
    cout << endl;
} /*>>>*/

void bs_tree::remove_all(bs_tree_node* x)
{
    //recursively remove all tree elements
    if (x != T_nil)
    {
        remove_all(x->left);
        remove_all(x->right);
        
        delete x;
    }
}


