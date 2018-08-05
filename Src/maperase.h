#ifndef MAPERASE_H
#define MAPERASE_H

#include <map>
#include <unordered_map>
#include <vector>

template <class Key, class T, class Compare, class Alloc, class Predicate>
void erase_if(std::map<Key,T,Compare,Alloc>& c, Predicate pred)
{
    for (auto i = c.begin(), last = c.end(); i != last; ) {
      if (pred(*i)) {
        i = c.erase(i);
      } else {
        ++i;
      }
    }
}

template <class Key, class T, class Hash, class KeyEqual, class Alloc, class Predicate>
void erase_if(std::unordered_map<Key,T,Hash,KeyEqual,Alloc>& c, Predicate pred)
{
    for (auto i = c.begin(), last = c.end(); i != last; ) {
      if (pred(*i)) {
        i = c.erase(i);
      } else {
        ++i;
      }
    }
}

template <class T, class Alloc, class Predicate>
void erase_if(std::vector<T,Alloc>& c, Predicate pred)
{
    c.erase(std::remove_if(c.begin(), c.end(), pred), c.end());
}


#endif // MAPERASE_H
