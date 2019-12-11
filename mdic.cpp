#include "mdic.h"

MDic::MDic(std::string dicpath)
{
    std::ifstream fin;
    fin.open(dicpath);
    assert(fin.is_open());

    std::string entry;
    int i = 0;
    while (1) {
        if (fin >> entry) {
            m_dic[entry] = i;
        }
        else {
            break;
        }
    }
}

bool MDic::find(std::string entry)
{
    return m_dic.count(entry);
}

int MDic::size()
{
    return static_cast<int>(m_dic.size());
}

void MDic::print()
{
    std::unordered_map<std::string, int>::iterator it;
    it = m_dic.begin();
    while (it != m_dic.end()) {
        std::cout << it->first << std::endl;
        it++;
    }
}
