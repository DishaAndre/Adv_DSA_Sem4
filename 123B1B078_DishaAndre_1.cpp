/*
Consider the Dictionary Implementations which allow for efficient storage and retrieval of
key-value pairs using binary search trees. Each node in the tree store (key, value) pair. The
dictionary should support the following operations efficiently:
1. Insert word (Handle insertion of duplicate entry)
2. Delete word
3. Search specific word
4. Display dictionary (Traversal)
5. Mirror image of dictionary
6. Create a copy of dictionary
7. Display dictionary level wise
*/

#include<iostream>
#include<queue>
using namespace std;

// Create a struct node
struct node{
    string name;
    string mobile_no;
    node *left;
    node *right;
};

class directory{
    private:
        node *root;
    public:
        directory(){
            root = NULL;
        }
        void add_contact(string n, string p){
            node *nn;
            nn = new node;
            if(!nn)
                return;
            nn -> name = n;
            nn -> mobile_no = p;
            nn -> left = NULL;
            nn -> right = NULL;
            if(!root){
                root = nn;
                return;
            }
            node *ptr = root;
            while(ptr){
                if(n == ptr-> name){
                    cout<<"Duplicate Entry.Word already exists."<<endl;
                    delete nn;
                    return;
                }
                if(n < ptr -> name){
                    if(ptr -> right == NULL){
                        ptr -> right = nn;
                        return;
                }
                ptr = ptr -> right;
                }
                else{
                if(ptr -> left == NULL){
                    ptr -> left = nn;
                    return;
                }
                ptr = ptr -> left;
            }
        }
    }
        void inorder_rec(node *r){
            if(!r)
                return;
            inorder_rec(r-> left);
                cout<<r -> name<<" : "<<r -> mobile_no<<endl;
            inorder_rec(r -> right);
                return;
            }

        void inorder(){
            if(!root){
                cout<<"Directory is empty."<<endl;
                return;
            }
            cout<<"Directory"<<endl;
            inorder_rec(root);
            cout<<endl;
        }        
        bool search(string n){
            node *ptr = root;
            while(ptr){
                if(ptr -> name == n){
                cout<<"Found! ---->\t"<<ptr -> name<<":"<<ptr -> mobile_no<<endl;
                return true;
                }
                else if(ptr -> name < n){
                    ptr = ptr -> right;
                }
                else{
                    ptr = ptr ->left;
                }   
            }
            cout<<"Contact not found"<<endl;
            return false;


        }
        int height(node *p){
            if( !p)
                return 0;
            int left_ht = height(p -> left);
            int right_ht = height(p -> right);

            return left_ht > right_ht ? left_ht + 1: right_ht + 1;
        }

        node* Inprec(node* p) {
        while (p && p-> right)
             p = p-> right;
        return p;
        }
        node* Insucc(node* p) {
        while (p && p->left) 
            p = p->left;
        return p;
        }
    node* Delete(node* p, string n) {
        if (!p) return NULL;

        if (p->left == NULL && p->right == NULL) {
            if (p == root) root = NULL;
            cout << "Deleted: " << p->name << endl;
            delete p;
            return NULL;
        }

        if (n < p->name) {
            p->left = Delete(p->left, n);
        } else if (n > p->name) {
            p->right = Delete(p->right, n);
        } else {
            node* t;
            if (height(p->left) > height(p->right)) {
                t = Inprec(p->left);
                p->name = t->name;
                p->mobile_no = t->mobile_no;
                p->left = Delete(p->left, t->name);
            } else {
                t = Insucc(p->right);
                p->name = t->name;
                p->mobile_no= t->mobile_no;
                p->right = Delete(p->right, t->name);
            }
        }
        return p;
    }
    void deletenode(string n) {
        root = Delete(root, n);
    }
    node* mirror(node* p) {
        if (!p) return NULL;

        node* temp = p->left;
        p->left = mirror(p->right);
        p->right = mirror(temp);

        return p;
    }
    void mirror_tree() {
        root = mirror(root);
        
    }
    void levelOrder(node* root) {
        if (!root) return;

        queue<node*> q;
        q.push(root);

        while (!q.empty()) {
            node* temp = q.front();
            q.pop();
            cout << temp->name << " : " << temp->mobile_no << endl;

            if (temp->left) q.push(temp->left);
            if (temp->right) q.push(temp->right);
        }
    }

    void displayLevelWise() {
        if (!root) {
            cout << "Directory is empty\n";
            return;
        }
        cout << "\nLevel-wise:\n";
        levelOrder(root);
    }
   node* copyTree(node* p) {
        if (!p) return NULL;
        node* newNode = new node;
        if(!newNode) return NULL;
        newNode->name = p->name;
        newNode->mobile_no = p->mobile_no;
        newNode->left = copyTree(p->left);
        newNode->right = copyTree(p->right);
        return newNode;
    }

    directory createCopy() {
        directory newDict;
        newDict.root = copyTree(root);
        return newDict;
    }
     
};

       

int main(){
    directory d1;
    cout<<endl;
    cout<<"*** PHONE DIRECTORY ***"<<endl;
    cout<<endl;
    d1.add_contact("Disha", "1234567867");
    d1.add_contact("Henry", "9824548412");
    d1.add_contact("Sana","7654458872");
    d1.add_contact("Onkar", "8746247216");
    d1.add_contact("Alice", "5748392543");
   
    cout << "Inorder traversal of the contact directory:" << endl;
    d1.inorder();

    cout<<"Searching Disha's contact no.: "<<endl;
    d1.search("Disha");
    cout<<endl;
    cout<<"Searching Ann's contact no.: "<<endl;
    d1.search("Ann");
    cout<<endl;

    d1.deletenode("Sana");
    d1.inorder();

    d1.displayLevelWise();
    cout<<endl;
    cout<<"Copy:"<<endl;
    directory copy = d1.createCopy();
    copy.inorder();

    cout<<endl;
    cout<<"Mirrored tree: "<<endl;
    d1.mirror_tree();
    d1.inorder();
    return 0;
}