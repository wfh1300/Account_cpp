
#include <iostream>
#include "Order_rt.h"
#include "Position_rt.h"
using namespace std;
#include <hikyuu/datetime/Datetime.h>
int main() {
	cout << Datetime().min_date() << endl;
}