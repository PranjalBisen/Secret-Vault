
    //ॐ गं गणपतये नमः
    //जय श्री राम
    //ॐ नमः शिवाय
#include <bits/stdc++.h>
using namespace std;

#ifndef SECRET_BINARY_STORAGE_H
#define SECRET_BINARY_STORAGE_H

struct SecretRecord{
    char name[32];
    char secret[256];
    bool is_deleted;
};

void create_dat_file(string);
long long append_dat_file(string, SecretRecord);
void read_all_dat_file(string, SecretRecord);
bool read_next_record(fstream&,SecretRecord&);
void read_from_record_number_one_dat_file(string, SecretRecord, int);
void read_from_offset_one_dat_file(string, SecretRecord, int);

#endif
