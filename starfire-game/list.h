#ifndef LIST_H
#define LIST_H
#include <inttypes.h>

template <class T> class List {
  public:

    struct ListNode {
      ListNode(const T& data, ListNode* next=NULL): data(data), next(next) {}
      ListNode* next;
      T data;
    };

    List(): _head(NULL), _length(0) {}

    ~List() {
      this->clear();
    }

    List(const List& list): _head(NULL) {
      for (const ListNode* i = list.begin(); i != list.end(); i = i->next()) {
        this->pushFront(i->data);
      }
      this->reverse();
    }

    void clear() {
      while (!this->empty()) this->popFront();
    }

    bool empty() {
      return !this->_head;
    }

    void pushFront(const T& data) {
      ListNode* p = new ListNode(data, this->_head);
      this->_head = p;
      this->_length++;
    }

    void popFront() {
      if (this->_head) {
        ListNode* p = this->_head;
        this->_head = this->_head->next;
        delete p;
        this->_length--;
      }
    }

    void insertAfter(ListNode* node, const T& data) {
      ListNode* p = new ListNode(data, node->next);
      node->next = p;
      this->_length++;
    }

    void eraseAfter(ListNode* node) {
      ListNode* p = node->next;
      if (p) {
        node->next = node->next->next;
        delete p;
        this->_length--;
      }
    }

    T& front() { return this->_head->data; }
    const T& front() const { return this->_head->data;   };

    ListNode* begin() { return this->_head; }
    ListNode* end() { return NULL; }

    uint16_t length() {
      return this->_length;
    }

  private:
    ListNode* _head;
    uint16_t _length;
};

#endif // LIST_H
