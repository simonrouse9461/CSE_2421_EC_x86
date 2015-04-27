// simplified disassembled pseudo code for main
int main(void) {

	// Initialize everything.
	short serial_1;
	short serial_2;
	short serial_3;
	short serial_4;
	char *name;
	
	// Read name.
	puts("Enter your name (First Last): ");
	gets(name);
	
	// Convert name to lowercase.
	for (i = 0; i < strlen(name); i++) {
		if ((name[i] >= 'A') && (name[i] <= 'Z')) {
			name[i] += 'a' - 'A';
		}
	}
	
	// Prompt for serial number.
	putchar('\n');
	puts("Enter your product's serial number: ");
	puts("(The serial number can be found on the back of the box, e.g. XXXX-XXXX-XXXX-XXXX)");
	scanf("%04x-%04x-%04x-%04x", &serial_1, &serial_2, &serial_3, &serial_4);
	putchar('\n');
	
	// test_key is the key point to this program, if this function returns 0 then the validation fails.
	// We need to analyze function test_key to avoid it from returning 0.
	eax = test_key(name, serial_1, serial_2, serial_3, serial_4);
	
	if (eax != 0) {
		// This method simply prints "Key accepted."
		correct(STK-1);
	} else {
	    // This method simply prints "Invalid key."
		incorrect(STK-1);
	}
	
	return 0;
}

// In order to find the correct serial number, further analysis on function test_key is needed.
// simplified disassembled pseudo code for function test_key
int test_key(char* name, short serial_1, short serial_2, short serial_3, short serial_4) {

	// This is the most tricky part of the program:
	// In the original binary file, there is a loop that iterates for six times. For each
	// time it iterates, one of the instructions in the loop changes the opcode of another
	// instruction whose operand is serial_4 and 0x8086. As a result, the value of serial_4
	// is modified for six times with different operations. In order, those opcode are add,
	// xor, sub, add, sub, and xor. Among them, an pair of continuous add and sub is eliminated.
	// So, after simplification, the actual effective instructions are as follows.
	serial_4 += 0x8086;
	serial_4 ^= 0x8086;
	serial_4 -= 0x8086;
	serial_4 ^= 0x8086;

    // Four instructions will be executed for each char in name
	for (i = 0; name[i]; i++){
		serial_1 -= (short)name[i];
		serial_2 -= (short)name[i];
		serial_3 += (short)name[i];
		serial_4 += (short)name[i];
	}

    // Validates the computed serial number
	if (serial_1 == 0xbeef) {
		if (serial_2 * serial_3 == 0xc0ffee) {
			if (serial_4 == 0x8086) {
				return 1;
			}
		}
	}

	return 0;
}

/***** The Pseudo Solution *****/
// The pseudo solution for serial number according to this disassembled code:
// Assume sum(char* x) is a function that returns the sum of all the char in string x.
// Assume factorize(int i) is a function that returns the largest factor of i which is
// smaller than the square root of i.
// In order to make sure that test_key returns 1, we must satisfy "serial_1 == 0xbeef",
// "serial_2 * serial_3 == 0xc0ffee", and "serial_4 == 0x8086", where serial_1, serial_2
// serial_3, and serial_4 are all final computed value rather than user input value.
// Then for user input value:
// serial_1 = 0xbeef + sum(name)
// serial_2 = factorize(0xc0ffee) + sum(name)
// serial_3 = 0xc0ffee / factorize(0xc0ffee) - sum(name)
// serial_4 = ((0x8086 - sum(name) ^ 0x8086) + 0x8086 ^ 0x8086) - 0x8086

/***** The Real Solution *****/
// I wrote a ruby program named serial_generator.rb which contains the real solution
// to the serial number program.
// That program implements the pseudo solution above.
// There are plenty of explanations in that file to describe how that works.
// That program should be run with command "ruby serial_generator.rb"