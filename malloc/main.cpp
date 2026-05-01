#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

void* m_malloc(size_t sze ) {
  struct mdata{
    size_t size;
    bool free;
  };
  if (sze==0){
    return nullptr;
  }
  sze = (sze + 7) / 8 * 8;
  auto val=sbrk(sze+sizeof(mdata));
  if (val == (void*)-1){
    cout<<"insufficient space"<<endl;
    return nullptr;
  }
  else{
    auto m = (mdata*) val;
    m->size = sze;
    m->free = false;
    return (void*)((uint8_t*)val+sizeof(mdata));
  }
}

int main(){
    // allocate memory
    int* a = (int*)m_malloc(sizeof(int));
    int* b = (int*)m_malloc(sizeof(int));

    // write values
    *a = 42;
    *b = 99;

    // print values
    std::cout << "a = " << *a << std::endl;
    std::cout << "b = " << *b << std::endl;

    // print addresses (important!)
    std::cout << "a addr = " << a << std::endl;
    std::cout << "b addr = " << b << std::endl;

    return 0;
    }
