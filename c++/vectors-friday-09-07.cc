// NOTE!!! Read the README to learn how to compile this

/*
 * main.cpp: Demonstrates some usages of vector, recursion, and
 * higher order functions.
 *  Created on: Sep 7, 2017
 *      Author: Kristopher Micinski
 */
#include <string>
#include <iostream>
#include <locale>   // The *right* way to handle international chars
#include <assert.h>

// This is a comment

/* So is this.. */

// You can read a good tutorial on vectors here:
// http://www.cprogramming.com/tutorial/stl/vector.html
#include <vector>

// We're going to use `transform` from algorithm
// http://www.cplusplus.com/reference/algorithm/transform/
#include <algorithm>

// Make it so that we don't have to preface a bunch of stuff with std::
using namespace std;

// Write this first
string capitalize(string input) // Note: as someone commented
{
    if (input.length() > 0) {
        input[0] = toupper(input[0], locale());
    }
    return input;
}

vector<string> capitalizeEach(vector<string> &strings)
{
    vector<string> vec(strings);

    // More complicated version
    // This uses the capabilities of a C++ iterator
    // http://www.cprogramming.com/tutorial/stl/iterators.html

/*    for (vector<string>::iterator iter = vec.begin();
            iter != vec.end();
            iter++) {
        *iter = capitalize(*iter);
    } */
    for(int i = 0;
        i < strings.size();
        i++) {
        vec[i] = capitalize(strings[i]);
    }

    return vec;
}

// Write this and then make it recursive
vector<string> capitalizeEachRecursive(vector<string> v, int i)
{
    if (i >= v.size()) {
        return v;
    }

    v[i] = capitalize(v[i]);
    return capitalizeEachRecursive(v, i+1);
}

int main(int argc, char *argv[])
{
    vector<string> arguments;

    for (int i = 1; i < argc; i++) {
        arguments.push_back(argv[i]);
    }

    vector <string> capitalized_args = capitalizeEachRecursive(arguments, 0);
    for (string arg : capitalized_args) {
        cout << "argument: " << arg << "\n";
    }

    // Read: http://www.cprogramming.com/c++11/c++11-lambda-closures.html
    vector<string> transformedArgs;

    // This is the magic...
    transform(arguments.begin()
             ,arguments.end()
             ,back_inserter(transformedArgs)
                  ,[] (string x) -> string {return capitalize(x);});

    for (string arg : transformedArgs) {
        cout << "argument: " << arg << "\n";
    }

    return 0;
}
