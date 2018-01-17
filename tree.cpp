//Jared Haddix
//TreeClass
#include"tree.h"
#include<iostream>
#include<iomanip>
using namespace std;

/* Input: two vector<double>, one x-values, one f(x)-values
 * Output: None
 * Return: None
 *
 * This is a constructor for the tree class.  It will take
 * two vectors and convert them into a newton's divided
 * difference tree.
 */
Tree::Tree(vector<double> &xValues, vector<double> &fxValues)
{
    vector<double>::iterator xiter = xValues.begin();
    vector<double>::iterator fxiter = fxValues.begin();
    vector<Tree *> answer;
    vector<Tree *> temp;
    while(xiter != xValues.end() && fxiter != fxValues.end())
    {
        double numerator = (*(fxiter+1) - *fxiter);
        double denominator = (*(xiter+1) - *xiter);
        root = new Tree(numerator/denominator,*(xiter+1),*xiter,false);
        left = new Tree(*fxiter,*xiter,true);
        right = new Tree(*(fxiter+1),*(xiter+1),true);
        Tree *tempTree = new Tree(root,left,right);
        answer.push_back(tempTree);
        ++xiter;
        ++fxiter;
        if(fxiter+1 == fxValues.end())
        {
            break;
        }
    }
    while(answer.size() > 1)
    {
        temp.clear();
        vector<Tree *>::iterator iter = answer.begin();
        
        while(iter != answer.end())
        {
            double numerator = (*(iter+1))->xval - (*iter)->xval;
            double denominator = (*(iter+1))->rightchild -
                (*iter)->leftchild;
            temp.push_back(new Tree(
                        numerator/denominator,
                        *iter,
                        *(iter+1)));
            ++iter;
            if(iter+1 == answer.end())
            {
                break;
            }
        }
        answer = temp;
        
    }
    root = answer[0]->root;
    left = answer[0]->left;
    right = answer[0]->right;
    rightchild = answer[0]->rightchild;
    leftchild = answer[0]->leftchild;
    isLeaf = false;
    xval = answer[0]->xval;
    getcoefs(answer[0]);
}

/* Input:
 * Output:
 * Return:
 *
 *
 */
Tree::Tree(Tree *head, Tree *foo, Tree *bar)
{
    right = bar;
    left = foo;
    root = head;
    xval = head->xval;
    rightchild = bar->rightchild;
    leftchild = foo->leftchild;
     
    isLeaf = false;
}

/* Input: three double variables and one bool
 * Output: none
 * Return: none
 *
 * This function takes the value at the top of the tree and
 * the two values used to calculate the top of the tree and
 * then creates a tree structure.
 */
Tree::Tree(double value,double rval,double lval, bool leaf)
{
    right = NULL;
    left = NULL;
    root = NULL;
    isLeaf = leaf;
    rightchild = rval;
    leftchild = lval;
    xval = value;
}

/* Input: two double, one bool
 * Output: none
 * Return: none
 *
 * This function is used to create a tree node that is a leaf
 */
Tree::Tree(double value, double xinit,  bool leaf)
{
    right = NULL;
    left = NULL;
    root = NULL;
    isLeaf = leaf;
    xval = value;
    rightchild = xinit;
    leftchild = xinit;
}

/* Input: one double, two tree pointers
 * Output: none
 * Return: none
 *
 * This function takes a value, puts it at the head of the tree
 * then points its left pointer and right pointer to the nodes that
 * were used to calculate the input. 
 */
Tree::Tree(double value, Tree *lptr, Tree *rptr)
{
    leftchild = lptr->leftchild;
    rightchild = rptr->rightchild;
    isLeaf = false;
    right = rptr;
    left = lptr;
    root = NULL;
    xval = value;
}

/* Input: a tree
 * Output: none
 * Return: bool if the tree compared to is equal
 *
 * simply a comparison operator to verify if two
 * trees are equal in nature
 */
bool Tree::operator==(const Tree *value) const
{
    bool rVal = false;
    if(xval == value->xval)
    {
        rVal = true;
    }
    return rVal;
}

/* Input: a tree 
 * Output: none
 * Return: bool if the tree is less than the other tree
 *
 * a comparison operator to verify if one tree is less 
 * than another tree
 */
bool Tree::operator>(const Tree *value) const
{
    bool rVal = false;
    if(xval > value->xval)
    {
        rVal = true;
    }
    return rVal;
}

/* Input: a tree
 * Output: none
 * Return: bool if the tree is greater than the other tree
 *
 * a comparison operator to verify if one tree is greater
 * than another tree
 */
bool Tree::operator<(const Tree *value) const
{
    bool rVal = false;
    if(xval < value->xval)
    {
        rVal = true;
    }
    return rVal;
}

/* Input: a tree
 * Output: none
 * Return: none
 *
 * destructor class, this chops down the tree as to not leak memory
 */
void Tree::chop ( Tree * n )
{
    if ( n )
    {
        chop ( n->left );
        chop ( n->right );
        delete n;
    }
}

/* Input: tree, int and ostream
 * Output: outputs the tree in a tree form
 * Return: none
 *
 * This function prints the tree so it resembles that of a real tree
 */
void Tree::print (const Tree * n, int level, ostream & ost ) const
{
    static const int OFFSET = 6;

    if ( n )
    {
        print ( n->right, level + 1, ost );
        // output
        ost << setw( level * OFFSET ) << flush;
        ost << n->xval << flush;
        if(n->isLeaf)
        {
            ost << " : " <<  n->leftchild << endl;
        }
        else
        {
            ost << endl;
        }
        print ( n->left, level + 1, ost );

    }
}

/* Input: a tree
 * Output: none
 * Return: none
 *
 * recursively traverses the tree and puts the coefficient from each
 * left most branch into the vector at the top of the tree. These will
 * be the coefficients for the newton's divided difference equation.
 */
void Tree::getcoefs(Tree *redwood)
{
    if(redwood)
    {
        getcoefs(redwood->left);
        coefficients.push_back(redwood->xval);
    }
    
}
