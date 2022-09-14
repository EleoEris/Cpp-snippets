#include <iostream>

struct Color {
	Color() {}

	union {
		uint32_t rgba = 0;
		struct {
			uint8_t r, g, b, a;
		};
	};

	void print() {
		std::cout << std::hex << "RGBA(" << (int)r << ", " << (int)g << ", " << (int)b << ", " << (int)a << ")\t(" << rgba << ")\n";
	}
};

int main(int argc, char* argv[]) {
	Color A, B;
	A.print();
	A.a = 0xff;
	A.g = 0xaa;
	A.print();
	A.rgba = 0x116699aa;
	A.print();
	system("pause");
}

// Output: 
// RGBA(0, 0, 0, 0)        (0)
// RGBA(0, aa, 0, ff)      (ff00aa00) // be careful
// RGBA(aa, 99, 66, 11)    (116699aa) // about the order
