#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>


// Изограмма
/*bool is_isogramm(std::string str) {
    size_t len = str.length();
    for (size_t i = 0; i < len; ++i) {
        str[i] = std::tolower(str[i]);
    }

    std::sort(str.begin(), str.end());


    for (size_t i = 0; i < len; ++i) {
        if (std::isalpha(str[i]) && std::isalpha(str[i + 1]) && str[i] == str[i + 1]) {
            return false;
        }
    }

    return true;
}
*/
// Диалог с Бобом
/*void Bob(std::string request) {

    bool is_empty = true;
    for (size_t i = 0; i < request.length(); ++i) {
        if (!std::isspace(request[i])) {
            is_empty = false;
        }
    }
    if (is_empty) {
        std::cout << "Fine. Be that way" << std::endl;
        return;
    }

    bool is_upper = true;

    for (size_t i = 0; i < request.length(); ++i) {
        if (std::isalpha(request[i]) && !std::isupper(request[i])) {
            is_upper = false;
            break;
        }
    }

    if (is_upper) {
        if (request[request.length() - 1] == '?') {
            std::cout << "Calm down, I know what im doing!";
        } else {
            std::cout << "Whoa, chill out!";
        }
        return;
    }

    if (request[request.length() - 1] == '?') {
        std::cout << "Sure.";
        return;
    }

    std::cout << "Whatever" << std::endl;
}
*/
// Шифровальный квадрат
/*std::string Shifr(std::string str) {
    std::string new_str = "";
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '?' || str[i] == '.') {
            continue;
        }
        new_str += std::tolower(str[i]);
    }

    int new_len = new_str.length();

    int r, c;

    r = sqrt(new_len); //строки
    c = r + 1; //столбцы, c - r <=1
    if (new_len - r > pow(r, 2)) {
        ++r;
    }
    if (new_len == pow(r, 2)) {
        --c;
    }

    for (int j = 0; j < r; ++j) {
        for (int i = j * c; i < j * c + c; ++i) {
            if (i >= new_str.length()) {
                std::cout << " ";
            } else {
                std::cout << new_str[i];
            }
        }
        std::cout << std::endl;
    }
    std::string last_str = "";
    for (int j = 0; j <= r; ++j) {
        for (int i = j; i < new_str.length(); i += c) {
            last_str += new_str[i];
        }
        last_str += " ";
    }
    return last_str;
}

*/

#include <array>
#include <vector>

/*typedef std::array<int,5> MyArr;

void f(MyArr& a) {
    a[4] = 0;
}

int sum(MyArr a) {
    int r = 0;
    for (int i = 0; i < a.size(); ++i) {
        r += a[i];
    }
    return r;
}
*/


//#include <vector>
//#include <list>
#include <numeric>
#include <map>

/*int sum(MyArr a) {
    return std::accumulate(a.begin(), a.end() - a.size() / 2, 0);
}

int mult(MyArr a) {
    if (a.size() == 0) return 0;
    return std::accumulate(a.begin(), a.end(), 1, [](int c, int b) {
        return c * b;
    });
}
*/
// Сортировка пузырьком
/*std::vector<int> BubbleSort(std::vector<int> a){
    for(int i = 0; i < a.size() - 1; ++i){
        for(int j = 0; j < a.size() - i - 1; ++j){
            if(a[j] > a[j + 1]){
                std::swap(a[j], a[j+1]);

            }
        }
    }
    return a;
}
*/

#include <vector>
#include <list>
#include <map>
//ДЛЯ СЕБЯ
int main() {
    /*int a = 5;//просто создали переменную, поместили в ячейку памяти(в стэк),
    // у данной ячейки памяти есть ссылка(это тоже указатель, тольк константный)
    // значение данной ссылки - адрес памяти, напр. F4A34B, т. е. &a = F4A34B

    int* p; //создали указатель, который будет указывать на интовые ячейки памяти,
    //указатель тоже помещается в какую то ячейку памяти
    //данная ячейка памяти имеет тоже какой то адрес, например  А5A3СB
    //значение указателя - это адрес какой то ячейки памяти, в данном случае он ни на что не указывает
    //&p = A5A3CB
    //p = мусор

    p = &a; //привязали наш указатель к ячейки памяти a (то есть к ее константной ссылке, означающей адрес в памяти)
    //&p = A5A3CB
    //p = F4A34B

    *p = 10; //поменяли значение ячейки памяти переменной a с помощью разыменования указателя
    //теперь а = 10

    int* some = p; //создали новый указатель
    //&some = какая то новая ячейка памяти
    //some = F4A34B - указывает на всю ту же переменную a*/








    /////////////////
    //std::cout << is_isogramm("helo") << std::endl;

    /////////////////////
    /*std::string req;
    std::getline(std::cin, req);
    Bob(req);*/

    /////////////////////////////
    /*std::string str = "If man aaaaaaaafffwas meant to stay on the ground, god would have given us roots.";

    str = Shifr(str);

    std::cout << str;*/

    ///////////////////
    /*MyArr a = {1,2,3,4,5};
    std::cout << "Sum1: " << mult(a) << std::endl;*/
    /*f(a);
    std::cout << "Sum2: " << sum(a) << std::endl;*/

    ////////////////////
    /*int n;
    std::cin >> n;
    int* a = new int[n];
    for(int i = 0; i < n; ++i){
        std::cin >> a[i];
    }
    int k;
    std::cin >> k;
    int m = 0;
    for(int i = 0; i < n; ++i) {
        if(a[i] < k){
            ++m;
        }
    }

    int* b = new int[m];
    m = 0;
    for (int i = 0; i < n; ++i) {
        if(a[i] < k){
            b[m++] = a[i];
        }
    }
    delete[] a;
    for(int i = 0; i < m; ++i){
        std::cout << b[i] << " ";
    }
    delete[] b;*/
//////////////////////////////////////
    /*int n;
    std::cin >> n;
    std::vector<int> a(n);
    for(int i = 0; i < a.size(); ++i){
        std::cin >> a[i];
    }
    int k;
    std::cin >> k;
    std::vector<int> b;
    for(int i = 0; i < a.size(); ++i) {
        if(a[i] < k){
            b.push_back(a[i]);
        }
    }

    for(int i = 0; i < b.size(); ++i){
        std::cout << b[i] << " ";
    }*/




    ////////////////////////////////
   /* int n;
    std::cin >> n;
    int* a = new int[n];
    for(int i = 0; i < n; ++i){
        int v;
        std::cin >> v;
        for(int j = i; j > 0; --j){
            a[j] = a[j-1];
        }
        a[0] = v;
    }

    for(int i = 0; i < n; ++i){
        std::cout << a[i] << " ";
    }
    std::cout << '\n';
    delete[] a;*/

    /* int n;
     std::cin >> n;
     std::list<int> a;
     for(int i = 0; i < n; ++i){
         int v;
         std::cin >> v;
         a.insert(a.begin(), v);
     }

     for(auto i = a.begin(); i != a.end(); ++i){
         std::cout << *i << " ";
     }

     std::cout << '\n';*/

    //////////////////////////////////////////////////

    std::vector <int> vec = {31,12,15,1,67, 102, 11, 17, 73};
    //vec = BubbleSort(vec);
    std::sort(vec.begin(), vec.end(), [](int a, int b) {
        return a < b;
    });

    for(int i = 0; i < vec.size(); ++i){
        std::cout << vec[i] << " ";
    }

    int size;
    std::cin>>size;
    std::vector<int> search_vec(size);
    for(int i = 0; i < size; ++i){
        std::cin >> search_vec[i];
    }

    int BinarySearch(std::vector<int> &vec, int left, int right, int item, ){
        if(left>right){
            return -1;
        }
        int middle = (left + right) / 2;
        if (item == vec[middle]){
            return middle;
        }
        if (item > vec[middle]){
            return BinarySearch(vec,midle + 1, right, item)
        }else{
            return BinarySearch(vec,left, middle - 1, item)
        }
    }


    for(auto s : search_vec){
        if(std::binary_search(vec.begin(), vec.end(), s)){
            std::cout << "Found " << s << std::endl;
        }
    }

*/
//////////////////////////////////////////////////

    /*int n;
    std::cin>>n;
    std::string* word = new std::string[n];
    std::string* def = new std::string[n];

    for(int i = 0; i < n; ++i){
        std::cin >> word[i] >>def[i];
    }

    std::string s;
    while(std::cin >> s){
        bool found = false;
        for(int i = 0; !found && i < n; ++i){
            if(word[i] == s){
                found = true;
                std::cout << def[i] << "\n";
            }
        }
        if (!found){
            std::cout << "Not found";
        }
    }
    delete[] word;
    delete[] def;*/


    std::map<std::string , std::string> mapik;
    int n;
    std::cin>>n;

    for(int i = 0; i < n; ++i){
        std::string key;
        std::string value;
        std::cin >> key >> value;
        std::pair<std::string,std::string> p = std::make_pair(key,value);
        mapik.insert(p);
    }

    std::string s;


    while(std::cin >> s){
        std::map<std::string,std::string>::iterator it = mapik.find(s);
        if(it != mapik.end()){
            std::cout << it->second;
        }
        else{
            std::cout << "Not found";
        }
    }









}
