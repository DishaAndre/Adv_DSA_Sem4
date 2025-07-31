#include <iostream>
using namespace std;

struct Node {
    int player_id, score, bf;
    Node *left, *right, *parent;
};


class AVL {
private:
    Node *root;
public:
    AVL() { root = NULL; }
    
    int height(Node *root) {
        if (!root) return -1;
        int lh = height(root->left);
        int rh = height(root->right);
        return max(lh, rh) + 1;     
    }

    void LL_rotate(Node* i) {
        Node* j = i->left;
        if(i == root) {
            root = j;
        }
        j->parent = i->parent;
        i->parent = j;
        j->right = i;
        i->left = nullptr;
        updateBalanceFactors(i);
    }
    
    void RR_rotate(Node* i) {
        Node* j = i->right;
        if(i == root) {
            root = j;
        }
        j->parent = i->parent;
        i->parent = j;
        j->left = i;
        i->right = nullptr;
        updateBalanceFactors(i);
    }
    
    void LR_rotate(Node* i) {
        Node* j = i->left;
        Node* k = j->right;
        j->parent = k;
        k->parent = i;
        k->left = j;
        j->right = nullptr;
        LL_rotate(i);
    }
    
    void RL_rotate(Node* i) {
        Node* j = i->right;
        Node* k = j->left;
        j->parent = k;
        k->parent = i;
        k->right = j;
        j->left = nullptr;
        RR_rotate(i);
    }
    

    void updateBalanceFactors(Node *node) {
        Node *r = node;
        while (r) {
            r->bf = height(r->left) - height(r->right);
            r = r->parent;
        }
    }

    
    void insert(int player_id, int score) {
        Node *nn = new Node;
        if (!nn) return;
    
        nn->left = nn->right = nn->parent = NULL;
        nn->bf = 0;
        nn->player_id = player_id;  
        nn->score = score;          
    
        if (!root) {
            root = nn;
            return;
        }
    
        Node *p = root, *q = NULL;
    
        while (p) {
            q = p;
            if (p->score == score) {  
                delete nn;
                return;
            }
            p = (p->score < score) ? p->right : p->left; 
        }
    
        nn->parent = q;
    
        if (q->score < score)
            q->right = nn;
        else
            q->left = nn;
    
        
        Node *r = nn->parent;
        Node *i = NULL;  
    
        while (r) {
            r->bf = height(r->left) - height(r->right);
    
            if (r->bf == 2 || r->bf == -2) {
                if (!i) i = r;  
            }
    
            r = r->parent;
        }
    
        
        if (!i) return;
    
        if (i->bf == 2) {
            if (score < i->left->score)  
                LL_rotate(i);
            else  
                LR_rotate(i);
        } 
        else if (i->bf == -2) {
            if (score > i->right->score) 
                RR_rotate(i);
            else  
                RL_rotate(i);
        }
    }
    
    void leaderboard_2(Node *p) {
        if (!p) return;
        leaderboard_2(p->right);
        cout << "Player ID: " << p->player_id << ", Score: " << p->score << endl;
        leaderboard_2(p->left);
    }

    void leaderboard(){
        if(!root){
            cout<<"Leaderboard is empty.\n";
            return;
        }
        cout<<"Leaderboard:- \n"<<endl;
        leaderboard_2(root);

    }

    Node* Insucc(Node* p) {
        while (p && p->left) p = p->left;
        return p;
    }

    Node* Delete(Node* p, int key) {
        if (!p) return NULL;
    
        if (!p->left && !p->right) {  
            if (p == root) root = NULL;
            cout << "Deleted player: " << p->player_id << endl;
            delete p;
            return NULL;
        }
    
        if (key < p->player_id) {
            p->left = Delete(p->left, key);
        } 
        else if (key > p->player_id) {
            p->right = Delete(p->right, key);
        } 
        else {
                Node * t;  
                if (p->left && p->right) {  
                t = Insucc(p->right);  
                p->player_id = t->player_id;
                p->score = t->score;
                p->right = Delete(p->right, t->player_id);
                } 
                else {  
                Node* child = (p->left) ? p->left : p->right;
                if (!child) {  
                    if (p == root) root = NULL;
                    delete p;
                    return NULL;
                } 
                else {  
                    *p = *child;  
                    delete child;
                }
            }
        }
    
        
        p->bf = height(p->left) - height(p->right);
    
        
        if (p->bf > 1) {
            if (height(p->left->left) >= height(p->left->right)) {
                LL_rotate(p);
            } else {
                LR_rotate(p);
            }
        }
        if (p->bf < -1) {
            if (height(p->right->right) >= height(p->right->left)) {
                RR_rotate(p);
            } else {
                RL_rotate(p);
            }
        }
    
        return p;
    }

    void deletenode(int key) {
        root = Delete(root, key);
    }
    
    
};


int main() {
    AVL g1;

    
    g1.insert(001, 200);
    g1.insert(010, 540);
    g1.insert(007, 900);
    g1.insert(005, 450);
    g1.insert(011, 750);

   
    cout << "\nBefore Removing Players:\n";
    g1.leaderboard();

    g1.deletenode(001);

    cout << "\nAfter Removing Players:\n";
    g1.leaderboard();

    
    return 0;
}