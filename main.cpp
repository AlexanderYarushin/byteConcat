#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

void addToStorage(const char* fileName);
void sizeCalc(const char* fileName,unsigned &sizeAllFiles);



int main(int argc, char** argv)
{
    unsigned sizeAllFiles = 0;

    for(int i = 1; i < argc; ++i){
        char* fileName = argv[i];
        sizeCalc(fileName, sizeAllFiles);
        //addToStorage(fileName);

    }

    cout << "Full size: " << sizeAllFiles << " byte" << endl;
    return 0;
}

std::ifstream::pos_type fileSize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

void sizeCalc(const char* fileName, unsigned &sizeAllFiles){
    ifstream input(fileName, std::ios::in | std::ios::binary);

    if (!input.is_open()) {
        cout << "Failed to open file: " << fileName  << endl;
        return;
    }

    cout << "File size: " << fileSize(fileName) << " byte" << endl;
    sizeAllFiles += fileSize(fileName);

}

void addToStorage(const char* fileName){
    ifstream input(fileName, std::ios::in | std::ios::binary);
    if (!input.is_open()) {
        cout << "Failed to open file: " << fileName << endl;
        return;
    }
}
