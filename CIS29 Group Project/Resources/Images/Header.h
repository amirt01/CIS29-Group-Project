#ifndef HEADER_H
#define HEADER_H

template<typename T>
class DuplicateError : public std::logic_error
{
public:
    DuplicateError(const T& error) : std::logic_error(error) {};
    std::string Typeid() const;
    const char* what() const noexcept override;
};

template<typename T>
class Node
{
    T  data_;
    Node* next_;
    Node(const Node&) = delete;
    Node& operator=(const Node&) = delete;
public:
    Node() : data_(), next_(0) {};
    Node(T d, Node* n) : data_(d), next_(n) {};
    const T& data() const { return data_; };
    T& data() { return data_; };
    Node* next() const { return next_; };
    Node*& next() { return next_; };
    friend std::ostream& operator<<(std::ostream& out, const Node<T>& N) { return out << N.data(); };
};

template<typename T> class List
{
    Node<T>* top_;
    unsigned nodes = 0;

    List(const List&) = delete;
    List& operator=(const List&) = delete;
public:
    List() : top_(0) {};
    ~List();
    void push(T object);
    T pop();
    const unsigned size() const { return nodes; };
    const Node<T>* top() const { return top_; };
    bool remove(T object);
    const Node<T>* find(T object) const;
};

#endif