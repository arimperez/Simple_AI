
/**************************************
Author: Ari Perez
November, 2017
**************************************/

#include <stdlib.h>
#include <stdio.h>
#include "BinarySearchTreeAPI.h"

/**
 * Creates a TreeNode. TreeNode children are set to NULL and data is set to the passed in data.
 * @param data - the data to be stored within the Node.
 * @return Newly created TreeNode
 *
 */
TreeNode* createTreeNode(TreeDataPtr data)
{
    TreeNode *newNode = malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;//left;
    newNode->right = NULL;//right;
    return (newNode);
}

/**
 * createBinTree allocates memory for Tree and assigned function pointers
 * @param  compare [Function pointer to Compare data in tree nodes]
 * @param  del     [Function pointer to delete data from node]
 * @return Newly created Tree
 */
Tree * createBinTree(CompareFunc compare, DeleteFunc del)
{
    Tree *newTree = malloc(sizeof(Tree));
    newTree->root = NULL;
    newTree->compareFunc = compare;
    newTree->deleteFunc = del;
    return(newTree);
}

void printInts(void*data)
{
    int *i = (int *)data;
    printf("%d ",*i);
}
/**
 * destroyBinTree - remove all items and free memory
 * @param  toDestroy - the tree
 * @return
 */
void  destroyBinTree(Tree * toDestroy)
{
    //int count = 0;
	while (!isTreeEmpty(toDestroy))//(toDestroy->root != NULL)
	{
		removeFromTree(toDestroy, toDestroy->root->data);
        //printInts(toDestroy->root->data);
        //count++;
	}
	return;
}

/**
 * Add data to a tree
 * @param theTree
 * @param data
 */

void addToTree(Tree * theTree, TreeDataPtr data)
{
    if (theTree == NULL)
    {
        return;
    }

    TreeNode *toInsert = createTreeNode(data);

    if (theTree->root == NULL)
    {
        theTree->root = toInsert;
        return;
    }

    else
    {
        CompareFunc cmp = theTree->compareFunc;

        TreeNode *parent = theTree->root;

        //Changes to 1 when element has been placed
        int inPlace = 0;

        //I find this clever while not in place... Is it just me?
        while(!inPlace)
        {
            if (cmp(toInsert->data, parent->data) < 0)
            {
                if (parent->left == NULL)
                {
                    parent->left = toInsert;
                    inPlace = 1;
                }else {
                    parent = parent->left;
                }
            }

            else if (cmp(toInsert->data, parent->data) > 0)
            {
                if (parent->right == NULL)
                {
                    parent->right = toInsert;//right;
                    inPlace = 1;
                } else {
                    parent = parent->right;
                }
            }
        }

    }
}

/**
 * Remove data from the tree
 * @param theTree
 * @param data
 */
void removeFromTree(Tree * theTree, TreeDataPtr data)
{
	if (theTree == NULL)
	{
		return;
	}

	TreeNode *toDelete = createTreeNode(data);
	TreeNode *parent = theTree->root;
	TreeNode *prevParent = NULL;
	CompareFunc cmp = theTree->compareFunc;
	int found = 0;

    if (theTree->root!= NULL)
    {
        if (theTree->root->left == NULL && theTree->root->right == NULL)
        {
            //free(theTree->root);
            theTree->root = NULL;
            //free(theTree);
            //theTree = NULL;
            return;
        }
    }
	while(!found)
    {
		//printf("test\n");
        if (cmp(toDelete->data, parent->data) < 0)
        {
            if (parent->left == NULL)
            {
                found = 1;
            }else {
				prevParent = parent;
                parent = parent->left;
            }
        }

        else if (cmp(toDelete->data, parent->data) > 0)
        {
            if (parent->right == NULL)
            {
                found = 1;

            } else {
				prevParent = parent;
                parent = parent->right;
            }
        }


        else if (cmp(toDelete->data, parent->data) == 0)
        {
			if (cmp(toDelete->data, theTree->root->data) == 0)
			{
				prevParent = parent;
			}
			if (parent->left == NULL && parent->right == NULL)
			{
                if (theTree->root == parent)
                {
                    theTree->root = NULL;
                }

                else if (prevParent->left ==  parent)
                {

    				theTree->deleteFunc(parent->data);
    				free(parent);

    				parent = NULL;
    				prevParent->left = NULL;
    				found = 1;
    				return;
                }
                else
                {

                    theTree->deleteFunc(parent->data);
                    free(parent);
                    parent = NULL;
                    prevParent->right = NULL;
                    found = 1;
                    return;

                }
			}

			//Only has one child
			else if (!hasTwoChildren(parent))
			{
                if (parent == theTree->root)
                {
                    if(parent->right == NULL)
                    {
                        theTree->root = parent->left;
                        theTree->deleteFunc(parent->data);
						free(parent);
						parent = NULL;
						found = 1;
                    }
                    else {
                        theTree->root = parent->right;
                        theTree->deleteFunc(parent->data);
                        free(parent);
                        parent = NULL;
                        found = 1;

                    }
                }

				else if (parent->right==NULL)
				{
					if (prevParent->right == parent)
					{
						prevParent->right = parent->left;
						theTree->deleteFunc(parent->data);
						free(parent);
						parent = NULL;
						found = 1;
					} else {
						prevParent->left = parent->left;
						theTree->deleteFunc(parent->data);
						free(parent);
						parent = NULL;
						found = 1;
					}
				}

				else {

					if (prevParent->right == parent)
					{
						prevParent->right = parent->right;
						theTree->deleteFunc(parent->data);
						free(parent);
						parent = NULL;
						found = 1;
					} else {
						prevParent->left = toDelete->right;
						theTree->deleteFunc(parent->data);
						free(parent);
						parent = NULL;
						found = 1;
					}
				}
				//if element has two branches
			} else {
				//found = 1;
				TreeNode *toReplace = parent->left;
				int replaced = 0;
				while(!replaced)
				{
					//Will hopefully keep structure
					if (toReplace->right == NULL && toReplace->left == NULL)
					{


						if (prevParent->right == toReplace)//parent)
						{
							prevParent->right = NULL;//parent->right;
							toReplace->left = parent->left;
							toReplace->right = parent->right;
							if (theTree->root == parent)
							{
								theTree->root = toReplace;
							}
							theTree->deleteFunc(parent->data);
							free(parent);
							parent = NULL;
							replaced = 1;
						} else {
							prevParent->left = toDelete->right;
							toReplace->left = parent->left;
							toReplace->right = parent->right;
							if (theTree->root == parent)
							{
								theTree->root = toReplace;
							}
							theTree->deleteFunc(parent->data);
							free(parent);
							parent = NULL;
							replaced = 1;

						}

					}

					if (toReplace->right != NULL)
					{
						prevParent = toReplace;
						toReplace = toReplace->right;
					}
					else
					{
						prevParent = toReplace;
						toReplace = toReplace->left;
					}



				}
				found = 1;
        	}


    	}
	}

}


/**
 * This function searches the tree for the target data
 * @param  theTree
 * @param  data
 * @return         NULL if fail, otherwise return data
 */
TreeDataPtr findInTree( Tree* theTree, TreeDataPtr data )
{
    if (theTree == NULL)
    {
        return NULL;
    }

    TreeNode *toFind = createTreeNode(data);
	TreeNode *parent = theTree->root;
    CompareFunc cmp = theTree->compareFunc;

    int found = 0;

    while(!found)
    {
        if (cmp(toFind->data, parent->data) < 0)
        {
            if (parent->left == NULL)
            {
                return NULL;
            }else {
                parent = parent->left;
            }
        }

        else if (cmp(toFind->data, parent->data) > 0)
        {
            if (parent->right == NULL)
            {
                return NULL;

            } else {
                parent = parent->right;
            }
        }


        else if (cmp(toFind->data, parent->data) == 0)
        {
            return(parent->data);
            //return(toFind->data);
        }


    }

    return NULL;


}

/**
 * Get data from the root of the Tree if it exists.
 * @param  theTree
 * @return NULL if tree is empty, otherwise return root
 */
TreeDataPtr getRootData(Tree * theTree)
{
    if (theTree == NULL)
    {
        return NULL;
    }

    else {
        return theTree->root->data;
    }

	return NULL;
}

void inOrderRight(TreeNode *root, PrintFunc printData)
{
	if (root == NULL)
	{
		return;
	}
	else {
		//root->right
		if (root->right != NULL)
		{

			if (root->left != NULL)
			{
				inOrderLeft(root->left, printData);

				if (root->right != NULL)
				{

					printData(root->data);
					root = root->right;
					inOrderLeft(root, printData);
				}


			}
			else
			{
				printData(root->data);
				inOrderRight(root->right, printData);


			}
		}



		else {
			if (root->left == NULL)
			{
			//printf("The end is near:");
		    	printData(root->data);
			}
		}

	}
	return;
}
void inOrderLeft (TreeNode *root, PrintFunc printData)
{
	if (root == NULL)
	{
		return;
	}
	else {
		//printData(root->data);
		if (root->left != NULL && root->right != NULL)
		{
			//Go down branch
			inOrderLeft(root->left, printData);
			if (root->right != NULL)
			{
				printData(root->data);
				inOrderRight(root->right, printData);
			}
			else {
				printData(root->data);
			}
		}

		else if (root->left!= NULL)
		{

			inOrderLeft(root->left, printData);
			printData(root->data);
		}

		else {
			printData(root->data);
		}

	}
	return;

}
/**
 * [printInOrder This function prints the tree using an inOrder traversal
 * @param theTree   [description]
 * @param printData [description]
 */
void printInOrder(Tree * theTree, PrintFunc printData)
{

	if (theTree == NULL)
	{
		return;
	}

    else {
		inOrderLeft(theTree->root, printData);

	}

}

void preOrderRight(TreeNode *root, PrintFunc printData)
{
	if (root == NULL)
	{
		return;
	}
	else {
		//root->right
		if (root->right != NULL)
		{

			if (root->left != NULL)
			{
				printData(root->data);
				preOrderLeft(root->left, printData);

				if (root->right != NULL)
				{
					root = root->right;
					preOrderLeft(root, printData);
				}

			}
			else
			{
				printData(root->data);
				preOrderRight(root->right, printData);
			}

		}

		else {
			if (root->left == NULL)
			{
		    	printData(root->data);
			}
		}

	}
	return;
}
void preOrderLeft (TreeNode *root, PrintFunc printData)
{
	if (root == NULL)
	{
		return;
	}
	else {
		//printData(root->data);
		if (root->left != NULL && root->right != NULL)
		{
			//Go down branch
			printData(root->data);
			preOrderLeft(root->left, printData);
			if (root->right != NULL)
			{
				//printData(root->data);
				preOrderRight(root->right, printData);
			}
			/*else {
				//printf("Numb: ");
				//printData(root->data);
			}*/
			//printData(root);
		}

		else if (root->left!= NULL)
		{
			printData(root->data);
			preOrderLeft(root->left, printData);

		}

		else {
			//printf("TEST");
			printData(root->data);
		}

	}
	return;

}

/**
 * [printPreOrder This function prints the tree using an preOrder traversal
 * @param theTree   [description]
 * @param printData [description]
 */
void printPreOrder(Tree * theTree, PrintFunc printData)
{

	if (theTree == NULL)
	{
		return;
	}

    else {
		printData(theTree->root->data);
		preOrderLeft(theTree->root->left, printData);
		preOrderRight(theTree->root->right, printData);

	}

}

void postOrderRight(TreeNode *root, PrintFunc printData)
{
	if (root == NULL)
	{
		return;
	}
	else {
		//root->right
		if (root->right != NULL)
		{

			if (root->left != NULL)
			{
				//printData(root->data);
				postOrderLeft(root->left, printData);
				postOrderRight(root->right, printData);
				if (root->left != NULL)
				{

					printData(root->data);

				}

			}
			else
			{
				printData(root->data);
				postOrderRight(root->right, printData);


			}
		}


		else {
		    printData(root->data);
		}

	}
	return;
}
void postOrderLeft (TreeNode *root, PrintFunc printData)
{
	if (root == NULL)
	{
		return;
	}
	else {
		//printData(root->data);
		if (root->left != NULL && root->right != NULL)
		{
			//Go down branch
			inOrderLeft(root->left, printData);
			postOrderRight(root->right,printData);
			printData(root->data);
		}

		else if (root->left!= NULL)
		{
			printData(root->data);
			postOrderLeft(root->left, printData);
		}

		else {
			printData(root->data);
		}

	}
	return;

}

/**
 * [printPostOrder This function prints the tree using an postOrder traversal
 * @param theTree   [description]
 * @param printData [description]
 */
void printPostOrder(Tree * theTree, PrintFunc printData)
{

	if (theTree == NULL)
	{
		return;
	}

    else {

		postOrderLeft(theTree->root->left, printData);
		postOrderRight(theTree->root->right, printData);
		printData(theTree->root->data);
	}

}

/**
 * Checks if a tree is empty
 * @param  theTee [description]
 * @return        0 if false, 1 otherwise
 */
int isTreeEmpty(Tree* theTree)
{
    if (theTree == NULL)
    {
        return 1;
    }

    else if (theTree->root == NULL)
    {
        return 1;
    }

    else if (theTree->root != NULL)
    {
        return 0;
    }

    else {
        return 1;
    }
}


/**
 * Helper function for checking if a single node is a leaf (no children)
 * @param  treeNode [description]
 * @return          0 if false, 1 otherwise
 */
int isLeaf( TreeNode * treeNode)
{
    if(treeNode->left == NULL && treeNode->right == NULL)
    {
        return 1;
    }
    return 0;
}

/**
 * Helper funciton for checking if a single node has two children.
 * @param  treeNode [description]
 * @return         0 if false, 1 otherwise
 */
int hasTwoChildren( TreeNode *treeNode)
{
	//If they are both NULL
	if (treeNode->left != treeNode->right)
	{
		if (treeNode->left == NULL )
		{
			return 0;
		}

		else if(treeNode->right == NULL)
		{
			return 0;
		}

		else
		{
			return 1;
		}

	}
	return 0;
}

/**
 * Helper funciton Get the height of a particulat Node in the tree.
 * @param  treeNode [description]
 * @return    (1-Based) heigh for the tree.
 */
int getHeight( TreeNode* treeNode )
{
    if (treeNode == NULL)
    {
        return 0;
    }

    int left = getHeight(treeNode->left);
    int right = getHeight(treeNode->right);

    if (right > left)
    {
        return (right + 1);
    }

    else {
        return (left + 1);
    }



}
