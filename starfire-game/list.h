#ifndef LIST_H
#define LIST_H

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

    void destroy() {
      while (!this->empty()) {
        if (this->_head) {
          ListNode* p = this->_head;
          this->_head = this->_head->next;
          delete p->data;
          delete p;
          this->_length--;
        }
      }
    }

    void destroy(ListNode* node) {
      if (this->empty()) return;
      ListNode* temp = this->_head;

      if (this->_head == node) {
        this->_head = this->_head->next;
        delete temp->data;
        delete temp;
        this->_length--;
        return;
      }

      for (const ListNode* i = this->begin(); i != NULL && i != node; i = i->next) {
        temp = temp->next;
      }

      if (temp == NULL || temp->next == NULL) return;

      ListNode* next = temp->next->next;

      delete temp->next->data;
      delete temp->next;
      temp->next = next;
      this->_length--;
    }

    void destroy(T data) {
      if (this->empty()) return;
      ListNode* temp = this->_head;

      if (this->_head->data == data) {
        this->_head = this->_head->next;
        delete temp->data;
        delete temp;
        this->_length--;
        return;
      }

      for (const ListNode* i = this->begin(); i != NULL && i->data != data; i = i->next) {
        temp = temp->next;
      }

      if (temp == NULL || temp->next == NULL) return;

      ListNode* next = temp->next->next;

      delete temp->data;
      delete temp->next;
      temp->next = next;
      this->_length--;
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
