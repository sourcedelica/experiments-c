#include <iostream>

extern float func_half( float x );
extern float mul_by( float x, float scale );
extern float test_inline(  int nloops );
extern float test_stdfunc( std::function<float(float)> const & func, int nloops );
extern float test_funcptr( float (*func)(float), int nloops );

static const int Iterations = 1000000000;

int main() {
    using namespace std::chrono;


    for(int icase = 0; icase < 4; icase++){
        const auto start = high_resolution_clock::now();
        float result{};

        switch( icase ){
            case 0:
                result = test_inline( Iterations );
                break;
            case 1:
                result = test_funcptr( func_half, Iterations );
                break;
            case 2:
                result = test_stdfunc( func_half, Iterations );
                break;
            case 3:
                result = test_stdfunc( std::bind( mul_by, std::placeholders::_1, 0.5), Iterations );
                break;
            default:
                break;
        }

        const auto d = duration_cast<milliseconds>(high_resolution_clock::now() - start);
        std::cout << d.count() << std::endl;
        std::cout << result << std::endl;
    }
    return 0;
}