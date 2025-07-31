#include <iostream>
#include <string>
using namespace std;

struct Directory {
    string name;
    Directory* left;
    Directory* right;

    Directory(string n) : name(n), left(nullptr), right(nullptr) {}
};

Directory* rightRotate(Directory* x) {
    Directory* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

Directory* leftRotate(Directory* x) {
    Directory* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

Directory* splay(Directory* root, string name) {
    if (!root || root->name == name)
        return root;

    if (name < root->name) {
        if (!root->left) return root;

        if (name < root->left->name) {
            root->left->left = splay(root->left->left, name);
            root = rightRotate(root);
        } else if (name > root->left->name) {
            root->left->right = splay(root->left->right, name);
            if (root->left->right)
                root->left = leftRotate(root->left);
        }

        return (root->left == nullptr) ? root : rightRotate(root);
    } else {
        if (!root->right) return root;

        if (name < root->right->name) {
            root->right->left = splay(root->right->left, name);
            if (root->right->left)
                root->right = rightRotate(root->right);
        } else if (name > root->right->name) {
            root->right->right = splay(root->right->right, name);
            root = leftRotate(root);
        }

        return (root->right == nullptr) ? root : leftRotate(root);
    }
}

Directory* insert(Directory* root, string name) {
    if (!root)
        return new Directory(name);

    root = splay(root, name);

    if (root->name == name)
        return root;

    Directory* newNode = new Directory(name);

    if (name < root->name) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }

    return newNode;
}

Directory* search(Directory* root, string name) {
    return splay(root, name);
}

void displayDirectories(Directory* root) {
    if (root) {
        displayDirectories(root->left);
        cout << root->name << " ";
        displayDirectories(root->right);
    }
}

int main() {
    Directory* root = nullptr;

    string directories[] = {"home", "usr", "bin", "var", "tmp", "etc", "dev", "lib", "opt", "media", "boot"};
    int n = sizeof(directories)/sizeof(directories[0]);

    for (int i = 0; i < n; ++i) {
        root = insert(root, directories[i]);
    }

    cout << "Directory structure (inorder traversal):\n";
    displayDirectories(root);
    cout << endl;

    string searchDir = "etc";
    root = search(root, searchDir);

    if (root && root->name == searchDir)
        cout << "\nDirectory '" << searchDir << "' found and splayed to root.\n";
    else
        cout << "\nDirectory '" << searchDir << "' not found.\n";

    cout << "Directory structure after search:\n";
    displayDirectories(root);
    cout << endl;

    return 0;
}

