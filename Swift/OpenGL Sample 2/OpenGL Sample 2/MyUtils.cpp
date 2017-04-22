//
//  MyUtils.cpp
//  OpenGL Sample 2
//
//  Created by Jeffrey Ryan on 4/9/15.
//  Copyright (c) 2015 Fish in Space. All rights reserved.
//

#include "MyUtils.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

string getFileAsString(const char* fileName) {
    std::ifstream in(fileName, std::ios::in | std::ios::binary);
    
    if (in) {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

string getFileAsString(string fileName) {
    return getFileAsString(fileName.c_str());
}