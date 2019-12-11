#ifndef MDOCLIST_H
#define MDOCLIST_H

#include <cstdlib>
#include <iostream>

//文档链表结点
class MDocListNode
{
public:
    int m_docID;
    int m_occurTimes;
    MDocListNode * m_next;

public:
    MDocListNode() :m_docID(0), m_occurTimes(1), m_next(NULL) {}
    MDocListNode(int m_docID, int m_occurTimes) :m_docID(m_docID), m_occurTimes(m_occurTimes), m_next(NULL) {}
};

//文档链表头结点
class MDocListheadNode
{
public:
    int m_maxoccurTimes;
    MDocListNode * m_firstNode;

public:
    MDocListheadNode() :m_maxoccurTimes(0), m_firstNode(NULL) {}
    void insertnewNode(MDocListNode * pNode);//插入新节点
    void outputalldata();//输出文档链表内容
    void addinfo(int docID);//添加信息
    MDocListNode * ifexist(int docID);//查找是否存在结点
};
#endif // MDOCLIST_H
