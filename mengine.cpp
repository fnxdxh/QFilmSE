#include "mengine.h"

MEngine::MEngine(MAVLTree<MCharString> *tree)
{
    m_tree = tree;
    memset(m_totalOccurTimes, 0, sizeof(m_totalOccurTimes));
    memset(m_keywordOccurTimes, 0, sizeof(m_keywordOccurTimes));
}

void MEngine::search(MCharString *stringlist, int length)
{
    memset(m_totalOccurTimes, 0, sizeof(m_totalOccurTimes));
    memset(m_keywordOccurTimes, 0, sizeof(m_keywordOccurTimes));
    for (int i = 0; i < length; i++) {
        MTreeNode<MCharString> *treenode = m_tree->find(stringlist[i]);
        MDocListNode *doclistnode = treenode->head->m_firstNode;
        while (doclistnode) {
            //计算关键词出现总此处
            m_totalOccurTimes[doclistnode->m_docID] += doclistnode->m_occurTimes;
            //计算关键词出现个数
            m_keywordOccurTimes[doclistnode->m_docID]++;
            doclistnode = doclistnode->m_next;
        }
    }

    //输出搜索结果
    std::ofstream fout;
    fout.open("result1.txt", std::ios::app);
    int maxTotalOccurTimes = 0;
    int maxKeywordOccurTimes = 0;
    for (int i = 0; i < NUM_OF_FILES; i++) {
        if (m_totalOccurTimes[i] > maxTotalOccurTimes) {
            maxTotalOccurTimes = m_totalOccurTimes[i];
        }
        if (m_keywordOccurTimes[i] > maxKeywordOccurTimes) {
            maxKeywordOccurTimes = m_keywordOccurTimes[i];
        }
    }

    while (maxKeywordOccurTimes > 0) {
        int tmp = maxTotalOccurTimes;
        while(tmp > 0) {
            for (int i = 0; i < NUM_OF_FILES; i++) {
                if (m_totalOccurTimes[i] == tmp
                        && m_keywordOccurTimes[i] == maxKeywordOccurTimes) {
                    fout << "(" << i << "," << m_totalOccurTimes[i] << ") ";
                }
            }
            tmp--;
        }
        maxKeywordOccurTimes--;
    }
    fout << std::endl;
    fout.close();
}

void MEngine::engineSearch()
{
    //打开文件
    std::ifstream fin;
    std::ofstream fout;
    fout.open("result1.txt");
    fout.close();
    char buffer[256];
    fin.open("query1.txt");
    assert(fin.is_open());
    while (!fin.eof()) {
        fin.getline(buffer, 256, '\n');
        MCharString charbuffer(buffer);
        int num;
        MCharString *result = charbuffer.split(' ', num);
        this->search(result, num);
    }
    fin.close();
}
