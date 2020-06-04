#include "Sort_Methods/Sort_Method.h"

void Swap(ElemType& a, ElemType& b) {
    ElemType temp;
    temp = a;
    a = b;
    b = temp;
}