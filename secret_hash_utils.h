
    //ॐ गं गणपतये नमः
    //जय श्री राम
    //ॐ नमः शिवाय
#include <bits/stdc++.h>
using namespace std;

#ifndef SECRET_HASH_UTILS_H
#define SECRET_HASH_UTILS_H

string clean_string(string);
long long mul_mod(long long,long long,long long);
long long hash_polynomial_raw(string);
int hash_ascii(string,int);
int hash_polynomial(string,int);
int hash_djb2(string,int);
int hash_jenkins(string,int);

#endif
