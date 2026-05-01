#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;
struct mdata{
    size_t size;
    bool free;
    mdata* next;
  };
mdata* head = nullptr;
void m_free(void* ptr){
  if (ptr == nullptr) return;
  
  mdata* m=(mdata*)((uint8_t*)ptr-sizeof(mdata));
  m->free=true;
}
void* m_malloc(size_t sze ) {
  sze = (sze + 7) / 8 * 8;
  if (sze == 0) return nullptr;
  mdata* curr= head;
  mdata* prev=nullptr;
  while(curr != nullptr){
    if (curr->free == true && curr ->size>= sze+sizeof(mdata)){
      size_t r=curr->size - sze-sizeof(mdata);
      if (r>sizeof(mdata)){
      mdata* next_node = (mdata*)((uint8_t*)curr + sizeof(mdata) + sze);
      next_node->size = curr->size - sze - sizeof(mdata);
      next_node->free = true;
      next_node->next = curr->next;
      curr->size = sze;
      curr->next = next_node;
      }
      curr->free = false;
      return (void*)((uint8_t*)curr + sizeof(mdata));
      }
    prev=curr;
    curr=curr->next;
    }
  void* val = sbrk(sze + sizeof(mdata));
    if (val == (void*)-1) return nullptr;
    mdata* m = (mdata*)val;
    m->size = sze;
    m->free = false;
    m->next = nullptr;
    if (head == nullptr) head = m;
    else {
    prev->next = m;
    }

    return (void*)((uint8_t*)val + sizeof(mdata));
}

int main()
    int* a = (int*)m_malloc(sizeof(int));
    int* b = (int*)m_malloc(sizeof(int));
    *a = 42;
    *b = 99;
    std::cout << "a = " << *a << std::endl;
    std::cout << "b = " << *b << std::endl;
    std::cout << "a addres = " << a << std::endl;
    std::cout << "b address = " << b << std::endl;
    return 0;
    }
