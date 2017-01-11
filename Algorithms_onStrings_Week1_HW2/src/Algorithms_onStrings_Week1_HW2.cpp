//============================================================================
// Name        : Algorithms_onStrings_Week1_HW2.cpp
// Author      : Daniel Ramirez
// Version     :
// Copyright   : HW2_Week1
// Description : TrieMatching algorithm
//============================================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using std::vector;
using std::string;

class trieNode{
private:
    char x;
    int index;
    vector<trieNode*> children;
    bool leaf;
public:
      trieNode();
      trieNode* findNode(char symbol);
      void assignsymbol(char symbol);
      void assignindex(int value);
      void appendChild(trieNode *child);
      void setLeaf();
      char retX();
      int retIndex();
      bool retLeaf();
      void iterateNodes();
};

trieNode::trieNode(){
  index=0;
  leaf=false;
}

bool trieNode::retLeaf(){
   return leaf;
}

void trieNode::setLeaf(){
   leaf=true;
}

char trieNode::retX(){
   return x;
}

int trieNode::retIndex(){
   return index;
}

trieNode* trieNode::findNode(char symbol){
    vector<trieNode*>::iterator it;
    for(it=children.begin();it!=children.end();++it){
       if((*it)->x == symbol){
          return *it;
       }
    }
   return NULL;
}

void trieNode::iterateNodes(){
    vector<trieNode*>::iterator it;
    cout<<"children size="<<children.size()<<endl;
    it=children.begin();
    while ( (*it)->leaf != true){
    	cout<<"(*it)->leaf="<<(*it)->leaf<<" "<<(*it)->x<<endl;
    	it=(*it)->children.begin();
    }
    cout<<"(*it)->leaf"<<(*it)->leaf<<" "<<(*it)->x<<endl;
}

void trieNode::assignsymbol(char symbol){
   x=symbol;
}

void trieNode::assignindex(int value){
	index=value;
}

void trieNode::appendChild(trieNode *child){
	children.push_back(child);
}

class trieTree{
   public:
     trieTree();
     void addTrieNode(vector<string> &text);
     vector<int> trieMatching(const string &text,const vector<string> &patterns);
     bool prefixTrieMatching(const string &text,trieNode *node);
   private:
     trieNode *root;
     vector<int> matches;
};

trieTree::trieTree(){
    root=new trieNode();
}

/*
 it_a: iterator for patterns strings
 it_b: iterator for characters in patterns element;
*/
void trieTree::addTrieNode(vector<string> &text){
   char currentsymbol;
   vector<string>::iterator it_a;
   string::iterator it_b;
   int indexTrie;
   int numNodes=0;
   trieNode *current=root;

   for(it_a=text.begin();it_a!=text.end();++it_a){
     indexTrie=0;
     current=root;
     for(it_b=(*it_a).begin();it_b<(*it_a).end();++it_b){
    	if(*it_b == 'A' || *it_b == 'C' || *it_b == 'T' || *it_b == 'G'){
           currentsymbol=*it_b;
           trieNode *child=current->findNode(currentsymbol);
           if(child != NULL){
			   current = child;
			   indexTrie++;
           }
           else{
        	   trieNode *n=new trieNode();
        	   n->assignsymbol(currentsymbol);
        	   n->assignindex(numNodes);
        	   current->appendChild(n);
        	   current=n;
        	   indexTrie++;
           }
    	}
       }
       current->setLeaf();  //end of string in trie, leaf set to TRUE;
     }
}

bool trieTree::prefixTrieMatching(const string &text,trieNode *node){
    string text_tmp;
	string::iterator it;
	char symbol;
	bool match;
	trieNode *v;

	text_tmp=text;
	it=text_tmp.begin();
	symbol=*it;
	v=node;
	match=true;

	trieNode *tmp=v->findNode(symbol);
	v=tmp;
	while(v!=NULL){
		if((v->retX() == symbol) && v->retLeaf()){
	      return match;
		}
		else if(v->retX() == symbol){
			//match=true;
			symbol=*(++it);
			trieNode *tmp=v->findNode(symbol);
			if(tmp==NULL) return false;
			v=tmp;
		}
		else{
			match=false;
			return match;
		}
	}
	return false;
}

vector<int> trieTree::trieMatching(const string &text,const vector<string> &patterns){
	trieNode *current=root;
    string text_tmp=text;
    bool prefix_matching;
    int pos_text=0;
    vector<int>::iterator it;

    while(!text_tmp.empty()){
        prefix_matching=prefixTrieMatching(text_tmp,current);
    	if(prefix_matching){
    	   matches.push_back(pos_text);
    	}
    	text_tmp.erase(0,1);
    	++pos_text;
    }
    std::sort (matches.begin(),matches.end());

    for(it=matches.begin();it!=matches.end();++it)
    	cout<<*it<<" ";

	return matches;
}

int main(){

   string text;
   vector<string> patterns;
   trieTree *tree=new trieTree();

   cin>>text;
   if(text.size()>=1 && text.size()<=10000){
	  int n;
      cin>>n;

      if(n>=1 && n<=5000){
	     for(int i=0;i<n;i++){
	        string s;
	        cin>>s;

            if(s.size()>=1 && s.size()<=100)
               patterns.push_back(s);
	     }
      }
      tree->addTrieNode(patterns);
      tree->trieMatching(text,patterns);
   }
   return 0;
}
