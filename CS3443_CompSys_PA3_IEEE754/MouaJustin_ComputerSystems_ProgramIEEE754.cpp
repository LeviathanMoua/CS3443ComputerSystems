/*
Program name : MouaJustin_ComputerSystems_ProgramIEEE754.cpp
Author       : Justin Moua
Professor    : N. Park
Course       : CS 3443 | Computer Systems
Date         : 27 November 2023
Description  :
			CS3443 Assignment


			This assignment is to implement IEEE 754.
			1) Take a decimal value operand and convert it into Encode each operand into IEEE 754 format.
			2) Perform an addition.
			3) Perform a multiplication.

			The language is not restrictd as long as one of the compilers on CSX,
			e.g., C, C++, or Java. In other words, your simulator should be compilable
			and executable on CSX.
			The size to simulate 32 bit.


			Sample 1:

			Input: command line input as below,

			Enter operand1 (decimal): 2345.125
			Enter operand2 (decimal): .75
			Enter operator (add or mult): add

			(Note that the inputs are to be entered as a string)

			Output: standard output on screen as below,

			operand1: 0     10001010    00100101001001000000000
			operand2: 0     01111110    10000000000000000000000

			sum:      0     10001010    00100101001111000000000


			Sample2:

			Input: command line input as below,

			Enter operand1 (decimal): -18
			Enter operand2 (decimal): 9.5
			Enter operator (add or mult): mult

			(Note that the inputs are to be entered as a string)

			Output: standard output on screen as below,

			operand1: 1     10000011    00100000000000000000000
			operand2: 0     10000010    00110000000000000000000

			product:  1     10000110    01010101100000000000000
*/

#include <iostream>
#include <string>


//What I can do is take the string input of both values. Then split the string. Remembering that 
//There is always a null character or "\0" that the end of a string. I try to start from the decimal and find the null 
//character to indicate what the fractional part is. 
//As for the integer part, I just need to start from the beginning and end where the decimal is. 

//This function is used for the exponent. 
std::string intToBinary8Bit(int strLHS) {
	int intLHS = strLHS; //Converts strLHS that is passed through as a string into an integer.
	int intDiv = intLHS;
	int intMod;
	std::string strLHSBinary; //This is the LHS as Binary

	if (std::to_string(strLHS) == "0") {
		strLHSBinary += "0";
	}
	else {
		while (intDiv > 0) {
			intMod = intDiv % 2;
			intDiv = intDiv / 2;
			//Concatenates strResult with the whatever intMod is. 
			strLHSBinary += std::to_string(intMod);
		}
	}

	if (strLHSBinary.size() != 8) {
		int i = 0;
		while (strLHSBinary[i] != '\0') {
			i++;
		}
		for (int j = i; j < 8; j++) {
			strLHSBinary += '0';
		}
	}
	
	return strLHSBinary;
}
/*
std::string intToBinary8Bit(int intDecVal)
{
	// array to store binary number 
	//int intBinaryNum[8];
	int intTemp;
	std::string strResult;
	

	// counter for binary array 
	int i = 0;
	while (intDecVal > 0) {

		// storing remainder in binary array 
		intTemp = intDecVal % 2;
		strResult += std::to_string(intTemp);
		intDecVal = intDecVal / 2;
		i++;
	}

	reverse(strResult.begin(), strResult.end());
	return strResult;
}*/

std::string fnStrIEEE754(bool boolSignBit, std::string strLHS, std::string strRHS) {	
	std::string strFinalResult;

	//=======INTEGER/LHS PART TO BINARY===================
	//intDiv gets divded by 2 until it reaches 0. This is because we want to get the binary vaclue
	//for whole numbers. For example, 2345. 2345/2 then 2345%2. And so on. 
	int intLHS = std::stoi(strLHS); //Converts strLHS that is passed through as a string into an integer.
	int intDiv = intLHS; 
	int intMod;
	std::string strLHSBinary; //This is the LHS as Binary
	if (strLHS == "0") {
		strLHSBinary += "0";
	}
	else {
		while (intDiv > 0) {
			intMod = intDiv % 2;
			intDiv = intDiv / 2;
			//Concatenates strResult with the whatever intMod is. 
			strLHSBinary += std::to_string(intMod);
		}
	}

	reverse(strLHSBinary.begin(), strLHSBinary.end());
	//Sanity Check
	//std::cout << "LHS in Binary is: " << strLHSBinary;
	//std::cout << std::endl << std::endl;
	//=======INTEGER/LHS PART TO BINARY===================

	//=======FRACTIONAL/RHS PART TO BINARY================
	float fltRHS = std::stof(strRHS); //Converts strRHS to float
	float fltMult = fltRHS; 
	std::string strRHSBinary; //This is the RHS as binary. 

	while (fltMult != 0) {
		fltMult = fltMult * 2;

		/*Say we enter 19.59375. Then,.59375 * 2 = 1.1875.
		We don't want the 1 on the LHS so we subtract 1 from it. Then continue multiplying fltMult by 2. 
		Also, because it would be >= 1, we concatenate a 1 to strRHSBinary. Otherwise, we concatenate 0. 
		*/
		if (fltMult >= 1) { //Say a value 1.1875 occurs. Well, we only want to continue on with .1875. 
			fltMult = fltMult - 1;
			strRHSBinary += '1'; //Concatenates a 1. This is the RHS of a given float converted into binary. 
		}
		else if (fltMult < 1) {
			strRHSBinary += '0'; //Concatenates a 1. This is the RHS of a given float converted into binary. 
		}
		//This is a sanity check that checks to make sure that the float is being multiplied up until we obtain an integer or LHS of 1. (In this case, where fltMult = 0 since in one of the if branches we do fltMult - 1 and 1-1 = 0)
		//std::cout << "\nfltMult is: " << fltMult;
		//std::cout << std::endl << std::endl;

		//std::cout << fltMult << std::endl;
	}
	//Sanity Check
	//std::cout << "RHS in Binary is: " << strRHSBinary;
	//std::cout << std::endl << std::endl;
	//=======FRACTIONAL/RHS PART TO BINARY================

	//==========BRINGING LHS AND RHS TOGETHER STARTS HERE==========BRINGING LHS AND RHS TOGETHER STARTS HERE=======================
	//Bring the LHS and RHS together. If we did something such as 19.59375, then
	//19 would be 10011 and .59375 would be 10011 (yes both are coincidentally 10011). 
	//It would then look like 10011.10011. 
	//Say we entered 2345.125 then. Well, 2345 would be represented as 100100101001 and
	//.125 represented as 001. This would mean that 2345.125 is 100100101001.001. 
	//Because of this, we need to normalize the binary number and move it to the left making sure that the string (technically floating point)
	//has no leading 0s. This is also known as implicit normalization. 

	//Make a new string that is equal to every binary number OTHER than the 1st element and OTHER than the decimal. 
	//Then, make a new string that is set equal to the 1st element of the binary number AND has a dot after it. Then concatonate. 
	std::string strBroughtTogether;
	bool boolMoveRightOrNot = false;
	if (strLHSBinary == "0") {
		boolMoveRightOrNot = true;
		strLHSBinary[0] = strRHSBinary[0];
		
		//Sanity Check
		//std::cout << "strLHSBinary[0] is: " << strLHSBinary;
		//std::cout << std::endl << std::endl;

		strRHSBinary[0] = '.';
		strBroughtTogether = strLHSBinary + strRHSBinary;
		//int i = 0;
		//while (strRHSBinary[i] != '\0') {
		//	strBroughtTogether += strRHSBinary[i];
		//	std::cout << "strRHSBinary[" << i << "] is: " << strRHSBinary[i];
		//	std::cout << std::endl;
		//	i++;

		//}
		//Sanity Check
		//std::cout << "strBroughtTogether is: " << strBroughtTogether;
		//std::cout << std::endl << std::endl;
	}
	else {
		strBroughtTogether = strLHSBinary + '.' + strRHSBinary;
		//std::cout << "strBroughtTogether is: " << strBroughtTogether;
		//std::cout << std::endl << std::endl;
	}

	//==========BRINGING LHS AND RHS TOGETHER ENDS HERE==========BRINGING LHS AND RHS TOGETHER ENDS HERE=======================

	//============SIGN BIT STARTS HERE==============SIGN BIT STARTS HERE==============SIGN BIT STARTS HERE==============SIGN BIT STARTS HERE
	std::string strBinarySignBit;
	if (boolSignBit == true) {
		strBinarySignBit = "1";
	}
	else {
		strBinarySignBit = "0";
	}
	//============SIGN BIT ENDS HERE==============SIGN BIT ENDS HERE==============SIGN BIT ENDS HERE==============SIGN BIT ENDS HERE

	//=============EXPONENT STARTS HERE=====================EXPONENT STARTS HERE=====================EXPONENT STARTS HERE=====================
	//Checks how many spaces to move
	int intHowManyDecimalPlaces = 0;
	if (boolMoveRightOrNot == true) {
		intHowManyDecimalPlaces = -1;
	}
	else{
		//We could have just done i will start on the 2nd element (or element [1] up until it sees a '.')
		int i = 1;
		while (strBroughtTogether[i] != '.') {
			i++; //This counts how many places the decimal will be nmoving. 
			intHowManyDecimalPlaces++;
		}
		//Sanity Check
		//std::cout << "The decimal will need to move " << intHowManyDecimalPlaces << " places to the left.";
		//std::cout << std::endl << std::endl;
	}
	//I have to fix something here. I have to make sure that when entering in .75 or 0.75, 
	//I account for that the entire binary value is 0.11. I need ot move the decimal to the right then delete the 0. I could reverse this. 
	//This would then become 11.0 and I can replace 0 with a \0


	int intExponent = intHowManyDecimalPlaces + 127;
	//Sanity Check
	//std::cout << "Exponent is: " << intExponent;
	//std::cout << std::endl << std::endl;

	//I think I know the problem now. 
	std::string strBinaryExponent = intToBinary8Bit(intExponent);
	reverse(strBinaryExponent.begin(), strBinaryExponent.end());
	//Sanity Check
	//std::cout << "Exponent in Binary is: " << strBinaryExponent;
	//std::cout << std::endl << std::endl;
	//=============EXPONENT ENDS HERE=====================EXPONENT ENDS HERE=====================EXPONENT ENDS HERE=====================

	//=============MANTISSA STARTS HERE=====================MANTISSA STARTS HERE=====================MANTISSA STARTS HERE=====================

	//Creates an Mantissa that is not Normalized
	std::string strUnNormalizedMantissa = strBroughtTogether[0] + std::string(1, '.'); 	//this grabs all the values of the binary excluding the first element and the period. 
	for (int j = 1; j < strBroughtTogether.size(); j++) { //note we start at j = 1 to avoid first element.
		if (strBroughtTogether[j] != '.') {
			strUnNormalizedMantissa += strBroughtTogether[j];
		}
	}
	//Sanity Check
	//std::cout << "Non-Normalized Mantissa is: " << strUnNormalizedMantissa;
	//std::cout << std::endl << std::endl;

	//Sanity Check
	//std::cout << "Size of Non-Normalized Mantissa excluding the first digit and decimal is: " << strUnNormalizedMantissa.size()-2;
	//std::cout << std::endl << std::endl;


	std::string strNormalizedMantissa;

	//This normalizes the mantissa and adds necessary 0s to the end of it. 
	for (int j = 2; j <= 25; j++) { //Note we start at j = 2 to avoid first element and period then stop at 25 to get to 23 characters.. 
		if (j <= strUnNormalizedMantissa.size()) {
			strNormalizedMantissa += strUnNormalizedMantissa[j];
			//std::cout << "\n\n============\nBranch 1 is true\n============\n\n";
		}
		else {
			strNormalizedMantissa = strNormalizedMantissa + '0';
			//std::cout << "\n\n============\nBranch 2 is true\n============\n\n";

		}
		//std::cout << "Normalized Mantissa at loop " << j << " is currently: " << strNormalizedMantissa;
		//std::cout << std::endl << std::endl;
	}

	//Sanity Check
	//std::cout << "Normalized Mantissa: " << strNormalizedMantissa;
	//std::cout << std::endl;
	//=============MANTISSA ENDS HERE=====================MANTISSA ENDS HERE=====================MANTISSA ENDS HERE=====================


	strFinalResult = strBinarySignBit + "-" + strBinaryExponent + "-" + strNormalizedMantissa;
	

	return strFinalResult;
}

std::string fnSpacer(std::string strUsrInpOp1) {
	//std::string strUsrInpOp1;
	std::string strUsrInpOp1LHS; //Integer part
	std::string strUsrInpOp1RHS; //Fractional part
	std::string strReturnVal;
	//=====================OPERAND 1 STARTS HERE=====================OPERAND 1 STARTS HERE=====================OPERAND 1 STARTS HERE=====================OPERAND 1 STARTS HERE=====================

	//====================SEPERATE LHS AND RHS OF OPERAND 1 STARTS HERE=====================
			//If Operand 1 is just 0
	if (strUsrInpOp1 == "0" || strUsrInpOp1 == "0.0" || strUsrInpOp1 == "0." || strUsrInpOp1 == ".0") {
		strReturnVal = "0-00000000-00000000000000000000000";
		//std::cout << "0-00000000-00000000000000000000000";
		//std::cout << std::endl;
	}
	//If Operand 1 is a decimal AND IS NOT negative AND '.' is not at the beginning AND '.' is not at the end. (Example 123.456
	//Note that != actually "if '.' is in there" while == means "if '-' is not in there"). when using the .find and std::string::npos. 
	else if ((strUsrInpOp1.find('.') != std::string::npos) && (strUsrInpOp1.find('-') == std::string::npos) && (strUsrInpOp1[0] != '.') && (strUsrInpOp1[strUsrInpOp1.size() - 1] != '.')) {
		//Grabs the LHS of Operand 1
		int i = 0;
		while (strUsrInpOp1[i] != '.') {
			strUsrInpOp1LHS += strUsrInpOp1[i];
			i++;
		}
		//Sanity Check
		//std::cout << "Left-hand side: " << strUsrInpOp1LHS;
		//std::cout << std::endl << std::endl;

		//Grabs RHS of Operand 1
		while (strUsrInpOp1[i] != '\0') {
			//if (strUsrInpOp1[i] != '.') {
			strUsrInpOp1RHS += strUsrInpOp1[i];
			//}
			i++; //Note that this has to be outside the if loop since even if the first character is a '.', we are still looping through the string. 
		}
		//Sanity Check
		//std::cout << "Right-hand side: " << strUsrInpOp1RHS;
		//std::cout << std::endl << std::endl;
		//We pass false indicating that the integer is not negative. 
		strReturnVal = fnStrIEEE754(false, strUsrInpOp1LHS, strUsrInpOp1RHS);

	}

	//(Example: -123.456) | IF Operand 1 is a decimal AND is negative AND '.' is not at the beginning AND '.' is not at the end. Note that the '.' would be the 2nd character or 1st element. 
	else if (strUsrInpOp1.find('.') != std::string::npos && (strUsrInpOp1.find('-') != std::string::npos) && (strUsrInpOp1[1] != '.') && (strUsrInpOp1[strUsrInpOp1.size() - 1] != '.')) {
		//Grabs the LHS of Operand 1
		//Notice how i = 1 to avoid grabbing the negative sign. 
		int i = 1;
		while (strUsrInpOp1[i] != '.') {
			strUsrInpOp1LHS += strUsrInpOp1[i];
			i++;
		}
		//Sanity Check
		//std::cout << "Left-hand side: " << strUsrInpOp1LHS;
		//std::cout << std::endl << std::endl;

		//Grabs RHS of Operand 1
		while (strUsrInpOp1[i] != '\0') {
			//if (strUsrInpOp1[i] != '.') {
			strUsrInpOp1RHS += strUsrInpOp1[i];
			//}
			i++; //Note that this has to be outside the if loop since even if the first character is a '.', we are still looping through the string. 
		}
		//Sanity Check
		//std::cout << "Right-hand side: " << strUsrInpOp1RHS;
		//std::cout << std::endl << std::endl;

		//We pass true indicating that the number is negative. 
		strReturnVal = fnStrIEEE754(true, strUsrInpOp1LHS, strUsrInpOp1RHS);

	}

	//========TO WORK ON========TO WORK ON========TO WORK ON========TO WORK ON========TO WORK ON========TO WORK ON=======
	//If Operand 1 is a decimal AND IS NOT negative AND HAS a decimal at the beginning. (Example: .123)
	else if ((strUsrInpOp1[0] == '.') && (strUsrInpOp1.find('-') == std::string::npos)) {
		//Sanity Check
		//std::cout << "Positive float value with decimal at the beginning.";
		//std::cout << std::endl;
		
		//Adds 0 before the decimal 
		reverse(strUsrInpOp1.begin(), strUsrInpOp1.end());
		strUsrInpOp1 += "0";
		reverse(strUsrInpOp1.begin(), strUsrInpOp1.end());

		//Sanity Check
		//std::cout << "Fixed. Now it is: " << strUsrInpOp1;
		//std::cout << std::endl;

		//Grabs the LHS of Operand 1
		int i = 0;
		while (strUsrInpOp1[i] != '.') {
			strUsrInpOp1LHS += strUsrInpOp1[i];
			i++;
		}
		//Sanity Check
		//std::cout << "Left-hand side: " << strUsrInpOp1LHS;
		//std::cout << std::endl << std::endl;

		//Grabs RHS of Operand 1
		while (strUsrInpOp1[i] != '\0') {
			//if (strUsrInpOp1[i] != '.') {
			strUsrInpOp1RHS += strUsrInpOp1[i];
			//}
			i++; //Note that this has to be outside the if loop since even if the first character is a '.', we are still looping through the string. 
		}
		//Sanity Check
		//std::cout << "Right-hand side: " << strUsrInpOp1RHS;
		//std::cout << std::endl << std::endl;
		//We pass false indicating that the integer is not negative. 
		strReturnVal = fnStrIEEE754(false, strUsrInpOp1LHS, strUsrInpOp1RHS);
	}

	//If Operand 1 is a decimal AND IS negative AND HAS a decimal at the beginning. (Example: -.123) | Note that the '.' would be the 2nd character or 1st element. 
	else if ((strUsrInpOp1[1] == '.') && (strUsrInpOp1.find('-') != std::string::npos)) {
		//Sanity Check
		//std::cout << "Negative float value with decimal at the beginning.";
		//std::cout << std::endl;
		//Add 0 before the decimal. 
		reverse(strUsrInpOp1.begin(), strUsrInpOp1.end());
		strUsrInpOp1[strUsrInpOp1.size() - 1] = '0';
		strUsrInpOp1 += "-";
		reverse(strUsrInpOp1.begin(), strUsrInpOp1.end());
		//Sanity Check
		//std::cout << "Fixed. Now it is: " << strUsrInpOp1;
		//std::cout << std::endl;
	}

	//If Operand 1 is a decimal AND IS NOT negative AND HAS a decimal at the end. (Example: 123.)
	else if ((strUsrInpOp1[strUsrInpOp1.size() - 1] == '.') && (strUsrInpOp1.find('-') == std::string::npos)) {
		//Sanity Check
		//std::cout << "Positive float value with decimal at the end.";
		//std::cout << std::endl;
		
		//Adds a 0 after the after the decimal. 
		strUsrInpOp1 += "0";

		//Sanity Check
		//std::cout << "Positive whole number.";
		//std::cout << std::endl;

		//Grabs the LHS of Operand 1
		int i = 0;
		while (strUsrInpOp1[i] != '.') {
			strUsrInpOp1LHS += strUsrInpOp1[i];
			i++;
		}
		
		//Sanity Check
		//std::cout << "Left-hand side: " << strUsrInpOp1LHS;
		//std::cout << std::endl << std::endl;

		//Grabs RHS of Operand 1
		while (strUsrInpOp1[i] != '\0') {
			//if (strUsrInpOp1[i] != '.') {
			strUsrInpOp1RHS += strUsrInpOp1[i];
			//}
			i++; //Note that this has to be outside the if loop since even if the first character is a '.', we are still looping through the string. 
		}
		//Sanity Check
		//std::cout << "Right-hand side: " << strUsrInpOp1RHS;
		//std::cout << std::endl << std::endl;
		
		//We pass false indicating that the integer is not negative. 
		strReturnVal = fnStrIEEE754(false, strUsrInpOp1LHS, strUsrInpOp1RHS);
	}

	//If Operand 1 is a decimal AND IS negative AND HAS a decimal at the (Example: -123.)
	else if ((strUsrInpOp1[strUsrInpOp1.size() - 1] == '.') && (strUsrInpOp1.find('-') != std::string::npos)) {
		//Sanity Check
		//std::cout << "Negative float value with decimal at the end.";
		//std::cout << std::endl;
		
		//Adds a 0 after the after the decimal.  
		strUsrInpOp1 += "0";

		//Sanity Check
		//std::cout << "Negative whole number.";
		//std::cout << std::endl;

		//Grabs the LHS of Operand 1
		//Notice how i = 1 to avoid grabbing the negative sign. 
		int i = 1;
		while (strUsrInpOp1[i] != '.') {
			strUsrInpOp1LHS += strUsrInpOp1[i];
			i++;
		}
		//Sanity Check
		//std::cout << "Left-hand side: " << strUsrInpOp1LHS;
		//std::cout << std::endl << std::endl;

		//Grabs RHS of Operand 1
		while (strUsrInpOp1[i] != '\0') {
			//if (strUsrInpOp1[i] != '.') {
			strUsrInpOp1RHS += strUsrInpOp1[i];
			//}
			i++; //Note that this has to be outside the if loop since even if the first character is a '.', we are still looping through the string. 
		}
		//Sanity Check
		//std::cout << "Right-hand side: " << strUsrInpOp1RHS;
		//std::cout << std::endl << std::endl;

		//We pass true indicating that the number is negative. 
		strReturnVal = fnStrIEEE754(true, strUsrInpOp1LHS, strUsrInpOp1RHS);
	}

	//If Operand 1 is a whole number/does not have a decimal AND IS NOT negative. (Example: 123)
	else if ((strUsrInpOp1.find('.') == std::string::npos) && (strUsrInpOp1.find('-') == std::string::npos)) {
		//Adds a decimal and 0 at the end.
		strUsrInpOp1 += ".0";

		//Sanity Check
		//std::cout << "Positive whole number.";
		//std::cout << std::endl;

		//Grabs the LHS of Operand 1
		int i = 0;
		while (strUsrInpOp1[i] != '.') {
			strUsrInpOp1LHS += strUsrInpOp1[i];
			i++;
		}
		//Sanity Check
		//std::cout << "Left-hand side: " << strUsrInpOp1LHS;
		//std::cout << std::endl << std::endl;

		//Grabs RHS of Operand 1
		while (strUsrInpOp1[i] != '\0') {
			//if (strUsrInpOp1[i] != '.') {
			strUsrInpOp1RHS += strUsrInpOp1[i];
			//}
			i++; //Note that this has to be outside the if loop since even if the first character is a '.', we are still looping through the string. 
		}
		//Sanity Check
		//std::cout << "Right-hand side: " << strUsrInpOp1RHS;
		//std::cout << std::endl << std::endl;
		
		//We pass false indicating that the integer is not negative. 
		strReturnVal = fnStrIEEE754(false, strUsrInpOp1LHS, strUsrInpOp1RHS);

	}

	//If Operand 1 is a whole number//does not have a decimal AND IS negative. (Example: -123)
	else if ((strUsrInpOp1.find('.') == std::string::npos) && (strUsrInpOp1.find('-') != std::string::npos)) {
		//Adds a decimal and a 0 at the end. 
		strUsrInpOp1 += ".0";

		//Sanity Check
		//std::cout << "Negative whole number.";
		//std::cout << std::endl;

		//Grabs the LHS of Operand 1
		//Notice how i = 1 to avoid grabbing the negative sign. 
		int i = 1;
		while (strUsrInpOp1[i] != '.') {
			strUsrInpOp1LHS += strUsrInpOp1[i];
			i++;
		}

		//Sanity Check
		//std::cout << "Left-hand side: " << strUsrInpOp1LHS;
		//std::cout << std::endl << std::endl;

		//Grabs RHS of Operand 1
		while (strUsrInpOp1[i] != '\0') {
			//if (strUsrInpOp1[i] != '.') {
			strUsrInpOp1RHS += strUsrInpOp1[i];
			//}
			i++; //Note that this has to be outside the if loop since even if the first character is a '.', we are still looping through the string. 
		}

		//Sanity Check
		//std::cout << "Right-hand side: " << strUsrInpOp1RHS;
		//std::cout << std::endl << std::endl;

		//We pass true indicating that the number is negative. 
		strReturnVal = fnStrIEEE754(true, strUsrInpOp1LHS, strUsrInpOp1RHS);

	}
	//might need to make an else statement here to account for numbers that do not have decimals. 
	//====================SEPERATE LHS AND RHS OF OPERAND 1 ENDS HERE=====================
	return strReturnVal;
}

int main() {
	// Statements
	std::cout << "\n==============================================================\n\nAssignment: IEEE 754\nAuthor of Program: Justin moua\nProfessor: N. Park \nCourse: CS 3443 | Computer Systems\n\n==============================================================\n\n";
	std::cout << std::endl << std::endl;
	
	//Variable Declaration
	double long dlUsrInpOp1;
	std::string strOperand1;

	double long dlUsrInpOp2;
	std::string strOperand2;

	double long dlSum;
	std::string strSum;

	double long dlProduct;
	std::string strProduct;

	//While loop to continously run the program until asked to stop.
	while (true) {
		std::cout << "Enter operand 1 here: ";
		std::cin >> strOperand1;
		std::cout << std::endl;
		dlUsrInpOp1 = std::stof(strOperand1); 		//Turns the string input into a float so we can add and multiply it. 

		std::cout << "Enter operand 2 here: ";
		std::cin >> strOperand2;
		std::cout << std::endl;
		dlUsrInpOp2 = std::stof(strOperand2); 		//Turns the string input into a float so we can add and multiply it. 

		//Addition and Multiplication are perforemd
		dlSum = dlUsrInpOp1 + dlUsrInpOp2;
		if (dlSum * 1 == 0) {
			strSum = "0.0";
		}
		else {
			strSum = std::to_string(dlSum);
		}

		dlProduct = dlUsrInpOp1 * dlUsrInpOp2;
		if (dlProduct * 1 == 0) {
			strProduct = "0.0";
		}
		else {
			strProduct = std::to_string(dlProduct);
		}

		std::cout << "Operand 1: " << fnSpacer(strOperand1);
		std::cout << std::endl;

		std::cout << "Operand 2: " << fnSpacer(strOperand2);
		std::cout << std::endl;

		std::cout << "Sum:       " << fnSpacer(strSum);
		std::cout << std::endl;

		std::cout << "Product:   " << fnSpacer(strProduct);
		std::cout << std::endl;

		std::cout << std::endl;


		//=====================WHILE LOOP TO STAY OR QUIT STARTS HERE=====================WHILE LOOP TO STAY OR QUIT STARTS HERE=====================
		bool boolStayOrQuit = true;
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
		//=====================WHILE LOOP TO STAY OR QUIT ENDS HERE=====================WHILE LOOP TO STAY OR QUIT ENDS HERE=====================

	}
	return 0;
}