// Do NOT add any other includes
#include "search.h"
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

SymNode::SymNode(string k,int bc,int pag,int par, int sn){
    key=k;
    book_code=bc;
    page=pag;
    paragraph=par;
    sentence_no=sn;
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

void SymbolTable::insert(string k,int bc,int pag,int par, int sn){
    if(k==""){
        return;
    }
    SymNode* run=root;
    SymNode* runpar=NULL;
    if(root==NULL){
        root=new SymNode(k,bc,pag,par,sn);
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
                run->left = new SymNode(k,bc,pag,par,sn);
                run->left->par=run;
                run = run->left;
                break;
            }
        }else{
            if(run->right != NULL)
                run = run->right;
            else{
                ++size;
                run->right = new SymNode(k,bc,pag,par,sn);
                run->right->par=run;
                run = run->right;
                break;
            }
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

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

SymbolTable::~SymbolTable(){
    delete root;
}
vector<int> SearchEngine::help3(string s1, string s2){
    //LPS calculation
    int one=s1.size();
    int two=s2.size();
    vector<int> ret;
    if(one<two){
        return ret;
    }
    int temp[two]={0};
    int i=0;
    for(int j=1; j<two;++j){
        if(s2[i]==s2[j]){
            ++i;
            temp[j]=i;
        }else{
            if(i==0){
                temp[j]=0;
            }else{
                temp[j]=i-1;
                i=0;
            }
        }
    }
    i=0;
    int j=0;
    while(one-i>=two-j){
        if(s1[i]==s2[j]){
            ++i;
            ++j;
        }
        if(j==two){
            ret.push_back(i-j);
            j=temp[j-1];
        }else if(i<one && s1[i]!=s2[j]){
            if(j!=0){
                j=temp[j-1];
            }else{
                ++i;
            }
        }
    }
    return ret;
}
void SearchEngine::help4(SymNode* N,string s,int& n,Node*& re2){
    if(N->left!=NULL){help4(N->left,s,n,re2);}
    vector<int> offf=help3(N->key,s);
    if(offf.size()!=0){
        for(int in: offf){
            Node*ne=new Node(N->book_code,N->page,N->paragraph,N->sentence_no,in);
            re2->left->right=ne;
            re2->left=ne->left;
            re2->left=ne;
            ne->right=re2;
        }
        n+=offf.size();
    }
    if(N->right!=NULL){help4(N->right,s,n,re2);}
}

SearchEngine::SearchEngine(){
    // Implement your function here
    Se=new SymbolTable();  
}

SearchEngine::~SearchEngine(){
    // Implement your function here  
    delete Se;
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here  
    string sent="";
    for(char c: sentence){
        char temp=tolower(c);
        sent+=temp;
    }
    Se->insert(sent,book_code,page,paragraph,sentence_no);
}

Node* SearchEngine::search(string pattern, int& n_matches){
    // Implement your function here  
    if(Se->get_root()){
        string pat="";
        for(char c: pattern){
            char temp=tolower(c);
            pat+=temp;
        }
        Node* fakehead=new Node(0,0,0,0,0);
        Node* faketail=new Node(0,0,0,0,0);
        fakehead->right=faketail;
        faketail->left=fakehead;        
        help4(Se->get_root(),pat,n_matches,faketail);
        faketail->left->right=NULL;
        delete faketail;
        Node* temp=fakehead->right;
        delete fakehead;
        return temp;
    }
    return NULL;
}