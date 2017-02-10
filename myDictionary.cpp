#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
//initialize the node with the word and its definition 
struct treenode {
    string word;
    string def;
    struct treenode *left;
    struct treenode *right;
    //contstructor with known word and definition but no left child and right child
    treenode(string word, string def){
    	this->word = word;
        this->def = def;
        this->left = NULL;
        this->right = NULL;
    }
    //constructor with known word, definition and children
    treenode(string word, string def, treenode *left, treenode *right) {
        this->word = word;
        this->def = def;
        this->left = left;
        this->right = right;
    }
};
//balanced search tree implemented by myself
class tree {

    private:
 
    //print all the nodes, just help me to make sure the insertion is fine.
    void printHelper(treenode *root) {
    	if (root==NULL)
    		return;
        printHelper(root->left);
        cout<<root->word<<endl;
        printHelper(root->right);
    }
	//add the word into the tree
    void add_tree(string word, string def, treenode *root) {
        if (root->word > word) {
            if (root->left==NULL) {
                root->left = new treenode(word, def);
                
            } 
			else 
                add_tree(word, def, root->left);
        } 
		else {
            if (root->right==NULL) 
                root->right = new treenode(word, def); 
			else 
                 add_tree(word, def, root->right);
        }
    }
    //find the word and print its definition
    void find_def(string word, treenode *root){
    	
    	if (root==NULL)
    		return;
    	if (root->word==word)
			cout<<root->def<<endl;
		else if (root->word < word)
			find_def(word, root->right);
		else 
			find_def(word, root->left);
	}
	//count the words in the collection
    int count_words(treenode *root) {
        if (!root) 
			return 0;
        else 
			return 1 + count_words(root->left) + count_words(root->right);
    }
	//delete the word from the collection
    int delete_word(string word, treenode* parent, treenode* current) {
        if (current==NULL) 
			return 0;
        if (current->word == word) {
            if (current->left == NULL || current->right == NULL) {
                treenode *temp = current->left;
                if (current->right!=NULL) 
					temp = current->right;
                if (parent!=NULL) {
                    if (parent->left == current) {
                        parent->left = temp;
                    } 
					else {
                        parent->right = temp;
                    }
                } 
				else {
                    root = temp;
                }
            } 
			else {
                treenode* nodetochange = current->right;
                while (nodetochange->left!=NULL) {
                    nodetochange = nodetochange->left;
                }
                string tempword = current->word;
                current->word = nodetochange->word;
                nodetochange->word = tempword;
                return delete_word(tempword, current, current->right);
            }
            
            delete current;
            return 0;
        }
        return delete_word(word, current, current->left) || delete_word(word, current, current->right);
    }
    //handle range queries
    void range_query(string string1, string string2, treenode *root){

    	if (root==NULL)
    		return;
    	if (root->word > string2){
    		range_query(string1, string2, root->left);
    		return;
		}
    	else if(root->word < string1){
    		range_query(string1, string2, root->right);
    		return;
		}
		else 
			cout<<root->word<<endl;
			range_query(string1, string2, root->right);
			range_query(string1, string2, root->left);
		}
	
    public:
    treenode *root;
    
    tree(){
    	root=NULL;
	}
	void range(string string1, string string2){
		range_query(string1, string2, root);
	}
    void add(string word, string def) {
    	
        if (root!=NULL) 
    		add_tree(word, def, root); 
		else 
            root = new treenode(word, def); 
    }
    void find(string word){
		find_def(word, root);
		}
	
	void print() {
	    printHelper(root); 
	    
    }

    void count() {
        cout <<count_words(root)<<endl;
    }

    void deleteword(string word) {
    	
    	delete_word(word, NULL, root);
    }
   
};

int main(){
	tree tree1;
	ifstream input("knownwords.txt");
    string line ,line2 ,word , word2, definition, str;
    string  cut, target;
    int flag=0;
    
    while( getline( input, line ) ) {
    	int i=0, l=0;
    	//basic idea if there exists dash to indicate the continuation of the definitions for the word in the previous line
		if(line[0]=='-'){
			line.erase(0,1);
			line=line2+line;
		}
			
		else if (line2==""){
			flag=1;
		}
		else{
			while(l<line2.length()){
				if(line2[l]==' '){
					word = line2.substr(0,l);
					definition = line2.substr(l+1,line2.length());
					break;
					} 
				l+=1;
			}
			tree1.add(word, definition);
			line2="";
	}		
    	while(getline(input, line2)){
    		if(line2[0]=='-'){
    			line2.erase(0,1);
				line=line+line2;
    		}
    		else{
   				break;
			}
    	}
    
    	//distinguish the word and definition in the string
    	i=0;
    	while(i<line.length()){
			if(line[i]==' '){
				
				word = line.substr(0,i);
				definition = line.substr(i+1, line.length());
				break;
			} 
			i+=1;
		}
		tree1.add(word,definition);
		
	}
	if (line2!=""){
		int i=0;
    	while(i<line2.length()){
			if(line2[i]==' '){
				
				word = line2.substr(0,i);
				definition = line2.substr(i+1, line2.length());
				break;
			} 
			i+=1;
		}
		tree1.add(word,definition);
	}
	//the command in the dictionary, including find, new, count, quit, delete, find, query
	while (getline(cin, cut)){
		
		string command=" ", word1, definition1,target1,target2,temp; 
		int j=0;
		int k=0;
		int flag1=0;
		while(j<cut.length()){
			if(cut=="count")
				command="count";
			if(cut[j]==' '){
				command = cut.substr(0,j);
				target = cut.substr(j+1,cut.length());
				break;
			}
			j+=1;
		}
		if (command=="find"){
			while(k<target.length()){
				if(target[k]==' '){
					target1 = target.substr(0,k);
					target2 = target.substr(k+1,target.length());
					flag1=-1;
					break;
				}
			k+=1;
		}	
			if(flag1==0)
				tree1.find(target);
			else{
				if (target1>target2){
					temp=target1;
					target1=target2;
					target2=temp;
				}
				tree1.range(target1, target2);	
			}
			
		}
			
		else if (command=="new"){
			target.erase(target.end()-1,target.end());
			while(k<target.length()){
				if(target[k]=='"'){
				int n = target.length()-1;
				word1 = target.substr(0,k-1);
				definition1=target.substr(k+1,target.length());
				break;
				
			}
			k+=1;
		}	
		
			tree1.add(word1, definition1);
		}
		else if (command=="count")
			tree1.count();
		else if (command=="quit")
			return 0;
		else if (command=="delete")
			tree1.deleteword(target);
		else
			continue;
	}
}




