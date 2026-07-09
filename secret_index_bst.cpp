
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


struct BSTNode{
    string key;
    ll offset;
    BSTNode* left_child;
    BSTNode* right_child;
};

void print_bst_secret(BSTNode* node){
    /*
    Just a simple Helper function to
    print the secrets in a node
    */
   cout<<"Key : "<<node->key<<" offset: "<<node->offset<<endl;
}

BSTNode* create_new_node(string key, ll offset){
    /*
    Function to create and return a new BST node 
    Since there's no info about the nodes its connected
    to, we will set left and right child to nullptr
    */
   BSTNode* node = new BSTNode();
   node->key=key;
   node->offset=offset;
   node->left_child=nullptr;
   node->right_child=nullptr;
   return node;
}

void insert_new_node_in_bst(BSTNode* new_node, BSTNode* &root){
    /*
    Simple function to insert a node in existing BST
    */
   if(!root){
    root=new_node;
    return;
   }
   if(new_node->key>root->key)insert_new_node_in_bst(new_node,root->right_child);
   else if(new_node->key<root->key)insert_new_node_in_bst(new_node,root->left_child);
   else{
    /*
    Didn't think much about duplicate records,
    Probably need to add a vector node to store them in 
    same node or just a counter to tell this exists
    multiple times
    */
   }
}

BSTNode* search_node_in_bst(string key, BSTNode* node){
    /*
    Search function which recursively searches
    to match key values to infer whether a node
    exists or not.
    */
   if(!node)return nullptr;
   if(node->key==key){
    return node;
   }
   if(key<node->key&&node->left_child) return search_node_in_bst(key,node->left_child);
   else if(key>node->key&&node->right_child) return search_node_in_bst(key,node->right_child);
   return  nullptr;
}

void preorder_traversal_of_bst(BSTNode* node){
    /*
    Simple function to print the preorder 
    traversal of BST
    */
   if(!node)return;
   cout<<node->key<<" ";
   preorder_traversal_of_bst(node->left_child);
   preorder_traversal_of_bst(node->right_child);
}

void inorder_traversal_of_bst(BSTNode* node){
    /*
    Simple function to print the inorder 
    traversal of BST
    */
   if(!node)return;
   inorder_traversal_of_bst(node->left_child);
   cout<<node->key<<" ";
   inorder_traversal_of_bst(node->right_child);
}

void postorder_traversal_of_bst(BSTNode* node){
    /*
    Simple function to print the postorder 
    traversal of BST
    */
   if(!node)return;
   postorder_traversal_of_bst(node->left_child);
   postorder_traversal_of_bst(node->right_child);
   cout<<node->key<<" ";
}

/*
preorder -> root left right
inorder -> left root right
postorder -> left right root
*/

void test_binary_search_tree(){
    /*
    Function to test the capabilites 
    of my BST
    */
   BSTNode* n1=create_new_node("Pranjal",0);
   BSTNode* n2=create_new_node("PranjalBisen",48);
   BSTNode* n3=create_new_node("GanpatiBappa",96);
   BSTNode* n4=create_new_node("IDK what to put here",144);
   insert_new_node_in_bst(n2,n1);
   insert_new_node_in_bst(n3,n1);
   insert_new_node_in_bst(n4,n1);
   BSTNode* check=search_node_in_bst("GanpatiBappa",n1);
   if(check){
    cout<<"Here is your Secret"<<endl;
    print_bst_secret(check);
   }
   else{
    cout<<"Search Failed Bruvvv,"<<endl;
    cout<<"We don't have your secret"<<endl;
   }
   preorder_traversal_of_bst(n1);
   cout<<endl;
   inorder_traversal_of_bst(n1);
   cout<<endl;
   postorder_traversal_of_bst(n1);
}
// int main() {
//     cout<<sizeof(BSTNode)<<endl;
//     test_binary_search_tree();
//     fast_io;
//     return 0;
// }