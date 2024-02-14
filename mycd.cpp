#include <cctype>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct node {
    node* parent;
    vector<node*> children;
    string name;
};

node* root = new node;

void deleteTree(node* n) {
    for (unsigned int i = 0; i < n->children.size(); i++) {
        deleteTree(n->children.at(i));
    }
    delete(n);
}

string makepath(node * tail) {
    string answer = "";
    vector<string> path;
    node * curr = tail;
   
    while(curr != root) {
        path.push_back(curr->name);
        curr=curr->parent;
    }
    reverse(path.begin(), path.end());
   
    answer.append("/");
    for(unsigned int i = 0; i < path.size(); i++) {
        answer.append(path.at(i));
        if(i != path.size()-1) {
            answer.append("/");
        }
    }
   
    return answer;
}

int main(int argc, char* argv[])
{
    root->parent = root;
   
    vector<string> firstpath;
    char* token = strtok(argv[1], "/");  
    while(token != NULL) {                  //turn first input into vector of strings
        firstpath.push_back(token);
        token = strtok(NULL, "/");
    }
   
    node* curr = root;
    for(unsigned int i = 0; i < firstpath.size(); i++) {   //create initial tree from first input
        node * child = new node;
        child->name = firstpath.at(i);
        curr->children.push_back(child);
        child->parent = curr;
        curr = child;
       
    }
   
    if (argv[2][0] == '/') {     //return to root if first char of second input is /
        curr = root;
    }
   
    vector<string> secondpath;           //turn second input into vector of strings
    token = strtok(argv[2], "/");
    while(token != NULL) {
        secondpath.push_back(token);
        token = strtok(NULL, "/");
    }
   
    for (unsigned int i = 0; i < secondpath.size(); i++) {
        string str = secondpath.at(i);
        if (!all_of(str.begin(), str.end(), [](unsigned char ch) {return isalnum(ch);})){
            if (str.length() == 1 && str[0] == '.') {   //perform . action
                curr = curr;
            } else if (str.length()==2 && str[0]=='.' && str[1]=='.') { //perform .. action
                curr = curr->parent;
            } else {  //directory does not exist
                cout << str <<": No such file or directory" << endl;
                exit(0);
            }
        } else {  //move into "existing" directory
            bool found = false;
            for(unsigned int i = 0; i < curr->children.size(); i++) {
                if (curr->children.at(i)->name == str) { //node already exists
                found = true;
                    curr=curr->children.at(i);
                    break;
                }
            }
            if (!found) {   //new node must be created
                node * child = new node;
                child->name = str;
                curr->children.push_back(child);
                child->parent = curr;
                curr = child;
            }
           
        }
    }
   
    cout << makepath(curr) << endl;
    
    deleteTree(root);

    return 0;
}