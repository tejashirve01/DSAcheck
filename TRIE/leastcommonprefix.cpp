#include<iostream>
using namespace std;
#include<string>

class TrieNode{
    public:
    char data;
    TrieNode* children[26];
    int childCount;
    bool isTerminal;

    TrieNode(char ch){
        data = ch;
        for(int i = 0; i < 26; i++ ){
            children[i] = NULL;
        }
        childCount = 0; 
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
            root -> childCount++;
        }
        insertUtil(child, word.substr(1));
    }

    void insert(string word){
        insertUtil(root, word);
    }

    void lcp(string str, string &ans){
        TrieNode* node = root;  
        for(int i = 0; i < str.length(); i++ ){
            char ch = str[i];
            if( root ->childCount == 1){
                ans.push_back(ch);
                int index = ch - 'A';
                root = root ->children[index];
            }
            else{
                break;
            }
            if(root->isTerminal){
                break;
            }
        }
    }

};


int main(){
    Trie* t = new Trie();

    t->insert("CODING");
    t->insert("CODEZEN");
    t->insert("CODINGNIN");
    t->insert("CODERS");

    string first = "CODING";
    string ans = "";
    
    t->lcp(first,ans);
    cout << ans << endl;
    
    
    return 0;
}