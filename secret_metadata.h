
    //ॐ गं गणपतये नमः
    //जय श्री राम
    //ॐ नमः शिवाय
#include <bits/stdc++.h>
using namespace std;

#ifndef SECRET_METADATA_H
#define SECRET_METADATA_H

struct VaultMetadata{
    long long password_hash;
};

void create_metadata(string,string);
VaultMetadata read_metadata(string);
long long hash_password(string);
bool verify_password(string,string);

#endif
