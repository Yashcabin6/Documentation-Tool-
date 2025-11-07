// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
class SymNode {
public:
    string key;
    int height;
    int count=1;
    
    SymNode* par = NULL;
    SymNode* left = NULL;
    SymNode* right = NULL;

    SymNode();
    SymNode(string k);

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
    void insert(string k);

 
    // Find the memory address corresponding to the variable in the symbol table
    int search(string k);

    // Assigns a memory address to the key in the symbol table

    // Get size
    int get_size();

    // Get root 
    SymNode* get_root();
};
class Dict {
private:
    // You can add attributes/helper functions here
    SymbolTable* di;
    string sep=" .,-:!\"\'()?[];@";
    bool help(char ch);
    void help2(SymNode* n,string s,ofstream& ss);

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};