//
// BST_Search_Insert.cpp
// C++ code, harshly and successfully compiled by g++
//


#include <iostream>
#include <string>
#include <queue>

using std::string;
using std::cout;
using std::endl;

class BST;
class TreeNode {
private:
	TreeNode *leftchild;
	TreeNode *rightchild;
	TreeNode *parent;
	int key;
	string element;
public:
	TreeNode() :leftchild(0), rightchild(0), parent(0), key(0), element("") {};
	TreeNode(int a, string b) :leftchild(0), rightchild(0), parent(0), key(a), element(b) {};



	TreeNode* GetLeftchild(){ return leftchild; }
	int GetKey() { return key; }              // 為了在main()要能夠檢視node是否正確
	string GetElement() { return element; }   // 才需要這兩個member function讀取private data

											  // 其餘情況, 因為class BST是class TreeNode的friend class
											  // 在class BST的member function中, 可以直接存取class TreeNode的private data

	friend class BST;   // 放在 private 或 public 都可以 
};

class BST {
public:
	TreeNode* Successor(TreeNode *current);
	BST() :root(0) {};
	TreeNode *root;
	TreeNode* Search(int key);
	TreeNode* Leftmost(TreeNode *current);

	TreeNode* Search_given_k(TreeNode *current,int k);


	void InsertBST(int key, string element);
	void InorderPrint();        // 可以用來確認BST是否建立成功
	void Levelorder();          // 可以確認BST是否建立成功
};




TreeNode* BST::Search(int KEY) {

	TreeNode *current = root;               // 將curent指向root作為traversal起點

	while (current != NULL && KEY != current->key) {  // 兩種情況跳出迴圈：
													  // 1.沒找到 2.有找到
		if (KEY < current->key) {
			current = current->leftchild;   // 向左走
		}
		else {
			current = current->rightchild;  // 向右走
		}
	}
	return current;
}

void BST::InsertBST(int key, string element) {

	TreeNode *y = 0;        // 準新手爸媽
	TreeNode *x = 0;        // 哨兵
	TreeNode *insert_node = new TreeNode(key, element);

	x = root;
	while (x != NULL) {                // 在while中, 以如同Search()的方式尋找適當的位置       
		y = x;
		if (insert_node->key < x->key) {
			x = x->leftchild;
		}
		else {
			x = x->rightchild;
		}
	}                                  // 跳出迴圈後, x即為NULL
									   // y即為insert_node的parent
	insert_node->parent = y;           // 將insert_node的parent pointer指向y

	if (y == NULL) {                    // 下面一組if-else, 把insert_node接上BST
		this->root = insert_node;
	}
	else if (insert_node->key < y->key) {
		y->leftchild = insert_node;
	}
	else {
		y->rightchild = insert_node;
	}
}

/*TreeNode* BST::Leftmost(TreeNode *current) {

	while (current->leftchild != NULL) {
		current = current->leftchild;
	}
	return current;
}*/

TreeNode* BST::Leftmost(TreeNode *current) {


	if (current->leftchild != NULL) {
		current = current->leftchild;
		Leftmost(current);
	}else {
		return current;
	}
}
TreeNode* BST::Successor(TreeNode *current) {

	if (current->rightchild != NULL) {
		return Leftmost(current->rightchild);
	}

	TreeNode *new_node = current->parent;

	while (new_node != NULL && current == new_node->rightchild) {
		current = new_node;
		new_node = new_node->parent;
	}

	return new_node;
}


TreeNode* BST:: Search_given_k(TreeNode *current,k) {




};

void BST::InorderPrint() {
	TreeNode *current = new TreeNode;
	current = Leftmost(root);
	while (current) {
		cout << current->element << "(" << current->key << ")" << " ";
		current = Successor(current);
	}
}

void BST::Levelorder() {

	std::queue<TreeNode*> q;
	q.push(this->root);					    // 把root作為level-order traversal之起點
											// 推進queue中
	while (!q.empty()) {                     // 若queue不是空的, 表示還有node沒有visiting

		TreeNode *current = q.front();      // 取出先進入queue的node
		q.pop();
		cout << current->element << "(" << current->key << ")" << " ";

		if (current->leftchild != NULL) {    // 若leftchild有資料, 將其推進queue
			q.push(current->leftchild);
		}
		if (current->rightchild != NULL) {   // 若rightchild有資料, 將其推進queue
			q.push(current->rightchild);
		}
	}
}


int main() {

	BST T;

	T.InsertBST(5, "龜仙人");
	T.InsertBST(7, "悟空");
	T.InsertBST(1, "喵嗚");
	T.InsertBST(3, "汪汪");
	T.InsertBST(6, "龜頭人");
	T.InsertBST(2, "奇倫");
	T.InsertBST(4, "士豪");
	T.InsertBST(-100, "-100");
	


	cout << "Level-order Traversal:\n";
	T.Levelorder();
	cout << endl;



	TreeNode *node = T.Search(1000);

	TreeNode *node2 = T.Leftmost(T.root);


	if (node2 != NULL) {
		cout << "There is " << node2->GetElement() << "(" << node2->GetKey() 
		<< ")" << endl;
	}


	system("pause");
	return 0;
}
