#include <stdint.h>
#include <stdio.h>

union {
	double d;
	uint64_t l;
} pd;

int main() {
	pd.d = -13.0;
	uint64_t sign = (pd.l >> 63) & 1;
	uint64_t exponent = (pd.l >> 52) & 0xfff;

	uint64_t one = 1;
	
	uint64_t coef_mask = (one << 52) - 1;
	uint64_t coef = pd.l & coef_mask;

	printf("%d\n", sign);
	printf("%d\n", exponent);
	printf("0x%x\n", coef);
	
}