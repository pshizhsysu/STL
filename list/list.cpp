
#ifndef LIST_CPP
#define LIST_CPP
// List_iterator.cpp  
  
#include "List.h"  
#include <cstdlib>  
  
  
/* -------------------- List_iterator ------------------------- */  
template<class T>  
List_iterator<T>::List_iterator()  
{  
    ptr = 0;  
}  
  
template<class T>  
List_iterator<T>::List_iterator(node<T>* ptr1)  
{  
    ptr = ptr1;  
}  
  
template<class T>  
List_iterator<T>& List_iterator<T>::operator++()  
{  
    ptr = ptr -> next;  
    return *this;  
}  
  
template<class T>  
List_iterator<T> List_iterator<T>::operator++(int)  
{  
    List_iterator tmp(*this);  
    ptr = ptr -> next;  
    return tmp;  
}  
  
template<class T>  
List_iterator<T>& List_iterator<T>::operator--()  
{  
    ptr = ptr -> pre;  
    return *this;  
}  
  
template<class T>  
List_iterator<T> List_iterator<T>::operator--(int)  
{  
    List_iterator tmp(*this);  
    ptr = ptr -> pre;  
    return tmp;  
}  
  
template<class T>  
bool List_iterator<T>::operator==(const List_iterator& other) const  
{  
    return (ptr == other.ptr);  
}  
  
template<class T>  
bool List_iterator<T>::operator!=(const List_iterator& other) const  
{  
    return (ptr != other.ptr);  
}  
  
template<class T>  
typename List_iterator<T>::reference  
List_iterator<T>::operator*() const  
{  
    return ptr -> data;  
}  
  
template<class T>  
typename List_iterator<T>::pointer  
List_iterator<T>::operator->() const  
{  
    return &(ptr -> data);  
}  
  
  
/* ------------------------- List_iterator<const T> -------------------*/  
template<class T>  
List_iterator<const T>::List_iterator()  
{  
    ptr = 0;  
}  
  
template<class T>  
List_iterator<const T>::List_iterator(node<T>* ptr1)  
{  
    ptr = (node<const T>*)ptr1;  
}  
  
template<class T>  
List_iterator<const T>::List_iterator(node<const T>* ptr1)  
{  
    ptr = ptr1;  
}  
  
template<class T>  
List_iterator<const T>::List_iterator(const List_iterator<T>& it)  
{  
    ptr = (node<const T>*)it.ptr;  
}  
  
template<class T>  
List_iterator<const T>& List_iterator<const T>::operator++()  
{  
    ptr = ptr -> next;  
    return *this;  
}  
  
template<class T>  
List_iterator<const T> List_iterator<const T>::operator++(int)  
{  
    List_iterator tmp(*this);  
    ptr = ptr -> next;  
    return tmp;  
}  
  
template<class T>  
List_iterator<const T>& List_iterator<const T>::operator--()  
{  
    ptr = ptr -> pre;  
    return *this;  
}  
  
template<class T>  
List_iterator<const T> List_iterator<const T>::operator--(int)  
{  
    List_iterator tmp(*this);  
    ptr = ptr -> pre;  
    return tmp;  
}  
  
template<class T>  
bool List_iterator<const T>::operator==(const List_iterator& other) const  
{  
    return (ptr == other.ptr);  
}  
  
template<class T>  
bool List_iterator<const T>::operator!=(const List_iterator& other) const  
{  
    return (ptr != other.ptr);  
}  
  
template<class T>  
typename List_iterator<const T>::reference  
List_iterator<const T>::operator*() const  
{  
    return ptr -> data;  
}  
  
template<class T>  
typename List_iterator<const T>::pointer  
List_iterator<const T>::operator->() const  
{  
    return &(ptr -> data);  
}  
  
  
  
/* --------------------------- List --------------------------------*/  
template<class T, class Allocator>  
List<T, Allocator>::List(const Allocator& alloc)  
{  
    initialize_List();    
}  
  
template<class T, class Allocator>  
List<T, Allocator>::List(const List& other)  
{  
    initialize_List();  
    insert(end(), other.begin(), other.end());  
}  
  
template<class T, class Allocator>  
List<T, Allocator>::List(size_type count, const T& value, const Allocator& alloc)  
{  
    initialize_List();    
    insert(end(), count, value);      
}  
  
template<class T, class Allocator>  
template<class InputIterator>  
List<T, Allocator>::List(InputIterator first, InputIterator last, const Allocator& alloc)  
{  
    initialize_List();  
    insert(end(), first, last);  
}  
  
template<class T, class Allocator>  
List<T, Allocator>::~List()  
{  
    destroy(begin(), end());  
    deallocate(begin(), end());  
    node_allocator_type().deallocate(head, 1);    
}  
  
template<class T, class Allocator>  
List<T, Allocator>&  
List<T, Allocator>::operator=(const List& other)  
{  
    destroy(begin(), end());  
    deallocate(begin(), end());  
    insert(end(), other.begin(), other.end());  
    return *this;  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::assign(size_type count, const T& value)  
{  
    assign_aux(count, value, std::true_type());  
}  
  
template<class T, class Allocator>  
template<class InputIterator>  
void List<T, Allocator>::assign(InputIterator first, InputIterator last)  
{  
    typedef std::integral_constant<bool, std::is_integral<InputIterator>::value> type;  
    assign_aux(first, last, type());  
}  
  
template<class T, class Allocator>  
typename List<T, Allocator>::allocator_type  
List<T, Allocator>::get_allocator() const  
{  
    return Allocator();  
}  
  
// Member Access  
template<class T, class Allocator>  
typename List<T, Allocator>::reference  
List<T, Allocator>::front()  
{  
    return head -> next -> data;  
}  
  
template<class T, class Allocator>  
typename List<T, Allocator>::const_reference  
List<T, Allocator>::front() const  
{  
    return head -> next -> data;  
}  
  
template<class T, class Allocator>  
typename List<T, Allocator>::reference  
List<T, Allocator>::back()  
{  
    return head -> pre -> data;  
}  
  
template<class T, class Allocator>  
typename List<T, Allocator>::const_reference  
List<T, Allocator>::back() const  
{  
    return head -> pre -> data;  
}  
  
// Iterators  
template<class T, class Allocator>  
typename List<T, Allocator>::iterator  
List<T, Allocator>::begin()  
{  
    return iterator(head -> next);  
}  
  
template<class T, class Allocator>  
typename List<T, Allocator>::const_iterator  
List<T, Allocator>::begin() const  
{  
    return const_iterator(head -> next);  
}  
  
template<class T, class Allocator>  
typename List<T, Allocator>::iterator  
List<T, Allocator>::end()  
{  
    return iterator(head);  
}  
  
template<class T, class Allocator>  
typename List<T, Allocator>::const_iterator  
List<T, Allocator>::end() const  
{  
    return const_iterator(head);      
}  
  
template<class T, class Allocator>  
typename List<T, Allocator>::reverse_iterator  
List<T, Allocator>::rbegin()  
{  
    std::cout << "rbegin()" << std::endl;  
    return reverse_iterator(end());   
}  
  
template<class T, class Allocator>  
typename List<T, Allocator>::const_reverse_iterator  
List<T, Allocator>::rbegin() const  
{  
    std::cout << "rbegin() const" << std::endl;  
    return const_reverse_iterator(end());     
}  
  
template<class T, class Allocator>  
typename List<T, Allocator>::reverse_iterator  
List<T, Allocator>::rend()  
{  
    return reverse_iterator(begin());     
}  
  
template<class T, class Allocator>  
typename List<T, Allocator>::const_reverse_iterator  
List<T, Allocator>::rend() const  
{  
    return const_reverse_iterator(begin());   
}  
  
// Capacity  
template<class T, class Allocator>  
bool List<T, Allocator>::empty() const  
{  
    return head -> next == head;  
}  
  
template<class T, class Allocator>  
typename List<T, Allocator>::size_type  
List<T, Allocator>::size() const  
{  
    return std::distance(begin(), end());  
}  
  
template<class T, class Allocator>  
typename List<T, Allocator>::size_type  
List<T, Allocator>::max_size() const  
{  
    return size_type(-1) / sizeof(node<T>);  
}  
  
// Modifier  
template<class T, class Allocator>  
void List<T, Allocator>::push_back(const T& value)  
{  
    insert_aux(end(), 1, value, std::true_type());  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::push_front(const T& value)  
{  
    insert_aux(begin(), 1, value, std::true_type());  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::insert(iterator pos, const T& value)  
{  
    insert_aux(pos, 1, value, std::true_type());  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::insert(iterator pos, size_type count, const T& value)  
{  
    insert_aux(pos, count, value, std::true_type());  
}  
  
template<class T, class Allocator>  
template<class InputIterator>  
void List<T, Allocator>::insert(iterator pos, InputIterator first, InputIterator last)  
{  
    typedef std::integral_constant<bool, std::is_integral<InputIterator>::value> type;  
    insert_aux(pos, first, last, type());  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::pop_back()  
{  
    erase(--end());  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::pop_front()  
{  
    erase(begin());  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::erase(iterator pos)  
{     
    Allocator().destroy(&*pos);   
    pos.ptr -> pre -> next = pos.ptr -> next;    
    pos.ptr -> next -> pre = pos.ptr -> pre;     
    node_allocator_type().deallocate(pos.ptr, 1);     
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::erase(iterator first, iterator last)  
{  
    destroy(first, last);  
    deallocate(first, last);  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::clear()  
{  
    destroy(begin(), end());  
    deallocate(begin(), end());  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::resize(size_type count, T value)  
{  
    if(size() >= count)  
        return;   
    insert_aux(end(), count - size(), value, std::true_type());  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::swap(List& other)  
{  
    node<T>* tmp = other.head;  
    other.head = head;  
    head = tmp;  
}  
  
// Operations  
template<class T, class Allocator>  
void List<T, Allocator>::merge(List& other)  
{  
    const_iterator pos = begin();  
    const_iterator first = other.begin();  
    const_iterator last = first;  
    while(pos != end() && last != other.end())  
    {  
        if(*last > *pos)  
        {  
            transfer(pos, first, last);  
            ++pos;  
            first = last;  
        }  
        else      
            ++last;   
    }     
    transfer(pos, first, other.end());  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::splice(const_iterator pos, List& other)  
{  
    if(this == &other)  
        return;  
    transfer(pos, other.begin(), other.end());  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::splice(const_iterator pos, List& other, const_iterator it)  
{  
    if(this == &other)  
        return;  
    const_iterator last = it;  
    last++;  
    transfer(pos, it, last);  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::splice(const_iterator pos, List& other, const_iterator first, const_iterator last)  
{  
    if(this == &other)  
        return;   
    transfer(pos, first, last);  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::remove(const T& value)  
{  
    iterator it, next;  
    it = begin();  
    while(it != end())  
    {  
        if(*it == value)  
        {  
            next = it;  
            next++;  
            erase(it);  
            it = next;  
        }  
        else  
            it++;  
    }  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::reverse()  
{  
    node<T> *cur, *tmp;  
    cur = head;  
    do  
    {  
        tmp = cur -> next;  
        cur -> next = cur -> pre;  
        cur -> pre = tmp;  
        cur = cur -> next;  
    }while(cur != head);  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::unique()  
{  
    iterator first, last;  
    first = begin();  
    last = ++begin();  
    while(last != end())  
    {  
        if(*first != *last)  
        {  
            iterator second = first;  
            second++;  
            erase(second, last);  
            first = last;  
        }  
        last++;  
    }  
    erase(++first, end());  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::sort()  
{  
    if(empty() || size() == 1)  
        return;  
    List carry;  
    List counter[64];  
    int fill = -1;    
    while(!empty())  
    {         
        carry.splice(carry.begin(), *this, begin());              
        int i;  
        for(i = 0; !counter[i].empty(); i++)                  
            carry.merge(counter[i]);              
        carry.swap(counter[i]);       
        if(fill + 1 == i)         
            fill++;               
    }  
    int i;  
    for(i = 1; i <= fill; i++)         
        counter[i].merge(counter[i - 1]);     
    swap(counter[fill]);  
}  
  
  
  
  
template<class T, class Allocator>  
void List<T, Allocator>::display()  
{  
    iterator it;  
    for(it = begin(); it != end(); ++it)  
        std::cout << *it << " ";  
    std::cout << std::endl;  
}  
  
/* ------------------- auxiliary functions ---------------------- */  
template<class T, class Allocator>  
void List<T, Allocator>::initialize_List()  
{  
    head = node_allocator_type().allocate(1);  
    head -> next = head;  
    head -> pre = head;  
}  
  
// requirement : n > 0  
template<class T, class Allocator>  
node<typename List<T, Allocator>::value_type>* // equals to node<T>*  
List<T, Allocator>::allocate_n_node(size_type n)  
{  
    node<T>** tptr = (node<T>**)malloc(sizeof(node<T>*) * n);  
    size_type i;  
    for(i = 0; i < n; i++)  
        tptr[i] = node_allocator_type().allocate(1);  
    for(i = 0; i < n; i++)  
    {  
        tptr[i] -> next = tptr[(i + 1 > n - 1) ? 0 : (i + 1)];  
        tptr[i] -> pre = tptr[((i < 1) ? (n - 1) : (i - 1))];       
    }  
    node<T>* retur = tptr[0];   
    free(tptr);  
    return retur;  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::insert_aux(iterator pos, size_type count, const T& value, std::true_type)  
{  
    if(count < 1)  
        return;  
    node<T>* thead = allocate_n_node(count);  
    node<T>* tail = thead -> pre;  
    pos.ptr -> pre -> next = thead;  
    tail -> next = pos.ptr;  
    thead -> pre = pos.ptr -> pre;  
    pos.ptr -> pre = tail;  
    std::uninitialized_fill(iterator(thead), pos, value);  
}  
  
template<class T, class Allocator>  
template<class InputIterator>  
void List<T, Allocator>::insert_aux(iterator pos, InputIterator first, InputIterator last, std::false_type)  
{  
    if(first == last)  
        return;   
    size_type count = std::distance(first, last);  
    node<T>* thead = allocate_n_node(count);    
    node<T>* tail = thead -> pre;    
    pos.ptr -> pre -> next = thead;  
    tail -> next = pos.ptr;  
    thead -> pre = pos.ptr -> pre;  
    pos.ptr -> pre = tail;  
    std::uninitialized_copy(first, last, iterator(thead));    
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::destroy(iterator first, iterator last)  
{  
    if(first == last)  
        return;  
    iterator it;  
    for(it = first; it != last; ++it)  
    {  
        Allocator().destroy(&*it);  
    }     
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::deallocate(iterator first, iterator last)  
{  
    if(first == last)  
        return;  
    first.ptr -> pre -> next = last.ptr;  
    last.ptr -> pre = first.ptr -> pre;  
    node<T>* to_be_free = first.ptr;  
    node<T>* next_free = to_be_free -> next;  
    while(to_be_free != last.ptr)  
    {  
        node_allocator_type().deallocate(to_be_free, 1);  
        to_be_free = next_free;  
        next_free = to_be_free -> next;  
    }  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::assign_aux(size_type count, const T& value, std::true_type)  
{  
    destroy(begin(), end());  
    deallocate(begin(), end());  
    insert_aux(end(), count, value, std::true_type());  
}  
  
template<class T, class Allocator>  
template<class InputIterator>  
void List<T, Allocator>::assign_aux(InputIterator first, InputIterator last, std::false_type)  
{  
    destroy(begin(), end());  
    deallocate(begin(), end());  
    insert_aux(end(), first, last, std::false_type());  
}  
  
template<class T, class Allocator>  
void List<T, Allocator>::transfer(const_iterator pos, const_iterator first, const_iterator last)  
{  
    if(first == last)  
        return;  
    node<const T>* tmp_ptr = pos.ptr -> pre;  
    pos.ptr -> pre = last.ptr -> pre;  
    pos.ptr -> pre -> next = pos.ptr;  
    last.ptr -> pre = first.ptr -> pre;  
    last.ptr -> pre -> next = last.ptr;  
    tmp_ptr -> next = first.ptr;  
    first.ptr -> pre = tmp_ptr;    
}  
  
template<class T, class Allocator>  
template<class BidirectionalIterator>  
void List<T, Allocator>::quick_sort(BidirectionalIterator front, BidirectionalIterator back)  
{  
    BidirectionalIterator pass_back = back;  
    if(front == back || front == ++pass_back)  
        return;  
    BidirectionalIterator pivot, nfront, nback;  
    pivot = partition(front, back);  
    nfront = pivot;  
    nfront++;  
    nback = pivot;  
    nback--;  
    this -> quick_sort(front, nback);  
    this -> quick_sort(nfront, back);  
}  
  
template<class T, class Allocator>  
template<class BidirectionalIterator>  
BidirectionalIterator List<T, Allocator>::partition(BidirectionalIterator front, BidirectionalIterator back)  
{  
    BidirectionalIterator cur, pivot;  
    cur = pivot = front;  
    while(cur != back)  
    {  
        if(*cur < *back)  
        {  
            swap(cur, pivot);  
            pivot++;  
        }  
        cur++;  
    }  
    this -> swap(pivot, back);  
    return pivot;  
}  
  
template<class T, class Allocator>  
template<class Iterator>  
void List<T, Allocator>::swap(Iterator first, Iterator second)  
{  
    typedef typename std::iterator_traits<Iterator>::value_type value_type;  
    value_type tmp;  
    tmp = *first;  
    *first = *second;  
    *second = tmp;  
}  

#endif