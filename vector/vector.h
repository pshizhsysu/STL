// Vector.h  
#ifndef VECOTR_H
#define VECTOR_H

#include <memory>  
#include <type_traits>  
  
template<class T, class Allocator = std::allocator<T> >  
class Vector{  
public:  
    typedef T                   value_type;  
    typedef Allocator           allocator_type;  
    typedef std::size_t         size_type;  
    typedef std::ptrdiff_t      difference_type;  
    typedef typename Allocator::reference       reference;  
    typedef typename Allocator::const_reference const_reference;      
    typedef typename Allocator::pointer         pointer;  
    typedef typename Allocator::const_pointer   const_pointer;  
    typedef value_type*         iterator;  
    typedef const value_type*   const_iterator;  
    typedef std::reverse_iterator<iterator> reverse_iterator;  
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;  
      
    /* Member functions */  
    Vector();  
    Vector(const Vector&);  
    ~Vector();  
    Vector& operator=(const Vector&);  
    void assign(size_type count, const_reference value);  
    template<class InputIterator>  
    void assign(InputIterator first, InputIterator last);  
    allocator_type get_allocator() const;  
      
    /* Element access */  
    reference at(size_type index);  
    const_reference at(size_type index) const;  
    reference operator[](size_type index);  
    const_reference operator[](size_type index) const;  
    reference front();  
    const_reference front() const;  
    reference back();  
    const_reference back() const;  
      
    /* Iterator */  
    iterator begin();  
    const_iterator begin() const;  
    iterator end();  
    const_iterator end() const;  
    reverse_iterator rbegin();  
    const_reverse_iterator rbegin() const;  
    reverse_iterator rend();  
    const_reverse_iterator rend() const;  
      
    /* Capacity */  
    bool empty() const;  
    size_type size() const;  
    size_type capacity() const;  
    size_type max_size() const;  
    void reserve(size_type new_cap);  
      
    /* Modifier */  
    void push_back(const_reference value);  
    iterator insert(iterator pos, const_reference value);  
    template<class InputIterator>  
    void insert(iterator pos, InputIterator first, InputIterator last);  
    void insert(iterator pos, size_type count, const_reference value);  
    iterator erase(iterator pos);   
    iterator erase(iterator first, iterator last);  
    void pop_back();      
    void clear();  
    void resize(size_type count, value_type value = value_type());  
    void swap(Vector& other);     
    // display() is not in c++ standard, it's only for testing  
    void display();  
protected:  
    /* auxiliary functions, not interfaces to user */  
    void initialize_to_null();  
    void destroy(iterator first, iterator last);  
    void deallocate();    
    void insert_aux(iterator pos, size_type count, const_reference value, std::true_type);  
    template<class InputIterator>  
    void insert_aux(iterator pos, InputIterator first, InputIterator last, std::false_type);  
    void assign_aux(size_type count, const_reference value, std::true_type);  
    template<class InputIterator>  
    void assign_aux(InputIterator first, InputIterator last, std::false_type);    
private:  
    iterator start;  
    iterator finish;  
    iterator end_of_storage;  
};  

#endif