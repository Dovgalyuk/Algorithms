#define MAX_LEN_STRING 12

#include <clocale>
#include <iostream>
#include <fstream>
#include <ctime>
#include <set>
#include <string>

#include "interface.h"
#include "avltree.h"

using namespace std;

//Ôóíêöèÿ âûïîëíåíèÿ
void demoInterface(Interface &container) {
	cout << "ÄÅÌÎÍÑÒÐÀÖÈß ÐÀÁÎÒÛ ÈÍÒÅÐÔÅÉÑÀ:" << endl;
	string s1 = "abcd";
	string s2 = "ef";
	string s3 = "xyz";
	string s4 = "hi";

	//Äîáàâëåíèå ñòðîê
	container.addValue(&s1);
	cout << s1 << " äîáàâëåíà." << endl;
	container.addValue(&s2);
	cout << s2 << " äîáàâëåíà." << endl;
	container.addValue(&s3);
	cout << s3 << " äîáàâëåíà." << endl;

	//Ïîèñê ñòðîêè
	if (container.findValue(&s4) == true)
		cout << s4 << " íàéäåíà." << endl;
	else
		cout << s4 << " íå íàéäåíà â êîíòåéíåðå." << endl;

	if (container.findValue(&s1) == true)
		cout << s1 << " íàéäåíà." << endl;
	else
		cout << s1 << " íå íàéäåíà â êîíòåéíåðå." << endl;


	//Óäàëåíèå ñòðîê
	if (container.deleteValue(&s4) == true)
		cout << s4 << " óäàëåíà." << endl;
	else
		cout << s4 << " íå óäàëåíà, òàê êàê íåò â êîíòåéíåðå." << endl;

	if (container.deleteValue(&s2) == true)
		cout << s2 << " óäàëåíà." << endl;
	else
		cout << s2 << " íå óäàëåíà, òàê êàê íåò â êîíòåéíåðå." << endl;
}

//Ãåíåðàòîð âõîäíûõ äàííûõ ðàçëè÷íîãî îáúåìà äëÿ íàøåãî AVL êîíòåéíåðà è çàïèñü â ôàéë
void generatorData() {
	srand((unsigned int)time(NULL));	//Íà÷àëüíàÿ ãåíåðàöèÿ
	int numString = rand()*5 + 1;				//Êîëè÷åñòâî ñòðîê. Ñëó÷àéíîå îò 1 äî 32768.
	int lenString;						//Äëèíà òåêóùåé ñòðîêè			
	ofstream out("InputData.txt");
	if (out.is_open()) {
		for (int i = 0;i < numString;i++) {
			lenString = rand() % MAX_LEN_STRING;
			for (int j = 0; j < lenString;j++) {
				out.put(rand() % 26 + 97);
			}
			out.put('\n');
		}
	}
	out.close();
}

//×òåíèå äàííûõ â êîíòåéíåð
void readDataInContainer(Interface &container) {
	string*str=new string;
	ifstream in("InputData.txt");
	if (in.is_open())
	{
		clock_t start = clock();
		while (getline(in, str, '\n')) {
			container.addValue(&str);
			str = new string;
		}
		clock_t finish = clock();
		cout << "Âðåìÿ äîáàâëåíèå â ñîçäàííûé êîíòåéíåð ñîäåðæèìîãî ôàéëà: " << (double)(finish - start) / CLOCKS_PER_SEC << endl;
	}
	else {
		cout << "Ôàéë InputData.txt íå íàéäåí èëè íå óäàëîñü îòêðûòü." << endl;
	}
	in.close();
}

//×òåíèå äàííûõ â set
void readDataInSet(set <string> &containerSet) {
	string *str = new string;
	ifstream in("InputData.txt");
	if (in.is_open())
	{
		clock_t start = clock();
		while (getline(in, str, '\n')) {
			containerSet.insert(*str);
			str = new string;
		}
		clock_t finish = clock();
		cout << "Âðåìÿ äîáàâëåíèå â êîíòåéíåð set ñîäåðæèìîãî ôàéëà (ñåê): " << (double)(finish - start) / CLOCKS_PER_SEC << endl;
	}
	else {
		cout << "Ôàéë InputData.txt íå íàéäåí èëè íå óäàëîñü îòêðûòü." << endl;
	}
	in.close();
}
void deleteDataFromContainer(Interface &container) {
	string str;
	ifstream in("InputData.txt");
	int numDelString = 10000;
	cout << "Удаляем " << numDelString << " строк из контейнера." << endl;
	if (in.is_open())
	{
		for (int i = 0; i < numDelString; i++) {		//Удаляем numDelString количество строк
			getline(in, str, '\n');
			container.deleteValue(&str);
		}
	}
	else {
		cout << "Файл InputData.txt не найден или не удалось открыть." << endl;
	}
	cout << "Строки удалены из контейнера." << endl;
	in.close();
}
//ÃËÀÂÍÀß ÔÓÍÊÖÈß
int main() {
	setlocale(LC_ALL, "Russian");

	//1. Äåìîíñòðàöèÿ ðàáîòû èíòåðôåéñà
	AVLTree container;
	demoInterface(container);

	//4. ÃÅÍÅÐÀÒÎÐ ÂÕÎÄÍÛÕ ÄÀÍÍÛÕ ÐÀÇËÈ×ÍÎÃÎ ÎÁÚÅÌÀ ÄËß ÍÀØÅÃÎ AVL ÊÎÍÒÅÉÍÅÐÀ.
	cout << "ÑÐÀÂÍÅÍÈÅ ÑÊÎÐÎÑÒÅÉ ÎÏÅÐÀÖÈÈ ÄÎÁÀÂËÅÍÈß Â ÊÎÍÒÅÉÍÅÐÛ:" << endl;
	//4.1. Ãåíåðèðóåì ñòðîêè è çàïèñûâàåì â ôàéë
	generatorData();

	//4.2. Cêîðîñòü âûïîëíåíèÿ îïåðàöèè äîáàâëåíèÿ â êîíòåéíåð ñîäåðæèìîãî ôàéëà
	AVLTree container2;
	readDataInContainer(container2);

	//4.3. Cêîðîñòü âûïîëíåíèÿ îïåðàöèè äîáàâëåíèÿ â êîíòåéíåð std:set
	set <string> containerSet;
	readDataInSet(containerSet);
        //4.4. Берём часть строк из InputData.txt и удаляем из container2 (уже хранит все строки из InputData.txt)
	deleteDataFromContainer(container2);
	system("pause");
	return 0;
}
