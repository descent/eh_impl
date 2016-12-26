#include <iostream>
#include <typeinfo>
using namespace std;


extern "C" 
{
  // libsupc++/eh_alloc.cc
  void * __cxa_allocate_exception(std::size_t thrown_size);

  // libsupc++/eh_throw.cc
  void __cxa_throw (void *obj, std::type_info *tinfo, void (*dest) (void *));
}

void func1()
{
  //throw 100;

  void *throw_obj = __cxa_allocate_exception(sizeof(int));
  *(int*)throw_obj = 100;
  __cxa_throw(throw_obj, (std::type_info*)&typeid(int), NULL);
}

int main(int argc, char *argv[])
{
  try
  {
    cout << "hello" << endl; 
    func1();
  }
  catch (int)
  {
    cout << "catch int" << endl; 
  }
  return 0;
}
