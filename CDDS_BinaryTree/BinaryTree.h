#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#pragma once
template<typename T>
class TreeNode;

template<typename T>
class BinaryTree
{
public:

	/// <summary>
	/// The constructor for the binary tree
	/// </summary>
	BinaryTree();

	/// <summary>
	/// The deconstructor for the binary tree
	/// </summary>
	~BinaryTree();

	/// <summary>
	/// Returns whether or not there are any nodes in the list
	/// </summary>
	bool isEmpty() const;
	/// <summary>
	/// Creates a new node that stores the given value and places it into the tree
	/// </summary>
	/// <param name="value">The new value to add to the tree</param>
	void insert(T value);
	/// <summary>
	/// Finds the node with the given value and removes it from the tree
	/// </summary>
	/// <param name="value">The value of the node to search for in the tree</param>
	void remove(T value);
	/// <summary>
	/// Finds and returns a node with the given value in the tree
	/// </summary>
	/// <param name="value">The value of the node to search for</param>
	TreeNode<T>* find(T value);

	/// <summary>
	/// Draws the nodes to the screen
	/// </summary>
	/// <param name="selected"></param>
	void draw(TreeNode<T>* selected = nullptr);

private:
	/// <summary>
	/// Finds the node that matches the value in the list
	/// </summary>
	/// <param name="searchValue">The value of the node to search for</param>
	/// <param name="nodeFound">A pointer that will store the address of the node that was found</param>
	/// <param name="nodeParent">A pointer that will store the address of the parent of the node that was found</param>
	/// <returns>Whether or not a node matching the value could be found</returns>
	bool findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent);

	void draw(TreeNode<T>*, int x, int y, int horizontalSpacing, TreeNode<T>* selected = nullptr);

	TreeNode<T>* m_root = nullptr;
};

#endif

template<typename T>
inline BinaryTree<T>::BinaryTree()
{
	//sets the root to be null
	m_root = nullptr;
}

template<typename T>
inline BinaryTree<T>::~BinaryTree(){}

template<typename T>
inline bool BinaryTree<T>::isEmpty() const
{
	//if the root is null
	if (m_root == nullptr)
		//return that the tree is empty
		return true;
	//else return false
	return false;
}

template<typename T>
inline void BinaryTree<T>::insert(T value)
{
	//Temp nodes for iterating through the binary tree
	TreeNode<T>* newNode = new TreeNode<T>(value);
	TreeNode<T>* tempNode = m_root;
	bool nodeInserted = false;

	//if the root isn't set
	if (m_root == nullptr)
	{
		//set the root to be the new node
		m_root = newNode;
		return;
	}

	//while the node isn't inserted into the tree
	while (!nodeInserted)
	{
		//if the value is less then the current nodes data
		if (value < tempNode->getData())
		{
			//if the current node has a left
			if (tempNode->getLeft())
				//set the current node to be the current nodes left
				tempNode = tempNode->getLeft();
			else
			{
				//set the temp nodes left to be the new node
				tempNode->setLeft(newNode);
				nodeInserted = true;
			}
		}

		//if the value is bigger than the current nodes data
		else if (value > tempNode->getData())
		{
			//if the current node has a right
			if (tempNode->getRight())
				//set the current node to the current nodes right
				tempNode = tempNode->getRight();
			else
			{
				//set the current nodes right to be the new node
				tempNode->setRight(newNode);
				nodeInserted = true;
			}
		}

		//if the value is equal to the data then return
		else if (value == tempNode->getData())
			return;
	}

	return;
}

template<typename T>
inline void BinaryTree<T>::remove(T value)
{
	//the node to remove is set useing the value given
	TreeNode<T>* nodeToRemove = new TreeNode<T> (value);
	//the node parent will be set to the current nodes parent
	TreeNode<T>* nodeParent = new TreeNode<T>();
	//the current node for iterating
	TreeNode<T>* currentNode = nullptr;

	//if the node cannot be found then return
	if (!findNode(value, nodeToRemove, nodeParent))
		return;

	//If the node to remove dowsn't have a right or a left'
	if (!nodeToRemove->hasRight() && !nodeToRemove->hasLeft())
	{
		//If the parent doesn't have a right or left then it is the root
		if (!nodeParent->getLeft() && !nodeParent->getRight())
			//so set the root to be null
			m_root = nullptr;
		//if the node to remove is less than the parent
		if (nodeToRemove->getData() < nodeParent->getData())
			//then it is to the left of the parent, so set the parents left
			nodeParent->setLeft(nullptr);
		//if the node to remove is more than the parent
		if (nodeToRemove->getData() > nodeParent->getData())
			//then it is to the right of the parent, so set the parents right
			nodeParent->setRight(nullptr);
		//delete the node to remove
		delete nodeToRemove;
	}
	//If the node to remove only has one right or left
	else if (bool(nodeToRemove->hasRight()) ^ bool(nodeToRemove->hasLeft()))
	{
		//if this is the root...
		//...and it has a left, set the left to be the root
		if (!nodeParent->getLeft() && !nodeParent->getRight() && nodeToRemove->hasLeft()) 
			m_root = nodeToRemove->getLeft();
		//...and it haqs a right, set the right to be the node
		if (!nodeParent->getLeft() && !nodeParent->getRight() && nodeToRemove->hasRight())
			m_root = nodeToRemove->getRight();
		

		//if the node to remove is greater than the node parent...
		//...and it has a right, set the parents right to be the node to removes right
		if (nodeParent->getData() < nodeToRemove->getData() && nodeToRemove->hasRight())
			nodeParent->setRight(nodeToRemove->getRight());
		//...and it has a left, set the parents right to be the node to removes left
		if (nodeParent->getData() < nodeToRemove->getData() && nodeToRemove->hasLeft())
			nodeParent->setRight(nodeToRemove->getLeft());
		
		//if the node to remove is less than the node parent...
		//...and it has a right, set the parents left to be the node to removes right
		if (nodeParent->getData() > nodeToRemove->getData() && nodeToRemove->hasRight())
			nodeParent->setLeft(nodeToRemove->getRight());
		//...and it has a left, set the parents left to be the node to removes left
		if (nodeParent->getData() > nodeToRemove->getData() && nodeToRemove->hasLeft())
			nodeParent->setLeft(nodeToRemove->getLeft());
		
		//delete the node to remove
		delete nodeToRemove;
	}

	//If the node to remove has two children
	else if (nodeToRemove->hasRight() && nodeToRemove->hasLeft())
	{
		//set the current node to be the node to removes right
		currentNode = nodeToRemove->getRight();

		//if the current node has a left
		if (currentNode->hasLeft())
		{
			//set the parent to be the current node
			nodeParent = currentNode;

			//create a bool to search for the left most node from the current node
			bool searching = true;

			//while the searching bool is true
			while (searching)
			{
				//if the node parents left has a left
				if (nodeParent->getLeft()->hasLeft())
					//set the parent to be the parents left
					nodeParent = nodeParent->getLeft();
				
				//else we are at the left most nodes parent
				else
				{
					//set the current node to be the parents left
					currentNode = nodeParent->getLeft();
					searching = false;
				}
			}
			//set the data of the node to remove to be the current nodes data
			nodeToRemove->setData(currentNode->getData());
			//set the parents left to be the current nodes right
			nodeParent->setLeft(currentNode->getRight());
			//delete the current node since the data has already been copied
			delete currentNode;
		}
		//if the current node has no left
		else
		{
			//set the node to removes data to the current nodes data
			nodeToRemove->setData(currentNode->getData());

			//if the current node has a right
			if (currentNode->hasRight())
				//set the node to removes right to be the current nodes right
				nodeToRemove->setRight(currentNode->getRight());
			//if the current node doesnt have a right
			else
				//set the node to removes right to be null
				nodeToRemove->setRight(nullptr);

			//delete the current node
			delete currentNode;
		}
	}
	return;
}

template<typename T>
inline TreeNode<T>* BinaryTree<T>::find(T value)
{
	//a node to iterate through the tree
	bool nodeFound = false;
	TreeNode<T>* currentNode = m_root;

	//while the node has not been found
	while (!nodeFound)
	{
		//if the value is less than the current node
		if (value < currentNode->getData())
		{
			//if the current node has a left
			if (currentNode->getLeft())
				//set the current node to be the current nodes left
				currentNode = currentNode->getLeft();
		}

		//if the value is greater than the current node
		else if (value > currentNode->getData())
		{
			//if the current node has a right
			if (currentNode->getRight())
				//set the current node to be the current nodes right
				currentNode = currentNode->getRight();
		}

		//if the value has been found
		else if (value == currentNode->getData())
			//return the found node
			return currentNode;
	}
	//return the current node
	return currentNode;
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* selected)
{
	//draw the node to the screen
	draw(m_root, 400, 40, 400, selected);
}

template<typename T>
inline bool BinaryTree<T>::findNode(T searchValue, TreeNode<T>*& nodeFound, TreeNode<T>*& nodeParent)
{
	//a current node to iterate through the tree
	TreeNode<T>* currentNode = m_root;
	bool found = false;

	//while the current node isn't null
	while(currentNode)
	{
		//if the search value is less then the current data
		if (searchValue < currentNode->getData())
		{
			//if the current node has a left
			if (currentNode->getLeft())
			{
				//set the node parent to be the current node
				nodeParent = currentNode;
				//set the current node to be the current nodes left
				currentNode = currentNode->getLeft();
			}
			//if it doesn't have a left
			else
				return false;
		}

		//if the search value is greater than the current node
		else if (searchValue > currentNode->getData())
		{
			//if the current node has a right
			if (currentNode->getRight())
			{
				//set the node parent to be the current node
				nodeParent = currentNode;
				//set the current node to be the current nodes right
				currentNode = currentNode->getRight();
			}
			//if the current node does not have a right
			else
				return false;
		}

		//if the search value has been found
		else if (searchValue == currentNode->getData())
		{
			//set the node found to the current node and return
			nodeFound = currentNode;
			found = true;
			return found;
		}
	}
	return found;
}

template<typename T>
inline void BinaryTree<T>::draw(TreeNode<T>* currentNode, int x, int y, int horizontalSpacing, TreeNode<T>* selected)
{
	//Decrease the horizontl space as the nodes draw
	horizontalSpacing /= 2;

	//Check if the current node is null
	if (currentNode)
	{
		//Draws left child if this node has one
		if (currentNode->hasLeft())
		{
			//Draws a line child if this node has one
			DrawLine(x, y, x - horizontalSpacing, y + 80, BLACK);
			//Draws the left child
			draw(currentNode->getLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		//Draws the right child if this node has one
		if (currentNode->hasRight())
		{
			//Draws a line between this child and the current node
			DrawLine(x, y, x + horizontalSpacing, y + 80, BLACK);
			//Draws the right child
			draw(currentNode->getRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}
		//Draws the current node
		currentNode->draw(x, y, (selected == currentNode));
	}
}
