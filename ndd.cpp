/* Jared Haddix
 * Newton's Divided Difference Calculator
 *
 * Spring 2008
 * MATH 3300 Numerical Methods
 *
 * Pseudocode:
 * a comma seperated list of xvalues and a comma seperated list of
 * f(x)-values will be entered on the command line.
 *
 * parse the command line input to single values
 *
 * take the parsed values and create a newton's divided difference tree
 *
 * from that tree extract the coefficients
 *
 * from the coefficients create a polynomial
 */

#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>
#include<vector>
#include<sstream>
#include"tree.h"

using namespace std;

void parse(string, vector<double> &);
ostream & operator<<(ostream &, const vector<double> &);

int main(int argc, const char *argv[])
{
    string xValueInput, fxValueInput;
    vector<double> xValues;
    vector<double> fxValues;
    string polynomial;
    stringstream s;

    if(argc != 3)
    {
        cerr << "Invalid command line arguments" << endl;
        cerr << "Correct syntax: " << argv[0]
            << " A B" << endl; 
        cerr << "A: [list of X values, comma separated]" << endl;
        cerr << "B: [list of f(X) values, comma seperated]" << endl;
        exit(1);
    }

    //Grab the arguments entered from the command line
    xValueInput = argv[1];
    fxValueInput = argv[2];

    //Parse the x-values and f(x)-values
    parse(xValueInput,xValues);
    parse(fxValueInput,fxValues);

    cout << "\nX-Values: " << xValues << flush;
    cout << "F(X)-Values: " << fxValues << endl; 

    //iterators to traverse the vector
    vector<double>::iterator iterx = xValues.begin();
    vector<double>::iterator iterfx = fxValues.begin();

    //Create the divided difference tree
    Tree *answer = new Tree(xValues,fxValues);

    cout << "Tree: \n" << *answer << endl;
    cout << "Coefficients: " << answer->coefficients << endl;
    vector<double>::iterator step = answer->coefficients.begin();
    int counter = 0;

    //Step through every coefficient to create the polynomial
    while(step != answer->coefficients.end())
    {
        if(counter == 0)
        {
            s.str("");
            s << *step;
            polynomial.append(s.str());
            ++counter;
        }
        else
        {
            if(*step)
            {
                polynomial.append(" + ");
                s.str("");
                s << *step;
                if(*step != 1)
                {
                    polynomial.append(s.str());
                }
                for(int i = 0; i < counter; i++)
                {
                    polynomial.append("(x - ");
                    s.str("");
                    s << xValues[i];
                    polynomial.append(s.str());
                    polynomial.append(")");  
                }
            }
            ++counter;
        }
        ++step;
    }
    cout << "Polynomial: \n" << polynomial << endl;
    return 0;
}

/* Input: string of comma seperated numbers
 *        vector<double> to hold the parsed numbers
 * Output: None
 * Return: None
 *
 * This function seperates the comma seperated values on the
 * command line into individual numbers and stores them
 * into a vector.
 */
void parse(string input, vector<double> &vars)
{
    string token;
    string::size_type start = 0;
    string::size_type end = 0;

    while(end != string::npos)
    {
        end = input.find_first_of(",",start);

        token = input.substr(start,(end-start));
        vars.push_back(atof(token.c_str()));

        start = end+1;
        token.clear();
    }
}

/* Input: vector<double> of values
 * Output: each value in the vector is output between brackets [ ]
 * Return: the ostream
 *
 * This function simply outputs a tree using the standard << operator
 */
ostream & operator<<(ostream&output, const vector<double> &vars)
{
    vector<double>::const_iterator iter = vars.begin();
    output << "[ " << flush;
    while(iter != vars.end())
    {
        output << *iter << " " << flush;
        ++iter;
    }
    output << "]" << endl;
    return output;
}
