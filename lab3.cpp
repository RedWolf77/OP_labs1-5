// Вариант 5
// (м) PropustiteMenya(а) который продвигает элемент а на одну позицию вверх по очереди.
// (A=a1-a2-a3-а4-а5, А.PropustiteMenya(а3), A=a1-a3-a2-а4-а5)


#include <iostream>

class Elem {
    public:
        Elem* next;
        std::string data;

    Elem(Elem* next, std::string data) : next(next), data(data) { }
};

class Queue {
    private:
        Elem* head;
        Elem* tail;
        int curr_size;
    public:
        Queue() : head(nullptr), tail(nullptr), curr_size(0) {}

        bool is_empty() {
            if (curr_size == 0) {
                return true;
            }
            return false;
        }

        void push(Elem* elem) {
            Elem* new_elem = new Elem(elem->next, elem->data);
            if (is_empty()) {
                head = new_elem;
                tail = new_elem;
            }
            else if (!head->next) {
                head->next = new_elem;
                tail = new_elem;
            }
            else {
                tail->next = new_elem;
                tail = new_elem;
            }
            curr_size += 1;
        }

        void pop() {
            if (is_empty()) {
                std::cerr << "Очередь пуста, невозможно удалить элемент." << std::endl;
                return;
            }
            Elem* current = head;
            head = current->next;
            curr_size -= 1;
            std::cout << "Извлечен элемент: " << current->data << std::endl;
            delete current;
        }

        bool find(std::string a) {
            Elem* current = head;
            while (current != nullptr) {
                if (current->data == a) {
                    return true;
                }
                current = current->next;
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
                current = current->next;
                i++;
            }
            return -1;
        }

        Queue operator+(const Queue& other) {
            Queue result;
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

        Queue operator*(const Queue& other) {
            Queue result;
            Elem* current1 = head;
            Elem* current2 = other.head;

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

            return result;
        }

        Queue operator-() {
            Queue result;
            Elem* current = head;
            while (current != nullptr) {
                result.push(new Elem(nullptr, current->data));
                current = current->next;
            }

            Elem* tempHead = nullptr;
            current = result.head;
            while (current != nullptr) {
                Elem* nextElem = current->next;
                current->next = tempHead;
                tempHead = current;
                current = nextElem;
            }
            result.head = tempHead;
            return result;
        }

        void print_queue() {
            if (is_empty()) {
                std::cout << "Очередь пуста." << std::endl;
                return;
            }
            Elem* current = head;
            while (current != nullptr) {
                std::cout << current->data << " ";
                current = current->next;
            }
            std::cout << std::endl;
        }

        void PropustiteMenya(std::string a) {
            if (curr_size < 2) {
                return;
            }

            if (head->next->data == a) {
                Elem* current = head->next;
                Elem* next_current = current->next;
                current->next = head;
                head->next = next_current;
                head = current;
                
            }
            else {
                Elem* elem1 = head;
                Elem* elem2 = elem1->next;
                Elem* elem3 = elem2->next;
                
                while (elem3 != nullptr) {
                    if (elem3->data == a) {
                        if (elem1 == head) {
                            head->next = elem3;
                        }
                        Elem* next_elem3 = elem3->next;
                        elem3->next = elem2;
                        elem2->next = next_elem3;
                        elem1->next = elem3;
                        return;
                    }
                    elem1 = elem1->next;
                    elem2 = elem2->next;
                    elem3 = elem3->next;
                }
            }
        }
};

int main() {
    Queue q1;
    q1.push(new Elem(nullptr, "1"));
    q1.push(new Elem(nullptr, "2"));
    q1.push(new Elem(nullptr, "3"));

    std::cout << "Очередь q1: ";
    q1.print_queue();

    std::cout << "Поиск элемента 2: ";
    bool inQ = q1.find("2");
    if (inQ) {
        std::cout << "Элемент " << "2" << " содержится в очереди." << std::endl;
    }
    else {
        std::cout << "Элемент " << "2" << " не содержится в очереди." << std::endl;
    }

    std::cout << "Вес элемента 3: " << q1.weight("3") << std::endl;

    q1.pop();

    std::cout << "Очередь после удаления: ";
    q1.print_queue();

    Queue q2;
    q2.push(new Elem(nullptr, "4"));
    q2.push(new Elem(nullptr, "5"));

    std::cout << "Очередь q2: ";
    q2.print_queue();

    Queue q3 = q1 + q2;
    std::cout << "Результат q1 + q2: ";
    q3.print_queue();

    q3.PropustiteMenya("3");
    std::cout << "Очередь после PropustiteMenya(): ";
    q3.print_queue();
    std::cout << std::endl;

    Queue q4 = q1 * q2;
    std::cout << "Результат q1 * q2: ";
    q4.print_queue();

    Queue q5 = -q1;
    std::cout << "Результат -q1: ";
    q5.print_queue();
}