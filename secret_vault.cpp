
// ॐ गं गणपतये नमः
// जय श्री राम
// ॐ नमः शिवाय
#include "secret_binary_storage.h"
#include "secret_bloom_filter.h"
#include "secret_index_bst.h"
#include "secret_metadata.h"
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
const ll MOD = 1e9 + 7;
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
#define fast_io                                                                \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORR(i, a, b) for (int i = (a); i >= (b); --i)
#define TESTS                                                                  \
  int t;                                                                       \
  cin >> t;                                                                    \
  while (t--)                                                                  \
    solve();
#define mem(x, v) memset(x, v, sizeof(x))

// Bloom Filter config
const int BLOOM_SIZE = 8192;

SecretRecord create_record_helper(string key, string secret) {
  /*
  Simple helper function to create the secretrecord struct
  */
  SecretRecord record;
  strcpy(record.name, key.c_str());
  strcpy(record.secret, secret.c_str());
  record.is_deleted = false;
  return record;
}

void insert_secret(string vault_file_name, BSTNode *&root,
                   vector<bool> &bloom) {
  /*
  Function to store a secret, now with bloom filter
  Bloom says definitely not present -> straight insert
  Bloom says maybe present -> check BST to confirm
  If actually duplicate -> reject, else insert
  */
  string key, secret;
  cout << "Enter Your Name Bruvvv" << endl;
  cin.ignore();
  getline(cin, key);

  if (lookup_bloom_filter(bloom, key, BLOOM_SIZE)) {
    /*
    Bloom says maybe present, gotta check BST to be sure
    */
    BSTNode *existing = search_node_in_bst(key, root);
    if (existing) {
      /*
      Check if the record is actually alive in .dat
      BST can have stale entries from soft deletes
      */
      SecretRecord temp;
      fstream file(vault_file_name, ios::binary | ios::in);
      file.seekg(existing->offset);
      file.read((char *)&temp, sizeof(temp));
      file.close();
      if (!temp.is_deleted) {
        no;
        cout << "This name already exists bruv, no duplicates allowed" << endl;
        return;
      }
    }
  }

  cout << "Its time to know your secret" << endl;
  getline(cin, secret);

  SecretRecord secretrecord = create_record_helper(key, secret);
  ll current_write_offset = append_dat_file(vault_file_name, secretrecord);
  BSTNode *new_node = create_new_node(key, current_write_offset);
  insert_new_node_in_bst(new_node, root);
  insert_bloom_filter(bloom, key, BLOOM_SIZE);
  cout << "Secret inserted successfully" << endl;
}

bool vault_exists(string vault_file_name) {
  /*
  Function to check if there is an existing
  vault with same name
  */
  fstream file(vault_file_name, ios::binary | ios::in);
  return file.good();
}

BSTNode *rebuild_bst_from_file(string vault_file_name, vector<bool> &bloom) {
  /*
  We already had a bst before we killed the program
  so now we gotta rebuild the tree from the secret vault
  Also rebuilds bloom filter in the same pass, one read
  two structures rebuilt, beautiful
  */
  BSTNode *root = nullptr;
  fstream file(vault_file_name, ios::binary | ios::in);
  if (!file) {
    cout << "Error while opening vault for rebuild" << endl;
    return root;
  }
  SecretRecord record;
  ll offset = 0;
  while (read_next_record(file, record)) {
    if (!record.is_deleted) {
      BSTNode *new_node = create_new_node(string(record.name), offset);
      insert_new_node_in_bst(new_node, root);
      insert_bloom_filter(bloom, string(record.name), BLOOM_SIZE);
    }
    offset += sizeof(SecretRecord);
  }
  file.close();
  return root;
}

void search_secret(string vault_file_name, BSTNode *&root,
                   vector<bool> &bloom) {
  /*
  Search flow now goes through bloom filter first
  Bloom says definitely not present -> return immediately
  Bloom says maybe -> check BST -> check .dat -> print
  */
  cout << "Tell me what you wanna search for" << endl;
  string key;
  cin.ignore();
  getline(cin, key);

  if (!lookup_bloom_filter(bloom, key, BLOOM_SIZE)) {
    /*
    Bloom says definitely not present, no need to touch BST
    */
    no;
    cout << "Sorry bruv we don't have your secret" << endl;
    return;
  }

  BSTNode *searched_node = search_node_in_bst(key, root);
  if (!searched_node) {
    no;
    cout << "Sorry bruv we don't have your secret" << endl;
  } else {
    ll searched_offset = searched_node->offset;
    SecretRecord temp;
    fstream file(vault_file_name, ios::binary | ios::in);
    file.seekg(searched_offset);
    file.read((char *)&temp, sizeof(temp));
    file.close();
    if (temp.is_deleted) {
      no;
      cout << "Sorry bruv we don't have your secret" << endl;
    } else {
      yes;
      print_secret_record(temp);
    }
  }
}

void delete_secret(string vault_file_name, BSTNode *&root) {
  /*
  Function to soft delete a secret
  BST finds offset, then we mark is_deleted=true
  in the .dat file, BST node stays as is
  Bloom filter stays as is, cant delete from bloom lol
  */
  cout << "Who's secret do you wanna delete bruv" << endl;
  string key;
  cin.ignore();
  getline(cin, key);

  BSTNode *searched_node = search_node_in_bst(key, root);
  if (!searched_node) {
    no;
    cout << "No such secret exists bruvvv" << endl;
  } else {
    ll searched_offset = searched_node->offset;
    if (soft_delete_record(vault_file_name, searched_offset)) {
      cout << "Secret Deleted Successfully" << endl;
    } else {
      cout << "Deletion Failed" << endl;
    }
  }
}

void menu() {
  /*
  The main menu, now with authorization and bloom filter
  Every component has a purpose now
  Metadata -> auth, Bloom -> fast negative lookup
  BST -> exact indexing, .dat -> persistent storage
  */
  string vault;
  cout << "What should your vault's name be?" << endl;
  getline(cin, vault);
  string vault_file_name = vault + ".dat";
  BSTNode *root = nullptr;
  vector<bool> bloom(BLOOM_SIZE, false);

  if (vault_exists(vault_file_name)) {
    /*
    Vault exists, authenticate first then rebuild
    */
    cout << "Vault found! Enter your password bruv" << endl;
    string password;
    getline(cin, password);
    if (!verify_password(vault, password)) {
      cout << "Wrong password bruv, get outta here" << endl;
      return;
    }
    cout << "Password verified! Recovering vault..." << endl;
    root = rebuild_bst_from_file(vault_file_name, bloom);
    cout << "BST and Bloom Filter rebuilt successfully" << endl;
  } else {
    /*
    New vault, ask for password and create everything
    */
    cout << "New vault! Set your password bruv" << endl;
    string password;
    getline(cin, password);
    create_metadata(vault, password);
    create_dat_file(vault);
  }

  while (true) {
    cout << "Welcome to My Secret Vault" << endl;
    cout << "1. Insert Secret" << endl;
    cout << "2. Search Secret" << endl;
    cout << "3. Delete Secret" << endl;
    cout << "4. Print all Secrets like a madman" << endl;
    cout << "5. I'm a loser, Byeeee" << endl;

    int choose;
    cin >> choose;

    if (choose == 1) {
      insert_secret(vault_file_name, root, bloom);
    } else if (choose == 2) {
      search_secret(vault_file_name, root, bloom);
    } else if (choose == 3) {
      delete_secret(vault_file_name, root);
    } else if (choose == 4) {
      SecretRecord temp;
      read_all_dat_file(vault_file_name, temp);
    } else if (choose == 5) {
      cout << "Bye loseerrrr" << endl;
      break;
    } else {
      cout << "Read properly and enter bruvvv" << endl;
    }
  }
  inorder_traversal_of_bst(root);
}

int main() {
  /*
  Simple flow, first create a secret.dat file,
  ask user to give key and their secret,
  make a record from that and after that make
  a node from same record and append to BST.
  */
  fast_io;
  menu();
  return 0;
}