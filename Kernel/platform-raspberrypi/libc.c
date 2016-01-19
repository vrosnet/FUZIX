#include <kernel.h>

void *memcpy(void *d, const void *s, size_t sz)
{
	unsigned char *dp = d;
	const unsigned char *sp = s;
	while(sz--)
		*dp++=*sp++;
	return d;
}

void *memset(void *d, int c, size_t sz)
{
	unsigned char *p = d;
	while(sz--)
		*p++ = c;
	return d;
}

size_t strlen(const char *p)
{
	const char *e = p;
	while(*e++);
	return e-p-1;
}

int strcmp(const char *s1, const char *s2) 
{
	char c1, c2;

	while ((c1 = *s1++) == (c2 = *s2++) && c1)
		;
	return c1 - c2;
}

int memcmp(const void* s1, const void* s2, size_t n)
{
	const uint8_t* p1 = (const uint8_t*) s1;
	const uint8_t* p2 = (const uint8_t*) s2;
	uint8_t c1 = 0;
	uint8_t c2 = 0;

	while (n-- > 0)
	{
		c1 = *p1++;
		c2 = *p2++;
		if (c1 != c2)
			break;
	}

	return c1 - c2;
}

void raise(int sig)
{
	panic("raise()");
}

uint16_t read_unaligned_16(const uint8_t* addr)
{
	return addr[0] | (addr[1]<<8);
}

uint32_t read_unaligned_32(const uint8_t* addr)
{
	return read_unaligned_16(addr) | (read_unaligned_16(addr+2) << 16);
}

uint16_t write_unaligned_16(uint8_t* addr, uint16_t value)
{
	addr[0] = value;
	addr[1] = value>>8;
	return value;
}

uint32_t write_unaligned_32(uint8_t* addr, uint32_t value)
{
	write_unaligned_16(addr, value);
	write_unaligned_16(addr+2, value>>16);
	return value;
}

