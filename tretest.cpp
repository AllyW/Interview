#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

struct TreeNode { 
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* createTree(int a[], int n)
{
	if (n<=0) return NULL;
    TreeNode **tree = new TreeNode*[n];
	for(int i=0; i<n; i++) {
		tree[i] = new TreeNode(a[i]);
	}
	int pos=1;
	for(int i=0; i<n && pos<n; i++) {
		if (tree[i])
		{
			tree[i]->left = tree[pos++];
			if (pos<n)
			{
				tree[i]->right = tree[pos++];
			}
		}
	}
	return tree[0];
}
void printTree_post_order(TreeNode *root)
{
	if (root == NULL){
		//cout << "# ";
		return ;
	}
	printTree_post_order(root->left);
	printTree_post_order(root->right);
	cout << root->val << " ";
}

void printTree_bylevel(TreeNode* root)
{
	if(!root) return;
	queue<TreeNode*> q;
	q.push(root);
	q.push(NULL);
    int pos = 18;
	for(int i = 0; i < pos; ++i)
	{
		cout << " ";
	}
	pos = 0;
	while(!q.empty())
	{
		TreeNode* p = q.front(); q.pop();
		if(p)
		{
			cout << p -> val << " ";
			if( p -> left) q.push( p-> left);
			if( p -> right) q.push( p -> right);
			pos +=1;
		}
		else
		{
			if(q.empty()) return;
			q.push(NULL);
			cout << endl;
			for(int i = 0; i < 18 - pos; ++i)
			{
				cout << " ";
			}

		}
	}
}

vector<int> visibNodes(TreeNode *root)
{
	// visible nodes: in the ppath from root to the current node, there is 
	// no node whose value exceeds the current one's.
	vector<int> result;
	if(!root) return result;
	stack<int > pathValue;
	stack<int > maxValue;
	maxValue.push(INT_MIN);
	stack<TreeNode* > s;
	TreeNode *last = NULL;
	while(!s.empty() || root)
	{
		if(root)
		{
			s.push(root);
			pathValue.push(root -> val);
			if(root -> val >= maxValue.top())
			{
				maxValue.push(root -> val);
			}
			root = root -> left;
		}
		else
		{
			TreeNode* peak = s.top();
			if(peak -> right && last != peak -> right)
			{
				root = peak -> right;
			}
			else
			{
				last = peak;
				if(peak -> val >= maxValue.top())
				{
					result.push_back(peak -> val);
					maxValue.pop();
				}
				pathValue.pop();
				s.pop();
			}
		}
	}
	return result;
}

void printArray(vector<int> v)
{
	for(int i=0; i<v.size(); i++){
		cout << v[i] << " ";
	}
	cout << endl;
}
int main(int argc, const char * argv[]) {
    int a[] = {5, 3, 20, 21, 7, 12, 8};
	TreeNode* p = createTree(a, sizeof(a)/sizeof(int));
    cout <<"nodes in post order traversal: " << endl;	
	printTree_post_order(p);
	cout << endl;
    cout << "nodes in traversal by level: " << endl;
	printTree_bylevel(p);
	cout << endl;
	vector<int> v =  visibNodes(p);
	cout << "visible nodes: "<<endl;
	printArray(v);
	cout << endl;
	return 0;
}
