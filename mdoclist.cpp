#include "mdocList.h"

//插入结点
void MDocListheadNode::insertnewNode(MDocListNode * pNode)
{
    if (m_firstNode == NULL)
    {
        m_maxoccurTimes = pNode->m_occurTimes;
        m_firstNode = pNode;
    }
    else
    {
        MDocListNode * p = m_firstNode;
        while (p->m_next != NULL)
        {
            p = p->m_next;
        }
        p->m_next = pNode;
    }
}

//输出内容
void MDocListheadNode::outputalldata()
{
    MDocListNode * p = m_firstNode;
    while (p != NULL)
    {
        //输出内容
        std::cout << '(' << p->m_docID << ',' << p->m_occurTimes << ')';
        p = p->m_next;
    }
    std::cout << std::endl;
}

//添加内容
void MDocListheadNode::addinfo(int m_docID)
{
    MDocListNode * p = ifexist(m_docID);
    if (p == NULL)
    {
        MDocListNode * pNode = new MDocListNode(m_docID, 1);
        insertnewNode(pNode);
    }
    else
    {
        p->m_occurTimes++;
    }
}

//判断存在与否
MDocListNode * MDocListheadNode::ifexist(int m_docID)
{
    MDocListNode * p = m_firstNode;
    while (p != NULL)
    {
        if (p->m_docID == m_docID)
        {
            return p;
        }
        p = p->m_next;
    }
    return NULL;
}
