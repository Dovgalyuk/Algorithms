#include <iostream>
#include <fstream>
#include <locale>
#include "queue.h"
using namespace std;

//Ôóíêöèÿ ÷òåíèÿ äàííûõ èç ôàéëà
char** readFile(int &numCol, int &numRow) {
	numCol = 0, numRow = 0;
	int i = 0;
	char **labir = NULL;	//Èíèöèàëèçàöèÿ äâóìåðíîãî ìàññèâà äëÿ ëàáèðèíòà
	string line;			//Ñòðîêà, êîòîðàÿ áóäåò èñïîëüçîâàòüñÿ ïðè ÷òåíèè èç ôàéëà
	ifstream in("input.txt");	//Âõîäíîé ôàéë
	if (in.is_open())	//Åñëè ôàéë óäàëîñü îòêðûòü
	{
		while (getline(in, line)) {	//Ïðîáåãàåì ôàéë äëÿ ïîäñ÷åòà äëèíû ñòðîêè numRow
			numRow++;
		}
		numCol = line.size();	//Äëèíà êîëîíêè
		labir = new char*[numRow];	//Âûäåëÿåì ïàìÿòü äëÿ ëàáèðèíòà

		cout << "Ðàçìåðû ïðÿìîóãîëüíèêà:" << numRow << '*' << numCol << endl;
		cout << "Âõîä:" << endl;
		in.clear();				//Ñáðàñûâàåì in äëÿ ïîâòîðíîãî ÷òåíèÿ ôàéëà
		in.seekg(0, ios::beg);	//
		//Ñ÷èòûâàåì äàííûå èç ôàéëà è çàïèñûâàåì â ìàññèâ labir
		while (getline(in, line)) {
			labir[i] = new char[numCol];
			for (int j = 0; j < line.size(); j++) {
				labir[i][j] = line[j];
				cout << labir[i][j];
			}
			cout << endl;
			i++;
		}
	}
	else {
		cout << "Ôàéë input.txt íå íàéäåí èëè íå óäàëîñü îòêðûòü." << endl;
	}
	in.close();	//Çàêðûâàåì ôàéë
	return labir;	//Âîçâðàùàåì ìàññèâ ñ ëàáèðèíòîì â ãëàâíóþ ôóíêöèþ main
}

//Ôóíêöèÿ íàõîæäåíèÿ êðàò÷àéøåãî ïóòè ñ ïîìîùüþ âîëíîâîãî àëãîðèòìà
void findPath(bool &mark, int numCol, int numRow, char **labir, int **visited, int **path, queue &q) {
	int xStartX, yStartX, xEndY, yEndY;	//Êîîðäèíàòû ñòàðòà è ôèíèøà
	int x, y;	//Êîîðäèíàòû âûáðàííîé êëåòêè
	for (int i = 0; i < numRow; i++) {
		visited[i] = new int[numCol];	//Âûäåëÿåì ïàìÿòü äëÿ ìàññèâà
		path[i] = new int[numCol];		//Âûäåëÿåì ïàìÿòü äëÿ ìàññèâà
		for (int j = 0; j < numCol; j++) {
			visited[i][j] = 0;
			path[i][j] = -1;
			if (labir[i][j] == 'X') { /* íàõîäèì íà÷àëî ïóòè*/
				xStartX = i;
				yStartX = j;
				q.push(i);  /* çàíîñèì íà÷àëüíóþ êëåòêó */
				q.push(j);  /* â ïëàí ïîñåùåíèÿ */
				path[i][j] = 0;
			}
			else if (labir[i][j] == 'Y') { /* íàõîäèì êîíå÷íóþ òî÷êó */
				xEndY = i;
				yEndY = j;
			}
		}
	}

	//Ïîêà î÷åðåäü ïîñåùåíèÿ êëåòîê
	while (q.empty() == false) {	//Ïîêà î÷åðåäü íå ïóñòàÿ, äåëàåì
		x = q.front();	//Áåð¸ì êîîðäèíàòó x ïåðâîãî ýëåìåíòà î÷åðåäè
		q.pop();		//Óäàëÿåì åãî èç î÷åðåäè
		y = q.front();	//Áåð¸ì êîîðäèíàòó y ïåðâîãî ýëåìåíòà î÷åðåäè
		q.pop();		//Óäàëÿåì åãî èç î÷åðåäè

		if (!visited[x][y]) {	//Åñëè åù¸ íå ïîñåòèëè äàííóþ êëåòêó, òî äåëàåì äëÿ åãî ñîñåäíèõ êëåòîê
			//Ïðîâåðÿåì íå âûøëè ëè çà ãðàíèöó ëàáèðèíòà, ïîñåùåíà ëè ñîñåäíÿÿ êëåòêà, ìîæíî ëè ïðîéòè ÷åðåç íåãî.
			if ((x + 1) < numRow && !visited[x + 1][y] &&
				(labir[x + 1][y] == '.' || labir[x + 1][y] == 'Y')) {
				path[x + 1][y] = path[x][y] + 1;
				q.push(x + 1);
				q.push(y);
			}
			if ((x - 1) >= 0 && !visited[x - 1][y] &&
				(labir[x - 1][y] == '.' || labir[x - 1][y] == 'Y')) {
				path[x - 1][y] = path[x][y] + 1;
				q.push(x - 1);
				q.push(y);
			}
			if ((y + 1) < numCol && !visited[x][y + 1] &&
				(labir[x][y + 1] == '.' || labir[x][y + 1] == 'Y')) {
				path[x][y + 1] = path[x][y] + 1;
				q.push(x);
				q.push(y + 1);
			}
			if ((y - 1) < numCol && (y - 1) >= 0 && !visited[x][y - 1] &&
				(labir[x][y - 1] == '.' || labir[x][y - 1] == 'Y')) {
				path[x][y - 1] = path[x][y] + 1;
				q.push(x);
				q.push(y - 1);
			}
			visited[x][y] = 1;	//Îòìå÷àåì ÷òî ïîáûâàëè â äàííîé êëåòêå
		}
     }
		if (visited[xEndY][yEndY]) {	//Åñëè ïîñåòèëè ôèíèøíóþ êëåòêó
			mark = true;
			x = xEndY;	//x áóäåò êîðäèíàòîé õ ôèøèøà Y
			y = yEndY;	//y áóäåò êîðäèíàòîé y ôèøèøà Y
			//Âîññòàíîâëåíèå êðàò÷àéøåãî ïóòè
			while (path[x][y] > 1) {
				if ((x - 1) >= 0 && (x - 1) < numRow && (path[x - 1][y] == path[x][y] - 1)) {
					x = x - 1;
					labir[x][y] = 'x';
				}
				else if ((x + 1) < numRow && (path[x + 1][y] == path[x][y] - 1))  {
					x = x + 1;
					labir[x][y] = 'x';
				}
				else if ((y - 1) >= 0 && (y - 1) < numCol && (path[x][y - 1] == path[x][y] - 1)) {
					y = y - 1;
					labir[x][y] = 'x';
				}
				else if ((y + 1) < numCol && (path[x][y + 1] == path[x][y] - 1)) {
					y = y + 1;
					labir[x][y] = 'x';
				}
			}
		}
}

//Ôóíêöèÿ çàïèñè äàííûõ â ôàéë
void writeFile(bool &mark, int &numCol, int &numRow, char **labir){
	ofstream out("output.txt");	//Âûõîäíîé ôàéë
	if (out.is_open())	//Åñëè ôàéë óäàëîñü îòêðûòü
	{
		cout << endl;
		cout << "Âûõîä:" << endl;
		if (mark == true) {	//Ïóòü ñóùåñòâóåò
			//Çàïèñûâàåì ëàáèðèíò èç ìàññèâà â ôàéë
			for (int i = 0; i < numRow; i++) {
				for (int j = 0; j < numCol; j++) {
					out << labir[i][j];
					cout << labir[i][j];
				}
				out << endl;
				cout << endl;
			}
		}
		else {	//Ïóòü íå ñóùåñòâóåò
			cout << "IMPOSSIBLE" << endl;
			out << "IMPOSSIBLE";
		}
	}
	out.close();
}

//ÃËÀÂÍÀß ÔÓÍÊÖÈß
int main() {
	setlocale(LC_ALL, "Russian");	//Äëÿ âûâîäà ðóññêèõ ñëîâ
	int numCol;	//Ðàçìåð ëàáèðèíòà: äëèíà êîëîíêè
	int numRow;	//Ðàçìåð ëàáèðèíòà: äëèíà ðÿäà(ñòðîêè)
	bool mark = false;	//Åñëè true, òî ïóòü ñóùåñòâóåò
	char **labir;	//Äâóìåðíûé ìàññèâ õðàíÿùèé ëàáèðèíò
	int **visited;	//Äâóìåðíûé ìàññèâ õðàíÿùèé ïîñåùåííûå êëåòêè ëàáèðèíòà
	int **path;		//Äâóìåðíûé ìàññèâ õðàíÿùèé ïóòè â ëàáèðèíòå
	queue q;		//Î÷åðåäü ïîñåùåíèÿ êëåòîê (ïîèñêà ïóòè)

	//Ôóíêöèÿ ÷òåíèÿ äàííûõ èç ôàéëà. Îòòóäà ïîëó÷àåì íàø ëàáèðèíò â ìàññèâ labir
	labir = readFile(numCol, numRow);
	
	visited = new int* [numRow];	//Âûäåëÿåì ïàìÿòü äëÿ ìàññèâîâ. Äåëàåì èõ îäíîìåðíûìè
	path = new int* [numRow];		//

	//Ôóíêöèÿ ïîèñêà êðàò÷àéøåãî ïóòè
	findPath(mark, numCol, numRow, labir, visited, path, q);

	//Ôóíêöèÿ çàïèñè äàííûõ (ïðåîáðàçîâàííîãî ëàáèðèíòà) â ôàéë. 
	writeFile(mark,numCol, numRow, labir);

	system("pause");
	return 0;
}
