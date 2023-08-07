#include "FileHandler.h"
#include <fstream>
#include <iostream>
using namespace std;

FileHandler::FileHandler()
{

}

FileHandler::~FileHandler() {

}


bool FileHandler::loadLevelFromFile(Level &lRef, int levelNumber) {
    string level, str, filename;

    level = levelNumber + '0';
    filename = "Level" + level;
    filename += ".txt";

    ifstream in(filename); //open existing file

    if (!in) return false; //check if file actual exists return otherwise

    int line = 1;
    while (getline(in, str))
    {
        if (line == 2) {
            lRef.levelName = str;
        }
        if (line > 2) {
            // load the line as a Block
            const char ch = str.at(0);
            // skip comment lines
            if (ch == '/') {
                continue;
            }
            const int blockInt = ch - '0'; // this produces the ASCII value of the int we want
            const BLOCK t = static_cast<BLOCK>(blockInt);
            Block newBlock(t);
            lRef.data.push_back(t);
        }

        ++line;

        if (in.eof()) break; //check if end of file is reached
    }

    in.close(); //close file

    return true;

}


bool FileHandler::saveLevelToDisk(std::vector<BlockButton>& blocks, int cols, int levelNumber) {
    string level, filename;
    SYSTEMTIME st;

    // build timestamp
    GetSystemTime(&st);
    std::string timeStamp = std::to_string(st.wYear);
    timeStamp += "." + std::to_string(st.wMonth) + "." + std::to_string(st.wDay);
    timeStamp += "-" + std::to_string(st.wHour) + ":" + std::to_string(st.wMinute) + ":" + std::to_string(st.wSecond);

    // write to the selected file on disk
    level = levelNumber + '0';
    filename = "Level" + level;
    filename += ".txt";

    ofstream out(filename); //open existing file
    if (out.is_open()) {
        //
        out << timeStamp;
        out << "\n";
        out << "EDITOR SAVE\n";

        for (int i = 0; i < blocks.size(); i++) {
            out << blocks.at(i).getBlockType() << "\n";
            // 0-8 row 1
            // 9-17 row 2
            // 18-26 row 3
            if (i == cols - 1 || i == cols * 2 - 1) {
                out << "// new row " << i << "\n";
            }
        }
    }

    out.close();

    return true;
}