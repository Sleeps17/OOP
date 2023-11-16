#ifndef LIST
#define LIST

#include<memory>
#include<type_traits>

namespace lab {

template<class InputIt>
concept Iterable = std::forward_iterator<InputIt> || std::random_access_iterator<InputIt> || std::bidirectional_iterator<InputIt>;

template<class T>
struct Node {
    T data;
    Node<T>* next;
    Node() = default;
    Node(const T& _data): data(_data), next(nullptr) {}

    bool operator==(const Node<T>& other) {
        return data == other.data && next == other.next;
    }
};

template<class T, class Allocator = std::allocator<T>>
class forward_list {
  
  public:
    using value_type            = T;
    using allocator_type        = Allocator;
    using size_type             = size_t;

    using reference_type        = value_type&;
    using const_reference_type	= const value_type&;

    using pointer_type          = value_type*;
    using const_pointer_type    = const value_type*;


  private:
    Node<T>* createNode(const T& value) {
        
        Node<T>* newNode = std::allocator_traits<Allocator>::allocate(alloc, 1);
        std::allocator_traits<Allocator>::construct(alloc, newNode, value);
        
        return newNode;
    }

    Node<T>* createDefaultNode() {
        
        static_assert(std::is_default_constructible_v<T>);

        Node<T>* newNode = std::allocator_traits<Allocator>::allocate(alloc, 1);
        std::allocator_traits<Allocator>::construct(alloc, newNode, T());
        
        return newNode;
    }

    void destroyNode(Node<T>* node) {
        std::allocator_traits<Allocator>::destroy(alloc, node);
        std::allocator_traits<Allocator>::deallocate(alloc, node, 1);
    }

    Node<T>* head;
    size_type size;
    allocator_type alloc;

  public:
    class const_iterator {

      public:
        const Node<T>* node;

        using iterator_category     = std::forward_iterator_tag;
        using difference_type       = std::ptrdiff_t;
        using value_type            = const T;
        using pointer_type          = const T*;
        using reference_type        = const T&;

        const_iterator() = default;
        const_iterator(const Node<T>* ptr) : node(ptr) {}

        reference_type operator*() const {
            return node->data;
        }

        const_iterator& operator++() {
            node = node->next;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator copy = *this;
            ++(*this);
            return copy;
        }

        bool operator==(const const_iterator& other) const {
            return this->node == other.node;
        }

        bool operator!=(const const_iterator& other) const {
            return !(*this == other);
        }
    };

    class iterator {

      public:
        Node<T>* node;

        using iterator_category     = std::forward_iterator_tag;
        using difference_type       = std::ptrdiff_t;
        using value_type            = T;
        using pointer_type          = T*;
        using reference_type        = T&;

        iterator() = default;
        iterator(Node<T>* ptr): node(ptr) {}

        reference_type operator*() {
            return node -> data;
        }

        iterator& operator++() {
            this -> node = this -> node -> next;
            return *this;
        }

        iterator operator++(int) {
            auto copy = *this;
            ++(*this);
            return copy;
        }

        bool operator==(const iterator other) {
            return *(this -> node) == *(other.node);
        }
        bool operator!=(const iterator other) {
            return !(*this == other);
        }

        operator const_iterator() {
            return const_iterator(this -> node);
        }
    };

    // Конструкторы
    forward_list() = default;
    explicit forward_list(size_type _count, const T& _value, const allocator_type& _alloc = Allocator()): alloc(_alloc), head(nullptr), size(0) {

        for (size_type i = 0; i < _count; ++i) {
            Node<T>* newNode = createNode(_value);
            newNode->next = head;
            head = newNode;
        }

        size = _count;
    }
    explicit forward_list(const allocator_type& _alloc): alloc(_alloc), head(nullptr), size(0) {}  
    forward_list(size_type _count, const allocator_type& _alloc = Allocator()): alloc(_alloc), head(nullptr), size(0) {
        for (size_type i = 0; i < _count; ++i) {
            Node<T>* newNode = createDefaultNode();
            newNode->next = head;
            head = newNode;
        }

        size = _count;
    }
    template<Iterable InputIt>
    forward_list(InputIt first, InputIt last, const Allocator& _alloc = Allocator()) : alloc(_alloc), head(nullptr), size(0) {
        
        Node<T>* curr;
        size = std::distance(first, last);

        for (auto it = first; it != last; ++it) {
            auto newNode = createNode(*it);
            if (!head) {
                head = newNode;
                curr = head;
            } else {
                curr -> next = newNode;
                curr = curr -> next;
            }
        }
    }
    // ???
    forward_list(const forward_list<T, allocator_type>& other): head(nullptr), size(other.size), alloc(std::allocator_traits<Allocator>::select_on_container_copy_construction(other.alloc)) {

        head = nullptr;
        Node<T>* otherHead = other.head;
        Node<T>* curr = nullptr;
        while(otherHead != nullptr) {
            auto newNode = createNode(otherHead -> data);

            if(!head) {
                head = newNode;
                curr = head;
            } else {
                curr -> next = newNode;
                curr = curr -> next;
            }
            otherHead = otherHead -> next;
        }
    }
    // ???    
    forward_list(forward_list<T, allocator_type>&& other) noexcept: head(other.head), size(other.size), alloc(other.alloc) {
        other.head = nullptr;
        other.size = 0;
    }
    forward_list(const std::initializer_list<T>& init, const Allocator& _alloc = Allocator()): head(nullptr), size(0), alloc(std::allocator_traits<Allocator>::select_on_container_copy_construction(_alloc)) {
        size = init.size();

        Node<T>* curr;
        for(auto elem : init) {
            Node<T>* newNode = createNode(elem);

            if (head == nullptr) {
                head = newNode;
                curr = head;
            } else {
                curr -> next = newNode;
                curr = curr -> next;
            }
        }
    }

   ~forward_list() {    
        this -> clear();
        this -> size = 0;
    }

    forward_list<T, allocator_type>& operator=(const forward_list<T, allocator_type>& other) {
        this -> size = other.size;
        this -> alloc = std::allocator_traits<Allocator>::select_on_container_copy_construction(other.alloc);

        head = nullptr;
        Node<T>* otherNode = other.head;
        Node<T>* tail = nullptr;

        while (otherNode != nullptr) {
            Node<T>* newNode = createNode(otherNode->data);
            if (head == nullptr) {
                head = newNode;
            } else {
                tail->next = newNode;
            }
            tail = newNode;
            otherNode = otherNode->next;
        }
        return *this;
    }
    forward_list<T, allocator_type>& operator=(forward_list<T, allocator_type>&& other) noexcept {
        this -> head = other.head;
        this -> size = other.size;
        this -> alloc = other.alloc;

        other.head = nullptr;
        other.size = 0;

        return *this;
    }
    
    void assign(size_type count, const T& value) {
        this -> clear();
        *this = forward_list<T, allocator_type>(count, value);
    }
    template<Iterable InputIt>
    void assign(InputIt first, InputIt last) {
        this -> clear();
        *this = forward_list<T, allocator_type>(first, last, allocator_type());
    }
    void assign(const std::initializer_list<T>& ilist ) {
        this -> clear();
        *this = forward_list<T, allocator_type>(ilist, allocator_type());
    }
    void clear() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            std::allocator_traits<Allocator>::destroy(alloc, temp);
            std::allocator_traits<Allocator>::deallocate(alloc, temp, 1);
        }
    }
    
    bool empty() const noexcept {
        return size == 0;
    }
    size_type lenght() const noexcept {
        return size;
    }    

    iterator begin() {
        return iterator(head);
    }
    iterator end() {
        return iterator(nullptr);
    }
    const_iterator begin() const {
        return const_iterator(head);
    }
    const_iterator end() const {
        return const_iterator(nullptr);
    }
    const_iterator cbegin() {
        return const_iterator(head);
    }
    const_iterator cend() {
        return const_iterator(nullptr);
    }
    iterator before_begin() noexcept {
        Node<T>* before = createDefaultNode();
        before -> next = head;
        return iterator(before);
    }
    const_iterator before_begin() const noexcept {
        auto before = createDefaultNode();
        before -> next = head;
        return const_iterator(before);
    }
    const_iterator cbefore_begin() const noexcept {
        auto before = createDefaultNode();
        before -> next = head;
        return const_iterator(before);
    }

    iterator insert_after(const iterator pos, const T& value) {

        Node<T>* newNode = createNode(value);
        size++;

        if (pos.node -> next == head) {
            newNode -> next = head;
            head = newNode;
        } else {
            newNode -> next = pos.node -> next;
            pos.node -> next = newNode;
        }
        
        return iterator(newNode);
    }
    iterator insert_after(const iterator pos, T&& value ) {
        Node<T>* newNode = createNode(value);
        size++;

        if (pos.node -> next == head) {
            newNode -> next = head;
            head = newNode;
        } else {
            newNode -> next = pos.node -> next;
            pos.node -> next = newNode;
        }
        
        return iterator(newNode);

    }
    iterator insert_after(const iterator pos, size_type count, const T& value ) {

        size += count;
        iterator curr = pos;
        for(size_type i = 0; i < count; ++i) {

            curr = insert_after(curr, value);
        }

        return curr;
    }
    template<Iterable InputIt>
    iterator insert_after(const iterator pos, InputIt first, InputIt last) {

        size += std::distance(first, last);

        iterator curr = pos;
        for(auto it = first; it != last; ++it) {
            curr = insert_after(curr, *it);
        }

        return curr;
    }
    iterator insert_after(const iterator pos, std::initializer_list<T> ilist) {

        size += ilist.size();

        iterator curr = pos;
        for(auto it = ilist.begin(); it != ilist.end(); ++it) {
            curr = insert_after(curr, *it);
        }

        return curr;
    }

    iterator erase_after(const iterator pos) {
        size--;

        if (pos.node -> next == head) {
            Node<T>* tmp = head;
            head = head -> next;
            destroyNode(tmp);
        } else {
            Node<T>* tmp = pos.node -> next;
            pos.node -> next = tmp->next;
            destroyNode(tmp);
        }
        
        return iterator(pos.node -> next);
    }
    iterator erase_after(const iterator first, const iterator last) {
        
        if (first.node == last.node) {
            return last;
        }

        iterator curr = first;
        while(curr.node -> next != last.node) {
            curr = erase_after(curr);
        }

        return last;
    }

    void push_front(const T& value) {
        this -> insert_after(this -> before_begin(), value);
    }
    void push_front(T&& value) {
        this -> insert_after(this -> before_begin(), value);
    }

    void pop_front() {
        this -> erase_after(this -> before_begin());
    }
};

}
#endif