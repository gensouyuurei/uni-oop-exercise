#pragma once

#include <iterator>

template<class T>
class Container {
private:

    struct Node {
        T element;
        Node *prev;
        Node *next;

        Node(T element, Node *prev, Node *next)
                : element(element), prev(prev), next(next) {}
    };

	class iterator {
	private:
		Node *node;

	public:
		iterator(Node *n) : node(n) {}

		iterator(const iterator &it) {
			node = it.node;
		}

		bool operator!=(iterator const &other) {
			return node != other.node;
		}

		T &operator*() {
			return node->element;
		}

		iterator &operator++() {
			node = node->next;
			return *this;
		}
	};

    size_t size;
    Node *head;
    Node *tail;

public:

    class empty_Container : public std::logic_error {
    public:
        empty_Container() : logic_error("Container is empty.") {}
    };

    Container() : size(0), head(nullptr), tail(nullptr) {}

    Container(const Container &other) {
        head = new Node(other.head->element, nullptr, nullptr);

        auto prev = head;
        for (auto i = ++other.begin(); i != other.end(); ++i) {
            auto current = new Node(*i, prev, nullptr);
            prev->next = current;
            prev = current;
        }

        tail = prev;
        size = other.size;
    }

    Container &operator=(const Container &other) {
        if (this == &other) {
            return *this;
        }

        clear();

        head = new Node(other.head->element, nullptr, nullptr);

        auto prev = head;
        for (auto i = ++other.begin(); i != other.end(); ++i) {
            auto current = new Node(*i, prev, nullptr);
            prev->next = current;
            prev = current;
        }

        tail = prev;
        size = other.size;

        return *this;
    }

    ~Container() {
        this->clear();
    }

	iterator begin() {
		return iterator(head);
	}

	iterator end() {
		return iterator(nullptr);
	}

    void push_front(const T &element) {
        if (size == 0) {
            head = new Node(element, nullptr, nullptr);
            tail = head;
        } else {
            auto node = new Node(element, nullptr, head);
            head->prev = node;
            head = node;
        }
        size++;
    }

    void push_back(const T &element) {
        if (size == 0) {
            tail = new Node(element, nullptr, nullptr);
            head = tail;
        }
		else {
            auto node = new Node(element, tail, nullptr);
            tail->next = node;
            tail = node;
        }
        size++;
    }

    void pop_front() {
        if (size == 0) {
            throw empty_Container();
        }

        if (size == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
		else {
            auto deleteAfter = head;
            head->next->prev = nullptr;
            head = head->next;
            delete deleteAfter;
        }
        size--;
    }

    void pop_back() {
        if (size == 0) {
            throw empty_Container();
        }

        if (size == 1) {
            delete tail;
            head = nullptr;
            tail = nullptr;
        }
		else {
            auto deleteAfter = tail;
            tail->prev->next = nullptr;
            tail = tail->prev;
            delete deleteAfter;
        }
        size--;
    }

	T getElement(int i) {

	}

    T getFront() const {
        return head->element;
    }

    T getBack() const {
        return tail->element;
    }

	Node * getNext() {
		return 
	}
    size_t getSize() const {
        return size;
    }

    bool is_empty() const {
        return size == 0;
    }

    void clear() {
        if (size == 0) return;

        auto i = head;
        while (i->next != nullptr) {
            i = i->next;
            delete i->prev;
        }
        delete i;

        size = 0;
        head = nullptr;
        tail = nullptr;
    }
};
