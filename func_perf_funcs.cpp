#include <functional>

// simple funct
inline float func_half( float x ) { return x * 0.5f; }

// func we can bind
float mul_by( float x, float scale ) { return x * scale; }

//
// func to call another func a zillion times.
//
float test_stdfunc( std::function<float(float)> const & func, int nloops ) {
    float x = 1.0;
    float y = 0.0;
    for(int i =0; i < nloops; i++ ){
        y += x;
        x = func(x);
    }
    return y;
}

// same thing with a function pointer
float test_funcptr( float (*func)(float), int nloops ) {
    float x = 1.0;
    float y = 0.0;
    for(int i =0; i < nloops; i++ ){
        y += x;
        x = func(x);
    }
    return y;
}

// same thing with inline function
float test_inline( int nloops ) {
    float x = 1.0;
    float y = 0.0;
    for(int i =0; i < nloops; i++ ){
        y += x;
        x = func_half(x);
    }
    return y;
}
