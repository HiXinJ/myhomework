---
layout: default
title: 二叉树的遍历
---


# 二叉树的遍历
二叉树的遍历是一种很重要的操作。与二叉树相关的许多算法是建立在二叉树遍历的基础上的。遍历算法可以分为递归和非递归两种，其中 _先序遍历_、_中序遍历_、 _后续遍历_ 由递归实现较为方便，而 _层序遍历_ 由非递归实现。

## 1、先序遍历
**`遍历过程：`**

 <li>访问根节点
 <li>访问左子树
 <li>访问右子树  

![](https://github.com/HiXinJ/myhomework/blob/gh-pages/images/TreeTraversal.png?raw=true)    

遍历次序：**7** ( **8** 5 1 2 ) ( **4** 0 )  

代码如下：
```c++
void preorder(Tree T)
{
    if (T){   
        visit(T);           //访问根节点
        preorder(T->left);  //访问左子树
        preorder(T->right); //访问右子树
    }
}
```
***

## 2、中序遍历
**`遍历过程：`**
<ol>
    <li>访问左子树
    <li>访问节根点
    <li>访问右子树
</ol>

![](https://github.com/HiXinJ/myhomework/blob/gh-pages/images/TreeTraversal.png?raw=true)  
遍历次序：( 5 **8** 1 2 ) **7** ( **4** 0 )   

代码如下：
```c++
void inorder(Tree T)
{
    if (T){
        inorder(T->left);   //访问左子树
        visit(T);           //访问根节点
        inorder(T->right);  //访问右子树
    }
}
```
***

## 3、后序遍历
**`遍历过程`**
<ol>
    <li>访问左子树
    <li>访问右子树
    <li>访问节根点
</ol>

![](https://github.com/HiXinJ/myhomework/blob/gh-pages/images/TreeTraversal.png?raw=true)  
遍历次序：( 5 2 1 **8** ) ( 0 **4** ) **7**  

代码如下：
```c++
void postorder(Tree T)
{
    if (T){
        postorder(T->left);     //访问左子树
        postorder(T->right);    //访问右子树
        visit(T);               //访问根节点
    }
}
```



***

## 4、层序遍历
层序遍历和宽度优先搜索类似，遍历过程从左到右，从上到下。    

实现方法：使用队列，首先根节点入队，然后循环：  
1. 节点出队  
1. 访问该节点    
1. 左儿子入队  
1. 右儿子入队  

例如上图的遍历次序：7 8 4 5 1 0 2  

代码如下：
```c++
void BFS(Tree T)
{
    if (!T)
        return;
    std::queue<Tree> Q;
    Q.push(T);
    Tree tmp;
    while (!Q.empty()){
        tmp = Q.front();
        Q.pop();
        visit(tmp);
        if (tmp->left)
            Q.push(tmp->left);
        if (tmp->right)
            Q.push(tmp->right);
    }
}
```