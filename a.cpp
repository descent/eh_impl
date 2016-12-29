// test c++ exception handle by g++ 3.4.4
// example code from binary hacks chinese version, page 145

#include <cstdio>
#include <iostream>
#include <typeinfo>
using namespace std;

#include <unwind.h>

extern "C" 
{
  // libsupc++/eh_alloc.cc
  void * __cxa_allocate_exception(std::size_t thrown_size);

  // libsupc++/eh_throw.cc
  //void __cxa_throw (void *obj, std::type_info *tinfo, void (*dest) (void *));
  void __cxa_throw (void *obj, void *tinfo, void (*dest) (void *));

  // libsupc++/eh_catch.cc
  void * __cxa_begin_catch (void *exc_obj_in);
  void __cxa_end_catch ();


  #define PERSONALITY_FUNCTION    __gxx_personality_sj0

  // libsupc++/eh_personality.cc
  _Unwind_Reason_Code PERSONALITY_FUNCTION (int version,
                      _Unwind_Action actions,
                      _Unwind_Exception_Class exception_class,
                      struct _Unwind_Exception *ue_header,
                      struct _Unwind_Context *context);


}

struct Lsda
{
  unsigned char start_format;
  unsigned char type_format;
  unsigned char type_length;
  unsigned char call_site_format;
  unsigned char call_site_length;
  unsigned char call_site_table[2];
  signed char action_table[2];
  const std::type_info *catch_type[1];
}__attribute__((packed));

Lsda my_lsda=
{
  0xff,
  0x00,
  10,
  0x01,
  2,
  {0,1},
  {1,0},
  &typeid(int),
};


// unwind-sjlj.c
/* This structure is allocated on the stack of the target function.
   This must match the definition created in except.c:init_eh.  */
struct SjLj_Function_Context
{
  /* This is the chain through all registered contexts.  It is
     filled in by _Unwind_SjLj_Register.  */
  struct SjLj_Function_Context *prev;
  
  /* This is assigned in by the target function before every call
     to the index of the call site in the lsda.  It is assigned by
     the personality routine to the landing pad index.  */
  int call_site;
  
  /* This is how data is returned from the personality routine to
     the target function's handler.  */
  _Unwind_Word data[4];
  
  /* These are filled in once by the target function before any
     exceptions are expected to be handled.  */
  _Unwind_Personality_Fn personality;
  void *lsda;

#ifdef DONT_USE_BUILTIN_SETJMP
  /* We don't know what sort of alignment requirements the system
     jmp_buf has.  We over estimated in except.c, and now we have
     to match that here just in case the system *didn't* have more
     restrictive requirements.  */
  jmp_buf jbuf __attribute__((aligned));
#else
  void *jbuf[];
#endif 
};

//#define CXX_EH

class Obj
{
  public:
    Obj()
    {
      //cout << "obj ctor" << endl;
      printf("obj ctor\n");
    }
    ~Obj()
    {
      //cout << "obj dtor" << endl;
      printf("obj dtor\n");
    }

};

void func2()
{
  cout << "func2 begin" << endl;
#ifdef CXX_EH
  throw 100;
#else
  void *throw_obj = __cxa_allocate_exception(sizeof(int));
  *(int*)throw_obj = 100;
  __cxa_throw(throw_obj, (std::type_info*)&typeid(int), NULL);
#endif
  cout << "func2 end" << endl;
}

void func1()
{
  cout << "func1 begin" << endl;
  Obj obj;

  func2();
  cout << "func1 end" << endl;
}

int main(int argc, char *argv[])
{
#ifdef CXX_EH
  try
  {
    cout << "hello" << endl; 
    func1();
  }
  catch (int eh)
  {
    cout << "catch int: " << eh << endl; 
  }

#else
  
  SjLj_Function_Context sjlj;

  sjlj.personality = __gxx_personality_sj0;
  sjlj.lsda = (void*)&my_lsda;
  sjlj.call_site = 1;

  if (__builtin_setjmp(sjlj.jbuf) == 1)
  {
    void *thrown_obj = __cxa_begin_catch((void*)sjlj.data[0]);
    printf("thrown_obj: %d\n", *(int*)thrown_obj);
    __cxa_end_catch();
  }
  else
  {
    _Unwind_SjLj_Register(&sjlj);
    //throw 100;
    func1();
  }
  _Unwind_SjLj_Unregister(&sjlj);
#endif
  return 0;
}
