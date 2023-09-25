#include <iostream>
#include <string>

int main()
{
    int n;
    std::cin >> n;
    std::string *word = new std::string[n];
    std::string *def = new std::string[n];
    for (int i = 0 ; i < n ; ++i)
        std::cin >> word[i] >> def[i];
  
    std::string s;
    while (std::cin >> s)
    {
        bool found = false;
        for (int i = 0 ; !found && i < n ; ++i)
        {
            if (word[i] == s)
            {
                found = true;
                std::cout << def[i] << '\n';
            }
        }
        if (!found)
            std::cout << "Not found\n";
    }

    delete[] word;
    delete[] def;
}
