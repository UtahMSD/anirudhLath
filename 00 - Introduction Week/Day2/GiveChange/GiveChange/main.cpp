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

    if (itemPrice < 0) {
        std::cout << "\nError: The item price cannot be negative. The program will exit.\n";
        return 1;
    }

    // Enter Amount Paid
    std::cout << "\nPlease enter the amount paid below in cents:\n";
    std::cin >> amountPaid;

    // Error Handling
    if (amountPaid < 0) {
        std::cout << "\nError: The amount paid cannot be negative. The program will exit.\n";
        return 1;
    }
    else if (amountPaid < itemPrice) {
        std::cout << "\nInsufficient Funds! Please try again!\n";
    }

    // Asking the user for input until he pays the amount required.
    while (amountPaid < itemPrice) {
        std::cout << "\nPlease enter the amount paid below in cents:\n";
        std::cin >> amountPaid;
    }
    
    // Logic
    int change = amountPaid - itemPrice;
    int quarters = change / 25;
    int centsLeftInQuarters = change % 25;
    int dimes = centsLeftInQuarters / 10;
    int centsLeftInDimes = centsLeftInQuarters % 10;
    int nickels = centsLeftInDimes / 5;
    int centsLeftInNickels = centsLeftInDimes % 5;
    int pennies = centsLeftInNickels;

    if (quarters > 2) {
        quarters = 2;
        centsLeftInQuarters = (change - (quarters * 25));
        dimes = centsLeftInQuarters / 10;
        if (dimes > 2) {
            dimes = 2;
            centsLeftInDimes = (change - (dimes * 10));
            nickels = centsLeftInDimes / 5;
            if (nickels > 2) {
                nickels = 2;
                centsLeftInNickels = (change - (nickels * 5));
                pennies = centsLeftInNickels;
                if (pennies > 2) {
                    std::cout << "There is not enough change to return, therefore we cannot sell you the product and here is your " << amountPaid << " cents back :)\n";
                }
            }
            else {
                nickels = centsLeftInDimes / 5;
                centsLeftInNickels = centsLeftInDimes % 5;
                pennies = centsLeftInNickels;
            }
        }
        else {
            dimes = centsLeftInQuarters / 10;
            centsLeftInDimes = centsLeftInQuarters % 10;
            nickels = centsLeftInDimes / 5;
            centsLeftInNickels = centsLeftInDimes % 5;
            pennies = centsLeftInNickels;
        }
    }
    else {
        quarters = change / 25;
        centsLeftInQuarters = change % 25;
        dimes = centsLeftInQuarters / 10;
        centsLeftInDimes = centsLeftInQuarters % 10;
        nickels = centsLeftInDimes / 5;
        centsLeftInNickels = centsLeftInDimes % 5;
        pennies = centsLeftInNickels;
    }
    
    // Output the change
    std::cout << "\nChange = " << change << " cents\n";
    std::cout << "Quarters: " << quarters << std::endl;
    std::cout << "Dimes: " << dimes << std::endl;
    std::cout << "Nickels: " << nickels << std::endl;
    std::cout << "Pennies: " << pennies << std::endl << "\n";
    
    return 0;
}
