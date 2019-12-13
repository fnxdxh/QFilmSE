#ifndef MENGINE_H
#define MENGINE_H

#include <cstring>
#include <fstream>
#include <assert.h>
#include "mAVLTree.h"
#include "mdoclist.h"
#include "mcharstring.h"

#define NUM_OF_FILES 10000

class MEngine
{
private:
    MAVLTree<MCharString> *m_tree;
    int m_totalOccurTimes[NUM_OF_FILES];
    int m_keywordOccurTimes[NUM_OF_FILES];

public:
    MEngine(MAVLTree<MCharString> *tree);
    void search(MCharString* stringlist, int length);
    void engineSearch();
};

#endif // MENGINE_H
