// Вариант 5
// (м) BigDzenga(i, j) удаляет часть стека от i до j.

#include <iostream>

class Elem {
    public:
        Elem* next;
        Elem* prev;
        std::string data;

    Elem(Elem* next, std::string data) : next(next), data(data) { }
};

class Stack {
private:
    Elem* head;

public:
    Stack() : head(nullptr) {}

    ~Stack() {
        while (!is_empty()) {
            pop();
        }
    }

    bool is_empty() {
        return head == nullptr;
    }

    void push(Elem* elem) {
        Elem* new_elem = new Elem(nullptr, elem->data);
        if (is_empty()) {
            head = new_elem;
        } else {
            Elem* current = head;
            head = elem;
            current->next = head;
            head->prev = current;
        }
    }

    void pop() {
        if (is_empty()) {
            std::cerr << "Стек пуст, невозможно удалить задачу." << std::endl;
            return;
        }
        Elem* to_delete = head;
        head = head->prev;
        if (head != nullptr) {
            head->next = nullptr;
        }
        delete to_delete;
    }

    bool find(std::string a) {
        Elem* current = head;
        while (current != nullptr) {
            if (current->data == a) {
                return true;
            }
            current = current->prev;
        }
        return false;
    }

    int weight(std::string a) {
        int i = 0;
        Elem* current = head;
        while (current != nullptr) {
            if (current->data == a) {
                return i;
            }
            current = current->prev;
            i++;
        }
        return -1;
    }

    Stack operator+(const Stack& other) {
        Stack result;
        Elem* current = head;
        while (true) {
            if (current->prev == nullptr) {
                break;
            }
            current = current->prev;
        }

        while (current != nullptr) {
            result.push(new Elem(nullptr, current->data));
            current = current->next;
        }

        current = other.head;
        while (true) {
            if (current->prev == nullptr) {
                break;
            }
            current = current->prev;
        }
        while (current != nullptr) {
            result.push(new Elem(nullptr, current->data));
            current = current->next;
        }

        return result;
    }

    Stack operator*(Stack& other) {
        Stack result;
        Elem* current1 = head;
        Elem* current2 = other.head;

        while (current1->prev != nullptr) {
            current1 = current1->prev;
        }
        while (current2->prev != nullptr) {
            current2 = current2->prev;
        }

        int size1 = size();
        int size2 = other.size();
        
         if (size2 >= size1) {
                for (int i = 0; i < (size2 - size1); i++) {
                    result.push(new Elem(nullptr, current2->data));
                    current2 = current2->next;
                }
                while (current1 != nullptr || current2 != nullptr) {
                    if (current2 != nullptr) {
                        result.push(new Elem(nullptr, current2->data));
                        current2 = current2->next;
                    }
                    if (current1 != nullptr) {
                        result.push(new Elem(nullptr, current1->data));
                        current1 = current1->next;
                    }
                }
            }
            else {
                for (int i = 0; i < (size1 - size2); i++) {
                    result.push(new Elem(nullptr, current1->data));
                    current1 = current1->next;
                }
                while (current1 != nullptr || current2 != nullptr) {
                    if (current1 != nullptr) {
                        result.push(new Elem(nullptr, current1->data));
                        current1 = current1->next;
                    }
                    if (current2 != nullptr) {
                        result.push(new Elem(nullptr, current2->data));
                        current2 = current2->next;
                    }
                }
            }

        return result;
    }

    Stack operator-() const {
        Stack result;
        Elem* current = head;
        while (current != nullptr) {
            result.push(new Elem(nullptr, current->data));
            current = current->prev;
        }
        return result;
    }

    int size() {
        int size = 0;
        Elem* current = head;
        while (current != nullptr) {
            size++;
            current = current->prev;
        }
        return size;
    }

    void BigDzenga(int i, int j) {
        if (is_empty()) {
            return;
        }
        int counted_size = size();
        if (i < 0 || j < 0 || i > j || i >= counted_size || j >= counted_size) {
            return;
        }

        Elem* current = head;
        for (int k = 0; k < counted_size - j - 1; k++) {
            current = current->prev;
        }

        Elem* prev_current;
        if (current == head) {
            for (int k = i; k <= j; k++) {
                prev_current = current;
                current = current->prev;
                delete prev_current;
            }
            head = current;
            if (head != nullptr) {
                head->next = nullptr;
            }
            return;
        }

        Elem* elem1 = current->next;
        for (int k = i; k <= j; k++) {
            prev_current = current;
            current = current->prev;
            delete prev_current;
        }

        if (current != nullptr) {
            elem1->prev = current;
            current->next = elem1;
        } else {
            elem1->prev = nullptr;
        }
    }

    void print_stack() {
        Elem* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->prev;
        }
        std::cout << std::endl;
    }
};

int main() {
    Stack s1;
    Stack s2;

    std::cout << "Вершина стека <-> Elem <-> Низ стека\n" << std::endl;

    s1.push(new Elem(nullptr, "A"));
    s1.push(new Elem(nullptr, "B"));
    s1.push(new Elem(nullptr, "C"));

    s2.push(new Elem(nullptr, "D"));
    s2.push(new Elem(nullptr, "E"));
    s2.push(new Elem(nullptr, "F"));
    s2.push(new Elem(nullptr, "G"));
    

    std::cout << "Стек s1: ";
    s1.print_stack();

    std::cout << "Стек s2: ";
    s2.print_stack();

    Stack s3 = s1 + s2;
    std::cout << "Результат s1 + s2: ";
    s3.print_stack();

    Stack s4 = s1 * s2;
    std::cout << "Результат s1 * s2: ";
    s4.print_stack();

    s3.BigDzenga(2, 5);
    std::cout << "(s1 + s2) после BigDzenga(): ";
    s3.print_stack();

    Stack s6 = -s1;
    std::cout << "Стек -s1: ";
    s6.print_stack();
    

    s2.pop();
    std::cout << "Стек s2 после pop(): ";
    s2.print_stack();

    std::cout << "Поиск элемента 'B' в стеке s1: ";
    bool inS = s1.find("B");
    if (inS) {
        std::cout << "Элемент " << "B" << " содержится в стеке." << std::endl;
    }
    else {
        std::cout << "Элемент " << "B" << " не содержится в стеке." << std::endl;
    }

    std::cout << "Вес элемента 'E' в стеке s2: ";
    std::cout << s2.weight("E") << std::endl;

    std::cout << "Размер стека s1: " << s1.size() << std::endl;

}