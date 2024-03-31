#include "Reverse.h"

// test for sum, subtraction, multiplication,
// division and remainder of division of two given numbers
template<typename T>
void count(T number1, T number2);

int main()
{
    std::cout << "Test 1 (int32_t)\n";
    count(45, 4);
    std::cout << "\n";
    count(-58, 13);
    std::cout << "\n";
    count(-635, -7);
    std::cout << "\n";
    count(724, -71);
    
    std::cout << "\n\n\nTest 2 (uint32_t)\n\n";
    uint32_t a = 68;
    uint32_t b = 7;
    count(a, b);

    std::cout << "\n\n\nTest 3 (int16_t)\n\n";
    int16_t c = -57;
    int16_t d = 6;
    count(c, d);

    return 0;
}

template<typename T>
void count(T number1, T number2)
{
    Reverse <T> num1(number1);
    Reverse <T> num2(number2);
    
    std::cout << "Sum: " << num1.toDecimal() << " + " << num2.toDecimal() << " = " << (num1 + num2).toDecimal() << "\n";

    std::cout << "Subtraction: " << num1.toDecimal() << " - " << num2.toDecimal() << " = " << (num1 - num2).toDecimal() << "\n";

    std::cout << "Multiplication: " << num1.toDecimal() << " * " << num2.toDecimal() << " = " << (num1 * num2).toDecimal() << "\n";

    std::cout << "Division: " << num1.toDecimal() << " / " << num2.toDecimal() << " = " << (num1 / num2).toDecimal() << "\n";

    std::cout << "Remainder of division: " << num1.toDecimal() << " % " << num2.toDecimal() << " = " << (num1 % num2).toDecimal() << "\n";
}
