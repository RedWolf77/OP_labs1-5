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
        Elem* tail;
        int curr_size;
    public:
        Stack() : head(nullptr), tail(nullptr), curr_size(0) {}

        bool is_empty() {
            if (curr_size == 0) {
                return true;
            }
            return false;
        }

        void push(Elem* elem) {
            Elem* new_elem = new Elem(nullptr, elem->data);
            if (is_empty()) {
                head = new_elem;
                tail = new_elem;
            }
            else if (head == tail) {
                new_elem->prev = head;
                head->next = new_elem;
                tail = new_elem;
            }
            else {
                tail->next = new_elem;
                new_elem->prev = tail;
                tail = new_elem;
            }
            curr_size += 1;
        }

        void pop() {
            if (is_empty()) {
                std::cerr << "Стек пуст, невозможно удалить задачу." << std::endl;
                return;
            }
            Elem* current = tail;
            tail = current->prev;
            curr_size -= 1;
            delete current;
        }

        bool find(std::string a) {
            Elem* current = tail;
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
            Elem* current = tail;
            while (current != nullptr) {
                if (current->data == a) {
                    return i;
                }
                current = current->prev;
                i++;
            }
            return -1;
        }

        int getSize() {
            return curr_size;
        }

        Stack operator+(const Stack& other) {
            Stack result;
            Elem* current = head;
            while (current != nullptr) {
                result.push(new Elem(nullptr, current->data));
                current = current->next;
            }

            current = other.head;
            while (current != nullptr) {
                result.push(new Elem(nullptr, current->data));
                current = current->next;
            }
            
            return result;
        }

        Stack operator*(const Stack& other) {
            Stack result;
            Elem* current1 = head;
            Elem* current2 = other.head;

            if (other.curr_size >= curr_size) {
                for (int i = 0; i < (other.curr_size - curr_size); i++) {
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
                for (int i = 0; i < (curr_size - other.curr_size); i++) {
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

        Stack operator-(const Stack& other) {
            Stack result;
            Elem* current = tail;
            while (current != nullptr) {
                result.push(new Elem(nullptr, current->data));
                current = current->next;
            }
            return result; 
        }

        void BigDzenga(int i, int j) {
            if (is_empty()) {
                return;
            }
            if (i < 0 || j < 0 || i > j || i > curr_size || j > curr_size) {
                return;
            }
            if (curr_size == 1) {
                pop();
            }

            Elem* current = head;
            for (int k = 0; k < i ; k++) {
                current = current->next;
            }

            Elem* prev_current;
            if (current == head) {
                for (int k = i; k <= j; k++) {
                    prev_current = current;
                    current = current->next;
                    delete prev_current;
                }
                head = current;
                return;
            }

            Elem* elem1 = current->prev;
            for (int k = i; k <= j; k++) {
                prev_current = current;
                current = current->next;
                delete prev_current;
            }

            if (head == nullptr) {
                head = current;
            }
            else if (current == nullptr) {
                tail = elem1;
                return;
            }
            elem1->next = current;
            current->prev = elem1;
        }

        void print_stack() {
            Elem* current = head;
            while (current != nullptr) {
                std::cout << current->data << " ";
                current = current->next;
            }
            std::cout << std::endl;
        }
};

int main() {
    Stack s1;
    Stack s2;

    s1.push(new Elem(nullptr, "A"));
    s1.push(new Elem(nullptr, "B"));
    s1.push(new Elem(nullptr, "C"));

    s2.push(new Elem(nullptr, "D"));
    s2.push(new Elem(nullptr, "E"));
    s2.push(new Elem(nullptr, "F"));

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

    s2.pop();
    std::cout << "Стек s2 after pop(): ";
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

    std::cout << "Размер стека s1: " << s1.getSize() << std::endl;

}