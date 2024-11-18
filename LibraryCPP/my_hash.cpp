#include <string>
#include "my_hash.h"

#define BLOCK_SIZE 32

static uint8_t get_byte(uint8_t *block, const uint8_t *T)
{
	uint8_t ans = 0;
	for (int i = 0; i < BLOCK_SIZE; i++) {
		ans ^= block[i];
		ans = T[ans];
	}
	
	return ans;
}

static Hash get_block_hash(const char *block, const uint8_t *permutation, const uint8_t *substitution, const uint8_t *T)
{
	uint8_t data[BLOCK_SIZE];
	uint8_t array[BLOCK_SIZE];

	for (int ind = 0; ind < BLOCK_SIZE; ind++)
		data[ind] = (uint8_t)block[ind];

	Hash ans = 0;
	uint8_t byte = get_byte(data, T);
	for (size_t i = 0; i < sizeof(Hash); i++) {
		for (size_t ind = 0; ind < BLOCK_SIZE; ind++)
			array[ind] = substitution[data[permutation[ind]] ^ byte];
		for (size_t ind = 0; ind < BLOCK_SIZE; ind++)
			data[ind] = array[ind];

		byte = get_byte(data, T);
		ans = (ans << 8) | byte;
	}
	
	return ans;
}

Hash my_hash(std::string a, const uint8_t *permutation, const uint8_t *substitution, const uint8_t *T)
{
	Hash ans = 0;
	a.push_back('a');
	while (a.length() % BLOCK_SIZE)
		a.push_back('b');

	const char *data = a.c_str();
	for (size_t i = 0; i < (a.length() / BLOCK_SIZE); i++) 
		ans = ((ans << 1) | (__builtin_popcount(ans) % 2)) ^ get_block_hash(data + i * BLOCK_SIZE, permutation, substitution, T);

	return ans;
}

Hash my_hash1(std::string a)
{
	const uint8_t permutation[] = {24, 29, 27, 8, 10, 13, 22, 21, 1, 0, 26, 15, 25, 20, 17, 2, 11, 14, 31, 6, 7, 16, 23, 3, 9, 5, 4, 30, 12, 28, 19, 18};
	const uint8_t substitution[] = {10, 105, 232, 46, 88, 71, 43, 233, 222, 239, 202, 55, 215, 92, 94, 170, 237, 60, 20, 110, 160, 181, 180, 28, 253, 30, 141, 34, 204, 137, 197, 21, 38, 212, 128, 49, 70, 54, 113, 136, 120, 99, 133, 44, 165, 52, 200, 13, 58, 107, 130, 0, 143, 214, 227, 98, 63, 177, 193, 102, 121, 26, 104, 14, 145, 198, 36, 122, 135, 206, 48, 144, 11, 37, 154, 162, 169, 148, 151, 150, 242, 100, 149, 241, 194, 247, 179, 220, 8, 124, 12, 173, 117, 40, 183, 123, 139, 59, 3, 42, 147, 189, 226, 62, 95, 223, 191, 93, 51, 234, 85, 156, 207, 86, 236, 47, 245, 254, 248, 205, 231, 185, 152, 167, 69, 35, 33, 158, 199, 108, 118, 75, 81, 255, 196, 87, 216, 217, 61, 208, 9, 109, 82, 115, 157, 6, 163, 195, 56, 119, 96, 174, 116, 79, 184, 17, 64, 176, 131, 57, 101, 155, 7, 78, 18, 83, 243, 68, 5, 114, 103, 106, 219, 228, 142, 50, 126, 41, 27, 190, 168, 171, 201, 230, 80, 229, 32, 16, 19, 132, 90, 252, 153, 25, 127, 125, 186, 175, 24, 77, 161, 187, 246, 224, 213, 146, 72, 178, 164, 4, 140, 225, 39, 1, 66, 111, 31, 67, 65, 188, 134, 249, 166, 238, 251, 159, 29, 250, 235, 218, 91, 221, 84, 192, 211, 210, 182, 138, 2, 22, 209, 112, 76, 23, 129, 172, 97, 89, 74, 203, 240, 45, 15, 73, 53, 244};
	const uint8_t T[] = {250, 192, 101, 241, 48, 92, 235, 247, 199, 132, 17, 197, 105, 234, 165, 219, 134, 154, 198, 22, 84, 163, 7, 166, 130, 96, 220, 146, 183, 161, 70, 209, 210, 34, 90, 15, 76, 240, 181, 245, 133, 237, 218, 10, 208, 152, 29, 71, 21, 112, 53, 145, 59, 62, 113, 238, 99, 171, 227, 82, 242, 184, 115, 195, 49, 149, 135, 207, 32, 95, 60, 107, 27, 232, 6, 164, 248, 186, 0, 85, 162, 119, 255, 231, 38, 196, 31, 23, 200, 125, 114, 221, 8, 148, 79, 144, 205, 126, 173, 139, 175, 251, 78, 141, 246, 11, 20, 24, 35, 170, 3, 213, 12, 142, 36, 239, 87, 168, 159, 178, 110, 254, 86, 249, 64, 224, 88, 111, 223, 122, 41, 66, 100, 52, 30, 83, 151, 25, 222, 214, 215, 194, 72, 193, 55, 28, 179, 229, 61, 206, 63, 9, 69, 43, 233, 140, 50, 182, 102, 225, 188, 81, 98, 14, 26, 44, 180, 46, 252, 74, 155, 68, 156, 150, 5, 108, 73, 204, 103, 104, 109, 187, 129, 54, 228, 56, 217, 158, 117, 45, 120, 138, 124, 121, 230, 91, 211, 51, 136, 201, 116, 4, 153, 65, 57, 172, 77, 123, 131, 212, 18, 106, 244, 47, 40, 185, 37, 190, 39, 226, 16, 176, 94, 147, 243, 236, 137, 97, 177, 67, 157, 203, 80, 143, 2, 169, 174, 189, 42, 191, 89, 75, 19, 253, 202, 127, 1, 216, 160, 167, 93, 33, 13, 128, 58, 118};

	return my_hash(a, permutation, substitution, T);
}

Hash my_hash2(std::string a)
{
	const uint8_t permutation[] = {18, 4, 13, 12, 31, 9, 5, 11, 25, 10, 22, 20, 7, 27, 8, 24, 23, 3, 15, 16, 17, 14, 6, 26, 29, 28, 30, 2, 21, 0, 1, 19};
	const uint8_t substitution[] = {159, 169, 100, 155, 2, 154, 26, 61, 210, 197, 133, 70, 231, 77, 67, 51, 237, 132, 23, 191, 158, 116, 36, 1, 194, 223, 9, 129, 171, 108, 174, 4, 153, 12, 113, 142, 249, 151, 208, 139, 44, 101, 244, 87, 57, 242, 239, 20, 19, 31, 245, 45, 11, 209, 68, 7, 241, 92, 252, 196, 184, 150, 238, 141, 80, 35, 29, 146, 183, 232, 143, 52, 218, 145, 90, 149, 8, 53, 172, 89, 97, 34, 200, 122, 222, 164, 27, 201, 195, 50, 166, 48, 25, 86, 49, 163, 235, 253, 144, 66, 243, 109, 251, 176, 33, 69, 246, 234, 225, 228, 105, 106, 14, 199, 6, 131, 82, 157, 120, 104, 0, 152, 240, 125, 73, 78, 74, 192, 138, 83, 185, 96, 64, 227, 32, 76, 229, 117, 56, 38, 170, 162, 123, 121, 214, 59, 93, 41, 72, 17, 28, 39, 46, 148, 217, 75, 110, 79, 204, 111, 118, 58, 247, 173, 188, 102, 16, 182, 181, 160, 124, 233, 98, 24, 179, 207, 126, 216, 10, 140, 190, 55, 178, 21, 136, 60, 107, 119, 13, 37, 115, 43, 203, 254, 250, 177, 94, 88, 220, 114, 71, 175, 65, 62, 85, 134, 221, 255, 137, 95, 226, 40, 213, 54, 230, 30, 42, 156, 215, 248, 198, 63, 168, 127, 202, 18, 130, 219, 47, 15, 161, 22, 84, 193, 205, 135, 189, 128, 91, 3, 81, 5, 147, 112, 236, 211, 187, 180, 165, 224, 186, 212, 167, 103, 99, 206};
	const uint8_t T[] = {79, 103, 1, 17, 73, 121, 143, 171, 189, 152, 251, 166, 66, 3, 28, 51, 41, 95, 69, 248, 208, 159, 202, 136, 112, 234, 200, 26, 5, 122, 125, 25, 53, 91, 144, 82, 187, 153, 123, 97, 163, 6, 180, 52, 22, 86, 35, 244, 139, 245, 20, 185, 177, 61, 223, 151, 240, 133, 193, 113, 16, 188, 63, 129, 130, 181, 11, 226, 145, 184, 116, 206, 54, 27, 57, 15, 42, 246, 147, 64, 182, 117, 83, 100, 221, 214, 30, 212, 31, 174, 89, 242, 19, 104, 194, 4, 36, 235, 114, 161, 247, 162, 9, 14, 70, 199, 157, 179, 167, 218, 183, 126, 80, 62, 142, 0, 48, 37, 252, 141, 238, 155, 21, 146, 60, 198, 216, 47, 94, 7, 160, 59, 101, 250, 201, 33, 138, 233, 18, 93, 158, 120, 230, 249, 124, 227, 45, 207, 149, 148, 46, 49, 150, 76, 107, 135, 137, 87, 254, 243, 172, 105, 231, 186, 191, 106, 12, 23, 178, 203, 2, 255, 128, 220, 40, 43, 119, 108, 210, 55, 34, 164, 196, 232, 170, 72, 211, 195, 134, 96, 204, 132, 205, 224, 228, 118, 253, 229, 77, 81, 50, 173, 78, 71, 127, 111, 219, 197, 115, 84, 140, 98, 24, 217, 74, 8, 13, 75, 39, 169, 68, 32, 38, 99, 56, 44, 67, 222, 58, 175, 110, 215, 209, 10, 154, 131, 92, 85, 29, 192, 156, 90, 165, 236, 109, 65, 102, 239, 237, 213, 168, 176, 225, 190, 241, 88};

	return my_hash(a, permutation, substitution, T);
}

