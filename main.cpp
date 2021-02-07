#include <fstream>
#include <iostream>

using namespace std;

static const char* outputFile = "output.concat";
static const char* separate = ";";
static string stringBuffer;

void writeOutput(const char* fileName, unsigned size);
unsigned fileSize(const char* filename);
void checkFile(const char* fileName);
void split(const char* fileName);

int main(int argc, char** argv)
{
    //    for(int i = 1; i < argc; ++i){
    //        char* fileName = argv[i];
    //        unsigned  size = fileSize(fileName);
    //        cout << size << endl;
    //        writeOutput(fileName, size);
    //    }

    char* fileName = argv[1];
    split(fileName);

    return 0;
}

void split(const char* fileName)
{
    checkFile(fileName);

    ifstream input(fileName, std::ios::in | std::ios::binary);

    char buffer;
    while (!input.eof()) {
        input.read(&buffer, sizeof(char));
        stringBuffer += buffer;
    }

    uint8_t mode = 0;

    string resFileName;
    string resContent;
    size_t prevIndex = 0;
    int resSize;

    for (size_t i = 0; i < stringBuffer.length(); ++i) {
        if (stringBuffer[i] == ';') {
            string temp = stringBuffer.substr(prevIndex, i - prevIndex);
            prevIndex = i;

            switch (mode) {
            case 0:
                resFileName = temp;
                prevIndex++;
                break;

            case 1:
                cout << temp << endl;
                // resSize = stoi(temp);
                //i += resSize;
                prevIndex++;
                break;

            case 2:
                resContent = temp;
                break;
            }

            mode++;
            if (mode > 2) {
                ofstream output(resFileName.c_str(), std::ios::out | std::ios::binary);

                output.write(resContent.c_str(), resContent.length());
                mode = 0;
            }
        }
    }
}

void checkFile(const char* fileName)
{
    std::fstream file(fileName);
    if (!file.is_open()) {
        cout << "Failed to open file: " << fileName << endl;
        exit(1);
    }
}

unsigned fileSize(const char* filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

const char* intToCharP(unsigned x)
{
    std::string* s = new string;
    *s = std::to_string(x);
    return s->c_str();
}

void writeOutput(const char* fileName, unsigned size)
{

    checkFile(fileName);

    ifstream input(fileName, std::ios::in | std::ios::binary);
    static ofstream output(outputFile, std::ios::out | std::ios::binary);

    size_t inputNameLength = strlen(fileName);

    output.write(fileName, inputNameLength);
    output.write(separate, sizeof(char));
    output.write(intToCharP(size), strlen(intToCharP(size)));
    output.write(separate, sizeof(char));

    char buffer;
    while (!input.eof()) {
        input.read(&buffer, sizeof(char));
        output.write(&buffer, sizeof(char));
    }

    for (int i = 0; i < 100; ++i) {
        output.write("X", sizeof(char));
    }
}
