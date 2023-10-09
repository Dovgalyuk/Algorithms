#ifndef ARRAY_H
#define ARRAY_H

#include <vector> // ���������� ������������ ���� ��� ������������� std::vector

using Data = int; // ���������� ��������� ���� int ��� ��������

class Array
{
public:
    explicit Array(size_t size) : m_data(size) {} // ����������� ����������, ����������� ������ ������� � ���������������� m_data � ������� ������������ std::vector

    Data get(size_t index) const // ����� ��� ��������� �������� �������� �� �������
    {
        if (index < m_data.size()) { // ���������, ��� ������ �� ������� �� ������� �������
            return m_data[index]; // ���������� �������� �������� �� �������
        }
        return -1; // ���������� �������� �� ��������� ��� ������������ �������
    }

    void set(size_t index, Data value) // ����� ��� ��������� �������� �������� �� �������
    {
        if (index < m_data.size()) { // ���������, ��� ������ �� ������� �� ������� �������
            m_data[index] = value; // ������������� �������� �������� �� �������
        }
    }

    size_t size() const // ����� ��� ��������� ������� �������
    {
        return m_data.size();
    }

private:
    std::vector<Data> m_data; // ���������� ���������, ������������ std::vector ��� �������� ������
};

#endif