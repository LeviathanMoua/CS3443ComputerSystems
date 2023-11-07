/*
Program name : MouaJustin_ProgramALU_CS3443_NPark.cpp
Author       : Justin Moua
Professor    : N. Park
Course       : CS 3443 | Computer Systems
Date         : 28 October 2023
Description  : CS3443: Simulating 4-bit MIPS ALU

                You are to write a gate level simulator for a simple 4-bit ALU with the following operations:
                AND, OR, ADD (1-bit full adder), SUB, SLT, Overflows/Zero Detection. All the operations and architectures to simulate are based on
                what we have studied in class. So, well review them before simulation. Note that the underlying number system is two's complement.
                You may use any language of your favor to write the simulator.

                1) Input format (to be input from the command line):
                Opcode (in string) operand1 operand2 (both operands in integer):
                e.g., ADD 1111 0001, SUB 1111 0001, AND 1111 0001, OR 1111 0001, SLT 1111 0001

                2) Output format (to be displayed on the screen):
                -For ADD, SUB, AND, OR:
                Opcode: 4-bit result, 1-bit overflow-detection, 1-bit zero-detection

                ADD: 0000, 1, 1
                SUB: 1110, 0, 0
                AND: 0001, 0, 0
                OR:  1111, 0, 0

                -For SLT:
                1-bit result (0 or 1)

                SLT: 0001
*/

#include <iostream>
#include <string>
#include <algorithm>

void fnADD(int intArrOperand1[4], int intArrOperand2[4], int intCarryOver) {
    int intArrNewOperand[4];

    int intZeroDetection = 0;
    //Left most bit
    int intNewOperandDigit1;
    //Second to first (right of left most bit)
    int intNewOperandDigit2;
    //Second to last (left of right most bit)
    int intNewOperandDigit3;
    //Right most bit
    int intNewOperandDigit4;

    //This adds all of the operands together. 
    //for (int i = 0; i < 4; i++) {
    //    intArrNewOperand[i] = intArrOperand1[i] + intArrOperand2[i];
    //}


    //===========checks d in abcd
    //If rightmost bit + rightmost bit is greater than 1. Then result is 0 with a carry over of 1. 
    //1 + 1 = 0 w/carry of 1

    //Note that sometimes we may carry a one over on the rightmost bit because we may be performing two's complement. 
    // In this case, 1 + 1 + two's complement of 1 would need to be accounted for. 
    // Say we have 0101 - 1010. Then it turns into 0101 + (0101 + 1)) where the 1 in (0101 + 1) is two's complement. 
    if (intArrOperand1[3] + intArrOperand2[3] + intCarryOver == 3) {
        intArrNewOperand[3] = 1;
        intCarryOver = 1;
    }
    else if (intArrOperand1[3] + intArrOperand2[3] + intCarryOver == 2) {
        intArrNewOperand[3] = 0;
        intCarryOver = 1;
    }
    //Otherwise, the result of those two added together is 1. 
    //0 + 1 = 1 or 1 + 0 = 1. 
    else if (intArrOperand1[3] + intArrOperand2[3] + intCarryOver == 1) {
        intArrNewOperand[3] = 1;
    }
    //0 + 0 = 0. 
    else {
        intArrNewOperand[3] = 0;
    }

    //=========checks c in abcd
    // 1 + 1 + 1, result is 1, with carry over of 1
    if (intArrOperand1[2] + intArrOperand2[2] + intCarryOver == 3) {
        intArrNewOperand[2] = 1;
        intCarryOver = 1;
    }
    // 1 + 1 + 0 
    else if (intArrOperand1[2] + intArrOperand2[2] + intCarryOver == 2) {
        intArrNewOperand[2] = 0;
        intCarryOver = 1;
    }
    // 0 + 1 + 1 or 1 + 0 + 0 or 0 + 0 + 1
    else if (intArrOperand1[2] + intArrOperand2[2] + intCarryOver == 1) {
        intArrNewOperand[2] = 1;
        //set CarryOver to 0 since there would be nothing else to carry over
        intCarryOver = 0;
    }
    // 0 + 0
    else {
        intArrNewOperand[2] = 0;
    }

    //=========checks b in abcd
    // 1 + 1 + 1, result is 1, with carry over of 1
    if (intArrOperand1[1] + intArrOperand2[1] + intCarryOver == 3) {
        intArrNewOperand[1] = 1;
        intCarryOver = 1;
    }
    // 1 + 1 + 0 
    else if (intArrOperand1[1] + intArrOperand2[1] + intCarryOver == 2) {
        intArrNewOperand[1] = 0;
        intCarryOver = 1;
    }
    // 0 + 1 + 1 or 1 + 0 + 0 or 0 + 0 + 1
    else if (intArrOperand1[1] + intArrOperand2[1] + intCarryOver == 1) {
        intArrNewOperand[1] = 1;
        //set CarryOver to 0 since there would be nothing else to carry over
        intCarryOver = 0;
    }
    // 0 + 0
    else {
        intArrNewOperand[1] = 0;
    }

    //=========checks a in abcd
    // 1 + 1 + 1, result is 1, with carry over of 1
    if (intArrOperand1[0] + intArrOperand2[0] + intCarryOver == 3) {
        intArrNewOperand[0] = 1;
        intCarryOver = 1;
    }
    // 1 + 1 + 0 
    else if (intArrOperand1[0] + intArrOperand2[0] + intCarryOver == 2) {
        intArrNewOperand[0] = 0;
        intCarryOver = 1;
    }
    // 0 + 1 + 1 or 1 + 0 + 0 or 0 + 0 + 1
    else if (intArrOperand1[0] + intArrOperand2[0] + intCarryOver == 1) {
        intArrNewOperand[0] = 1;
        //set CarryOver to 0 since there would be nothing else to carry over
        intCarryOver = 0;
    }
    // 0 + 0
    else {
        intArrNewOperand[0] = 0;
    }

    if ((intArrNewOperand[0] == 0) && (intArrNewOperand[1] == 0) && (intArrNewOperand[2] == 0) && (intArrNewOperand[3] == 0)) {
        intZeroDetection = 1;
    }

    //Outputs the addition of string 1 and 2
    for (int i = 0; i < 4; i++) {
        std::cout << intArrNewOperand[i];
    }
    std::cout << ", " << intCarryOver << ", " << intZeroDetection;
}

void fnSUB(int intArrOperand1[4], int intArrOperand2[4]) {

    bool boolApplyTwosComplement;
    int intArrTemp[4];
    //Loops through 2nd array and checks if any of the values are 0. This is crucial for the upcoming if statements below.

    //If bit string 2 is 0000, then do not apply two's complement. 
    if ((intArrOperand2[0] + intArrOperand2[1] + intArrOperand2[2] + intArrOperand2[3]) == 0) {
        boolApplyTwosComplement = false;
        //Print the first bit string since nothing even happens when we subtract 0 from it. 
        for (int i = 0; i < 4; i++) {
            std::cout << intArrOperand1[i];
        }
        std::cout << ", 0, 0";
    }
    //If bit string 1 is 1111, then do not apply two's complement. 
    else if ((intArrOperand1[0] + intArrOperand1[1] + intArrOperand1[2] + intArrOperand1[3]) == 4) {
        boolApplyTwosComplement = false;
        for (int i = 0; i < 4; i++) {
            std::cout << intArrOperand1[i] - intArrOperand2[i];
        }
        std::cout << ", 0, 0";
    }
    else if (((intArrOperand1[0] + intArrOperand1[1] + intArrOperand1[2] + intArrOperand1[3]) == 0) && ((intArrOperand2[0] + intArrOperand2[1] + intArrOperand2[2] + intArrOperand2[3]) == 4)) {
        std::cout << "0001, 0, 0";
    }
    //If bit string 2 IS NOT 0000, then apply two's complement
    else {
        boolApplyTwosComplement = true;
        //inverts all the bits in the second string
        for (int i = 0; i < 4; i++) {
            //If element's value is 0 then turn it into a 1. 
            if (intArrOperand2[i] == 0) {
                intArrTemp[i] = 1;
            }
            //Otherwise if element's value is 1, then turn it into a 0. 
            else {
                intArrTemp[i] = 0;
            }
        }

        //This makes it so we can +1 to the inverted bit when passing through the add function. 
        int intTwosComplement = 1;


        fnADD(intArrOperand1, intArrTemp, intTwosComplement);
    }


}

void fnAND(int intArrOperand1[4], int intArrOperand2[4]) {

    int intArrResult[4];
    for (int i = 0; i < 4; i++) {
        if (((intArrOperand1[i] == 1) && (intArrOperand2[i] == 1)) || ((intArrOperand1[i] == 0) && (intArrOperand2[i] == 0))) {
            intArrResult[i] = 1;
        }
        else {
            intArrResult[i] = 0;
        }
        std::cout << intArrResult[i];
    }

    int intZeroDetection = 0;
    for (int i = 0; i < 4; i++) {
        intZeroDetection = intZeroDetection + intArrResult[i];
    }

    //If the bit string is only 0. 
    if (intZeroDetection == 0) {
        std::cout << ", 0, " << 1;
    }
    else {
        std::cout << ", 0, 0";
    }
}

void fnOR(int intArrOperand1[4], int intArrOperand2[4]) {

    int intArrResult[4];
    for (int i = 0; i < 4; i++) {
        if (((intArrOperand1[i] == 1) || (intArrOperand2[i] == 1))) {
            intArrResult[i] = 1;
        }
        else {
            intArrResult[i] = 0;
        }
        std::cout << intArrResult[i];
    }

    int intZeroDetection = 0;
    for (int i = 0; i < 4; i++) {
        intZeroDetection = intZeroDetection + intArrResult[i];
    }


    //If the bit string is only 0. 
    if (intZeroDetection == 0) {
        std::cout << ", 0, " << 1;
    }
    else {
        std::cout << ", 0, 0";
    }

}

void fnSLT(int intArrOperand1[4], int intArrOperand2[4]) {

    int intDecimalValue1 = 0;
    int intDecimalValue2 = 0;


    //All of this converts the first 4-bit string into decimal to be compared to later. 
    if (intArrOperand1[0] == 1) {
        intDecimalValue1 = -8;
        //std::cout << "intArrOperand1[0] = 1 | intDecimalValue1 =" << intDecimalValue1;
        //std::cout << std::endl;
    }
    if (intArrOperand1[1] == 1) {
        intDecimalValue1 = intDecimalValue1 + 4;
        //std::cout << "intArrOperand1[1] = 1 | intDecimalValue1 =" << intDecimalValue1;
        //std::cout << std::endl;
    }
    if (intArrOperand1[2] == 1) {
        intDecimalValue1 = intDecimalValue1 + 2;
        //std::cout << "intArrOperand1[2] = 1 | intDecimalValue1 =" << intDecimalValue1;
        //std::cout << std::endl;
    }
    if (intArrOperand1[3] == 1) {
        intDecimalValue1 = intDecimalValue1 + 1;
        // std::cout << "intArrOperand1[3] = 1 | intDecimalValue1 =" << intDecimalValue1;
        //std::cout << std::endl;
    }
    //std::cout << std::endl << std::endl;

    //All of this converts the second 4-bit string into decimal to be compared to later. 
    if (intArrOperand2[0] == 1) {
        intDecimalValue2 = -8;
        //std::cout << "intArrOperand1[0] = 1 | intDecimalValue2 =" << intDecimalValue2;
        //std::cout << std::endl;
    }
    if (intArrOperand2[1] == 1) {
        intDecimalValue2 = intDecimalValue2 + 4;
        //std::cout << "intArrOperand2[1] = 1 | intDecimalValue2 =" << intDecimalValue2;
        //std::cout << std::endl;
    }
    if (intArrOperand2[2] == 1) {
        intDecimalValue2 = intDecimalValue2 + 2;
        //std::cout << "intArrOperand2[2] = 1 | intDecimalValue2 =" << intDecimalValue2;
        //std::cout << std::endl;
    }
    if (intArrOperand2[3] == 1) {
        intDecimalValue2 = intDecimalValue2 + 1;
        //std::cout << "intArrOperand2[3] = 1 | intDecimalValue2 =" << intDecimalValue2;
        //std::cout << std::endl;
    }

    if (intDecimalValue1 < intDecimalValue2) {
        std::cout << "0001";
    }
    else {
        std::cout << "0000";
    }

}

int main()
{

    //Opcode that the user chooses
    std::string strInpOpCode = "";
    int intCarryOver = 0;

    //Prints out information about the program
    std::cout << "==============================================================\nAssignment: Simulating 4-bit MIPS ALU\nAuthor: Justin Moua\nProfessor: N. Park\nCourse: CS 3443 | Computer Systems\n==============================================================";
    std::cout << std::endl << std::endl;

    bool boolStayOrQuit = true;
    while (true) {
        //===============ASKING FOR BIT STRINGS START HERE==========================ASKING FOR BIT STRINGS START HERE==========================
        int intOperand1;
        int intOperand2;

        std::cout << "Input Operand 1 (4-bits): ";
        std::cin >> intOperand1;
        std::cout << std::endl;

        std::cout << "Input Operand 2 (4-bits): ";
        std::cin >> intOperand2;
        std::cout << std::endl << std::endl;

        int intArrOperand1[4];
        int intArrOperand2[4];

        intArrOperand1[0] = intOperand1 / 1000 % 10;
        intArrOperand1[1] = intOperand1 / 100 % 10;
        intArrOperand1[2] = intOperand1 / 10 % 10;
        intArrOperand1[3] = intOperand1 % 10;


        intArrOperand2[0] = intOperand2 / 1000 % 10;
        intArrOperand2[1] = intOperand2 / 100 % 10;
        intArrOperand2[2] = intOperand2 / 10 % 10;
        intArrOperand2[3] = intOperand2 % 10;

        //===============ASKING FOR BIT STRINGS ENDS HERE==========================ASKING FOR BIT STRINGS ENDS HERE==========================

        //===============BRANCH STATEMENT AND OUTPUT STARTS HERE=============================BRANCH STATEMENT AND OUTPUT STARTS HERE=============================
        std::cout << "Opcode: 4 - bit result, 1 - bit overflow - detection, 1 - bit zero - detection";
        std::cout << std::endl;



        std::cout << "ADD: ";
        fnADD(intArrOperand1, intArrOperand2, intCarryOver);
        std::cout << std::endl;

        std::cout << "SUB: ";
        fnSUB(intArrOperand1, intArrOperand2);
        std::cout << std::endl;

        std::cout << "AND: ";
        fnAND(intArrOperand1, intArrOperand2);
        std::cout << std::endl;

        std::cout << "OR:  ";
        fnOR(intArrOperand1, intArrOperand2);
        std::cout << std::endl;

        std::cout << "SLT: ";
        fnSLT(intArrOperand1, intArrOperand2);
        std::cout << std::endl;
        std::cout << std::endl;


        //=============ASK IF USER WANTS TO CONTINUE===============ASK IF USER WANTS TO CONTINUE===============ASK IF USER WANTS TO CONTINUE===============
        //Checks to see if user wants to continue
        //Var to check if user wants to continue
        std::string strUsrInpContinueOrNo;
        while (true) {

            std::cout << "===========================\nWould you like to continue?\n===========================\n\nEnter Y or N here: ";
            std::cin >> strUsrInpContinueOrNo;
            std::cout << std::endl;

            if (strUsrInpContinueOrNo == "Y" || strUsrInpContinueOrNo == "y") {
                std::cout << std::endl;
                break;
            }
            else if (strUsrInpContinueOrNo == "N" || strUsrInpContinueOrNo == "n") {
                boolStayOrQuit = false;
                std::cout << std::endl;
                break;
            }
            else {
                std::cout << "=============\nInvalid Input!\n=============\n\nPlease enter Y or N.";
                std::cout << std::endl;
                std::cout << std::endl;
            }

        }
        //If the user has selected to quit, boolStayOrQuit will be false and thus break the while loop. 
        if (boolStayOrQuit == false) {
            break;
        }
        //=============ASK IF USER WANTS TO CONTINUE===============ASK IF USER WANTS TO CONTINUE===============ASK IF USER WANTS TO CONTINUE===============
    }


    std::cout << std::endl << std::endl;
}