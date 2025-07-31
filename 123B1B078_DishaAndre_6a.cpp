#include <iostream>
#include <queue>
using namespace std;

struct BTreeNode {
    BTreeNode *left, *center, *right;
    int key1, key2;
    bool hasTwoKeys;

    BTreeNode(int k) {
        key1 = k;
        left = center = right = nullptr;
        hasTwoKeys = false;
    }

    bool isLeaf() {
        return !left && !center && !right;
    }
};

class BTree {
    BTreeNode* root;

    BTreeNode* insert(BTreeNode* node, int key) {
        if (!node) return new BTreeNode(key);

        if (!node->hasTwoKeys) {
            if (key == node->key1) return node; // duplicate not allowed

            if (node->isLeaf()) {
                if (key < node->key1) {
                    node->key2 = node->key1;
                    node->key1 = key;
                } else {
                    node->key2 = key;
                }
                node->hasTwoKeys = true;
            } else {
                if (key < node->key1)
                    node->left = insert(node->left, key);
                else
                    node->center = insert(node->center, key);
            }
        } else {
            if (key == node->key1 || key == node->key2) return node;

            if (key < node->key1)
                node->left = insert(node->left, key);
            else if (key < node->key2)
                node->center = insert(node->center, key);
            else
                node->right = insert(node->right, key);
        }

        return node;
    }

    void levelOrder(BTreeNode* root) {
        if (!root) return;
    
        queue<BTreeNode*> q;
        q.push(root);
    
        while (!q.empty()) {
            BTreeNode* curr = q.front();
            q.pop();
    
            if (curr->hasTwoKeys)
                cout << "[" << curr->key1 << ", " << curr->key2 << "] ";
            else
                cout << "[" << curr->key1 << "] ";
    
            if (curr->left) q.push(curr->left);
            if (curr->center) q.push(curr->center);
            if (curr->right) q.push(curr->right);
        }
        cout << endl;
    }
    
    BTreeNode* findMin(BTreeNode* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    BTreeNode* remove(BTreeNode* root, int key) {
        if (!root) return nullptr;

        if (!root->hasTwoKeys) {
            if (root->key1 == key && root->isLeaf()) {
                delete root;
                return nullptr;
            }

            if (key < root->key1)
                root->left = remove(root->left, key);
            else
                root->center = remove(root->center, key);
        } else {
            if (key == root->key1) {
                if (root->isLeaf()) {
                    root->key1 = root->key2;
                    root->hasTwoKeys = false;
                } else {
                    BTreeNode* succ = findMin(root->center);
                    root->key1 = succ->key1;
                    root->center = remove(root->center, succ->key1);
                }
            } else if (key == root->key2) {
                if (root->isLeaf()) {
                    root->hasTwoKeys = false;
                } else {
                    BTreeNode* succ = findMin(root->right);
                    root->key2 = succ->key1;
                    root->right = remove(root->right, succ->key1);
                }
            } else {
                if (key < root->key1)
                    root->left = remove(root->left, key);
                else if (key < root->key2)
                    root->center = remove(root->center, key);
                else
                    root->right = remove(root->right, key);
            }
        }

        return root;
    }

public:
    BTree() {
        root = nullptr;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void displayLevelOrder() {
        cout << "\nLevel Order Traversal:\n";
        levelOrder(root);
    }

    void remove(int key) {
        root = remove(root, key);
    }
};

int main() {
    BTree tree;
    int arr[] = {34, 23, 89, 12, 90, 45};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; ++i)
        tree.insert(arr[i]);

    tree.displayLevelOrder();

    cout << "\nDeleting 23\n";
    tree.remove(23);
    tree.displayLevelOrder();

    cout << "\nDeleting 89\n";
    tree.remove(89);
    tree.displayLevelOrder();

    return 0;
}
