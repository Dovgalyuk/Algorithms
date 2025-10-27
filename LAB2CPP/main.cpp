#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include "stack.h"


using namespace std;

void process(string& l)  {

    for (char& ch : l)
    {
        if (!isspace(ch))
        {
            ch = static_cast<unsigned char> (std::tolower(ch));
        }
            
    }
}


int main(int argc, char* argv[])  
{
    setlocale(LC_CTYPE, "ru");
    string line;
    Stack<string>s_1;

    if (argc < 2)  
    {
        cerr << "Error: File not specified" << endl;
        return 1;
    }

    ifstream reader(argv[1]);  
    if (!reader.is_open())
    {
        cerr << "Error: Cannot open file: " << argv[1] << endl;  
        return 1;  
    }

    try
    {
        while (getline(reader, line))
        {
            
             process(line);
           
            
            for (size_t i = 0; i < line.length(); i++)
            {
                if (line[i] == '<')
                {
                    bool isClosing = false;
                    i++;
                    
                    if (line[i] == '/')
                    {
                        isClosing = true;
                        i++;
                        
                    }
                    size_t start = i;
                    size_t end = line.find('>', i);
                    if (end == string::npos) break;
                    string name_tag=line.substr(start,end-start);

                    if (isClosing)
                    {
                        
                        if (!s_1.empty() && s_1.get() == name_tag)
                        {

                            s_1.pop();

                        }
                        else
                        {
                            cout << "NO" << endl;
                            return 1;
                        }
                    }
                    else
                    {
                        s_1.push(name_tag);
                    }
                }
                
            }

           
           
        }
        if (s_1.empty())
        {
            cout << "YES" << endl;
        }
        else
        {
            cout << "NO" << endl;
        }

    }
    catch (const exception& e) 
    {
        cerr << "Error: " << e.what() << endl;  
        reader.close();
        return 1;
    }

    reader.close();
    return 0;  
}
