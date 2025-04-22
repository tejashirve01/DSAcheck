#include<iostream>
#include<queue>
#include<vector>
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

void inorder(Node* root, vector<int> in){
    if( root == NULL ){
        return;
    }

    inorder( root -> left, in);
    in.push_back( root -> data );
    inorder ( root -> right , in);

}

bool twosum(Node* root, int target){
    vector<int> inorderVal;
    inorder(root, inorderVal);
    int i = 0, j = inorderVal.size() - 1;

    while(i<j){
        int sum = inorderVal[i] + inorderVal[j];

        if ( sum == target ){
            return true;
        }
        else if ( sum > target ){
            j--;
        }
        else if(sum < target){
            i++;
        }
    return false;
    }
}

int main(){
    Node* root = NULL;
    cout<< "Enter data to create BST" << endl ;
    takeInput(root);

    int number;
    cout<< " Enter the number target to check in BST";
    cin >> number;
    if(twosum(root, number)){
        cout<< "Present";
    }
    else{
        cout<< "Not present";
    }
    return 0;
}
