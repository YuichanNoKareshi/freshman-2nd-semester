#include "Tree.h"
#include <iostream>
using namespace std;

void BinaryDimonTree::insert(int x, int y)
{
  if (root == NULL)
  {
    root = new TreeNode(x, y);
    return;
  }
  TreeNode *temp = root;

  int deep = 0;
  while (true)
  {
    if (deep % 2 == 0) //黑体是x
    {
      if (x < temp->X)
      {
        if (temp->isLeft())
        {
          temp = temp->left;
          deep++;
          continue;
        }
        else
        {
          temp->left = new TreeNode(x, y);
          break;
        }
      }

      else
      {
        if (temp->isRight())
        {
          temp = temp->right;
          deep++;
          continue;
        }
        else
        {
          temp->right = new TreeNode(x, y);
          break;
        }
      }
    } //该情况结束

    if (deep % 2 == 1) //黑体是y
    {
      if (y < temp->Y)
      {
        if (temp->isLeft())
        {
          temp = temp->left;
          deep++;
          continue;
        }
        else
        {
          temp->left = new TreeNode(x, y);
          break;
        }
      }

      else
      {
        if (temp->isRight())
        {
          temp = temp->right;
          deep++;
          continue;
        }
        else
        {
          temp->right = new TreeNode(x, y);
          break;
        }
      }
    } //该情况结束
  }
}

TreeNode *BinaryDimonTree::find_nearest_node(int x, int y)
{
  /*
  float distance = sqrt((root->X - x) * (root->X - x) + (root->Y - y) * (root->Y - y));
  float d = 0;
  TreeNode *result = root;
  Stack s;
  TreeNode *current = root;
  current->times = 0;
  s.push(current);

  while (!s.isEmpty())
  {
    current = s.pop();
    if (++current->times == 2)
    {
      if (current->isRight())
      {
        current->right->times = 0;
        s.push(current->right);
      }
      d = sqrt((current->X - x) * (current->X - x) + (current->Y - y) * (current->Y - y));
      if (d < distance)
      {
        distance = d;
        result = current;
      }
    }

    else
    {
      s.push(current);
      if (current->isLeft())
      {
        current->left->times = 0;
        s.push(current->left);
      }
    }
  }

  return result;
  */

  TreeNode *t=search(x, y, root, sqrt((root->X - x) * (root->X - x) + (root->Y - y) * (root->Y - y)));
  return t;
}

void BinaryDimonTree::clear(TreeNode *&t)
{
  if (t == NULL)
    return;
  if (t->isLeft())
    clear(t->left);
  if (t->isRight())
    clear(t->right);
  delete t;
  t = NULL;
}

BinaryDimonTree::~BinaryDimonTree()
{
  clear(root);
}

TreeNode *BinaryDimonTree::search(int x, int y, TreeNode *m, float d)
{
  float distance = d;
  TreeNode *current = m;
  TreeNode *guess = m;
  if (current == NULL)
  {
    s.pop();
    return guess;
  }
  if (sqrt((current->X - x) * (current->X - x) + (current->Y - y) * (current->Y - y)) < distance)
  {
    distance = sqrt((current->X - x) * (current->X - x) + (current->Y - y) * (current->Y - y));
    guess = current;
  }
  if (current->times % 2 == 0)
  {
    if (x < current->X)
    {
      s.push(current->right);
      search(x, y, current->left, distance);
    }
    else
    {
      s.push(current->left);
      search(x, y, current->right, distance);
    }
  }
  if (abs(current->X - x) < distance)
    search(x, y, s.pop(), distance);
  if (current->times % 2 == 1)
  {
    if (y < current->Y)
    {
      s.push(current->right);
      search(x, y, current->left, distance);
    }
    else
    {
      s.push(current->left);
      search(x, y, current->right, distance);
    }
  }
}