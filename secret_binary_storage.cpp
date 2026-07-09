
    //ॐ गं गणपतये नमः
    //जय श्री राम
    //ॐ नमः शिवाय
#include <bits/stdc++.h>
using namespace std;

// Typedefs for convenience
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef unordered_map<int, int> umii;
typedef unordered_map<ll, ll> umll;
typedef map<int, int> mii;
typedef map<ll, ll> mll;
typedef set<int> si;
typedef set<ll> sll;

// Constants
const ll MOD = 1e9+7;
const int M = 998244353;
const int N = 3e5 + 10;
const int N_sieve = 1000000;
const ll INF = LLONG_MAX;
const ld PI = acos(-1.0);
const ld EPS = 1e-9;

// Utility Macros
#define pb push_back
#define F first
#define S second
#define yes cout << "YES\n"
#define no cout << "NO\n"
#define bob cout << "Bob\n"
#define alice cout << "Alice\n"
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define fast_io ios_base::sync_with_stdio(false); cin.tie(0);
#define FOR(i, a, b) for(int i = (a); i < (b); ++i)
#define FORR(i, a, b) for(int i = (a); i >= (b); --i)
#define TESTS int t; cin >> t; while(t--) solve();
#define mem(x, v) memset(x, v, sizeof(x))


struct SecretRecord{
    /*
    Struct SecretRecord which contains user name, user secret 
    and a is_deleted flag.
    Will be used as a node and storage format later.
    */
    char name[32];
    char secret[256];
    bool is_deleted;
};

void print_secret_record(SecretRecord secretRecord){
    /*
    Helper Function to print the complete struct
    */
   cout<<"Name : "<<secretRecord.name<<" Secret : "<<secretRecord.secret<<endl;
}

void print_current_write_offset(fstream& file){
    cout<<"Current write offset is : "<<file.tellp()<<endl;
}

void print_current_read_offset(fstream& file){
    cout<<"Current read offset is : "<<file.tellg()<<endl;
}

void create_dat_file(string s){
    /*
    Simple function to create a data file 
    */
    fstream created_file(s+".dat", ios::binary|ios::out);
    print_current_write_offset(created_file);
    if(!created_file){
        no;
        cout<<"Error while creating file"<<endl;
        return ;
    }
    cout<<"File : "<<s<<".dat Successfully Created"<<endl;
    print_current_write_offset(created_file);
    created_file.close();
}

ll append_dat_file(string file_name, SecretRecord secretRecord){
    /*
    Here we have written code to append value at the end of file
    */
    fstream file(file_name, ios::binary|ios::out|ios::app);
    if(!file){
        no;
        cout<<"Error while creating file"<<endl;
        return -1;
    }
    print_current_write_offset(file);
    ll current_write_offset=file.tellp();
    file.write((char*)&secretRecord,sizeof(secretRecord));
    print_current_write_offset(file);
    cout<<"Data Appended Successfully"<<endl;
    cout<<"Size of Struct: "<<sizeof(secretRecord)<<endl;
    file.close();
    return current_write_offset;
}

void read_all_dat_file(string file_name, SecretRecord secretRecord){
    /*
    Function to read the complete file contents
    */
   fstream file(file_name,ios::binary|ios::in);
   print_current_read_offset(file);
   if(!file){
        no;
        cout<<"Error while creating file"<<endl;
        return ;
    }
    while(file.read((char*)&secretRecord, sizeof(secretRecord))){
        if(!secretRecord.is_deleted){
            print_secret_record(secretRecord);
            print_current_read_offset(file);
        }
    }
    print_current_read_offset(file);
    cout<<endl;
    cout<<"Complete File Read Successfully"<<endl;
    file.close();
}

bool read_next_record(fstream& file,SecretRecord& record){
    /*
    Literally a oneliner to read next record
    */
    return (bool)file.read((char*)&record,sizeof(record));
}

bool soft_delete_record(string file_name,int offset){
    /*
    Soft deletes a record by setting is_deleted=true
    at the given offset, record stays physically
    */
    fstream file(file_name,ios::binary|ios::in|ios::out);
    if(!file){
        cout<<"Error while opening file for soft delete"<<endl;
        return false;
    }
    SecretRecord record;
    file.seekg(offset);
    file.read((char*)&record,sizeof(record));
    record.is_deleted=true;
    file.seekp(offset);
    file.write((char*)&record,sizeof(record));
    file.close();
    return true;
}

void read_from_record_number_one_dat_file(string file_name, SecretRecord secretRecord, int index){
    /*
    Function to read exactly one Struct from a file
    according to the given record number
    */
   fstream file(file_name,ios::binary|ios::in);
   print_current_read_offset(file);
   if(!file){
        no;
        cout<<"Error while creating file"<<endl;
        return ;
    }
    file.seekg(index*sizeof(secretRecord));
    print_current_read_offset(file);
    if(file.read((char*)&secretRecord,sizeof(secretRecord))){
        if(!secretRecord.is_deleted){
            print_secret_record(secretRecord);
        }
        else{
            cout<<"This is Soft Deleted"<<endl;
            print_secret_record(secretRecord);
        }
    }
    print_current_read_offset(file);
    cout<<"Successfully read one struct record"<<endl;
    file.close();
}

void read_from_offset_one_dat_file(string file_name, SecretRecord secretRecord, int offset){
    /*
    Function to read exactly one Struct from a file
    at a given offset
    */
   fstream file(file_name,ios::binary|ios::in);
   print_current_read_offset(file);
   if(!file){
        no;
        cout<<"Error while creating file"<<endl;
        return ;
    }
    file.seekg(offset);
    print_current_read_offset(file);
    if(file.read((char*)&secretRecord,sizeof(secretRecord))){
        if(!secretRecord.is_deleted){
            print_secret_record(secretRecord);
        }
        else{
            cout<<"This is Soft Deleted"<<endl;
            print_secret_record(secretRecord);
        }
    }
    print_current_read_offset(file);
    cout<<"Successfully read one struct record"<<endl;
    file.close();
}

void test_file_handling(){
    /*
    Simple test function to test create, append, and various 
    read capabilites in .dat files.
    */
    SecretRecord s1={"Pranjal","It is currently way past my bedtime lol",false};
    SecretRecord s2={"Pranjal Bisen","I don't have to get up early tomorrow anyways",false};
    SecretRecord s3={"GanpatiBappa","Ganpati Bapppaaaa Morryyyyaaaaaaa",false};
    SecretRecord s4={"Naav Visarlo","Idk what to write here now",true};
    cout<<"Size of Struct : "<<sizeof(s1)<<endl;
    create_dat_file("Secret");
    append_dat_file("Secret.dat",s1);
    append_dat_file("Secret.dat",s2);
    append_dat_file("Secret.dat",s3);
    append_dat_file("Secret.dat",s4);
    read_all_dat_file("Secret.dat",s1);
    read_from_record_number_one_dat_file("Secret.dat",s1,2);
    read_from_offset_one_dat_file("Secret.dat",s1,100);
    read_from_offset_one_dat_file("Secret.dat",s1,289);
    read_from_record_number_one_dat_file("Secret.dat",s1,3);

}
/*
tellp() -> Current write offset.
tellg() -> Current read offset.
seekp() -> Move the write offset.
seekg() -> Move the read offset.
*/
// int main() {
//     fast_io;
//     // test_file_handling();
//     return 0;
// }