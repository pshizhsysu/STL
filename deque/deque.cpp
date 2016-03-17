
#ifndef DEQUE_CPP
#define DEQUE_CPP

#define MAX 512
inline std::size_t buffer_size_of_T(std::size_t size_of_T)  
{  
    return size_of_T < MAX ? MAX / size_of_T : (std::size_t)1;     
}  
  
/* -------------------------- Deque_iterator ----------------------------*/  
template<class T>  
Deque_iterator<T>& Deque_iterator<T>::operator++()  
{  
    if(cur != last)   
        cur++;    
    else  
    {  
        set_node(node + 1);  
        cur = first;  
    }  
    return *this;  
}  
  
template<class T>  
Deque_iterator<T> Deque_iterator<T>::operator++(int)  
{  
    Deque_iterator tmp = *this;  
    ++(*this);  
    return tmp;  
}  
  
template<class T>  
Deque_iterator<T>& Deque_iterator<T>::operator--()  
{  
    if(cur != first)      
        cur--;    
    else  
    {  
        set_node(node - 1);  
        cur = last;  
    }  
    return *this;  
}  
  
template<class T>  
Deque_iterator<T> Deque_iterator<T>::operator--(int)  
{  
    Deque_iterator<T> tmp = *this;  
    --(*this);  
    return tmp;  
}  
  
template<class T>  
Deque_iterator<T> Deque_iterator<T>::operator+(difference_type n) const  
{  
    Deque_iterator tmp = *this;  
    return (tmp += n);  
}  
  
template<class T>  
Deque_iterator<T> Deque_iterator<T>::operator-(difference_type n) const  
{  
    Deque_iterator tmp = *this;  
    return (tmp -= n);  
}  
  
template<class T>  
typename Deque_iterator<T>::difference_type   
Deque_iterator<T>::operator-(const Deque_iterator& other) const  
{  
    return difference_type((node - other.node) * buffer_size() + (cur - first) - (other.cur - other.first));  
}  
  
template<class T>  
Deque_iterator<T>& Deque_iterator<T>::operator+=(difference_type n)  
{  
    difference_type last_offset = last - cur;  
    difference_type div = n / buffer_size();  
    difference_type remain = n % buffer_size();  
    if(remain > last_offset)  
    {  
        div++;  
        last_offset = buffer_size() - (remain - last_offset);  
    }  
    else  
        last_offset = last_offset - remain;  
    set_node(node + div);  
    cur = last - last_offset;  
    return *this;  
}  
  
template<class T>  
Deque_iterator<T>& Deque_iterator<T>::operator-=(difference_type n)  
{  
    difference_type first_offset = cur - first;  
    difference_type div = n / buffer_size();  
    difference_type remain = n % buffer_size();  
    if(remain > first_offset)  
    {  
        div++;  
        first_offset = buffer_size() - (remain - first_offset);  
    }  
    else  
        first_offset = first_offset - remain;  
    set_node(node - div);  
    cur = first + first_offset;  
    return *this;  
}  
  
template<class T>  
T& Deque_iterator<T>::operator*()  
{  
    return *cur;  
}  
  
template<class T>  
T* Deque_iterator<T>::operator->()  
{  
    return &*cur;  
}  
  
template<class T>  
bool Deque_iterator<T>::operator==(const Deque_iterator& it) const  
{  
    return (cur == it.cur);  
}  
  
template<class T>  
bool Deque_iterator<T>::operator!=(const Deque_iterator& it) const  
{  
    return (cur != it.cur);  
}  
  
template<class T>  
bool Deque_iterator<T>::operator<(const Deque_iterator& it) const  
{  
    return (int(*this - it) < 0);  
}  
  
template<class T>  
bool Deque_iterator<T>::operator>(const Deque_iterator& it) const  
{  
    return (int(*this - it) > 0);  
}  
  
template<class T>  
bool Deque_iterator<T>::operator<=(const Deque_iterator& it) const  
{  
    return (int(*this - it) <= 0);  
}  
  
template<class T>  
bool Deque_iterator<T>::operator>=(const Deque_iterator& it) const  
{  
    return (int(*this - it) >= 0);  
}  
  
template<class T>  
void Deque_iterator<T>::set_node(T** node)  
{  
    this->node = node;  
    first = *node;  
    last = first + buffer_size() - 1;  
}  
  
template<class T>  
std::size_t Deque_iterator<T>::buffer_size() const  
{  
//  return sizeof(T) < MAX ? MAX / sizeof(T) : (size_t)1;  
    return 4;  
}  
  
  
/* -------------------------- Deque_const_iterator ----------------------------*/  
  
  
template<class T>  
Deque_const_iterator<T>::Deque_const_iterator()  
{}  
  
template<class T>  
Deque_const_iterator<T>::Deque_const_iterator(const Deque_iterator<T>& it)  
{  
    first = it.first;  
    cur = it.cur;  
    last = it.last;  
    node = it.node;  
}  
  
template<class T>  
Deque_const_iterator<T>& Deque_const_iterator<T>::operator++()  
{  
    if(cur != last)   
        cur++;    
    else  
    {  
        set_node(node + 1);  
        cur = first;  
    }  
    return *this;  
}  
  
template<class T>  
Deque_const_iterator<T> Deque_const_iterator<T>::operator++(int)  
{  
    Deque_const_iterator tmp = *this;  
    ++(*this);  
    return tmp;  
}  
  
template<class T>  
Deque_const_iterator<T>& Deque_const_iterator<T>::operator--()  
{  
    if(cur != first)      
        cur--;    
    else  
    {  
        set_node(node - 1);  
        cur = last;  
    }  
    return *this;  
}  
  
template<class T>  
Deque_const_iterator<T> Deque_const_iterator<T>::operator--(int)  
{  
    Deque_const_iterator<T> tmp = *this;  
    --(*this);  
    return tmp;  
}  
  
template<class T>  
Deque_const_iterator<T> Deque_const_iterator<T>::operator+(difference_type n) const  
{  
    Deque_const_iterator tmp = *this;  
    return (tmp += n);  
}  
  
template<class T>  
Deque_const_iterator<T> Deque_const_iterator<T>::operator-(difference_type n) const  
{  
    Deque_const_iterator tmp = *this;  
    return (tmp -= n);  
}  
  
template<class T>  
typename Deque_const_iterator<T>::difference_type   
Deque_const_iterator<T>::operator-(const Deque_const_iterator& other) const  
{  
    return (node - other.node) * buffer_size() + (cur - first) - (other.cur - other.first);  
}  
  
template<class T>  
Deque_const_iterator<T>& Deque_const_iterator<T>::operator+=(difference_type n)  
{  
    difference_type last_offset = last - cur;  
    difference_type div = n / buffer_size();  
    difference_type remain = n % buffer_size();  
    if(remain > last_offset)  
    {  
        div++;  
        last_offset = buffer_size() - (remain - last_offset);  
    }  
    else  
        last_offset = last_offset - remain;  
    set_node(node + div);  
    cur = last - last_offset;  
    return *this;  
}  
  
template<class T>  
Deque_const_iterator<T>& Deque_const_iterator<T>::operator-=(difference_type n)  
{  
    difference_type first_offset = cur - first;  
    difference_type div = n / buffer_size();  
    difference_type remain = n % buffer_size();  
    if(remain > first_offset)  
    {  
        div++;  
        first_offset = buffer_size() - (remain - first_offset);  
    }  
    else  
        first_offset = first_offset - remain;  
    set_node(node - div);  
    cur = first + first_offset;  
    return *this;  
}  
  
template<class T>  
const T& Deque_const_iterator<T>::operator*()  
{  
    return *cur;  
}  
  
template<class T>  
const T* Deque_const_iterator<T>::operator->()  
{  
    return &*cur;  
}  
  
template<class T>  
bool Deque_const_iterator<T>::operator==(const Deque_const_iterator& it) const  
{  
    return (cur == it.cur);  
}  
  
template<class T>  
bool Deque_const_iterator<T>::operator!=(const Deque_const_iterator& it) const  
{  
    return (cur != it.cur);  
}  
  
template<class T>  
bool Deque_const_iterator<T>::operator<(const Deque_const_iterator& it) const  
{  
    return (int(*this - it) < 0);  
}  
  
template<class T>  
bool Deque_const_iterator<T>::operator>(const Deque_const_iterator& it) const  
{  
    return (int(*this - it) > 0);  
}  
  
template<class T>  
bool Deque_const_iterator<T>::operator<=(const Deque_const_iterator& it) const  
{  
    return (int(*this - it) <= 0);  
}  
  
template<class T>  
bool Deque_const_iterator<T>::operator>=(const Deque_const_iterator& it) const  
{  
    return (int(*this - it) >= 0);  
}  
  
template<class T>  
void Deque_const_iterator<T>::set_node(T** node)  
{  
    this->node = node;  
    first = *node;  
    last = first + buffer_size();  
}  
  
template<class T>  
std::size_t Deque_const_iterator<T>::buffer_size() const  
{  
//  return sizeof(T) < MAX ? MAX / sizeof(T) : (size_t)1;  
    return 4;  
}  
  
  
/* ----------------------------- Deque ---------------------------- */   
  
// Member functions  
template<class T, class Allocator>  
Deque<T, Allocator>::Deque(const Allocator& alloc)  
: allocator(alloc)  
{     
    initially_allocate_Deque_with_count_elements(0);  
}  
  
template<class T, class Allocator>  
Deque<T, Allocator>::Deque(const Deque& other)  
: allocator()  
{     
    initially_allocate_Deque_with_count_elements(other.finish - other.start);  
    std::uninitialized_copy(other.start, other.finish, start);    
}  
  
template<class T, class Allocator>  
Deque<T, Allocator>::Deque(size_type count, const T& value, const Allocator& alloc)  
: allocator(alloc)  
{     
    initialize_with_count_elements(count, value, std::true_type());  
}  
  
template<class T, class Allocator>  
template<class InputIterator>  
Deque<T, Allocator>::Deque(InputIterator first, InputIterator last)  
{  
    typedef std::integral_constant<bool, std::is_integral<InputIterator>::value> type;  
    initialize_with_count_elements(first, last, type());      
}  
  
template<class T, class Allocator>  
Deque<T, Allocator>::~Deque()  
{  
    destroy(start, finish);  
    deallocate_Deque();  
}  
  
template<class T, class Allocator>  
Deque<T, Allocator>&  
Deque<T, Allocator>::operator=(const Deque& other)  
{  
    assign_aux(other.start, other.finish, std::false_type());  
    return *this;  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::assign(size_type count, const T& value)  
{  
    assign_aux(count, value, std::true_type());  
}  
  
template<class T, class Allocator>  
template<class InputIterator>  
void Deque<T, Allocator>::assign(InputIterator first, InputIterator last)  
{  
    typedef std::integral_constant<bool, std::is_integral<InputIterator>::value> type;  
    assign_aux(first, last, type());  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::allocator_type  
Deque<T, Allocator>::get_allocator() const  
{  
    return allocator;  
}  
  
// Member Access  
template<class T, class Allocator>  
typename Deque<T, Allocator>::reference  
Deque<T, Allocator>::at(size_type index)  
{  
    return *(start + index);  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::const_reference  
Deque<T, Allocator>::at(size_type index) const  
{  
    return *(start + index);  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::reference  
Deque<T, Allocator>::operator[](size_type index)  
{  
    return *(start + index);  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::const_reference  
Deque<T, Allocator>::operator[](size_type index) const  
{  
    return *(start + index);  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::reference  
Deque<T, Allocator>::front()  
{  
    return *start;  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::const_reference  
Deque<T, Allocator>::front() const  
{  
    return *start;  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::reference  
Deque<T, Allocator>::back()  
{  
    return *(finish - 1);  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::const_reference  
Deque<T, Allocator>::back() const  
{  
    return *(finish - 1);  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::iterator  
Deque<T, Allocator>::begin()   
{  
    return start;  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::const_iterator  
Deque<T, Allocator>::begin() const  
{  
    return *start;  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::iterator  
Deque<T, Allocator>::end()   
{  
    return finish;  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::const_iterator  
Deque<T, Allocator>::end() const  
{  
    return finish;  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::reverse_iterator  
Deque<T, Allocator>::rbegin()   
{  
    return reverse_iterator(finish);  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::const_reverse_iterator  
Deque<T, Allocator>::rbegin() const  
{  
    return const_reverse_iterator(finish);  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::reverse_iterator  
Deque<T, Allocator>::rend()   
{  
    return reverse_iterator(start);  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::const_reverse_iterator  
Deque<T, Allocator>::rend() const  
{  
    return const_reverse_iterator(start);  
}  
  
// Capacity  
template<class T, class Allocator>  
bool Deque<T, Allocator>::empty() const  
{  
    return start == finish;  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::size_type  
Deque<T, Allocator>::size() const  
{  
    return difference_type(finish - start);  
}  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::size_type  
Deque<T, Allocator>::max_size() const  
{  
    return size_type(-1) / sizeof(T);  
}  
  
// Modifier  
template<class T, class Allocator>  
void Deque<T, Allocator>::push_back(const T& value)  
{  
    insert_aux(finish, 1, value, std::true_type());  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::push_front(const T& value)  
{  
    insert_aux(start, 1, value, std::true_type());  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::insert(iterator pos, const T& value)  
{  
    insert_aux(pos, 1, value, std::true_type());  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::insert(iterator pos, size_type count, const T& value)  
{  
    insert_aux(pos, count, value, std::true_type());  
}  
  
template<class T, class Allocator>  
template<class InputIterator>  
void Deque<T, Allocator>::insert(iterator pos, InputIterator first, InputIterator last)  
{  
    typedef std::integral_constant<bool, std::is_integral<InputIterator>::value> type;  
    insert_aux(pos, first, last, type());  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::erase(iterator pos)  
{  
    erase(pos, pos + 1);  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::erase(iterator first, iterator last)  
{  
    size_type count = last - first;  
    if(first - start > finish - last) // front  
    {  
        std::copy_backward(start, first, last);  
        destroy(start, start + count);  
        T** old_start_node = start.node;  
        T** tmp;  
        start += count;  
        for(tmp = old_start_node; tmp != start.node; tmp++)  
            allocator.deallocate(*tmp, 1);    
    }  
    else // back  
    {  
        std::copy(last, finish, first);  
        destroy(finish - count, finish);  
        T** old_finish_node = finish.node;  
        T** tmp;  
        finish -= count;  
        for(tmp = old_finish_node; tmp != finish.node; tmp--)  
            allocator.deallocate(*tmp, 1);  
    }  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::pop_back()  
{  
    erase(finish - 1, finish);  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::pop_front()  
{  
    erase(start, start + 1);  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::clear()  
{  
    destroy(start, finish);  
    for(; finish.node != start.node; finish.node--)  
        allocator.deallocate(*finish.node, 1);  
    finish = start;  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::resize(size_type count, T value)  
{  
    if(count >= size())  
        insert_aux(finish, count - size(), value, std::true_type());  
    else  
        erase(start + count, finish);  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::swap(Deque& other)  
{  
    T** tmp_map = map;  
    size_type tmp_map_size = map_size;  
    iterator tmp_start = start;  
    iterator tmp_finish = finish;  
    map = other.map;  
    map_size = other.map_size;  
    start = other.start;  
    finish = other.finish;  
    other.map = tmp_map;  
    other.map_size = tmp_map_size;  
    other.start = tmp_start;  
    other.finish = tmp_finish;  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::display()  
{  
    if(start == finish)  
        std::cout << "empty" << std::endl;  
    else  
    {  
        iterator it;          
        for(it = start; it != finish; ++it)   
            std::cout << *it << ' ';          
        std::cout << std::endl;  
    }  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::display_configuration()  
{  
    std::cout << "map_size = " << map_size   
                << " buffer_size = " << buffer_size() << std::endl;  
    std::cout << "start.node = " << (start.node - map)  
                << " start.cur = " << (start.cur - start.first) << std::endl;  
    std::cout << "finish.node = " << (finish.node - map)  
                << " finish.cur = " << (finish.cur - finish.first) << std::endl;  
}  
// ------------ auxiliary functions ----------------  
  
  
  
template<class T, class Allocator>  
typename Deque<T, Allocator>::size_type  
Deque<T, Allocator>::buffer_size() const  
{  
//  return sizeof(T) < MAX ? MAX / sizeof(T) : (size_t)1;  
    return 4;  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::initially_allocate_Deque_with_count_elements(size_type count)  
{  
    map_size = count / buffer_size() + 3; // one reserve node both at the beginning and at the end  
    map = map_allocator.allocate(map_size);   
    size_type index;  
    for(index = 1; index < map_size - 1; index++)  
        map[index] = allocator.allocate(buffer_size());  
    start.set_node(map + 1);  
    start.cur = start.first;  
    finish.set_node(map + (map_size - 2));  
    finish.cur = finish.first + count % buffer_size();  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::initialize_with_count_elements(size_type count, const T& value, std::true_type)  
{  
    initially_allocate_Deque_with_count_elements(count);  
    std::uninitialized_fill(start, finish, value);  
}  
  
template<class T, class Allocator>  
template<class InputIterator>  
void Deque<T, Allocator>::initialize_with_count_elements(InputIterator first, InputIterator last, std::false_type)  
{  
    initially_allocate_Deque_with_count_elements(std::distance(first, last));  
    std::uninitialized_copy(first, last, start);  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::destroy(iterator first, iterator last)  
{  
    iterator it;  
    for(it = first; it != last; it++)  
        allocator.destroy(&*it);  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::deallocate_Deque()  
{  
    T** node;  
    for(node = start.node; node <= finish.node; node++)  
        allocator.deallocate(*node, 1);  
    map_allocator.deallocate(map, 1);  
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::assign_aux(size_type count, const T& value, std::true_type)  
{  
    destroy(start, finish);  
    if((finish.node - start.node + 1) * buffer_size() >= count) // no need to reallocate  
    {         
        start.cur = start.first;  
        finish = start + count;       
    }  
    else  
    {  
        deallocate_Deque();  
        initially_allocate_Deque_with_count_elements(count);        ;  
    }  
    std::uninitialized_fill_n(start, count, value);  
}  
  
template<class T, class Allocator>  
template<class InputIterator>  
void Deque<T, Allocator>::assign_aux(InputIterator first, InputIterator last, std::false_type)  
{  
    destroy(start, finish);   
    size_type count = std::distance(first, last);  
    if((finish.node - start.node + 1) * buffer_size() >= count) // no need to reallocate  
    {                 
        start.cur = start.first;  
        finish = start + count;       
    }  
    else  
    {         
        deallocate_Deque();  
        initially_allocate_Deque_with_count_elements(count);        ;  
    }     
    std::uninitialized_copy(first, last, start);      
}  
  
template<class T, class Allocator>  
void Deque<T, Allocator>::insert_aux(iterator pos, size_type count, const T& value, std::true_type)  
{  
    if(pos - start < finish - pos)       // expand in the beginning  
    {         
        if(count > start.cur - start.first)  // allocate new node  
        {  
            size_type new_nodes_num = (count - (start.cur - start.first)) / buffer_size()   
                                    + ((count - (start.cur - start.first)) % buffer_size() == 0) ? 0 : 1;  
            if(new_nodes_num > start.node - map) // not enough map space  
            {         
                size_type new_map_size = map_size + new_nodes_num;  
                T** new_map = map_allocator.allocate(new_map_size);               
                std::copy(start.node, finish.node, new_map + (new_nodes_num + (start.node - map)));               
                start.set_node(new_map +(new_nodes_num + (start.node - map)));  
                finish.set_node(new_map + new_map_size - (map + map_size - finish.node));   
                map_allocator.deallocate(map, 1);  
                map = new_map;  
                map_size = new_map_size;                                  
            }  
            size_type i;  
            for(i = 1; i <= new_nodes_num; i++)            
                *(start.node - i) = allocator.allocate(buffer_size());            
        }  
        if(pos - start >= count)  
        {  
            std::uninitialized_copy(start, start + count, start - count);  
            std::copy(start + count, pos, start);  
            std::fill(pos - count, pos, value);  
        }  
        else  
        {  
            std::uninitialized_copy(start, pos, start - count);  
            std::uninitialized_fill(start - (count - (pos - start)), start, value);  
            std::fill(start, pos, value);  
        }         
        start -= count;  
    }  
    else    // expand in the end  
    {             
        if(count > finish.last - finish.cur) // allocate new node  
        {                 
            size_type new_nodes_num = (count - (finish.last - finish.cur)) / buffer_size()   
                                    + (((count - (finish.last - finish.cur)) % buffer_size() == 0) ? 0 : 1);              
            if(new_nodes_num > map + map_size - 1 - finish.node) // not enough map space  
            {                 
                size_type new_map_size = map_size + new_nodes_num;  
                T** new_map = map_allocator.allocate(new_map_size);  
                std::copy(start.node, finish.node + 1, new_map + (start.node - map));                 
                start.set_node(new_map + (start.node - map));                 
                finish.set_node(new_map + (finish.node - map));               
                pos.set_node(new_map + (pos.node - map)); // ?                
                map_allocator.deallocate(map, 1);  
                map = new_map;  
                map_size = new_map_size;                  
            }             
            size_type i;  
            for(i = 1; i <= new_nodes_num; i++)            
                *(finish.node + i) = allocator.allocate(buffer_size());           
        }  
        if(finish - pos >= count)  
        {             
            std::uninitialized_copy(finish - count, finish, finish);              
            std::copy_backward(pos, finish - count, finish);              
            std::fill(pos, pos + count, value);           
        }  
        else  
        {                 
            std::uninitialized_copy(pos, finish, finish + (count - (finish - pos)));                      
            std::fill(pos, finish, value);                    
            std::uninitialized_fill(finish, finish + (count - (finish - pos)), value);                
        }  
        finish += count;  
        //  std::cout << "nine" << std::endl;  
    }  
}  
  
template<class T, class Allocator>  
template<class InputIterator>  
void Deque<T, Allocator>::insert_aux(iterator pos, InputIterator first, InputIterator last, std::false_type)  
{  
    size_type count = std::distance(first, last);  
    if(pos - start < finish - pos)   // expand at the beginning  
    {  
        if(count > start.cur - start.first)  // allocate new node  
        {  
            size_type new_nodes_num = (count - (start.cur - start.first)) / buffer_size()   
                                    + (((count - (start.cur - start.first)) % buffer_size() == 0) ? 0 : 1);  
            if(new_nodes_num > start.node - map) // not enough map space  
            {         
                size_type new_map_size = map_size + new_nodes_num;  
                T** new_map = map_allocator.allocate(new_map_size);               
                std::copy(start.node, finish.node, new_map + (new_nodes_num + (start.node - map)));               
                start.set_node(new_map +(new_nodes_num + (start.node - map)));  
                finish.set_node(new_map + new_map_size - (map + map_size - finish.node));   
                map_allocator.deallocate(map, 1);  
                map = new_map;  
                map_size = new_map_size;                                  
            }  
            size_type i;  
            for(i = 1; i <= new_nodes_num; i++)            
                *(start.node - i) = allocator.allocate(buffer_size());            
        }  
        if(pos - start >= count)  
        {  
            std::uninitialized_copy(start, start + count, start - count);  
            std::copy(start + count, pos, start);  
            std::copy(first, last, pos - count);  
        }  
        else  
        {  
            std::uninitialized_copy(start, pos, start - count);  
            InputIterator mid = first;  
            std::advance(mid, count - (pos - start));  
            std::uninitialized_copy(first, mid, pos - count);  
            std::copy(mid, last, start);  
        }         
        start -= count;  
    }  
    else    // expand at the end  
    {  
        if(count > finish.last - finish.cur) // allocate new node  
        {                 
            size_type new_nodes_num = ((count - (finish.last - finish.cur)) / buffer_size()   
                                    + ((count - (finish.last - finish.cur)) % buffer_size() == 0)) ? 0 : 1;  
            if(new_nodes_num > map + map_size - 1 - finish.node) // not enough map space  
            {  
                size_type new_map_size = map_size + new_nodes_num;  
                T** new_map = map_allocator.allocate(new_map_size);       
                std::copy(start.node, finish.node, new_map + (start.node - map));  
                start.set_node(new_map + (start.node - map));  
                finish.set_node(new_map + (finish.node - map));  
                pos.set_node(new_map + (pos.node - map)); // ?  
                map_allocator.deallocate(map, 1);  
                map = new_map;  
                map_size = new_map_size;  
            }             
            size_type i;  
            for(i = 1; i <= new_nodes_num; i++)            
                *(finish.node + i) = allocator.allocate(buffer_size());  
        }  
        if(finish - pos >= count)  
        {  
            std::uninitialized_copy(finish - count, finish, finish);              
            std::copy_backward(pos, finish - count, finish);              
            std::copy(first, last, pos);              
        }  
        else  
        {             
            std::uninitialized_copy(pos, finish, pos + count);    
            InputIterator mid = first;  
            std::advance(mid, finish - pos);  
            std::copy(first, mid, pos);           
            std::uninitialized_copy(mid, last, finish);           
        }  
        finish += count;  
    }  
}  

#endif