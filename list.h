// List.h  
#ifndef LIST_H
#define LIST_H

#include <iterator>  
#include <type_traits>  
  
template<class T>  
struct node{  
    node* next;  
    node* pre;  
    T data;  
};  
  
template<class T>  
struct List_iterator{  
    typedef std::bidirectional_iterator_tag iterator_category;  
    typedef T value_type;  
    typedef std::ptrdiff_t difference_type;  
    typedef T* pointer;  
    typedef T& reference;     
      
    List_iterator();  
    List_iterator(node<T>*);    
    List_iterator& operator++();  
    List_iterator operator++(int);  
    List_iterator& operator--();  
    List_iterator operator--(int);  
    bool operator==(const List_iterator& other) const;  
    bool operator!=(const List_iterator& other) const;  
    reference operator*() const;  
    pointer operator->() const;  
          
    node<T>* ptr;  
};  
  
template<class T>  
struct List_iterator<const T>{  
    typedef std::bidirectional_iterator_tag iterator_category;  
    typedef T value_type;  
    typedef std::ptrdiff_t difference_type;  
    typedef const T* pointer;  
    typedef const T& reference;   
      
    List_iterator();  
    List_iterator(node<T>*);    
    List_iterator(node<const T>*);  
    List_iterator(const List_iterator<T>&); // change iterator to const_iterator  
    List_iterator& operator++();  
    List_iterator operator++(int);  
    List_iterator& operator--();  
    List_iterator operator--(int);  
    bool operator==(const List_iterator& other) const;  
    bool operator!=(const List_iterator& other) const;  
    reference operator*() const;  
    pointer operator->() const;  
          
    node<const T>* ptr;  
};  
  
template<class T, class Allocator = std::allocator<T> >  
class List{  
public:  
    typedef T                           value_type;  
    typedef Allocator                   allocator_type;  
    typedef std::size_t                 size_type;  
    typedef std::ptrdiff_t              difference_type;  
    typedef typename Allocator::reference       reference;  
    typedef typename Allocator::const_reference     const_reference;  
    typedef typename Allocator::pointer             pointer;  
    typedef typename Allocator::const_pointer   const_pointer;  
    typedef List_iterator<T>          iterator;  
    typedef List_iterator<const T>        const_iterator;  
    typedef std::reverse_iterator<iterator>       reverse_iterator;  
    typedef std::reverse_iterator<const_iterator>     const_reverse_iterator;  
      
    // Member functions  
    explicit List(const Allocator& alloc = Allocator());  
    List(const List& other);  
    explicit List(size_type count, const T& = T(), const Allocator& alloc = Allocator());  
    template<class InputIterator>  
    List(InputIterator first, InputIterator last, const Allocator& alloc = Allocator());  
    ~List();  
    List& operator=(const List& other);  
    void assign(size_type count, const T& value);  
    template<class InputIterator>  
    void assign(InputIterator first, InputIterator last);  
    allocator_type get_allocator() const;  
      
    // Element Access  
    reference front();  
    const_reference front() const;  
    reference back();  
    const_reference back() const;  
      
    // Iterators  
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
      
    // Modifier  
    void push_back(const T& value);  
    void push_front(const T& value);  
    void insert(iterator pos, const T& value);    
    void insert(iterator pos, size_type count, const T& value);  
    template<class InputIterator>  
    void insert(iterator pos, InputIterator first, InputIterator last);  
    void pop_back();  
    void pop_front();  
    void erase(iterator pos);  
    void erase(iterator first, iterator last);  
    void clear();  
    void resize(size_type count, T value = T());  
    void swap(List& other);  
      
    // Operations  
    void merge(List& other);  
    void splice(const_iterator pos, List& other);  
    void splice(const_iterator pos, List& other, const_iterator it);  
    void splice(const_iterator pos, List& other, const_iterator first, const_iterator last);  
    void remove(const T&);  
    void reverse();  
    void unique();  
    void sort();  
      
    void display();   
      
protected:  
    typedef typename Allocator::template rebind<node<T> >::other node_allocator_type;  
    void initialize_List();   
    node<T>* allocate_n_node(size_type n);  
    void insert_aux(iterator pos, size_type count, const T& value, std::true_type);  
    template<class InputIterator>  
    void insert_aux(iterator pos, InputIterator first, InputIterator last, std::false_type);  
    void destroy(iterator first, iterator last);  
    void deallocate(iterator first, iterator last);  
    void assign_aux(size_type count, const T& value, std::true_type);  
    template<class InputIterator>   
    void assign_aux(InputIterator first, InputIterator last, std::false_type);  
    void transfer(const_iterator pos, const_iterator first, const_iterator last);  
      
    template<class BidirectionalIterator>  
    void quick_sort(BidirectionalIterator front, BidirectionalIterator back);  
    template<class BidirectionalIterator>  
    BidirectionalIterator partition(BidirectionalIterator front, BidirectionalIterator back);  
    template<class Iterator>  
    void swap(Iterator first, Iterator second);  
private:  
    node<T>* head;  
      
};  

#endif
