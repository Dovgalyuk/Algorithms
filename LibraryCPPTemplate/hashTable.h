#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

template<typename Data> class HashTable {

    public:

        // hash Node table
        struct Item {

            Data data;
            bool state = true; // delete or no delete, false = delet

        
            Item(Data data_) {
                data = data_;
            }

            void setData(Data data_) {
                data = data_;
            }

            Data getData() {
                return data;
            }

            void setState(bool state_) {
                state = state_;
            }

            bool getState() {
                return state;
            }
        };

        HashTable() {
            table = new Item*[size_table];

            for (int i = 0; i < size_table; i++) {
                table[i] = nullptr;
            }
        }

        ~HashTable() {
            for (int i = 0; i < size_table; i++) {
                if (table[i]) {
                    delete table[i];
                }
            }

            delete[] table;
        }

        void Resize_table() {
            int old_size_table = size_table;
            size_table *= 2;

            size = 0;

            Item** table_temp = new Item*[size_table];
            for (int i = 0; i < size_table; i++) {
                table_temp[i] = nullptr;
            }

            std::swap(table, table_temp);

            for (int i = 0; i < old_size_table; i++) {
                if (table_temp[i] && table_temp[i]->getState()) {
                    setData(table_temp[i]->getData());
                }
            }

            for (int i = 0; i < old_size_table; i++) {
                if (table_temp[i]) {
                    delete table_temp[i];
                }
            }
            delete[] table_temp;

        }

        bool setData(Data data_) {
            int hash1 = hash_1(data_, size_table);
            int hash2 = hash_2(data_, size_table);

            int i = 0;
            int first_delete = -1;

            if (size + 1 > int(size_table * threshold)) {
                Resize_table();
            }

            while (table[hash1] != nullptr && i < size_table) {

                if (table[hash1]->getData() == data_ && table[hash1]->getState()) {
                    return false;
                }
                if (!table[hash1]->getState() && first_delete == -1) {
                    first_delete = hash1;
                }
                hash1 = (hash1 + hash2) % size_table;
                i++;
             }

             if (first_delete == -1) {
                 table[hash1] = new Item(data_);
             }
             else {
                 table[first_delete]->setData(data_);
                 table[first_delete]->setState(true);
             }

             size++;
             return true;
        }

        bool deleteData(Data data_) {

            int hash1 = hash_1(data_, size_table);
            int hash2 = hash_2(data_, size_table);

            int i = 0;

            while (table[hash1] != nullptr && i < size_table) {
                
                if (table[hash1]->getData() == data_ && table[hash1]->getState()) {
                    table[hash1]->setState(false);
                    size--;
                    return true;
                }

                hash1 = (hash1 + hash2) % size_table;
                i++;
            }

            return false;
        }

        bool findData(Data data_) {

            int hash1 = hash_1(data_, size_table);
            int hash2 = hash_2(data_, size_table);

            int i = 0;

            while (table[hash1] != nullptr && i < size_table) {

                if (table[hash1]->getData() == data_ && table[hash1]->getState()) {
                    return true;
                }

                hash1 = (hash1 + hash2) % size_table;
                i++;
            }

            return false;
        }

    private:

        int size_table = 64; // default size
        int size = 0;
        Item **table;        
        float threshold = 0.65f;

        // int hash (std::string str, int size_table) {
        //     int sum_hash = 0;
        //     unsigned long long p = 1;

        //     for (int i = 0; i < str.size(); i++) {
        //         sum_hash = (p * sum_hash + str[i]) % size_table;
        //         p *= 31;
        //     }

        //     return sum_hash % size_table;
        // }

        int hash_horner(Data str, int size_table, int key) {
            
            int sum_hash = 0;

            for (int i = 0; i < str.size(); i++) {
                sum_hash = (key * sum_hash + str[i]) % size_table;
            }

            sum_hash = (sum_hash * 2 + 1) % size_table;

            return sum_hash;
        }

        int hash_1(Data str, int size_table) {
            return hash_horner(str, size_table, size_table - 1);
        }

        int hash_2(Data str, int size_table) {
            return hash_horner(str, size_table, size_table + 1);
        }
};

#endif