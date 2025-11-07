// Do NOT add any other includes
#include "dict.h"
int max(int a, int b){
    if(a>b){
        return a;
    }
    return b;
}
int get_height(SymNode* nd){
    if(nd==NULL){
        return -1;
    }
    return nd->height;
}
SymNode::SymNode(){

}

SymNode::SymNode(string k){
    key=k;
    height=0;
    count=1;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* self=left->par;
    SymNode* ret=left;
    left=ret->right;
    if(left!=NULL){
        ret->right->par=self;
    }    
    ret->right=self;
    ret->par=self->par;
    self->par=ret;
    self->height=1+max(get_height(self->right),get_height(self->left));
    ret->height=1+max(get_height(ret->right),get_height(ret->left));
    return ret;
}

SymNode* SymNode::RightRightRotation(){
    SymNode* self=right->par;
    SymNode* ret=right;
    right=ret->left;
    if(right!=NULL){
        ret->left->par=self;
    }
    ret->left=self;
    ret->par=self->par;
    self->par=ret;
    self->height=1+max(get_height(self->right),get_height(self->left));
    ret->height=1+max(get_height(ret->right),get_height(ret->left));
    return ret;
}

SymNode* SymNode::LeftRightRotation(){
    SymNode* self=left->par;
    SymNode* temp=left;
    SymNode* ret=left->right;
    temp->right=ret->left;
    self->left=ret->right;
    if(temp->right!=NULL){
        temp->right->par=temp;
    }
    if(self->left!=NULL){
        self->left->par=self;
    }
    ret->left=temp;
    ret->right=self;
    ret->par=self->par;
    ret->right->par=ret;
    ret->left->par=ret;
    self->height=1+max(get_height(self->right),get_height(self->left));
    temp->height=1+max(get_height(temp->right),get_height(temp->left));
    ret->height=1+max(get_height(ret->right),get_height(ret->left));
    return ret;
}

SymNode* SymNode::RightLeftRotation(){
    SymNode* self=right->par;
    SymNode* temp=right;
    SymNode* ret=right->left;
    temp->left=ret->right;
    self->right=ret->left;
    if(temp->left!=NULL){
        temp->left->par=temp;    
    }
    if(self->right!=NULL){
        self->right->par=self;
    }
    ret->right=temp;
    ret->left=self;
    ret->par=self->par;
    ret->left->par=ret;
    ret->right->par=ret;
    self->height=1+max(get_height(self->right),get_height(self->left));
    temp->height=1+max(get_height(temp->right),get_height(temp->left));
    ret->height=1+max(get_height(ret->right),get_height(ret->left));
    return ret;
}

SymNode::~SymNode(){

}
int mx(int a, int b){
    if(a>b){
        return a;
    }
    return b;
}
int get_ht(SymNode* nd){
    if(nd==NULL){
        return -1;
    }
    return nd->height;
}
int get_bal(SymNode* nd){
    if(nd==NULL){
        return 0;
    }
    return get_ht(nd->left)-get_ht(nd->right);
}
SymNode* findpred(SymNode* nd){
    while(nd->right!=NULL){
        nd=nd->right;
    }
    return nd;
}
SymbolTable::SymbolTable(){
    root=NULL;
    size=0;
}

void SymbolTable::insert(string k){
    if(k==""){
        return;
    }
    SymNode* run=root;
    SymNode* runpar=NULL;
    if(root==NULL){
        root=new SymNode(k);
        ++size;
        return;
    }
    while(true){
        runpar=run;
        if(run->key>k){
            if(run->left != NULL)
                run = run->left;
            else{
                ++size;
                run->left = new SymNode(k);
                run->left->par=run;
                run = run->left;
                break;
            }
        }else if(run->key<k){
            if(run->right != NULL)
                run = run->right;
            else{
                ++size;
                run->right = new SymNode(k);
                run->right->par=run;
                run = run->right;
                break;
            }
        }else{
            run->count+=1;
            return;
        }
    }
    while(runpar!=NULL){
        runpar->height=1+mx(get_ht(runpar->left),get_ht(runpar->right));
        SymNode* ran=runpar->par;
        if(get_bal(ran)>1){
            if(ran->par==NULL){
                if(get_bal(ran->left)<0){
                    root=ran->LeftRightRotation();
                }else{
                    root=ran->LeftLeftRotation();
                }
            }else{
                if(ran->par->left==ran){
                    if(get_bal(ran->left)<0){
                        ran->par->left=ran->LeftRightRotation();
                    }else{
                        ran->par->left=ran->LeftLeftRotation();
                    }
                }else{
                    if(get_bal(ran->left)<0){
                        ran->par->right=ran->LeftRightRotation();
                    }else{
                        ran->par->right=ran->LeftLeftRotation();
                    }
                }
            }
            break;
        }else if(get_bal(ran)<-1){
            if(ran->par==NULL){
                if(get_bal(ran->right)>0){
                    root=ran->RightLeftRotation();
                }else{
                    root=ran->RightRightRotation();
                }
            }else{
                if(ran->par->left==ran){
                    if(get_bal(ran->right)>0){
                        ran->par->left=ran->RightLeftRotation();
                    }else{
                        ran->par->left=ran->RightRightRotation();
                    }
                }else{
                    if(get_bal(ran->right)>0){
                        ran->par->right=ran->RightLeftRotation();
                    }else{
                        ran->par->right=ran->RightRightRotation();
                    }
                }
            }
            break;
        }
        run=run->par;
        runpar=runpar->par;
    }   
}

int SymbolTable::search(string k){
    SymNode* run=root;
    if(root->key==k){
        return root->count;
    }
    while(run!=NULL){
        if(run->key==k){
            return run->count;
        }else if(run->key>k){
            run=run->left;
        }else{
            run=run->right;
        }
    }
    return 0;
}
int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    delete root;
}
bool Dict::help(char ch){
    for(char c: sep){
        if(ch==c){
            return true;
        }
    }
    return false;
}
void Dict::help2(SymNode* n,string s,ofstream& ss){
    if(n->left!=NULL){help2(n->left,s,ss);}
    ss<<n->key<<", "<<n->count<<endl;
    if(n->right!=NULL){help2(n->right,s,ss);}
}
Dict::Dict(){
    di=new SymbolTable();
    // Implement your function here    
}

Dict::~Dict(){
    delete di;
    // Implement your function here    
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here  
    string curr="";
    char temp;
    for(char c: sentence){
        if(help(c)){
            di->insert(curr);
            curr="";
        }else{
            temp=tolower(c);
            curr+=temp;
        }
    }
    di->insert(curr);
}

int Dict::get_word_count(string word){
    // Implement your function here  
    string ret="";
    char temp;
    for(char c:word){
        temp=tolower(c);
        ret+=temp;
    }
    return di->search(ret);
}

void Dict::dump_dictionary(string filename){
    // Implement your function here  
    if(di->get_root()){
        ofstream writ2;
        writ2.open(filename,ios::app);
        help2(di->get_root(),filename,writ2);
        writ2.close();
    }
}