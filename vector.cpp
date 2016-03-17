
#ifndef VECTOR_CPP
#define VECTOR_CPP

// Vector.cpp  
#include "Vector.h"  
#include <algorithm>  
#include <iterator>  

template<class T, class Allocator>  
Vector<T, Allocator>::Vector()  
{  
    initialize_to_null();  
}  
  
template<class T, class Allocator>  
Vector<T, Allocator>::Vector(const Vector& other)  
{     
    if(other.empty())  
        initialize_to_null();  
    else  
    {  
        start = get_allocator().allocate(other.capacity());  
        finish = start + other.size();  
        end_of_storage = start + other.capacity();  
        std::uninitialized_copy(other.begin(), other.end(), start);  
    }  
}  
  
template<class T, class Allocator>  
Vector<T, Allocator>::~Vector()  
{  
    clear();  
    deallocate();  
}  
  
template<class T, class Allocator>  
Vector<T, Allocator>&   
Vector<T, Allocator>::operator=(const Vector& other)  
{  
    clear();  
    deallocate();  
    start = get_allocator().allocate(other.capacity());  
    finish = start + other.size();  
    end_of_storage = start + other.capacity();  
    std::uninitialized_copy(other.begin(), other.end(), start);  
    return *this;  
}  
  
template<class T, class Allocator>  
void Vector<T, Allocator>::assign(size_type count, const_reference value)  
{  
    assign_aux(count, value, std::true_type());  
}  
  
template<class T, class Allocator>  
template<class InputIterator>  
void Vector<T, Allocator>::assign(InputIterator first, InputIterator last)  
{  
    typedef std::integral_constant<bool,std::is_integral<InputIterator>::value> type;   
    assign_aux(first, last, type());  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::allocator_type   
Vector<T, Allocator>::get_allocator() const  
{  
    return typename Vector<T, Allocator>::allocator_type();  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::reference   
Vector<T, Allocator>::at(size_type index)  
{  
    return *(begin() + index);  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::const_reference   
Vector<T, Allocator>::at(size_type index) const  
{  
    return *(begin() + index);  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::reference   
Vector<T, Allocator>::operator[](size_type index)  
{  
    return *(begin() + index);  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::const_reference   
Vector<T, Allocator>::operator[](size_type index) const  
{  
    return *(begin() + index);  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::reference Vector<T, Allocator>::front()  
{  
    return *begin();  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::const_reference   
Vector<T, Allocator>::front() const  
{  
    return *begin();  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::reference Vector<T, Allocator>::back()  
{  
    return *(begin() + size() - 1);  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::const_reference   
Vector<T, Allocator>::back() const  
{  
    return *(begin() + size() - 1);  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::iterator   
Vector<T, Allocator>::begin()  
{  
    return start;  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::const_iterator   
Vector<T, Allocator>::begin() const  
{  
    return start;  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::iterator   
Vector<T, Allocator>::end()  
{  
    return finish;  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::const_iterator   
Vector<T, Allocator>::end() const  
{  
    return finish;  
}  
  
// is following implement right ?  
template<class T, class Allocator>  
typename Vector<T, Allocator>::reverse_iterator   
Vector<T, Allocator>::rbegin()  
{  
    return reverse_iterator(end());  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::const_reverse_iterator   
Vector<T, Allocator>::rbegin() const  
{  
    return reverse_iterator(end());  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::reverse_iterator   
Vector<T, Allocator>::rend()  
{  
    return reverse_iterator(begin());  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::const_reverse_iterator   
Vector<T, Allocator>::rend() const  
{  
    return reverse_iterator(begin());  
}  
  
template<class T, class Allocator>  
bool Vector<T, Allocator>::empty() const  
{  
    return (begin() == end());  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::size_type   
Vector<T, Allocator>::size() const  
{  
    return (end() - begin());  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::size_type   
Vector<T, Allocator>::capacity() const  
{  
    return (end_of_storage - start);  
}  
  
// is following implement right ?  
template<class T, class Allocator>  
typename Vector<T, Allocator>::size_type   
Vector<T, Allocator>::max_size() const  
{  
    return size_type(-1) / sizeof(value_type);  
}  
  
// ? 浅拷贝是否效率会更高  
//   
template<class T, class Allocator>  
void Vector<T, Allocator>::reserve(size_type new_cap)  
{  
    if(new_cap > capacity())  
    {  
        iterator nstart = get_allocator().allocate(new_cap); // allocate() return type of pointer  
        iterator nfinish = nstart + size();  
        iterator nend_of_storage = nstart + new_cap;  
        std::uninitialized_copy(start, finish, nstart);  
        clear();  
        deallocate();  
        start = nstart;  
        finish = nfinish;  
        end_of_storage = nend_of_storage;         
    }     
}  
  
template<class T, class Allocator>  
void Vector<T, Allocator>::push_back(const_reference value)  
{  
    if(capacity() > size())  
    {  
        get_allocator().construct(end(), value);  
        finish++;  
    }  
    else  
    {         
        size_type new_cap = (capacity() == 0 ? 1 : 2 * capacity());  
        //std::cout << (new_cap == 1 ? "first time\n" : "other\n");  
        reserve(new_cap);  
        get_allocator().construct(end(), value);  
        finish++;  
    }  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::iterator  
Vector<T, Allocator>::insert(iterator pos, const_reference value)  
{  
    if(capacity() > size())  
    {  
        get_allocator().construct(&*end(), back());  
        finish++;  
        std::copy_backward(pos, end() - 2, end() - 1);  
        *pos = value;  
        return pos;  
    }   
    else  
    {  
        size_type new_cap = (capacity() == 0 ? 1 : 2 * capacity());  
        iterator nstart = get_allocator().allocate(new_cap);  
        iterator nfinish, npos;  
        nfinish = std::uninitialized_copy(start, pos, nstart);  
        npos = nfinish;  
        get_allocator().construct(nfinish, value);  
        ++nfinish;  
        nfinish = std::uninitialized_copy(pos, end(), nfinish);  
        clear();  
        deallocate();  
        start = nstart;  
        finish = nfinish;  
        end_of_storage = start + new_cap;  
        return npos;  
    }  
}  
  
// boundary conditions: 1.capacity() == 0  2.pos == end()  
template<class T, class Allocator>  
template<class InputIterator>  
void Vector<T, Allocator>::insert(iterator pos, InputIterator first, InputIterator last)  
{     
    // is_integral is in type_traits since c++11  
    // so you may compile this file using 'gcc -std=c++11 source.cpp'  
    typedef std::integral_constant<bool, std::is_integral<InputIterator>::value> type;  
    insert_aux(pos, first, last, type());     
}  
  
// boundary conditions: 1.count == 0  2.capacity() == 0  
template<class T, class Allocator>  
void Vector<T, Allocator>::insert(iterator pos, size_type count, const_reference value)  
{     
    insert_aux(pos, count, value, std::true_type());  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::iterator  
Vector<T, Allocator>::erase(iterator pos)  
{  
    if(pos >= finish || pos < start)  
        throw 1;  
    std::copy(pos + 1, finish, pos);  
    get_allocator().destroy(finish);  
    finish--;  
    return pos;  
}  
  
template<class T, class Allocator>  
typename Vector<T, Allocator>::iterator  
Vector<T, Allocator>::erase(iterator first, iterator last)  
{  
    if(first == last)  
        return first;  
    std::copy(last, finish, first);  
    destroy(finish - (last - first), finish);  
    finish = finish - (last - first);  
    return first;  
}  
  
template<class T, class Allocator>  
void Vector<T, Allocator>::pop_back()  
{  
    if(empty())  
        return;  
    get_allocator().destroy(finish);  
    finish--;  
}  
  
template<class T, class Allocator>  
void Vector<T, Allocator>::clear()  
{  
    destroy(start, finish);  
    finish = start;  
}  
  
template<class T, class Allocator>  
void Vector<T, Allocator>::resize(size_type count, value_type value)  
{  
    if(size() >= count)  
        erase(start + count, finish);  
    else  
        insert(finish, count - size(), value);  
}  
  
template<class T, class Allocator>  
void Vector<T, Allocator>::swap(Vector& other)  
{  
    iterator tstart = start;  
    iterator tfinish = finish;  
    iterator tend_of_storage = end_of_storage;  
    start = other.start;  
    finish = other.finish;  
    end_of_storage = other.end_of_storage;  
    other.start = tstart;  
    other.finish = tfinish;  
    other.end_of_storage = tend_of_storage;  
}  
  
template<class T, class Allocator>  
void Vector<T, Allocator>::display()  
{  
    iterator it;  
    for(it = start; it != finish; it++)  
        std::cout << *it << " ";  
    std::cout << std::endl;  
}  
  
/* -------------- auxiliary functions ------------------- */  
template<class T, class Allocator>  
void Vector<T, Allocator>::initialize_to_null()  
{  
    start = finish = end_of_storage = 0;  
}  
  
template<class T, class Allocator>  
void Vector<T, Allocator>::destroy(iterator first, iterator last)  
{  
    iterator it;  
    for(it = first; it != last; ++it)  
        get_allocator().destroy(&*it);    
}  
  
template<class T, class Allocator>  
void Vector<T, Allocator>::deallocate()  
{  
    if(start != 0)  
    {  
        get_allocator().deallocate(start,1);  
        initialize_to_null();  
    }  
}  
  
template<class T, class Allocator>  
void Vector<T, Allocator>::insert_aux(iterator pos, size_type count, const_reference value, std::true_type)  
{  
    if(count == 0)  
        return;  
    if(capacity() >= size() + count)   
    {  
        std::uninitialized_copy(finish - count, finish, finish);          
        std::copy_backward(pos, finish - count, finish);  
        std::fill(pos, pos + count, value);  
        finish = finish + count;          
    }   
    else  
    {  
        size_type old_size = size();  
        size_type new_cap = capacity() * 2 + count;  
        iterator nstart = get_allocator().allocate(new_cap);          
        std::uninitialized_copy(start, pos, nstart);          
        std::uninitialized_fill_n(nstart + (pos - start), count, value);  
        std::uninitialized_copy(pos, finish, nstart + (pos - start + count));  
        clear();  
        deallocate();  
        start = nstart;  
        finish = start + (old_size + count);  
        end_of_storage = start + new_cap;         
    }  
}  
  
template<class T, class Allocator>  
template<class InputIterator>  
void Vector<T, Allocator>::insert_aux(iterator pos, InputIterator first, InputIterator last, std::false_type)  
{  
    size_type count = std::distance(first, last);  
    if(capacity() >= size() + count)  
    {  
        std::uninitialized_copy(finish - count, finish, finish);  
        std::copy_backward(pos, finish - count, finish);  
        std::copy(first, last, pos);  
        finish = finish + count;  
    }  
    else  
    {  
        size_type new_cap = capacity() * 2 + count;  
        iterator nstart = get_allocator().allocate(new_cap);  
        iterator nfinish;  
        nfinish = std::uninitialized_copy(start, pos, nstart);  
        nfinish = std::uninitialized_copy(first, last, nfinish);  
        nfinish = std::uninitialized_copy(pos, finish, nfinish);  
        clear();  
        deallocate();  
        start = nstart;  
        finish = nfinish;  
        end_of_storage = start + new_cap;  
    }  
}  
  
template<class T, class Allocator>  
void Vector<T, Allocator>::assign_aux(size_type count, const_reference value, std::true_type)  
{  
    clear();  
    deallocate();  
    start = get_allocator().allocate(count);  
    finish = start + count;  
    end_of_storage = finish;  
    std::uninitialized_fill_n(start, count, value);  
}  
  
template<class T, class Allocator>  
template<class InputIterator>  
void Vector<T, Allocator>::assign_aux(InputIterator first, InputIterator last, std::false_type)  
{  
    clear();  
    deallocate();  
    size_type count = std::distance(first, last);  
    start = get_allocator().allocate(count);  
    std::uninitialized_copy(first, last, start);  
    finish = start + count;  
    end_of_storage = finish;  
}  

#endif
