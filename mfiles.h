#ifndef FILES_H
#define FILES_H

#include <string>
#include <vector>
#include <io.h>
#include <iostream>
#include <assert.h>

class MFiles
{
private:
    std::vector<std::string> m_files;
    std::vector<std::string> m_filenames;
    int m_length;

public:
    MFiles(std::string path);
    int length();
    int size();
    std::string at(int index);
    void print();
};

#endif // FILES_H
