#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "AX12_manager.h"

using namespace std;

int main() {

    string dev = "tty_ACM0";
    AX12_manager manager(dev);
    manager.init_connection();

    return 0;
}