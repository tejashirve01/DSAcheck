#include<iostream>
#include<queue>
#include<climits> // for INT_MIN and INT_MAX
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int d) {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

class info {
public:
    int maxi;
    int mini;
    bool isBST;
    int size;

    // Constructor to initialize
    info(int mini, int maxi, bool isBST, int size) {
        this->maxi = maxi;
        this->mini = mini;
        this->isBST = isBST;
        this->size = size;
    }
};

// Function to insert a node into the BST
Node* insertintoBST(Node* root, int d) {
    if (root == NULL) {
        root = new Node(d);
        return root;
    }
    if (d > root->data) {
        root->right = insertintoBST(root->right, d);
    } else {
        root->left = insertintoBST(root->left, d);
    }
    return root;
}

// Function to take input for BST creation until user enters -1
void takeInput(Node* &root) {
    int data;
    cin >> data;

    while (data != -1) {
        root = insertintoBST(root, data);
        cin >> data;
    }
}

// Helper function to find the largest BST in a binary tree
info solve(Node* root, int &maxSize) {
    if (root == NULL) {
        return info(INT_MAX, INT_MIN, true, 0);
    }

    info left = solve(root->left, maxSize);
    info right = solve(root->right, maxSize);

    info currNode(min(root->data, left.mini), max(root->data, right.maxi), false, left.size + right.size + 1);

    // Check if the current node forms a BST
    if (left.isBST && right.isBST && (root->data > left.maxi && root->data < right.mini)) {
        currNode.isBST = true;
    } else {
        currNode.isBST = false;
    }

    // Update maximum size if current node forms a valid BST
    if (currNode.isBST) {
        maxSize = max(maxSize, currNode.size);
    }

    return currNode;
}

// Function to find the size of the largest BST in the binary tree
int largestBST(Node* root) {
    int maxSize = 0;
    solve(root, maxSize);
    return maxSize;
}

int main() {
    Node* root = NULL;

    // Input format: keep inputting numbers to create a BST, end input with -1
    cout << "Enter data to create BST (enter -1 to stop): ";
    takeInput(root);

    cout << "Size of largest BST is: " << largestBST(root) << endl;

    return 0;
}
