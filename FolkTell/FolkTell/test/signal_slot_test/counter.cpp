#include "counter.h"

void Counter::setvalue(int _value1, int _value2) {
        value1 = _value1;
        value2 = _value2;
        emit(value_change(value1, 9, value2));
}

