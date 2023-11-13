#include <iostream>

struct MyVector {
    int* data;
    size_t size;
    size_t max_size;

    MyVector() {
        size = 0;
        max_size = 1;
        data = new int[max_size];
    }

    ~MyVector() {
        delete[] data;
    }
};

MyVector* vector_create() {
    return new MyVector;
}

void vector_delete(MyVector* myVector) {
    delete myVector;
}

int vector_get(const MyVector* myVector, size_t index) {
    size_t size = myVector->size;
    if (size <= index) {
        throw "Error";
    }
    return myVector->data[index];
}

void vector_set(MyVector* myVector, size_t index, int value) {
    size_t size = myVector->size;
    if (size <= index) {
        throw "Error";
    }
    myVector->data[index] = value;
}

size_t vector_size(const MyVector* myVector) {
    return myVector->size;
}

void vector_resize(MyVector* myVector, size_t size) {
    if (size <= myVector->max_size) {
        myVector->size = size;
        return;
    }
    size_t _max_size = size * 2;
    int* tmp = new int[_max_size];
    for (size_t i = 0; i < myVector->size; i++) {
        tmp[i] = myVector->data[i];
    }
    delete[] myVector->data;

    myVector->data = tmp;
    myVector->max_size = _max_size;
    myVector->size = size;
}

int main() {
    MyVector* vector = vector_create();

    for (size_t i = 0; i < vector_size(vector); ++i) {
        vector_set(vector, i, static_cast<int>(i));
    }

    vector_delete(vector);

    return 0;
}