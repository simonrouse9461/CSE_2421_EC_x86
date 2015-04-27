// simplified disassembled pseudo code for function __TMC_END__
int __TMC_END__(char* name, short serial_1, short serial_2, short serial_3, short serial_4) {

	serial_4 += 0x8086;
	serial_4 ^= 0x8086;
	serial_4 -= 0x8086;
	serial_4 ^= 0x8086;
	
	for (i = 0; name[i]; i++){
		serial_1 -= (short)name[i];
		serial_2 -= (short)name[i];
		serial_3 += (short)name[i];
		serial_4 += (short)name[i];
	}
	
	if (serial_1 == 0xbeef) {
		if (serial_2 * serial_3 == 0xc0ffee) {
			if (serial_4 == 0x8086) {
				return 1;
			}
		}
	}
	
	return 0;
}

// Solution for serial number according to this disassembled code:
// Assume sum(char* x) is a function that returns the sum of all the char in string x.
// Assume factorize(int i) is a function that returns the largest factor of i which is
// smaller than the square root of i.
// Then:
// serial_1 = 0xbeef + sum(name)
// serial_2 = factorize(0xc0ffee) + sum(name)
// serial_3 = 0xc0ffee / factorize(0xc0ffee) - sum(name)
// serial_4 = ((0x8086 - sum(name) ^ 0x8086) + 0x8086 ^ 0x8086) - 0x8086