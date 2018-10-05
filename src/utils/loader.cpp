#include "loader.h"

std::string Loader::loadFile(const char* path)
{
    std::string result;
    std::ifstream file(path, std::ios::in);
    if(file.is_open())
    {
        std::string line = "";
        while(getline(file, line))
            result += line + "\n";
        file.close();
    }
    else
    {
        printf("No file in this directory");
    }
    return result;
}

std::vector<std::string> Loader::split(std::string str, std::string del)
{
    std::vector<std::string> v;

    std::string s = str;
    std::string delimiter = del;

    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
      token = s.substr(0, pos);
      v.push_back(token);
      s.erase(0, pos + delimiter.length());
    }
    v.push_back(s);

    return v;
}
