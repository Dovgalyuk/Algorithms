#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>


#include "../LibraryCPPTemplate/stack.h"
using namespace std;

string process(const string& l)  {
    string result = l;
    for (char& ch : result)
    {
        if (!isspace(ch))
        {
            ch = static_cast<unsigned char>(std::tolower(ch));
        }
            
    }
    return result;
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
            
            string r = process(line);
           
            
            for (size_t i = 0; i < r.length(); i++)
            {
                if (r[i] == '<')
                {
                    bool isClosing = false;
                    i++;
                    
                    
                    if (r[i] == '/')
                    {
                        isClosing = true;
                        i++;
                        
                    }
                    string name_tag;
                    while (i < r.length() && r[i] != '>')
                    {
                        name_tag += r[i];   
                        i++;
                        

                    }
                    if (isClosing)
                    {
                        
                        if (!s_1.empty() && s_1.get() == name_tag)
                        {

                            s_1.pop();
                           
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
