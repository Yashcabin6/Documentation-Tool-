// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;
class SymNode {
public:
    string key;
    int height;
    int book_code;
    int page;
    int paragraph;
    int sentence_no;
    
    SymNode* par = NULL;
    SymNode* left = NULL;
    SymNode* right = NULL;

    SymNode();
    SymNode(string k,int bc,int pag,int par, int sn);

    SymNode* LeftLeftRotation(); // case 1
    SymNode* RightRightRotation(); // case 2
    SymNode* LeftRightRotation(); // case 3
    SymNode* RightLeftRotation(); // case 4

    ~SymNode();
    
};
class SymbolTable {
private:
    int size = 0;
    SymNode* root = NULL;

public: 

    SymbolTable();
    ~SymbolTable();

    // Insert a key in the symbol table, there is no value now
    void insert(string k,int bc,int pag,int par, int sn);

 
    // Find the memory address corresponding to the variable in the symbol table

    // Assigns a memory address to the key in the symbol table

    // Get size
    int get_size();

    // Get root 
    SymNode* get_root();
};
class SearchEngine {
private:
    // You can add attributes/helper functions here
    SymbolTable* Se;
    vector<int>help3(string s1, string s2);
    void help4(SymNode* N,string s,int& n,Node*& re2);
public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node* search(string pattern, int& n_matches);

    /* -----------------------------------------*/
};