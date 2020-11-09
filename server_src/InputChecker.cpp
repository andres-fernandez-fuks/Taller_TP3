//
// Created by andy on 8/11/20.
//

#include <iostream>
#include <string>
#include "InputChecker.h"

void InputChecker::waitForInput() {
    std::string input;
    while (true) {
        std::getline(std::cin, input);
        if (input == "q")
            return;
    }
}
