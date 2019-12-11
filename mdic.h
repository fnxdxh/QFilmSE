#ifndef MDIC_H
#define MDIC_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <assert.h>

class MDic
{
private:
    std::unordered_map<std::string, int> m_dic;
    
public:
    MDic(std::string dicpath);
    bool find(std::string entry);
    int size();
    void print();
};

#endif // MDIC_H
