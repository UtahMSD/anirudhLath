//
//  main.cpp
//  GiveChange
//
//  Created by Anirudh Lath on 8/24/21.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    
    // Variables
    int itemPrice;
    int amountPaid;
    
    // Enter the Item Price
    std::cout << "Please enter the item price below in cents:\n";
    std::cin >> itemPrice;
    
    // Enter Amount Paid
    std::cout << "Please enter the amount paid below in cents:\n";
    std::cin >> amountPaid;
    
    // Logic
    int change = amountPaid - itemPrice;
    int quarters = change / 25;
    int centsLeftInQuarters = change % 25;
    int dimes = centsLeftInQuarters / 10;
    int centsLeftInDimes = centsLeftInQuarters % 10;
    int nickels = centsLeftInDimes / 5;
    int centsLeftInNickels = centsLeftInDimes % 5;
    int pennies = centsLeftInNickels;
    
    // Output the change
    std::cout << "Change = " << change << " cents\n";
    std::cout << "Quarters: " << quarters << std::endl;
    std::cout << "Dimes: " << dimes << std::endl;
    std::cout << "Nickels: " << nickels << std::endl;
    std::cout << "Pennies: " << pennies << std::endl;
    
    return 0;
}
