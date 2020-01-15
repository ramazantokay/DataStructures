#ifndef __HASHTABLE__
#define __HASHTABLE__

#include "HashUtils.h"

template <class T>
class HashTable
{
    struct Entry
    {
        std::string Key; // the key of the entry
        T Value;         // the value of the entry
        bool Deleted;    // flag indicating whether this entry is deleted
        bool Active;     // flag indicating whether this item is currently used

        Entry() : Key(), Value(), Deleted(false), Active(false) {}
    };

    struct Bucket
    {
        Entry entries[3];
    };

    int _capacity; // INDICATES THE SIZE OF THE TABLE
    int _size;     // INDICATES THE NUMBER OF ITEMS IN THE TABLE

    Bucket *_table; // HASH TABLE

private:
    int total_probes;

public:
    // CONSTRUCTORS, ASSIGNMENT OPERATOR, AND THE DESTRUCTOR
    HashTable();
    HashTable(const HashTable<T> &rhs);
    HashTable<T> &operator=(const HashTable<T> &rhs);
    ~HashTable();

    void Insert(std::string key, const T &value);

    void Delete(std::string key);

    T Get(std::string key) const;

    void Resize(int newCapacity);

    double getAvgSuccessfulProbe();

    double getAvgUnsuccessfulProbe();

    int Capacity() const;
    int Size() const;
};

template <class T>
HashTable<T>::HashTable()
{
    _table = NULL;
    _size = 0;
    _capacity = 0;
    total_probes = 0;
}

template <class T>
HashTable<T>::HashTable(const HashTable<T> &rhs)
{

    int temp_size = rhs.Capacity();
    _capacity = temp_size;
    _size = 0;
    total_probes = 0;
    _table = new Bucket[temp_size];

    for (int i = 0; i < temp_size; i++)
    {

        for (int j = 0; j < 3; j++)
        {
            Insert(rhs._table[i].entries[j].Key, rhs._table[i].entries[j].Value);
        }
    }
}

template <class T>
HashTable<T> &HashTable<T>::operator=(const HashTable<T> &rhs)
{
    int temp_size = rhs.Size();
    delete[] _table;

    _table = new Bucket[temp_size];

    for (int i = 0; i < temp_size; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            _table[i].entries[j] = rhs._table[i].entries[j];
        }
    }

    return *this;
}

template <class T>
HashTable<T>::~HashTable()
{
    delete[] _table;
}

template <class T>
void HashTable<T>::Insert(std::string key, const T &value)
{
    // TODO: IMPLEMENT THIS FUNCTION.
    // INSERT THE ENTRY IN THE HASH TABLE WITH THE GIVEN KEY & VALUE
    // IF THE GIVEN KEY ALREADY EXISTS, THE NEW VALUE OVERWRITES
    // THE ALREADY EXISTING ONE. IF LOAD FACTOR OF THE TABLE IS BIGGER THAN 0.5,
    // RESIZE THE TABLE WITH THE NEXT PRIME NUMBER.

    if (key == "")
    {
        return;
    }
    if (_table == NULL)
    {
        _capacity = NextCapacity(_capacity);
        _table = new Bucket[_capacity];
    }
    if ((double)_size / (3 * _capacity) > 0.50)
        Resize(NextCapacity(_capacity));

    int num_hash = Hash(key) % _capacity;
    int pos = 0;
    int a = 1;
    int index = num_hash;

    while (_table[index].entries[pos].Key != "" && _table[index].entries[pos].Key != key && _table[index].entries[pos].Deleted == false)
    {

        pos++;

        if (pos > 2)
        {
            index = (index + (a * a)) % _capacity;

            a++;
            pos = 0;
            total_probes++;
        }
    }

    if (_table[index].entries[pos].Key == key)
    {
        _table[index].entries[pos].Key = key;
        _table[index].entries[pos].Value = value;
        _table[index].entries[pos].Active = true;
        _table[index].entries[pos].Deleted = false;
        total_probes++;
    }
    else
    {
        _table[index].entries[pos].Key = key;
        _table[index].entries[pos].Value = value;
        _table[index].entries[pos].Active = true;
        _table[index].entries[pos].Deleted = false;
        _size++;
        total_probes++;
    }
}

template <class T>
void HashTable<T>::Delete(std::string key)
{

    int hash_num = Hash(key) % _capacity;
    int pos = 0, a = 1, index = hash_num;

    while (_table[index].entries[pos].Key != "" && _table[index].entries[pos].Key != key && _table[index].entries[pos].Deleted == false)
    {
        pos++;

        if (pos > 2)
        {
            index = (index + a) % _capacity;
            a += 2;
            pos = 0;
        }
    }
    if (_table[index].entries[pos].Key == key && _table[index].entries[pos].Deleted == false)
    {

        _table[index].entries[pos].Active = false;
        _table[index].entries[pos].Deleted = true;
        _size--;
    }
}

template <class T>
T HashTable<T>::Get(std::string key) const
{
    int hash_num = Hash(key) % _capacity;
    int pos = 0, a = 1, index = hash_num;
    while (_table[index].entries[pos].Key != "" && _table[index].entries[pos].Key != key && _table[index].entries[pos].Deleted == false)
    {
        pos++;

        if (pos > 2)
        {
            index = (index + a) % _capacity;
            a += 2;
            pos = 0;
        }
    }

    if (_table[index].entries[pos].Key == key && _table[index].entries[pos].Deleted == false)
    {
        return _table[index].entries[pos].Value;
    }
    else
    {
        return T();
    }
}

template <class T>
void HashTable<T>::Resize(int newCapacity)
{

    int temp_size = _capacity;

    Bucket *temp = new Bucket[temp_size];

    for (int i = 0; i < temp_size; i++)
    {
        for (int j = 0; j < 3; j++)
        {

            temp[i].entries[j] = _table[i].entries[j];
        }
    }

    delete[] _table;
    _size = 0;
    total_probes = 0;
    _capacity = newCapacity;
    _table = new Bucket[newCapacity];

    for (int i = 0; i < temp_size; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (temp[i].entries[j].Active == true)
            {

                Insert(temp[i].entries[j].Key, temp[i].entries[j].Value);
            }
        }
    }

    delete[] temp;
}

template <class T>
double HashTable<T>::getAvgSuccessfulProbe()
{
    return (double)total_probes / _size;
}

template <class T>
double HashTable<T>::getAvgUnsuccessfulProbe()
{

    int total = 0;
    int pos = 0;

    for (unsigned i = 0; i < _capacity; i++)
    {

        int pr = 1;
        int index = i;
        int a = 1;
        while (_table[index].entries[pos].Active == true || _table[index].entries[pos].Deleted == true)
        {
            pos++;

            if (pos > 2)
            {
                pr++;
                index = (index + a) % _capacity;
                a += 2;
                pos = 0;
            }
        }
        total += pr;
    }

    return ((double)total) / _capacity;
}

template <class T>
int HashTable<T>::Capacity() const
{
    return _capacity;
}

template <class T>
int HashTable<T>::Size() const
{
    return _size;
}

#endif