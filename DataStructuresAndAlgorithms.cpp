#pragma once

#include <assert.h>
#include <numeric>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <hash_map>
#include <stack>
#include <list>
#include <ctime>
#include <time.h>
#include <deque>
#include <bitset>
#include <fstream>
#include <stdlib.h>
#include <random>
#include <regex>


using namespace std;

class Practice
{
public:
  Practice(void);
	~Practice(void);
};


class BigInteger 
{
private:
	string integer;
	bool negative;
public:
	//BigInteger(int) ;impl this
	void setInteger(int bi)
	{
		if(bi==0){ 
			integer="0"; 
			negative = false;
			return;
	    }
		else if(bi<0){
			negative=true;
			bi = 0-bi;
		}
		else
			negative = false;
		int curr;
		while(bi){
		   curr = bi%10;
		   integer.insert(0,1,'0'+curr);
		   bi /= 10;
		}
	}
    bool isNegative() const {return negative;}
	void setInteger(string bi)
	{
		if(bi.empty()){
			integer = "";
			negative = false;
		}
		else if(bi[0]=='-'){
			negative = true;
		    integer = bi.substr(1);
		}
		else {
		    negative = false;
		    integer = bi;
		}
	}
	BigInteger(int bi)
	{
		setInteger(bi);
	}
	BigInteger()
	{
	    negative = false;
		integer = "";
	}
	BigInteger(string bi)
	{
		setInteger(bi);
	}
	string getStr() const
	{
		return negative?(string("-")+integer):integer;
	}
	string getStrNoSign() const
	{
		return integer;
	}
	BigInteger add(const BigInteger &bi) const
	{
		string bis = bi.getStrNoSign(); 
		if(bis.empty()) return *this;
		if(integer.empty()) return bi;
		int a=max((int)bis.size()-(int)integer.size(),0);
		int b=max((int)integer.size()-(int)bis.size(),0);
		string s1 = string(a,'0') + integer;
		string s2 = string(b,'0') + bis;

		reverse(s1.begin(), s1.end());
		reverse(s2.begin(), s2.end());

		string res; int carry = 0;

		for(int i=0; i<(int)s1.size(); i++){
			int sum = (s1[i]-'0')+(s2[i]-'0')+carry;
			res += (char)(sum%10+'0');
			carry = sum/10;
		}

		if(carry) res += ((char)(carry+'0'));
		reverse(res.begin(), res.end());
		return BigInteger(res);
	}
	BigInteger add(const string &bi) const
	{
		return this->add(BigInteger(bi));
	}
	BigInteger multiply(const BigInteger &bi) const
	{
	    string s1=integer;
		string s2=bi.getStrNoSign();
		reverse(s1.begin(), s1.end());
		reverse(s2.begin(),s2.end());
		
		BigInteger res("0");
		for(int i=0; i<s1.size(); i++){
			int carry = 0; 
			string tmp = string(i,'0');
			for(int j=0; j<s2.size(); j++){
				int pro = (int)(s1[i]-'0')*(s2[j]-'0');
				tmp += (char)(pro%10+'0');
				carry = pro/10;
			}
			if(carry) tmp += (char)(carry+'0');
			reverse(tmp.begin(), tmp.end());
			res.add(tmp);
		}
		return res;
	}

	BigInteger multiply(const string &bi) const
	{
		return this->multiply(bi);
	}


	BigInteger& operator= (const BigInteger &bi)
	{
		if(&bi==this)
			return *this;
		negative = bi.isNegative();
		integer = bi.getStrNoSign();

		return *this;
	}


	BigInteger& operator== (const BigInteger &bi);
	BigInteger operator+ (const BigInteger &bi)   //do not use & on the return value!
	{
		return this->add(bi);
	}
	BigInteger operator* (const BigInteger &bi)  //do not use & on the return value!
	{
		return this->multiply(bi);
	}
	friend ostream& operator<< (ostream &in, BigInteger &bi)
	{
		in << bi.getStrNoSign();
		return in;
	}
};

//
class AddMultiply
{
public:
	static string multiply(string num1, string num2)
	{
		string res(num1.size()+num2.size(), '0');
		int carry = 0;
		for(int i=num1.size()-1; i>=0; i--){
			for(int j=num2.size()-1; j>=0; j--){
				int pro = (num1[i]-'0')*(num2[j]-'0') + (res[i+j+1]-'0') + carry;
				res[i+j+1] = pro%10+'0';
				carry = pro/10;
		    }
			if(carry){
				int c=res[i]-'0'+carry;
				res[i] = c%10+'0';
				carry = c/10;
			}
		}
		for(int i=0; i<res.size(); i++){
			if(res[i]!='0')
				return res.substr(i);
		}
		return "0";
	}
	static string add(string num1, string num2)
	{
		string res(max((int)num1.size(),(int)num2.size())+1,'0');
		num1 = string(res.size()-num1.size(),'0')+num1;
		num2 = string(res.size()-num2.size(),'0')+num2;
		int carry = 0;
		for(int i=res.size()-1; i>=0; i--){
			int sum = (num1[i]-'0')+(num2[i]-'0')+carry;
			res[i] = sum%10+'0';
			carry = sum/10;
		}
	    for(int i=0; i<res.size(); i++){
			if(res[i]!='0')
				return res.substr(i);
		}
		return "0";
	}
};


class BackTracking
{
	vector<int> queuePlacement;
	
public:
	void printBoard(int boardSize)
	{
		for(int i=0; i<boardSize; i++){
			for(int j=0; j<boardSize; j++){
	           if(j==queuePlacement[i])
				   cout << "Q "; 
			   else 
				   cout << "* ";
			}
			cout << endl;
		}
	}
	void placeQueue(int level, const int boardSize)
	{
		if(level==boardSize){
			printBoard(boardSize);
			return;
		}

		for(int col=0; col<boardSize; col++){
			queuePlacement.push_back(col);
			bool canPlace = true;
			for(int i=0; i<level; i++){
				if(queuePlacement[i]==col || abs(level-i)==abs(col-queuePlacement[i])){
				    canPlace=false;	break;
				}
			}
			if(canPlace)
				placeQueue(level+1,boardSize);
			queuePlacement.pop_back();
		}
	}
	void placeQueue(int boardSize)
	{
		if(boardSize>16 || boardSize<=0)
			cerr << "Can not handle board size!" << endl;
		queuePlacement.clear();
		placeQueue(0,boardSize);
	}


	bool subsetSum(vector<int> &v, int W, int level, int pSum, int remaining)
	{
		if(level >= v.size() || pSum>W || remaining<W-pSum)
			return false;
		if(W==pSum)
			return true;
		return subsetSum(v, W, level+1, pSum, remaining-v[level]) || \
			subsetSum(v, W, level+1, pSum+v[level], remaining-v[level]);
	}
	bool subsetSum(vector<int> &v, int W)
	{
		if(v.empty()) return false;
		return subsetSum(v,W,0,0,accumulate(v.begin(),v.end(),0));
	}


	bool graphColor(vector<vector<bool> > &am, int numColors, vector<int> &colors, int node)
	{
		if(node>=am.size())
			return true;
		bool res = false;
		for(int color=0; color<numColors; color++){
			bool canColor = true;
			colors[node] = color;
			for(int i=0; i<am.size(); i++){
				if(am[node][i] && colors[i] == color){
					canColor = false;
			        break;
				}
			}
			if(canColor)
				res = res || graphColor(am,numColors,colors,node+1);
            colors[node] = -1;
		}
		return res;
	}
	bool graphColor(vector<vector<bool> > &am, int numColors)
	{
		vector<int> colors(am.size(),-1);
		return graphColor(am,numColors,colors,0);
	}
	
};


class ParenthesesMatcher
{
public:
	bool match(string fileName)
	{
		ifstream infile(fileName);
		assert(infile);
		string str;
		while(!infile.eof()){
			char c;
			infile.get(c);
			str.push_back(c);
		}
		unordered_map<char, char> cmap;
		cmap[')'] = '('; cmap[']'] = '['; cmap['}'] = '{';
		stack<char> st;
		for(int i=0; i<str.size(); i++){
			char c = str[i];
			if(c=='(' || c== '[' || c== '{')
				st.push(c);
			else if(c=='/' && i!=str.size()-1 && str[i+1]=='*'){
				i++;
				st.push('c');
			}
			else if(c==')' || c== ']' || c== '}'){
				if(st.empty())
					return false;
				else{
					char x = st.top();
					st.pop();
					if(x!=cmap[c])
						return false;
				}
			}
			else if(c=='*' && i!=str.size()-1 && str[i+1]=='/'){
				if(st.empty())
					return false;
				else{
					i++;
					char x = st.top();
					st.pop();
					if(x!='c')
						return false;
				}
			} 
		}
		return st.empty();
	}
};


class DivideAndConquer
{
public:
	int binarySearch(int A[], int key, int start, int end)
	{
		int m;
		while(start<=end){
			m = start + (end-start)/2;
			if(A[m]==key)
				return m;
			else if(A[m]>key)
				end = m-1;
			else
				start = m+1;
		}
		return -1;
	}
	int binarySearchRecursive(int A[], int key, int start, int end)
	{
		if(start>end)
			return -1;
		int m = start + (end-start)/2;
		if(key==A[m])
			return m;
		else if(key < A[m])
			return binarySearchRecursive(A,key,start,m-1);
		else
			return binarySearchRecursive(A,key,m+1, end);
	}
};


class Sorting
{
public:
	void insertionSort(int A[], int n)
	{
		if(n<=0) return;
		for(int i=1; i<n; i++){
			int j;
			int tmp = A[i];
			for(j=i-1; j>=0; j--){
				if(A[j]>tmp)
					A[j+1]=A[j];
				else
					break;
			}
			A[j+1] = tmp;  //this has to be out of the loop!
		}
	}
	void bubbleSort(int A[], int n)
	{
		if(n<=0) return;
		for(int i=0;i<n-1; i++){
			for(int j=n-1;j>i; j--){
				if(A[j]<A[j-1])
					swap(A[j], A[j-1]);
			}
		}
	}
	/* This partition does not guarantee the pivot to be in the partitioned position
	int partition(int A[], int start, int end)
	{
		if(start>=end) return start;
		int pivot = A[end];
		int s=start, e=end;
		while(s<e){
			if(A[s]<=pivot)
				s++;
			else{
				swap(A[s],A[e]);
				e--;
			}	
		}
		return A[s]<=pivot?s:(s-1);
	}*/
	int partition(int A[], int start, int end)
	{
		if(start>=end) return start;
		int pivot = A[end];
		int s=start, e=end;
		for(int i=s; i<=e; i++)
		{
			if(A[i]<pivot)
				swap(A[i],A[s++]);
			else if(A[i]>pivot)
				swap(A[i--],A[e--]);
		}
		return e;
	}
	void quickSort(int A[], int start, int end)
	{
		if(start>=end) return;
		int p = partition(A,start,end);
		quickSort(A,start,p-1);
		quickSort(A,p+1,end);
	}


	void merge(int A[], int start, int mid, int end)
	{
		if(start>=end) return;
		vector<int> tmp(end-start+1,0);
		int idx1=start, idx2=mid+1, idx=0;
		for(int i=0;i<tmp.size();i++){
			if(idx1<=mid &&idx2<=end)
				tmp[i] = (A[idx1]>A[idx2]?A[idx2++]:A[idx1++]);
			else if(idx1<=mid)
				tmp[i] = A[idx1++];
			else
				tmp[i] = A[idx2++];
		}
		for(int i=start, idx=0; i<=end; i++, idx++)
			A[i] = tmp[idx];
	}
	void mergeSort(int A[], int start, int end)
	{
		if(start>=end) return;
		int m = start+(end-start)/2;
		mergeSort(A,start,m);
		mergeSort(A,m+1,end);
		merge(A,start,m,end);
	}


	void coutingSort(int A[], int n, int range)  
	{
		int *B = new int[n]();
		int *C = new int[range]();
		for(int i=0; i<n; i++)
			C[A[i]]++;
		for(int i=1; i<range; i++)
			C[i] += C[i-1];
		for(int i=n-1; i>=0; i--){
			B[C[A[i]]-1] = A[i];
			C[A[i]]--;
		}
		for(int i=0; i<n; i++)
			A[i] = B[i];
		delete B;
		delete C;
	}
};


class Recursion
{
public:
	void SimpleTail(int i)
	{
		if(i<0) return;
		cout << i << " ";
		SimpleTail(i-1);
	}
	void Reverse()
	{
		char c;
		cin.get(c);
		if(c!='\n'){
			Reverse();
			cout << c;
		}
	}
};


class SList
{
	struct LNode
	{
		int data;
		LNode *next;
		LNode(int d=0, LNode *n=NULL):data(d),next(n) {}
	};
	LNode *head;
	LNode *tail;
public:
	SList():head(NULL),tail(NULL){}
	LNode* insert(LNode *n=NULL, int d=0)
	{
		if(!n) return NULL;
		n->next = new LNode(n->data,n->next);
		n->data = d;
		if(tail->next)
			tail=tail->next;
		return head;
	}
	LNode* insert(int d=0)
	{
		if(!head) {
			head=tail=new LNode(d,NULL);
			return head;
		}
		tail->next = new LNode(d,NULL);
		if(!head->next)
			head->next = tail;
		tail = tail->next;
		return head;
	}
    bool remove(int d)
	{
		if(!head) return false;
		if(head->data==d){
			LNode *tmp = head;
			head = head->next;
			delete tmp;
			if(!head){   //I forgot this
				tail = NULL;
				return true;
			}
		}
		LNode *prev = head, *curr=head->next;
		while(curr && curr->data!=d){
			prev = curr;
			curr = curr->next;
		}
		if(!curr) return false; 
		prev->next = curr->next;
		if(!prev->next) tail = prev;
		delete curr;
		return true;
	}
	LNode* reverse()
	{
		if(head==tail) return head;
		LNode *prev=head, *curr=head->next, *tmp;
		head->next = NULL;
		while(curr){
			tmp = curr->next;
			curr->next = prev;
			prev = curr;
			curr = tmp;
		}
		swap(head, tail);
		return head;
	}
};



template<class T>
class BTree
{
public:
    struct BTNode
	{
		T data;
		BTNode *left;
		BTNode *right;
		BTNode *parent;
		//other fields for future use
		BTNode(T d=0, BTNode* l=NULL, BTNode* r=NULL, BTNode *p=NULL):data(d),left(l),right(r),parent(p) {}
	};
	BTNode *root;


	BTree():root(NULL) {} 
	virtual void visit(BTNode *n) {} 
	T search() {}  //trivial, skipped
	BTNode* getRoot() {return root;}  
	BTNode* insert(T d) {}  //trivial, skipped
	

	void preOrder(BTNode *r)
	{
		if(r){
			visit(r)
			preOrder(r->left);
			preOrder(r->right);
		}
	}
	void inOrder(BTNode *r)
	{
		if(r){
			inOrder(r->left);
			visit(r);
			inOrder(r->right);
		}
	}
	void postOrder(BTNode *r)
	{
		if(r){
			visit(r);
			postOrder(r->left);
			postOrder(r->right);
		}
	}

	void iterativePreOrder(BTNode *r)
	{
		if(!r)
			return;
		stack<BTNode *> st;
		st.push(r);
		while(!st.empty()){
			BTNode *curr = st.top();
			st.pop();
			visit(curr);
			if(curr->right)
				st.push(curr->right);
			if(curr->left)
				st.push(curr->left);
		}
	}
	void iterativeInOrder(BTNode *r)
	{
         stack<BTNode *> st;
		 BTNode *current = r;
		 while(!st.empty() || current){
			 if(current){
				 st.push(current);
				 current = current->left;
			 }
			 else{
				 current = st.top();
				 st.pop();
				 visit(current);
				 current = current->right;
			 }
		 }
	}
	void iterativePostOrder(BTNode *r)
	{
		if(!r) return;
		stack<BTNode *> st;
		st.push(r);
		BTNode *prev = NULL, *curr;
		while(!st.empty()){
			curr = st.top();
			//when traversing downwards
			if(!prev || prev->left==curr || prev-right==curr){
				if(curr->left)
					st.push(curr->left);
				else if(curr->right)
					st.push(curr->right);
			}  //when traversing upwards from left child
			else if(curr->left==prev){
			     if(curr->right)
					 st.push(right);
			}
			else{  //when traversing upwards from right child
				visit(curr);
				st.pop();
			}
			prev = curr;
		}
	}

	void iterativePreOrderNoStackParentPointer(BTNode *r)
	{
		BTNode *curr = r;
		while(curr){
			//visit(curr);
			cout << curr->data << " ";
			if(curr->left)
				curr = curr->left;
			else if(curr->right)
				curr = curr->right;
			else{   //note the following condition.  It took me 40 minutes to got this right.
				while(curr->parent && (!curr->parent->right || curr->parent->right==curr)){
					curr = curr->parent;
				}
				if(curr->parent && curr->parent->right){
					curr = curr->parent->right;
				}
				else 
					break;
			}
		}
	}

	void iterativeInOrderNoStackParentPointer(BTNode *r)
	{
		if(!r) return;
		BTNode *prev=NULL, *curr=r;

		while(curr){
			if(curr->left)
				curr = curr->left;
			else if(curr->right)
				curr = curr->left;
			else{
				//visit(curr);
				cout << curr->data << " ";
				while(curr->parent){
					if(curr->parent->left==curr){
						curr = curr->parent;
						//visit(curr);
						cout << curr->data << " ";
						if(curr->right){
							curr = curr->right;
							break;
						}
					}
					else{
						curr = curr->parent;
					}
				}
				if(!curr->parent)break;
			}
		}
	}
	/* //see the following one-loop version:
	void in_order_traversal_iterative_with_parent(node* root) {
	node* current = root;
	node* previous = NULL;

	while (current) {
		if (previous == current->parent) { // Traversing down the tree.
			previous = current;
			if (current->left) {
				current = current->left;
			} else {
				cout << ' ' << current->data;
				if (current->right)
					current = current->right;
				else
					current = current->parent;
			}
		} else if (previous == current->left) { // Traversing up the tree from the left.
			previous = current;
			cout << ' ' << current->data;
			if (current->right)
				current = current->right;
			else
				current = current->parent;
		} else if (previous == current->right) { // Traversing up the tree from the right.
			previous = current;
			current = current->parent;
		}
	}

	cout << endl;
	}
	*/
	void breathFirst(BTNode *r)
	{
		if(!r) return;
		queue<BTNode *> qu;
		qu.push(r);
		while(!qu.empty()){
			BTNode *n = qu.top();
			visit(n);
			qu.pop();
			if(r->left)
				qu.push(r->left);
			if(r->right)
				qu.push(r->right);
		}
	}

	void changeToList();
	void balance();

	void deleteByCopying(T n);
    void deleteByMerge(T n);
	void rotationRight(BTNode *Chi);

	void rotationLeft(BTNode *Chi)
	{
		BTNode *Gra = 0, *Par = 0;
		int num = Chi->data;
		BTNode *Curr = root;
		while(Curr){
			if(num > Curr->data){
				Gra = Par;
				Par = Curr;
				Curr = Curr->right;
			}
			else if(num < Curr->data){
				Gra = Par;
				Par = Curr;
				Curr = Curr->left;
			}
			else
				break;
		}
		if(Curr != Chi)
			return;
		if(Par && Curr){
			Par->right = Chi->left;
			Chi->left = Par;
			if(Gra && Gra->right == Par)
				Gra->right = Chi;		
			else if(Gra && Gra->left == Par)
				Gra->left = Chi;
			if(Par == root)
				root = Chi;
		}
	}

	
	static BTNode* successor(BTNode* n)
	{
		if(!n) return NULL;
		if(n->right){  //if n has right child, go to leftmost of that child.
			BTNode *m = n->right;
			while(m->left)
				m=m->left;
			return m;
		}
		else{
			//look for the first parent whose left subtree contains n 
			BTNode *p = n->parent;
			while(p && p->right==n){
				n = p;
				p = p->parent;
			}
			return p;
		}
	}
	//symmetric to successor()
	static BTNode* predecessor(BTNode* n)
	{
		if(!n) return NULL;
		if(n->left){  //if n has right child, go to leftmost of that child.
			BTNode *m = n->left;
			while(m->right)
				m=m->right;
			return m;
		}
		else{
			//look for the first parent whose left subtree contains n 
			BTNode *p = n->parent;
			while(p && p->left==n){
				n = p;
				p = p->parent;
			}
			return p;
		}
	}


    //implemented based on tree.h in htmlcxx-0.85.tar in Dropbox\Hunting
	class iterator_base
	{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef size_t size_type;
		typedef std::bidirectional_iterator_tag iterator_category;

		iterator_base():node(0){}

		T& operator*() const
		{
			return node->data;
		}
		T* operator->() const
		{
			return &node->data;
		}

		typename BTree::BTNode *node;
	};

	class in_order_iterator:public iterator_base
	{
	public:
		in_order_iterator() {}
		bool operator==(const in_order_iterator& poi) const
		{
			return poi.node == this->node;
		}
		bool operator!=(const in_order_iterator& poi) const
		{
			return poi.node != this->node;
		}

		in_order_iterator& operator++ ()
		{
			assert(this->node);
			this->node = BTree::successor(this->node);
			return *this;
		}
		in_order_iterator& operator-- ()
		{
			assert(this->node);
			this.node = BTree::predecessor(this->node);
			return *this;
		}
	};


	in_order_iterator begin()
	{
		in_order_iterator poi;
		poi.node = root;
		return poi;
	}
	in_order_iterator end()
	{
		in_order_iterator poi;
		poi.node = NULL;
		return poi;
	}
};



//For now I skipped the implementation of a generic hash table due to a time constaint.
//The following is a hash table implementation I found online. 
/*
  1 //Copyright 2012, egmkang wang.
  2 // All rights reserved.
  3 //
  4 // Redistribution and use in source and binary forms, with or without
  5 // modification, are permitted provided that the following conditions are
  6 // met:
  7 //
  8 // * Redistributions of source code must retain the above copyright
  9 // notice, this list of conditions and the following disclaimer.
 10 // * Redistributions in binary form must reproduce the above
 11 // copyright notice, this list of conditions and the following disclaimer
 12 // in the documentation and/or other materials provided with the
 13 // distribution.
 14 // * Neither the name of green_turtle nor the names of its
 15 // contributors may be used to endorse or promote products derived from
 16 // this software without specific prior written permission.
 17 //
 18 // THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 19 // "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 20 // LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 21 // A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 22 // OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 23 // SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 24 // LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 25 // DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 26 // THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 27 // (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 28 // OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 29 //
 30 // author: egmkang (egmkang@gmail.com)
 31 
 32 #ifndef __MY_HASH_TABLE__
 33 #define __MY_HASH_TABLE__
 34 #include <utility>
 35 #include <functional>
 36 #include <cstddef>
 37 #include <stdlib.h>
 38 namespace green_turtle{
 39 
 40 //hash_table with linear probing
 41 template<class Key,
 42         class T,
 43         class Hash = std::hash<Key>,
 44         class KeyEqual = std::equal_to<Key> >
 45 class hash_map
 46 {
 47  public:
 48   typedef Key key_type;
 49   typedef T mapped_type;
 50   typedef std::pair<const Key,T> value_type;
 51   typedef size_t size_type;
 52   typedef Hash hash_fn;
 53   typedef KeyEqual equal_fn;
 54   typedef value_type* iterator;
 55 
 56   hash_map(size_type capacity = 32,key_type empty = key_type(),key_type deleted = key_type()):
 57     empty_key_(empty)
 58     ,deleted_key_(deleted)
 59     ,size_(0)
 60     ,capacity_(capacity)
 61     ,buckets_(nullptr)
 62     ,hasher_()
 63     ,equaler_()
 64   {
 65     init_buckets();
 66   }
 67   ~hash_map()
 68   {
 69     delete_buckets();
 70   }
 71   hash_map(hash_map&& m,size_type capacity = 32):
 72       buckets_(nullptr)
 73   {
 74     empty_key_ = m.empty_key_;
 75     deleted_key_ = m.deleted_key_;
 76     size_ = 0;
 77     capacity_ = m.capacity_;
 78     //to impl the increase and decrease method
 79     if(capacity_ != capacity && capacity >= 32)
 80       capacity_ = capacity;
 81     hasher_ = m.hasher_;
 82     equaler_ = m.equaler_;
 83 
 84     init_buckets();
 85 
 86     copy_from(m);
 87   }
 88   hash_map& operator = (const hash_map& m)
 89   {
 90     empty_key_ = m.empty_key_;
 91     deleted_key_ = m.deleted_key_;
 92     size_ = 0;
 93     capacity_ = m.capacity_;
 94     hasher_ = m.hasher_;
 95     equaler_ = m.equaler_;
 96 
 97     init_buckets();
 98 
 99     copy_from(m);
100   }
101   void swap(hash_map& m)
102   {
103     std::swap(empty_key_ , m.empty_key_);
104     std::swap(deleted_key_ , m.deleted_key_);
105     std::swap(size_ , m.size_);
106     std::swap(capacity_ , m.capacity_);
107     std::swap(hasher_ , m.hasher_);
108     std::swap(equaler_ , m.equaler_);
109     std::swap(buckets_ , m.buckets_);
110   }
111 
112   iterator end() { return nullptr; }
113   iterator end() const { return nullptr; }
114 
115   iterator find(const key_type& key)
116   {
117     if(is_key_empty(key) || is_key_deleted(key))
118       return NULL;
119     iterator pair_ = find_position(key);
120     if(!pair_ || !equaler_(key,pair_->first))
121       return NULL;
122     return pair_;
123   }
124   iterator find(const key_type& key) const
125   {
126     if(is_key_empty(key) || is_key_deleted(key))
127       return NULL;
128     iterator pair_ = find_position(key);
129     if(!pair_ || !equaler_(key,pair_->first))
130       return NULL;
131     return pair_;
132   }
133 
134   std::pair<iterator, bool> insert(const value_type& v)
135   {
136     std::pair<iterator, bool> result(nullptr, false);
137     result.first = _insert(v);
138     result.second = result.first ? true : false;
139     return result;
140   }
141 
142   template<class P>
143   std::pair<iterator, bool> insert(P&& p)
144   {
145     std::pair<iterator, bool> result(nullptr, false);
146     result.first = _insert(std::forward<P>(p));
147     result.second = result.first ? true : false;
148     return result;
149   }
150 
151   template<class... Args>
152   std::pair<iterator, bool> emplace(Args&&... args)
153   {
154     std::pair<iterator, bool> result(nullptr, false);
155     value_type _v(std::forward<Args>(args)...);
156     result.first = _insert(std::move(_v));
157     result.second = result.first ? true : false;
158     return result;
159   }
160 
161   mapped_type& operator[](const key_type& key)
162   {
163     value_type *pair_ = find(key);
164     if(!pair_)
165     {
166       pair_ = insert(std::make_pair(key,mapped_type()));
167     }
168     return pair_->second;
169   }
170 
171   mapped_type& operator[](key_type&& key)
172   {
173     value_type *pair_ = find(key);
174     if(!pair_)
175     {
176       pair_ = insert(std::make_pair(std::move(key), std::move(mapped_type())));
177     }
178     return pair_->second;
179   }
180 
181   void erase(const key_type& key)
182   {
183     assert(empty_key_ != deleted_key_ && "you must set a deleted key value before delete it");
184     value_type *pair = find(key);
185     if(pair && equaler_(key,pair->first))
186       set_key_deleted(pair);
187     --size_;
188     decrease_capacity();
189   }
190   void erase(const value_type* value)
191   {
192     if(value) erase(value->first);
193   }
194   void clear()
195   {
196     if(empty()) return;
197     for(size_t idx = 0; idx < capacity_; ++idx)
198     {
199       buckets_[idx]->first = empty_key_;
200       buckets_[idx]->second = mapped_type();
201     }
202     size_ = 0;
203   }
204   //bool (const value_type&);
205   template<class Fn>
206   void for_each(Fn f) const
207   {
208     if(empty()) return;
209     for(size_t idx = 0; idx < capacity_; ++idx)
210     {
211       if(is_key_deleted(buckets_[idx].first) ||
212          is_key_empty(buckets_[idx].first))
213         continue;
214       if(!f(buckets_[idx]))
215         break;
216     }
217   }
218 
219   inline void set_deleted_key(key_type k)
220   {
221     assert(empty_key_ != k);
222     if(deleted_key_ != empty_key_)
223       assert(deleted_key_ == k);
224     deleted_key_ = k;
225   }
226   inline bool empty() const { return size_ == 0; }
227   inline size_type size() const { return size_; }
228   inline size_type capacity() const { return capacity_; }
229  private:
230   //return key equal position
231   //or first deleted postion
232   //or empty postion
233   value_type* find_position(const key_type& key) const
234   {
235     size_type hash_pair_ = hasher_(key);
236     size_type mask_ = capacity_ - 1;
237     size_type begin_ = hash_pair_ & mask_;
238     size_type times_ = 0;
239     value_type *first_deleted_ = NULL;
240     while(true)
241     {
242       if(is_key_deleted(buckets_[begin_].first) && !first_deleted_)
243         first_deleted_ = &buckets_[begin_];
244       else if(is_key_empty(buckets_[begin_].first))
245       {
246         if(first_deleted_) return first_deleted_;
247         return &buckets_[begin_];
248       }
249       else if(equaler_(key,buckets_[begin_].first))
250         return &buckets_[begin_];
251 
252       begin_ = (begin_ + 1) & mask_;
253       assert(times_++ <= capacity_);
254       (void)times_;
255     }
256     return NULL;
257   }
258   void copy_from(hash_map&& m)
259   {
260     if(m.empty()) return;
261     for(size_t idx = 0; idx < m.capacity_; ++idx)
262     {
263       if(is_key_deleted(m.buckets_[idx].first) ||
264          is_key_empty(m.buckets_[idx].first))
265         continue;
266       _insert(std::move(m.buckets_[idx]));
267     }
268   }
269   void copy_from(const hash_map& m)
270   {
271     if(m.empty()) return;
272     for(size_t idx = 0; idx < m.capacity_; ++idx)
273     {
274       if(is_key_deleted(m.buckets_[idx].first) ||
275          is_key_empty(m.buckets_[idx].first))
276         continue;
277       _insert(m.buckets_[idx]);
278     }
279   }
280   void increase_capacity()
281   {
282     if(size_ > (capacity_ >> 1))
283     {
284       hash_map _m(std::move(*this),capacity_ << 1);
285       swap(_m);
286     }
287   }
288   void decrease_capacity()
289   {
290     if(size_ < (capacity_ >> 2))
291     {
292       hash_map _m(*this,capacity_ >> 2);
293       swap(_m);
294     }
295   }
296   void set_key_deleted(value_type& pair)
297   {
298       pair.first = deleted_key_;
299       pair.second = mapped_type();
300   }
301   inline bool is_key_deleted(const key_type& key) const { return equaler_(key,deleted_key_); }
302   inline bool is_key_empty(const key_type& key) const { return equaler_(key,empty_key_); }
303   void init_buckets()
304   {
305     delete[] buckets_;
306     buckets_ = new value_type[capacity_]();
307     if(empty_key_ != key_type())
308     {
309       for(unsigned idx = 0; idx < capacity_; ++idx)
310       {
311         const_cast<key_type&>(buckets_[idx].first) = empty_key_;
312       }
313     }
314   }
315   void delete_buckets()
316   {
317     delete[] buckets_;
318   }
319   value_type* _insert(const value_type& _v)
320   {
321     const key_type& key = _v.first;
322     if(is_key_deleted(key) || is_key_empty(key))
323       return NULL;
324     increase_capacity();
325     value_type *pair_ = find_position(key);
326     if(!pair_ || equaler_(key,pair_->first))
327       return NULL;
328 
329     auto& k1 = const_cast<key_type&>(pair_->first);
330     auto& v1 = const_cast<mapped_type&>(pair_->second);
331     k1 = key;
332     v1 = _v.second;
333 
334     ++size_;
335     return pair_;
336   }
337   template<class P>
338   value_type* _insert(P&& p)
339   {
340     std::pair<key_type, mapped_type> _v(p.first, p.second);
341     const key_type& key = _v.first;
342     if(is_key_deleted(key) || is_key_empty(key))
343       return NULL;
344     increase_capacity();
345     value_type *pair_ = find_position(key);
346     if(!pair_ || equaler_(key,pair_->first))
347       return NULL;
348 
349     auto& k1 = const_cast<key_type&>(pair_->first);
350     auto& v1 = const_cast<mapped_type&>(pair_->second);
351     k1 = std::move(_v.first);
352     v1 = std::move(_v.second);
353 
354     ++size_;
355     return pair_;
356   }
357  private:
358   key_type empty_key_;
359   key_type deleted_key_;
360   size_type size_;
361   size_type capacity_;
362   value_type *buckets_;
363   hash_fn hasher_;
364   equal_fn equaler_;
365 };
366 
367 }//end namespace green_turtle
368 #endif//__MY_HASH_TABLE__

*/


//Graph structures
enum Color
{
	WHITE,
	BLACK,
	GRAY
};
enum EdgeType
{
	UNKOWN,
	TREE,
	BACK,
	FORWARD,
	CROSS
};
//For simplicity we use the GNode to represent 
class GNode
{
	friend class GraphAlgorithms;
	int data;
	//
	bool visited;
	int preTime;
	int postTime;
	int dis;
	GNode *prev;
	Color color;
	vector<GNode *> neighbors;
	vector<EdgeType> edges;
	vector<int> edgeWeights;
public:
	GNode(int d=0):data(d),visited(false),preTime(0),postTime(0), \
		dis(100000),prev(NULL),color(WHITE) {}
	void addNeighbor(GNode *n, int w=1) 
	{ 
		neighbors.push_back(n); 
		edges.push_back(UNKOWN); 
		edgeWeights.push_back(w);
	}
};
class GraphAlgorithms
{
private:
	unsigned int timer;
	vector<GNode *> sortedNodes;
public:
	GraphAlgorithms():timer(0){}
	//init() skip this, which does navive initialization  
	//for the members defined in the GNode objects in the graph.
	//It also intialize the timer.
	void DFS(GNode *s)
	{  
		if(!s) return;
		s->color = GRAY;
		s->preTime = timer++;
		s->visited = true;
		cout << s->data << " ";
		for(int i=0; i<s->neighbors.size(); i++){
			if(!s->neighbors[i]->visited)
				DFS(s->neighbors[i]);
		}
		s->postTime = timer++;
		s->color = BLACK;
	}
	//The following function get edge types for directed graph.
	//Calculating edge types for undirected graph is simpler since
	//there could be only TREE and BACK edges
	void getEdgeType(GNode *s)
	{
		if(!s) return;
		s->color = Color::GRAY;
		s->preTime = timer++;
		s->visited = true;
		for(int i=0; i<s->neighbors.size(); i++){
			if(s->neighbors[i]->color == WHITE)
				s->edges[i] = TREE;
			else if(s->neighbors[i]->color == GRAY)
				s->edges[i] = BACK;
			else{
				if(s->preTime<s->neighbors[i]->preTime)
					s->edges[i] = FORWARD;
				else
					s->edges[i] = CROSS;
			}
			if(!s->neighbors[i]->visited)
				getEdgeType(s->neighbors[i]);
		}
		s->postTime = timer++;
		s->color = BLACK;
	}

	void BFS(GNode *s)
	{
		if(!s) return;
		s->visited = true;
		s->dis = 0;
		s->prev = NULL;
		queue<GNode *> qu;
		qu.push(s);
		while(!qu.empty()){
			GNode *curr = qu.front();
			cout << curr->data << " ";
			qu.pop();
			for(int i=0; i<curr->neighbors.size(); i++){
				if(!curr->neighbors[i]->visited){
					curr->neighbors[i]->visited = true;
					if(curr->neighbors[i]->dis>curr->dis+1){
					    curr->neighbors[i]->dis = curr->dis+1;
						curr->neighbors[i]->prev = curr;
					}
					qu.push(curr->neighbors[i]);
			   }
		   }
		}
	}

	/*
	TOPOLOGICAL-SORT(G)
    1 call DFS(G) to compute finishing times f[v] for each vertex v
    2 as each vertex is finished, insert it onto the front of a linked list
    3 return the linked list of vertices
	*/
	void PrintTopologySort(GNode *s)
	{
	    TopologySort(s);
		for(int i=0; i<sortedNodes.size(); i++)
			cout << sortedNodes[i]->data << endl;
	}
	void TopologySort(GNode *s)
	{
		if(!s) return;
		//For simplicity I just write the topology sort, omitting the acyclic checking. 
		s->preTime = timer++;
		s->visited = true;
		for(int i=0; i<s->neighbors.size(); i++){
			if(!s->neighbors[i]->visited)
				TopologySort(s->neighbors[i]);
		}
		s->postTime = timer++;
		sortedNodes.insert(sortedNodes.begin(),s); //we can make this a return value
	}
	//Dijkstras shortest path algorithm: the single-source shortest-paths 
	//problem on a weighted, directed graph G = (V, E) for the case in which 
	//all edge weights are nonnegative.   Not tested.
	struct GNodeComp
	{
		bool operator() (const GNode *n1, const GNode *n2){
			return n1->dis > n2->dis;
		}
	};
	void DijkstrasShortestPath(GNode *s)
	{
		if(!s) return;
		s->dis = 0;
		s->prev = NULL;
		priority_queue<GNode*, vector<GNode*>, GNodeComp> vq;
		//Call DFS to collect nodes.  Here for simplicity we 
		//use the nodes collected by the TopologySort() routine.
		for(int i=0; i<sortedNodes.size(); i++){
			vq.push(sortedNodes[i]);
		}
		while(!vq.empty()){
			GNode *curr=vq.top();
			vq.pop();
			for(int i=0; i<curr->neighbors.size(); i++){
				if(curr->neighbors[i]->dis > curr->dis+curr->edgeWeights[i])
					curr->neighbors[i]->dis = curr->dis+curr->edgeWeights[i];
			}	
		}
	}

	void DagShortestPath(GNode *s)
	{
		if(!s) return;
		s->dis = 0;
		TopologySort(s);
		for(int i=0; i<sortedNodes.size(); i++){
			GNode *n = sortedNodes[i];
			for(int j=0; j<n->neighbors.size(); j++){
				if(n->neighbors[j]->dis > n->dis + n->edgeWeights[j]){
					n->neighbors[j]->dis = n->dis + n->edgeWeights[j];
					n->neighbors[j]->prev = n;
				}
			}
		}
	}

	/* This is the more general shortest path algorithm runing in O(V*E):
	BELLMAN-FORD(G, w, s)
	1 INITIALIZE-SINGLE-SOURCE(G, s)
	2 for i ← 1 to |V[G]| - 1
	3 do for each edge (u, v)  E[G]
	4 do RELAX(u, v, w)
	5 for each edge (u, v)  E[G]
	6 do if d[v] > d[u] + w(u, v)
	7 then return FALSE
	8 return TRUE
	*/
};

template<class T>
class Heap
{
	vector<T> data;
	void maxHeapIfy(unsigned idx)
	{
		unsigned n = data.size();
		if(idx>=n) return;
		unsigned maxIdx;
		if(2*idx+2<n && data[2*idx+2]>data[2*idx+1] && data[2*idx+2]>data[idx]){
			maxIdx = 2*idx+2;
			swap(data[idx],data[maxIdx]);
			maxHeapIfy(maxIdx);
		}
		else if(2*idx+1<n&&(2*idx+2>=n||data[2*idx+1]>data[2*idx+2])&&data[2*idx+1]>data[idx]){
			maxIdx = 2*idx+1;
			swap(data[idx],data[maxIdx]);
			maxHeapIfy(maxIdx);
		}
	}
public:
	void makeHeap(const T A[], int n)
	{
		if(n<=0) return;
		data.clear();
		for(int i=0; i<n; i++)
			data.push_back(A[i]);
		for(int i=n/2; i>=0; i--){
			maxHeapIfy(i);
		}
	}
	void push(const T d)
	{
		data.insert(data.begin(),d);
		maxHeapIfy(0);
	}
	T pop()
	{
		if(data.empty()) return T(); //I forgot this.
		swap(data.front(), data.back());
		T res = data.back();
		data.pop_back();
		maxHeapIfy(0);
		return res;
	}
	size_t size()
	{
		return data.size();
	}
};

