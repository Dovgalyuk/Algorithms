#include <iostream>
#include "queue.h"

using namespace std;

const int LETTERS = 26;
bool visited_vertex[LETTERS] = { false };
int ascii = 'A';

void showTransformations(string answer_string) {
    for (int i = 0; i < answer_string.length(); i++) {
        if (answer_string[i + 1] == '\0') cout << answer_string[i];
        else cout << answer_string[i] << "->";
    }
}
void writeTransformations(int count_transformations, string &input_string) {
    char substance_for_transformation, resulted_substance;

    while (count_transformations) {

        cout << "from: ";
        cin >> substance_for_transformation;
        input_string.push_back(substance_for_transformation);
        cout << "to: ";
        cin >> resulted_substance;
        input_string.push_back(resulted_substance);
        input_string.push_back(' ');

        count_transformations--;
    }
}
void writeInitialSubstanceAndCountTransformations(char& initial_substance, int& count_transformations, string &answer_string) {
    cout << "Write initial substance: ";
    cin >> initial_substance;

    answer_string += initial_substance;

    cout << "Write count transformations: ";
    cin >> count_transformations;
}
void execute(Queue* queue, string input_string, string &answer_string) {
    while (!queue_empty(queue)) {
        for (int j = 0; j < input_string.length(); j += 3)
        {
            char current_vertex = queue_get(queue);
            if (current_vertex == input_string[j] && !visited_vertex[current_vertex - ascii])
            {
                answer_string.push_back(input_string[j + 1]);
                queue_insert(queue, input_string[j + 1]);
                visited_vertex[current_vertex - ascii] = true;
            }
        }
        queue_remove(queue);
    }
}
    
int main() {
    char initial_substance;
    string input_string, answer_string; //Strings for input and answer
    int count_transformations;
    Queue* queue = queue_create();

    //writing the original substance and the number of transformations
    writeInitialSubstanceAndCountTransformations(initial_substance, count_transformations, answer_string);

    //adding initial_substance in the queue
    queue_insert(queue, initial_substance);

    //writing transformations
    writeTransformations(count_transformations, input_string);

    //execute program
    execute(queue, input_string, answer_string);

    //out the response to the console
    showTransformations(answer_string);

    //delete queue
    queue_delete(queue);

    return 0;
}









//char initial_substance, substance_for_transformation, resulted_substance;
//
//cout << "Write initial substance: ";
//cin >> initial_substance;
//
//visited_vertex[initial_substance - ascii] = true;
//
//Queue* queue = queue_create();
//queue_insert(queue, initial_substance);
//
//int count_transformations, point;
//cout << "Write count transformations: ";
//cin >> count_transformations;
//
//string str, str_save;
//
//while (count_transformations) {
//
//    cout << "from: ";
//    cin >> substance_for_transformation;
//    str.push_back(substance_for_transformation);
//    cout << "to: ";
//    cin >> resulted_substance;
//    str.push_back(resulted_substance);
//    str.push_back(' ');
//
//    count_transformations--;
//}
//
//str_save += initial_substance;
//
//while (!queue_empty(queue)) {
//    for (int j = 0; j < str.length(); j += 3)
//    {
//        if ((char)queue_get(queue) == str[j])
//        {
//            for (auto i = 0; i < str_save.length(); i++)
//            {
//                if ((str[j + 1] == str_save[i]) || (str[j + 1] == initial_substance)) {
//                    continue;
//                }
//            }
//            str_save.push_back(str[j + 1]);
//            queue_insert(queue, str[j + 1]);
//        }
//    }
//    queue_remove(queue);
//}
//
//for (int i = 0; i < str_save.length(); i++) {
//    if (str_save[i + 1] == '\0') cout << str_save[i];
//    else cout << str_save[i] << "->";
//}
//
//queue_delete(queue);