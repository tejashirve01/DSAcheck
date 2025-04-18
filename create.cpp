#include<iostream>
using namespace std;
#include<string>

class TrieNode{
    public:
    char data;
    TrieNode* children[26];
    bool isTerminal;

    TrieNode(char ch){
        data = ch;
        for(int i = 0; i < 26; i++ ){
            children[i] = NULL;
        } 
        isTerminal = NULL;
    }
};

class Trie{
    public:
    TrieNode* root;
    Trie(){
        root = new TrieNode('\0');
    }
    void insertUtil(TrieNode* root, string word){
        if(word.length() == 0){
            root->isTerminal = true;
            return;
        }

        int index = word[0] - 'A';
        TrieNode* child;
        if(root->children[index]!= NULL){
            child = root->children[index];

        }
        else{
            child = new TrieNode(word[0]);
            root->children[index] = child;
        }
        insertUtil(child, word.substr(1));
    }

    void insert(string word){
        insertUtil(root, word);
    }

    bool searchUtil(TrieNode* root, string word){
        if(word.length() == 0){
            return root->isTerminal;
        }

        int index = word[0] - 'A';
        TrieNode* child;

        if( root -> children[index] != NULL){
            child = root -> children[index];
        }

        else{
            return false;
        }

        return searchUtil(child, word.substr(1));
    }

    bool search(string word){
        return searchUtil(root, word);
    }

    bool deleteUtil(TrieNode* root, string word, int depth){
        if(root == NULL) {
            return false;
        }

        if(depth == word.size()){
            // If the last character of the word is reached
            if(root->isTerminal){
                root->isTerminal = false;
            }

            // If the node has no children, it can be deleted
            for(int i = 0; i < 26; i++){
                if(root->children[i] != NULL){
                    return false; // Don't delete if there are children
                }
            }

            return true;
        }

        int index = word[depth] - 'A';
        TrieNode* child = root->children[index];

        bool shouldDeleteChild = deleteUtil(child, word, depth + 1);

        if(shouldDeleteChild){
            delete child;
            root->children[index] = NULL;

            // If root is not a terminal and has no other children
            for(int i = 0; i < 26; i++){
                if(root->children[i] != NULL){
                    return false;
                }
            }

            return !root->isTerminal;
        }

        return false;
    }

    void deleteNode(string word){
        deleteUtil(root, word, 0);
    }


};


int main(){
    Trie* t = new Trie();
    t->insert("ABCD");
    cout<< t->search("ABCD") << endl;
    t->insert("CFAE");
    t->deleteNode("CFAE");
    cout<< t->search("CFAE") << endl;
    
    return 0;
}