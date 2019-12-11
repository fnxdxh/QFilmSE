#ifndef MENGINE_H
#define MENGINE_H

#include "mAVLTree.h"
#include "mdoclist.h"
#include "mcharstring.h"

class MEngine
{
private:
    MAVLTree<MCharString> *m_tree;


public:
    MEngine(MAVLTree<MCharString> *tree);
};

#endif // MENGINE_H
