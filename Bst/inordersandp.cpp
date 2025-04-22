#include<iostream>
#include<queue>
using namespace std;

class Node{
    public:
    int data;
    Node* left;
    Node* right;

    Node(int d){
        this -> data = d;
        this -> left = NULL;
        this -> right = NULL;
    }
};

Node* insertintoBST(Node* root, int d){

    if(root == NULL){
        root = new Node(d);
        return root;
    }
    if(d>root->data){
        root -> right = insertintoBST(root -> right , d);
    }

    else{
        root -> left = insertintoBST( root -> left , d);
    }
    return root;
}


void takeInput(Node* &root){
    int data;
    cin >> data;

    while(data != -1){
        root = insertintoBST(root,data);
        cin >> data;
    }
}

void inorder(Node* root){  
    if(root==NULL){
        return;
    }
    inorder(root->left);
    cout<<root->data<< " ";
    inorder(root->right);
} 

pair<int,int> pands(Node* root, int key){
    Node* temp = root;
    int pred = -1;
    int succ = -1;
    while(temp->data != key){

        if(temp->data > key){
            succ = temp->data;
            temp = temp->left;
        }
        else{
            pred = temp -> data;
            temp = temp -> right;         
        }

    }

    Node* leftTree = temp->left;
    while (leftTree != NULL) {
        pred = leftTree-> data;
        leftTree = leftTree->right;
    }

    Node* rightTree = temp->right;
    while (rightTree != NULL) {
        succ = rightTree-> data;
        rightTree = rightTree->left;
    }

    pair <int,int> ans = make_pair(pred,succ);
    return ans;
}




int main(){
    Node* root = NULL;
    cout<< "Enter data to create BST" << endl ;
    takeInput(root);
    int key;
    cout << "Enter key to find predecessor and successor: ";
    cin >> key;

    pair<int, int> result = pands(root, key);
    cout << "Predecessor: " << result.first << ", Successor: " << result.second << endl;

    return 0;
}