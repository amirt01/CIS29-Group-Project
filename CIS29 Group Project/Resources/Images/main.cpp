/******************************
 * Name: Amir Tadros          *
 * Assignment # 4             *
 * Compiler: CodeBlocks 20.03 *
 * OS: Windows 10             *
 *****************************/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>

#include "Mystring.h"
#include "Header.h"

template <typename T>
const char* DuplicateError<T>::what() const noexcept
{
    static char ret[128];
    strcpy_s(ret, "Duplicate ");
    strcat_s(ret, Typeid().c_str());
    strcat_s(ret, ": ");
    strcat_s(ret, logic_error::what());
    return ret;
}

template <typename T>
std::string DuplicateError<T>::Typeid() const {
    std::string id = typeid(T).name();

#ifdef _MSC_VER
    id = id.substr(6);
#endif // _MSC_VER

#ifdef __GNUC__
    id = id.substr(id.find_first_not_of("0123456789"));
#endif // __GNUC__

    return id;
}

template<typename T>
List<T>::~List()
{
    Node<T>* ptr = top_;
    while (ptr)
    {
        top_ = top_->next();
        delete ptr;
        ptr = top_;
    }
}

template<typename T>
void List<T>::push(T object)
{
    Node<T>* ptr = new Node<T>(object, top_);
    top_ = ptr;
    nodes++;
}

template<typename T>
T List<T>::pop()
{
    Node<T>* ptr = top_;
    top_ = top_->next();
    T data = ptr->data();
    delete ptr;
    return data;
}

template<typename T>
const Node<T>* List<T>::find(T object) const
{
    const Node<T>* ptr = top();
    while (ptr)
    {
        if (ptr->data() == object)
        {
            return ptr;
        }
        ptr = ptr->next();
    }
    return nullptr;
}

template<typename T>
bool List<T>::remove(T object)
{
    if (!find(object))
    {
        std::cerr << object << " not found\n";
        return false;
    }
    Node<T>* ptr2current = top_;
    Node<T>* ptr2previous = top_;
    if (top_->data() == object)
    {
        top_ = top_->next();
        delete ptr2current;
        return true;
    }
    while (ptr2current)
    {
        ptr2current = ptr2current->next();
        if (ptr2current->data() == object)
        {
            ptr2previous->next() = ptr2current->next();
            delete ptr2current;
            return true;
        }
        ptr2previous = ptr2current;
    }
    return false;
}

template<typename T, const unsigned K>
class Myhash
{
    const unsigned BUCKETS = K;
    float numberOfWords = 0;
    unsigned numberOfWordsNotStored = 0;

    List<T> table[K];
public:
    Myhash() {};
    float size() const { return numberOfWords; };
    float percentOfBucketsUsed() const;
    float averageNonEmptyBucketSize() const;
    unsigned largestBucketSize() const;
    void insert(T x);
    bool find(T key);
    unsigned hashFunction(unsigned key);
};

template<typename T, const unsigned K>
unsigned Myhash<T, K>::largestBucketSize() const
{
    unsigned largestBucketSize = 0;

    for (unsigned i = 0; i < BUCKETS; i++)
    {
        if (table[i].size() > largestBucketSize) {
            largestBucketSize = table[i].size();
        }
    }

    return largestBucketSize;
}

template<typename T, const unsigned K>
float Myhash<T, K>::percentOfBucketsUsed() const
{
    float filledBuckets = 0;

    for (unsigned i = 0; i < BUCKETS; i++)
    {
        if (table[i].size() > 0) {
            filledBuckets++;
        }
    }

    return filledBuckets / BUCKETS * 100;
}

template<typename T, const unsigned K>
float Myhash<T, K>::averageNonEmptyBucketSize() const
{
    float filledBuckets = 0;

    for (unsigned i = 0; i < BUCKETS; i++)
    {
        if (table[i].size() > 0) {
            filledBuckets++;
        }
    }

    return numberOfWords / filledBuckets;
}

template<typename T, const unsigned K>
void Myhash<T, K>::insert(T key)
{
    unsigned index = hashFunction(key);
    if (table[index].find(key))
        throw(DuplicateError<T>(key));

    table[index].push(key);
    numberOfWords++;
}

template<typename T, const unsigned K>
bool Myhash<T, K>::find(T key)
{
    unsigned index = hashFunction(key);
    if (table[index].find(key))
        return true;
    else
        return false;
}

// hash function adapted from: Thomas Wang https://gist.github.com/badboy/6267743
template<typename T, const unsigned K>
unsigned Myhash<T, K>::hashFunction(unsigned key) {
    int c2 = 0x27d4eb2d; // a prime or an odd constant
    key = (key ^ 61) ^ (key >> 16);
    key = key + (key << 3);
    key = key ^ (key >> 4);
    key = key * c2;
    key = key ^ (key >> 15);
    return key % BUCKETS;
}

int main()
{
    Myhash<Mystring, 1500> Dictionary;
    Mystring buffer;

    const std::string DictionaryFileName = "ass4words.txt";
    const std::string DocumentFileName = "roosevelt_first_inaugural.txt";

    std::ifstream fin(DictionaryFileName.c_str());
    if (!fin)
    {
        std::cerr << "Can't find " << DictionaryFileName << std::endl;
        exit(-1);
    }
    while (std::getline(fin, buffer))
    {
        // remove \r if present (this for Mac/Linux)
        if (buffer[buffer.size() - 1] == '\r')
            buffer.resize(buffer.size() - 1);

        buffer.tolower();
        try
        {
            Dictionary.insert(buffer);
        }
        catch (const DuplicateError<Mystring>& error)
        {
            std::cout << error.what() << std::endl;
        }
    }

    std::cout << "Number of words in the dictionary = " << Dictionary.size() << std::endl;
    std::cout << "Percent of hash table buckets used = " << std::fixed << std::setprecision(2) << Dictionary.percentOfBucketsUsed() << '%' << std::endl;
    std::cout << "Average non-empty bucket size = " << std::fixed << std::setprecision(2) << Dictionary.averageNonEmptyBucketSize() << std::endl;
    std::cout << "Largest bucket size = " << Dictionary.largestBucketSize() << std::endl;

    fin.close();
    fin.clear();

    // Spellcheck
    unsigned misspelledWords = 0;

    fin.open(DocumentFileName.c_str());
    if (!fin)
    {
        std::cerr << "Can't find " << DocumentFileName << std::endl;
        exit(-1);
    }
    while (fin >> buffer)
    {
        buffer.tolower();
        buffer.removePunctuation();
        if (!buffer.size())
            continue;
        if (!Dictionary.find(buffer))
        {
            misspelledWords++;
            std::cout << "Not found in the dictionary: " << buffer << std::endl;
        }
    }
    std::cout << "Total mispelled words = " << misspelledWords << std::endl;
}
