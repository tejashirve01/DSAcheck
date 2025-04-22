#include <iostream>
#include <limits.h> // Include for INT_MIN and INT_MAX

using namespace std;

// Node class definition
class node {
public:
    int data;
    node* left;
    node* right;

    node(int d) {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

// Function to build the binary tree
node* buildTree(node* root) {
    cout << "Enter the data in node (enter -1 for NULL): " << endl;
    int data;
    cin >> data;

    if (data == -1) {
        return NULL;
    }

    root = new node(data);
    
    cout << "Enter data for inserting in left of " << data << endl;
    root->left = buildTree(root->left);
    
    cout << "Enter data for inserting in right of " << data << endl;
    root->right = buildTree(root->right);
    
    return root;
}

// Helper function to validate BST
bool isBST(node* root, int min, int max) {
    if (root == NULL) {
        return true;
    }

    if (root->data > min && root->data < max) {
        bool left = isBST(root->left, min, root->data);
        bool right = isBST(root->right, root->data, max);
        return left && right;
    } else {
        return false;
    }
}

// Main function to validate BST
bool validateBST(node* root) {
    return isBST(root, INT_MIN, INT_MAX);
}

int main() {
    node* root = NULL;

    // Build the tree
    root = buildTree(root);

    // Validate if the built tree is a BST
    if (validateBST(root)) {
        cout << "The tree is a valid BST." << endl;
    } else {
        cout << "The tree is not a valid BST." << endl;
    }

    return 0;
}
