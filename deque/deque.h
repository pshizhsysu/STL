// Deque.h  
#ifndef DEQUE_H
#define DEQUE_H
  
#include <iterator>  
#include <type_traits>  
  
template<class T>  
struct Deque_iterator{  
public:  
    typedef std::random_access_iterator_tag iterator_category;  
    typedef T value_type;  
    typedef std::ptrdiff_t difference_type;   
    typedef T* pointer;  
    typedef T& reference;     
      
    Deque_iterator& operator++();  
    Deque_iterator operator++(int);  
    Deque_iterator& operator--();  
    Deque_iterator operator--(int);  
    Deque_iterator operator+(difference_type n) const;  
    Deque_iterator operator-(difference_type n) const;  
    difference_type operator-(const Deque_iterator& it) const;  
    Deque_iterator& operator+=(difference_type n);  
    Deque_iterator& operator-=(difference_type n);  
    T& operator*();  
    T* operator->();  
    bool operator==(const Deque_iterator& it) const;  
    bool operator!=(const Deque_iterator& it) const;  
    bool operator<(const Deque_iterator& it) const;  
    bool operator<=(const Deque_iterator& it) const;  
    bool operator>(const Deque_iterator& it) const;  
    bool operator>=(const Deque_iterator& it) const;  
  
    void set_node(T** node);  
    std::size_t buffer_size() const;  
      
    T *cur;       
    T *first;     
    T *last;    // pointing to the last address, not past the last  
    T **node;     
};  
  
template<class T>  
struct Deque_const_iterator{  
public:  
    typedef std::random_access_iterator_tag iterator_category;  
    typedef T value_type;  
    typedef std::ptrdiff_t difference_type;   
    typedef const T* pointer;  
    typedef const T& reference;   
      
    Deque_const_iterator();  
    Deque_const_iterator(const Deque_iterator<T>&);  
      
    Deque_const_iterator& operator++();  
    Deque_const_iterator operator++(int);  
    Deque_const_iterator& operator--();  
    Deque_const_iterator operator--(int);  
    Deque_const_iterator operator+(difference_type n) const;  
    Deque_const_iterator operator-(difference_type n) const;  
    difference_type operator-(const Deque_const_iterator& it) const;  
    Deque_const_iterator& operator+=(difference_type n);  
    Deque_const_iterator& operator-=(difference_type n);  
    const T& operator*();  
    const T* operator->();  
    bool operator==(const Deque_const_iterator& it) const;  
    bool operator!=(const Deque_const_iterator& it) const;  
    bool operator<(const Deque_const_iterator& it) const;  
    bool operator<=(const Deque_const_iterator& it) const;  
    bool operator>(const Deque_const_iterator& it) const;  
    bool operator>=(const Deque_const_iterator& it) const;  
  
    void set_node(T** node);  
    std::size_t buffer_size() const;  
      
    const T *cur;         
    T *first;     
    T *last;    // pointing to the last address, not past the last  
    T **node;     
};  
  
template<class T, class Allocator = std::allocator<T> >  
class Deque{  
public:  
    typedef T                           value_type;  
    typedef Allocator                   allocator_type;  
    typedef std::size_t                 size_type;    
    typedef std::ptrdiff_t              difference_type;  
    typedef T&                          reference;  
    typedef const T&                    const_reference;  
    typedef typename Allocator::pointer         pointer;  
    typedef typename Allocator::const_pointer   const_pointer;  
    typedef Deque_iterator<T>             iterator;  
    typedef Deque_const_iterator<T>       const_iterator;  
    typedef std::reverse_iterator<iterator>       reverse_iterator;  
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;  
    typedef typename Allocator::template rebind<T*>::other    map_allocator_type;   
      
    // Member functions  
    explicit Deque(const Allocator& alloc = Allocator());  
    Deque(const Deque& other);  
    explicit Deque(size_type count, const T& value = T(), const Allocator& alloc = Allocator());  
    template<class InputIterator>  
    Deque(InputIterator first, InputIterator last);  
    ~Deque();  
    Deque& operator=(const Deque& other);  
    void assign(size_type count, const T& value);  
    template<class InputIterator>  
    void assign(InputIterator first, InputIterator last);  
    allocator_type get_allocator() const;  
      
    // Element access  
    reference at(size_type index);  
    const_reference at(size_type index) const;  
    reference operator[](size_type index);  
    const_reference operator[](size_type index) const;  
    reference front();  
    const_reference front() const;  
    reference back();  
    const_reference back() const;  
          
    // Iterator  
    iterator begin();  
    const_iterator begin() const;  
    iterator end();  
    const_iterator end() const;  
    reverse_iterator rbegin();  
    const_reverse_iterator rbegin() const;  
    reverse_iterator rend();  
    const_reverse_iterator rend() const;  
      
    // Capacity  
    bool empty() const;  
    size_type size() const;  
    size_type max_size() const;  
      
    // Modifiers  
    void push_back(const T& value);  
    void push_front(const T& value);  
    void insert(iterator pos, const T& value);  
    void insert(iterator pos, size_type count, const T& value);  
    template<class InputIterator>  
    void insert(iterator pos, InputIterator first, InputIterator last);  
    void erase(iterator pos);  
    void erase(iterator first, iterator last);  
    void pop_back();  
    void pop_front();  
    void clear();  
    void resize(size_type count, T value = T());  
    void swap(Deque& other);  
      
    void display();  
    void display_configuration();  
    // auxiliary functions  
protected:  
    size_type buffer_size() const;  
    void initially_allocate_Deque_with_count_elements(size_type count);  
    void initialize_with_count_elements(size_type count, const T& value, std::true_type);  
    template<class InputIterator>  
    void initialize_with_count_elements(InputIterator first, InputIterator last, std::false_type);  
    void destroy(iterator first, iterator last);  
    void deallocate_Deque();  
    void assign_aux(size_type count, const T& value, std::true_type);  
    template<class InputIterator>  
    void assign_aux(InputIterator first, InputIterator last, std::false_type);  
    void insert_aux(iterator pos, size_type count, const T& value, std::true_type);  
    template<class InputIterator>  
    void insert_aux(iterator pos, InputIterator first, InputIterator last, std::false_type);  
  
      
private:  
    Allocator allocator;  
    map_allocator_type map_allocator;  
      
private:  
    size_t map_size;      
    T** map;  
    iterator start;     // start.first,start.cur:first element; start.last:last+1 element; start.node:  
    iterator finish;    // past the last  
};

#endif
