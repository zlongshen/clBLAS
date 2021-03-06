#ifndef CLBLASDGEMMFUNCTORGCN
#define CLBLASDGEMMFUNCTORGCN
#include <string>

class clblasDgemmFunctorGCN : public clblasDgemmFunctor 
{
public:
  
  //
  // A structure that describes a kernel variant. 
  //
  // It is important that all instances of those structures shall 
  // be const and static because their addresses are used as keys 
  // in the internal functor cache. 
  // 
  // Also, they shall all have a unique kernel name.
  // 
  struct Variant 
  {    
    const char *    kernel_name ;  
    const char *    source ;   // the kernel source (shall be unique)
    const char *    build_options;
    const char *    bin ; 
    size_t          bin_size ; 
    clblasTranspose transA ;   //
    clblasTranspose transB ;   //
    unsigned        divN ;     // Required divisor of N  (use 1 when N can be of any value) 
    unsigned        divM ;     // Required divisor of M  (use 1 when M can be of any value) 
    unsigned        divK ;     // Required divisor of K  (use 1 when K can be of any value) 
    size_t          ls[2]  ;   // Local size (the work-group size)
    size_t          bwi[2] ;   // Block size work-item:  Number of elements calculated by each work items 
                               // So basically each kernel is computing a block of
                               //   (ls[0]*bwi[0]) x (ls[1]*bwi[1])  
                               // elements of C. 
    std::string mult;
    
  } ;
  
private:  // Constructor & Destructor

  //clblasDgemmFunctorGCN(Args & args, const Variant * variant, cl_int & err) ;
  
public:

  // Provide a suitable clblasDgemmFunctorGCN for the specified args
  // or NULL if none 
  //static clblasDgemmFunctorGCN * provide(clblasDgemmFunctor::Args & args, const char* DevName) ;

public: // inherited member from clblasDgemmFunctor

  virtual clblasStatus execute(Args &args) ;

protected:

  cl_program      m_program ;  
  const Variant * m_variant ; // Pointer to a 'const static' object describing the kernel variant. 
} ; 

#endif
