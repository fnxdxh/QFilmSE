#ifndef MAVLTREE_H
#define MAVLTREE_H

#include <iostream>
#include <cstdlib>
#include "mdoclist.h"

//AVL树节点信息
template<class T>
class MTreeNode
{
public:
    MTreeNode();//默认构造函数
    MTreeNode(T m_data);//构造函数
    T data;//值
    int hgt;//高度
    unsigned int freq;//频率
    int DF;//单词出现在多少文章中
    int occurTimes;//单词总的出现次数
    MDocListheadNode * head;//对应的文档链表头结点
    MTreeNode* lson;//指向左儿子的地址
    MTreeNode* rson;//指向右儿子的地址
};

//AVL树类的属性和方法声明
template<class T>
class MAVLTree
{
private:
    MTreeNode<T>* root;//根节点
    void insertpri(MTreeNode<T>* &node, T x);//插入
    MTreeNode<T>* findpri(MTreeNode<T>* node, T x);//查找
    void insubtree(MTreeNode<T>* node);//中序遍历
    void Deletepri(MTreeNode<T>* &node, T x);//删除
    int height(MTreeNode<T>* node);//求树的高度
    void SingRotateLeft(MTreeNode<T>* &k2);//左左情况下的旋转
    void SingRotateRight(MTreeNode<T>* &k2);//右右情况下的旋转
    void DoubleRotateLR(MTreeNode<T>* &k3);//左右情况下的旋转
    void DoubleRotateRL(MTreeNode<T>* &k3);//右左情况下的旋转
    int Max(int cmpa, int cmpb);//求最大值

public:
    MAVLTree() :root(NULL) {}
    void insert(T x);//插入接口
    MTreeNode<T>* find(T x);//查找接口
    void Delete(T x);//删除接口
    void traversal();//遍历接口

};

//构造函数
template<class T>
MTreeNode<T>::MTreeNode()
{
    lson = NULL;
    rson = NULL;
    freq = 1;
    hgt = 0;
    DF = 0;
    occurTimes = 0;
    head = new MDocListheadNode;
}

template<class T>
MTreeNode<T>::MTreeNode(T m_data)
{
    data = m_data;
    lson = NULL;
    rson = NULL;
    freq = 1;
    hgt = 0;
    DF = 0;
    occurTimes = 0;
    head = new MDocListheadNode;
}

//计算节点的高度
template<class T>
int MAVLTree<T>::height(MTreeNode<T>* node)
{
    if (node != NULL)
        return node->hgt;
    return -1;
}

//求最大值
template<class T>
int MAVLTree<T>::Max(int cmpa, int cmpb)
{
    return cmpa>cmpb ? cmpa : cmpb;
}

//左左情况下的旋转
template<class T>
void MAVLTree<T>::SingRotateLeft(MTreeNode<T>* &k2)
{
    MTreeNode<T>* k1;
    k1 = k2->lson;
    k2->lson = k1->rson;
    k1->rson = k2;

    k2->hgt = Max(height(k2->lson), height(k2->rson)) + 1;
    k1->hgt = Max(height(k1->lson), k2->hgt) + 1;
}

//右右情况下的旋转
template<class T>
void MAVLTree<T>::SingRotateRight(MTreeNode<T>* &k2)
{
    MTreeNode<T>* k1;
    k1 = k2->rson;
    k2->rson = k1->lson;
    k1->lson = k2;

    k2->hgt = Max(height(k2->lson), height(k2->rson)) + 1;
    k1->hgt = Max(height(k1->rson), k2->hgt) + 1;
}

//左右情况的旋转
template<class T>
void MAVLTree<T>::DoubleRotateLR(MTreeNode<T>* &k3)
{
    SingRotateRight(k3->lson);
    SingRotateLeft(k3);
}

//右左情况的旋转
template<class T>
void MAVLTree<T>::DoubleRotateRL(MTreeNode<T>* &k3)
{
    SingRotateLeft(k3->rson);
    SingRotateRight(k3);
}

//插入
template<class T>
void MAVLTree<T>::insertpri(MTreeNode<T>* &node, T x)
{
    if (node == NULL)//如果节点为空,就在此节点处加入x信息
    {
        node = new MTreeNode<T>();
        node->data = x;
        return;
    }
    if (node->data>x)//如果x小于节点的值,就继续在节点的左子树中插入x
    {
        insertpri(node->lson, x);
        if (2 == height(node->lson) - height(node->rson))
            if (x<node->lson->data)
                SingRotateLeft(node);
            else
                DoubleRotateLR(node);
    }
    else if (node->data<x)//如果x大于节点的值,就继续在节点的右子树中插入x
    {
        insertpri(node->rson, x);
        if (2 == height(node->rson) - height(node->lson))//如果高度之差为2的话就失去了平衡,需要旋转
            if (x>node->rson->data)
                SingRotateRight(node);
            else
                DoubleRotateRL(node);
    }
    else ++(node->freq);//如果相等,就把频率加1
    node->hgt = Max(height(node->lson), height(node->rson));
}

//插入接口
template<class T>
void MAVLTree<T>::insert(T x)
{
    insertpri(root, x);
}

//查找
template<class T>
MTreeNode<T>* MAVLTree<T>::findpri(MTreeNode<T>* node, T x)
{
    if (node == NULL)//如果节点为空说明没找到,返回NULL
    {
        return NULL;
    }
    if (node->data>x)//如果x小于节点的值,就继续在节点的左子树中查找x
    {
        return findpri(node->lson, x);
    }
    else if (node->data<x)//如果x大于节点的值,就继续在节点的左子树中查找x
    {
        return findpri(node->rson, x);
    }
    else return node;//如果相等,就找到了此节点
}

//查找接口
template<class T>
MTreeNode<T>* MAVLTree<T>::find(T x)
{
    return findpri(root, x);
}

//删除
template<class T>
void MAVLTree<T>::Deletepri(MTreeNode<T>* &node, T x)
{
    if (node == NULL) return;//没有找到值是x的节点
    if (x < node->data)
    {
        Deletepri(node->lson, x);//如果x小于节点的值,就继续在节点的左子树中删除x
        if (2 == height(node->rson) - height(node->lson))
            if (node->rson->lson != NULL && (height(node->rson->lson)>height(node->rson->rson)))
                DoubleRotateRL(node);
            else
                SingRotateRight(node);
    }

    else if (x > node->data)
    {
        Deletepri(node->rson, x);//如果x大于节点的值,就继续在节点的右子树中删除x
        if (2 == height(node->lson) - height(node->rson))
            if (node->lson->rson != NULL && (height(node->lson->rson)>height(node->lson->lson)))
                DoubleRotateLR(node);
            else
                SingRotateLeft(node);
    }

    else//如果相等,此节点就是要删除的节点
    {
        if (node->lson&&node->rson)//此节点有两个儿子
        {
            MTreeNode<T>* temp = node->rson;//temp指向节点的右儿子
            while (temp->lson != NULL) temp = temp->lson;//找到右子树中值最小的节点
                                                         //把右子树中最小节点的值赋值给本节点
            node->data = temp->data;
            node->freq = temp->freq;
            Deletepri(node->rson, temp->data);//删除右子树中最小值的节点
            if (2 == height(node->lson) - height(node->rson))
            {
                if (node->lson->rson != NULL && (height(node->lson->rson)>height(node->lson->lson)))
                    DoubleRotateLR(node);
                else
                    SingRotateLeft(node);
            }
        }
        else//此节点有1个或0个儿子
        {
            MTreeNode<T>* temp = node;
            if (node->lson == NULL)//有右儿子或者没有儿子
                node = node->rson;
            else if (node->rson == NULL)//有左儿子
                node = node->lson;
            delete(temp);
            temp = NULL;
        }
    }
    if (node == NULL) return;
    node->hgt = Max(height(node->lson), height(node->rson)) + 1;
    return;
}

//删除接口
template<class T>
void MAVLTree<T>::Delete(T x)
{
    Deletepri(root, x);
}

//中序遍历函数
template<class T>
void MAVLTree<T>::insubtree(MTreeNode<T>* node)
{
    if (node == NULL) return;
    insubtree(node->lson);//先遍历左子树
    std::cout << node->data.toSTLstring();
    node->head->outputalldata();
    insubtree(node->rson);//再遍历右子树
}

//中序遍历接口
template<class T>
void MAVLTree<T>::traversal()
{
    insubtree(root);
}

#endif // MAVLTREE_H
