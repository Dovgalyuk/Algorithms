#ifndef ARRAY_TEMPLATE_H
#define ARRAY_TEMPLATE_H

// ��������� ��������� ����� Array ��� ������ � ��������� ������������� ���� Data
template <typename Data>
class Array {
public:
    // ����������� ��� �������� �������
    explicit Array(size_t size) {
        this->data = new Data[size]; // ��������� ������ ��� ������
        this->size_array = size;     // ����������� ������� �������
    }

    // ���������� ��� ����������� ������� � ������������ ������
    ~Array() {
        delete[] data; // ������������ ������
    }

    // ����������� �����������
    Array(const Array<Data>& a) {
        size_array = a.size_array;         // ����������� ������� �������
        data = new Data[size_array];       // ��������� ������ ��� ����� �������
        for (size_t i = 0; i < size_array; i++) {
            data[i] = a.data[i];           // ����������� ��������� �������
        }
    }

    // �������� ������������
    Array& operator=(const Array<Data>& a) {
        if (this == &a) {
            // �������� �� ����������������
            return *this;
        }

        // �������� ������� ������
        delete[] data;

        // �������� �����������
        size_array = a.size_array;        // ����������� ������� �������
        data = new Data[size_array];      // ��������� ������ ��� ����� ������
        for (size_t i = 0; i < size_array; i++) {
            data[i] = a.data[i];          // ����������� ��������� �������
        }

        return *this; // ����������� �������� �������
    }

    // ���������� ��������� �� ������� ������� �� �������
    Data* get(size_t index) const {
        return &data[index];
    }

    // ������������� �������� �������� ������� �� �������
    void set(size_t index, Data value) {
        data[index] = value;
    }

    // ���������� ������ �������
    size_t size() const { return this->size_array; }

    size_t size_array; // ���������� ��� �������� ������� �������
private:
    Data* data; // ��������� �� ������
};

#endif // ARRAY_TEMPLATE_H