/* avl tree insertion......*/
#include<stdio.h>
#include<stdlib.h>
#define MAX 100

struct node{
	int data;
	int height;
	struct node *left;
	struct node *right;
};

struct node *avlInsert(struct node *root,int data);
struct node *newNode(int data);
int height(struct node* node);
void printTree(struct node *root);
int max(struct node *a,struct node *b);
struct node *leftRotate(struct node *root);
struct node *rightRotate(struct node *root);

int main()
{
	int limit,i;
	int values[MAX];
	struct node *root=NULL;
	printf("Enter the number of  tree nodes: ");
	scanf("%d",&limit);
	printf("Enter %d values\n",limit);
	for(i=0;i<limit;i++){
		scanf("%d",&values[i]);
		root=avlInsert(root,values[i]);
	}
	printf("AVL tree:\n");
	printTree(root);
	printf("\n\n");
	return;
}
struct node *leftRotate(struct node *root)
{
	struct node *newRoot=root->right;
	root->right=newRoot->left;
	newRoot->left=root;
	root->height=1+max(newRoot->left,newRoot->right);
	newRoot->height=1+max(newRoot->left,newRoot->right);
	return newRoot;
	
}
struct node *rightRotate(struct node *root)
{
	struct node *newRoot=root->left;
	root->left=newRoot->right;
	newRoot->right=root;
	root->height=1+max(root->left,root->right);
	newRoot->height=1+max(newRoot->left,newRoot->right);
	return newRoot;
}
int height(struct node* node) {
	if (node==NULL) {
		return(0);
	}
	else {
		int lDepth = height(node->left);
		int rDepth = height(node->right);

		if (lDepth > rDepth) return(lDepth+1);
		else return(rDepth+1);
	}
}
void printTree(struct node *root)
{
	if(root!=NULL){
		printTree(root->left);
		printf("%d  ",root->data);
		printTree(root->right);
	}
}
struct node *avlInsert(struct node *root,int data)
{
	int balance;
	if(root==NULL)
		return(newNode(data));
	else{
		if(data <= root->data)
			root->left=avlInsert(root->left,data);
		else
			root->right=avlInsert(root->right,data);
	}

	balance=height(root->left)-height(root->right);
	if(balance>1){
		if(height(root->left->left) >= height(root->left->right)){
			return rightRotate(root);
		}else{

			root->left =leftRotate(root->left);
			return rightRotate(root);
		}
	
	}else if(balance<-1){
		if(height(root->right->right) >= height(root->right->left)){
			return leftRotate(root);
		}else{
			root->right=rightRotate(root->right);
			return leftRotate(root);
		}
	
	}
	root->height=1+max(root->left,root->right);
	return root;
	
}
int max(struct node *a,struct node *b)
{
	if(height(a)>height(b))
		return height(a);
	else
		return height(b);

}
struct node *newNode(int data)
{
	struct node *node;
	node=malloc(sizeof(struct node));
	node->data=data;
	node->left=NULL;
	node->right=NULL;
	return(node);

}
