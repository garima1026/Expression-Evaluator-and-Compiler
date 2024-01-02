/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"


    UnlimitedInt::UnlimitedInt() : size(1), sign(1), capacity(1), unlimited_int(new int[1]) {
        unlimited_int[0] = 0;
    }

    UnlimitedInt::UnlimitedInt(string s) {
        size = 0;
        capacity = s.size();
        unlimited_int = new int[capacity];

        if (s.size() == 1 && s[0] == '0') {
            sign = 0;
            unlimited_int[size++] = 0;
        } else if (s[0] == '-') {
            sign = -1;
            for (long unsigned int i = 1; i < s.size(); i++) {
                unlimited_int[size++] = s[i] - '0';
            }
        } else {
            sign = 1;
            for (long unsigned int i = 0; i < s.size(); i++) {
                unlimited_int[size++] = s[i] - '0';
            }
        }

    }

    UnlimitedInt::UnlimitedInt(int i) {
        size = 0;
        sign = (i < 0) ? -1 : 1;
        i = std::abs(i);
        int temp = i;

        while (temp > 0) {
            temp /= 10;
            size++;
        }

        capacity = size;
        unlimited_int = new int[capacity];

        for (int j = size - 1; j >= 0; j--) {
            unlimited_int[j] = i % 10;
            i /= 10;
        }
    }

    UnlimitedInt::UnlimitedInt(int* ulimited_int, int cap, int sgn, int sz) {
        capacity = cap;
        size = sz;
        sign = sgn;
        unlimited_int = new int[capacity];

        for (int i = 0; i < size; i++) {
            unlimited_int[i] = ulimited_int[i];
        }
    }


    UnlimitedInt::~UnlimitedInt() {
        delete[] unlimited_int;
    }

    int UnlimitedInt::get_size() {
        return size;
    }

    int* UnlimitedInt::get_array() {
        return unlimited_int;
    }

    int UnlimitedInt::get_sign() {
        return sign;
    }

    int UnlimitedInt::get_capacity() {
        return capacity; 
    }

 UnlimitedInt* UnlimitedInt::add(UnlimitedInt* i1, UnlimitedInt* i2) {
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();

    int* array1 = i1->get_array();
    int* array2 = i2->get_array();

    int size1 = i1->get_size();
    int size2 = i2->get_size();

    int resultSign = 1; // Default to positive
    int resultSize = std::max(size1, size2) + 1; // +1 for possible carry
    int* resultArray = new int[resultSize];

    int carry = 0;
    int i = size1 - 1;
    int j = size2 - 1;
    int k = resultSize - 1;

    
    
    auto compare_magnitude = [&](UnlimitedInt* a, UnlimitedInt* b) {
        if (a->get_size() < b->get_size()) return -1;
        if (a->get_size() > b->get_size()) return 1;
        for (int i = 0; i < a->get_size(); i++) {
            if (a->get_array()[i] < b->get_array()[i]) return -1;
            if (a->get_array()[i] > b->get_array()[i]) return 1;
        }
        return 0;
    };

    if ((sign1 == -1 && sign2 == 1) || (sign1 == 1 && sign2 == -1)) {
        // One number is negative, and the other is positive
        UnlimitedInt abs_i1(array1, size1, 1, size1);
        UnlimitedInt abs_i2(array2, size2, 1, size2);

        int magnitudeComparison = compare_magnitude(&abs_i1, &abs_i2);

        if (magnitudeComparison > 0) {
            // Absolute value of i1 is greater, subtract abs_i2 from abs_i1
            while (i >= 0 || j >= 0 || carry != 0) {
                int num1 = (i >= 0) ? abs_i1.get_array()[i] : 0;
                int num2 = (j >= 0) ? abs_i2.get_array()[j] : 0;

                int diff = num1 - num2 - carry;
                if (diff < 0) {
                    diff += 10;
                    carry = 1;
                } else {
                    carry = 0;
                }

                resultArray[k] = diff;

                i--;
                j--;
                k--;
            }

            // Set the sign of the result based on the original signs
            resultSign = (sign1 == -1) ? -1 : 1;
        } else if (magnitudeComparison < 0) {
            // Absolute value of i2 is greater, subtract abs_i1 from abs_i2
            while (i >= 0 || j >= 0 || carry != 0) {
                int num1 = (i >= 0) ? abs_i1.get_array()[i] : 0;
                int num2 = (j >= 0) ? abs_i2.get_array()[j] : 0;

                int diff = num2 - num1 - carry;
                if (diff < 0) {
                    diff += 10;
                    carry = 1;
                } else {
                    carry = 0;
                }

                resultArray[k] = diff;

                i--;
                j--;
                k--;
            }

            // Set the sign of the result based on the original signs
            resultSign = (sign2 == -1) ? -1 : 1;
        } else {
            // Magnitudes are equal, result is zero
            resultArray[0] = 0;
            resultSize = 1;
        }
    } else {
        // Both numbers have the same sign or both are zero
        while (i >= 0 || j >= 0 || carry != 0) {
            int num1 = (i >= 0) ? array1[i] : 0;
            int num2 = (j >= 0) ? array2[j] : 0;

            int sum = num1 + num2 + carry;
            carry = sum / 10;
            resultArray[k] = sum % 10;

            i--;
            j--;
            k--;
        }

        // Set the sign of the result based on the original signs
        resultSign = sign1; // This assumes both signs are the same or both are zero
    }
    
    // Remove leading zeros from the result
    while (resultSize > 1 && resultArray[0] == 0) {
        for (int l = 0; l < resultSize - 1; l++) {
            resultArray[l] = resultArray[l + 1];
        }
        resultSize--;
    }
int resultCapacity =0;
if(resultSign==1){resultCapacity=resultSize;}
else{resultCapacity=resultSize+1 ;}


    UnlimitedInt* result = new UnlimitedInt(resultArray, resultCapacity, resultSign, resultSize);

    delete[] resultArray;

    return result;
}

UnlimitedInt* UnlimitedInt::sub(UnlimitedInt* i1, UnlimitedInt* i2) {
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();

   // int* array1 = i1->get_array();
    int* array2 = i2->get_array();

    //int size1 = i1->get_size();
    int size2 = i2->get_size();

    //int resultSign = 1; // Default to positive
    //int resultSize = std::max(size1, size2); // Result size won't exceed max of input sizes
    //int* resultArray = new int[resultSize];


    if (sign1 == 1 && sign2 == 1) {
        // Both numbers are positive
        UnlimitedInt neg_i2(array2, size2, -1, size2);
        UnlimitedInt* result = UnlimitedInt::add(i1 ,&neg_i2);
        return result;


    } else if (sign1 == -1 && sign2 == -1) {
        // Both numbers are negative
        UnlimitedInt neg_i2(array2, size2, 1, size2);
        UnlimitedInt* result = UnlimitedInt::add(i1 ,&neg_i2);
        return result;

    
    } else {

        if (sign1 == 1&& sign2== -1) {
            UnlimitedInt neg_i2(array2, size2, 1, size2);
            UnlimitedInt* result = UnlimitedInt::add(i1 ,&neg_i2);
            return result;
        } else {
            UnlimitedInt neg_i2(array2, size2, -1, size2);
            UnlimitedInt* result = UnlimitedInt::add(i1 ,&neg_i2);
            return result;
        }
    }
}

UnlimitedInt* UnlimitedInt::mul(UnlimitedInt* i1, UnlimitedInt* i2) {
    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();
    
    int* array1 = i1->get_array();
    int* array2 = i2->get_array();
    
    int size1 = i1->get_size();
    int size2 = i2->get_size();
    
    // Calculate the sign of the result
    int resultSign = (sign1 == sign2) ? 1 : -1;
    
    // Calculate the size of the result
    int resultSize = size1 + size2;
    
    // Initialize an array to store the result of multiplication
    int* resultArray = new int[resultSize];
    for (int i = 0; i < resultSize; i++) {
        resultArray[i] = 0;
    }
    
    // Perform long multiplication
    for (int i = size1 - 1; i >= 0; i--) {
        int carry = 0;
        int num1 = array1[i];
        
        for (int j = size2 - 1, k = i + size2; j >= 0; j--, k--) {
            int num2 = array2[j];
            int product = num1 * num2 + carry + resultArray[k];
            resultArray[k] = product % 10;
            carry = product / 10;
        }
        
        if (carry > 0) {
            resultArray[i] = carry;
        }
    }
    
    // Remove leading zeros from the result
    while (resultSize > 1 && resultArray[0] == 0) {
        for (int l = 0; l < resultSize - 1; l++) {
            resultArray[l] = resultArray[l + 1];
        }
        resultSize--;
    }
    
    UnlimitedInt* result = new UnlimitedInt(resultArray, resultSize, resultSign, resultSize);
    
    delete[] resultArray;
    
    return result;
}

UnlimitedInt* UnlimitedInt::div(UnlimitedInt* i1, UnlimitedInt* i2) {



 auto compare= [&](UnlimitedInt* num1, UnlimitedInt* num2){
        if (num1->get_size() < num2->get_size()) {
            return -1;
        }
        if (num1->get_size() > num2->get_size()) {
            return 1;
        }

        for (int i = 0; i < num1->get_size(); i++) {
            if (num1->get_array()[i] < num2->get_array()[i]) {
                return -1;
            }
            if (num1->get_array()[i] > num2->get_array()[i]) {
                return 1;
            }
        }

        return 0; // The two numbers are equal
    };





    // Make both numbers positive for the division
    UnlimitedInt* num1 = new UnlimitedInt(i1->get_array(), i1->get_capacity(), 1, i1->get_size());
    UnlimitedInt* num2 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), 1, i2->get_size());
    UnlimitedInt* result = new UnlimitedInt("0");

    // Check if i2 is zero, division by zero is undefined
    if (i2->get_size() == 1 && i2->get_array()[0] == 0) {
        delete num1;
        delete num2;
        return result;  // Division by zero
    }

    int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();
    int resultSign = sign1 * sign2;

    // Ensure num1 is greater than or equal to num2
    if (compare(num1,num2) < 0) {
        delete num1;
        delete num2;
        return result;
    }

    // Initialize temp as a copy of num1
    UnlimitedInt* temp = new UnlimitedInt(*num1);

    while (compare(temp,num2) >= 0) {
        *temp = *sub(temp, num2);  // Subtract num2 from temp
        *result = *add(result, new UnlimitedInt(1));  // Increment result by 1
    }

    result->sign=(resultSign);

    delete num1;
    delete num2;
    delete temp;

    return result;
}

UnlimitedInt* UnlimitedInt::mod(UnlimitedInt* i1, UnlimitedInt* i2) {

    UnlimitedInt* quotient = div(i1, i2);
    UnlimitedInt* product = mul(i2,quotient);
    UnlimitedInt* result = sub(i1, product);

    delete quotient;
    delete product;

    return result;
}

 string UnlimitedInt::to_string() {
        std :: string result;

        if (sign == -1) {
            result += "-";
        }

        for (int i = 0; i < size; i++) {
            result += std::to_string(unlimited_int[i]);
        }

        return result;
    }