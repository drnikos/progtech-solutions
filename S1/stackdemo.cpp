#include <iostream>
using namespace std;

template<typename T>
class stack {
public:
    stack(int size);
    stack(const stack &s);
    ~stack();
    const stack &operator=(const stack &s);
    bool empty() const;
    void push(const T &x);
    T pop();
    int size() const;
    template<typename U>
    friend ostream &operator<<(ostream &out, const stack<U> &s);

private:
    int stack_size;
    int c_index;
    T *li;
};

template<typename T>
stack<T>::stack(int size) {
    stack_size = size;
    c_index = 0;
    li = new T[stack_size];
}

template<typename T>
stack<T>::stack(const stack &s) {
    stack_size = s.stack_size;
    c_index = s.c_index;
    li = new T[stack_size];
    for (int i = 0; i < c_index; i++) {
        li[i] = s.li[i];
    }
}

template<typename T>
stack<T>::~stack() {
    delete[] li;
}

template<typename T>
const stack<T> &stack<T>::operator=(const stack &s) {
    if (this != &s) {
        delete[] li;
        stack_size = s.stack_size;
        c_index = s.c_index;
        li = new T[stack_size];
        for (int i = 0; i < c_index; i++) {
            li[i] = s.li[i];
        }
    }
    return *this;
}

template<typename T>
bool stack<T>::empty() const {
    return c_index == 0;
}

template<typename T>
void stack<T>::push(const T &x) {
    if (c_index < stack_size) {
        li[c_index++] = x;
    } else {
        cout << "Stack overflow!" << endl;
    }
}

template<typename T>
T stack<T>::pop() {
    if (c_index > 0) {
        return li[--c_index];
    } else {
        cout << "Stack underflow!" << endl;
        return T();
    }
}

template<typename T>
int stack<T>::size() const {
    return c_index;
}

template<typename T> // Return default value of Ttemp

ostream &operator<<(ostream &out, const stack<T> &s) {
    out << "[";
    for (int i = 0; i < s.c_index; i++) {
        out << s.li[i];
        if (i < s.c_index - 1)
            out << ", ";
    }
    out << "]";

    return out;
}

#ifndef CONTEST2
int main() {
    stack<int> s(10);
    cout << "s is empty: " << s.empty() << endl;

    s.push(42);
    cout << "s has one element: " << s << endl;

    s.push(17);
    s.push(34);
    cout << "s has more elements: " << s << endl;
    cout << "How many? " << s.size() << endl;

    stack<int> t(5);
    t.push(7);
    cout << "t: " << t << endl;

    t = s;
    cout << "popping from s: " << s.pop() << endl;

    s.push(8);
    stack<int> a(s);
    t.push(99);
    a.push(77);

    cout << "s: " << s << endl;
    cout << "t: " << t << endl;
    cout << "a: " << a << endl;

    stack<double> c(4);
    c.push(3.14);
    c.push(1.414);
    cout << "c contains doubles " << c << endl;

    stack<char> k(4);
    k.push('$');
    cout << "k contains a character " << k << endl;

    return 0;
}
#endif
