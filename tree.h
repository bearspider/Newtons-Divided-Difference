//Jared Haddix
//TreeClass
#include <vector>
#include <string>
using namespace std;

class Tree
{
    private:
        Tree ( const Tree & );
        const Tree & operator = ( const Tree & );
    public:
        Tree (double, double, double, bool);
        Tree (double, double, bool);
        Tree (double, Tree *, Tree *);
        Tree (vector<double> &, vector<double> &);
        Tree (Tree *,Tree *, Tree *);
        ~Tree ( void )
        {
            clear();
        }

        void clear ( void )
        {
            chop(root);
            root = NULL;
        }
        void getcoefs(Tree *);
        bool operator==(const Tree *) const;
        bool operator>(const Tree *) const;
        bool operator<(const Tree *) const;
        friend ostream & operator << ( ostream & ost, const Tree & t )
        {
            t.print ( &t, 1, ost );
            return ost;
        }
        
        double xval;
        double rightchild;
        double leftchild;
        vector<double> coefficients;
        
        Tree * left;
        Tree * right;       
        Tree * root;
        bool isLeaf;
    
    private:
        void chop ( Tree * );
        void print ( const Tree *, int level, ostream & ) const;
};


