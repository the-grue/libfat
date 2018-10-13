/* libfat : A FAT file system library written in C.
 *
 * Copyright (C) 2018 Taylor Holberton
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "string.h"

void
fat_memcpy (void* dst, const void* src, fat_uint_least64 cnt)
{
	fat_uint8 *d = (fat_uint8 *) dst;

	const fat_uint8 *s = (const fat_uint8 *) src;

	if (cnt != 0) {
		do {
			*d++ = *s++;
		} while (--cnt);
	}
}


void
fat_memset (void* dst, int val, fat_uint_least64 cnt)
{
	fat_uint8 *d = (fat_uint8*) dst;

	do {
		*d++ = (fat_uint8)val;
	} while (--cnt);
}

int
fat_memcmp (const void* dst, const void* src, fat_uint_least64 cnt)
{
	const fat_uint8 *d = (const fat_uint8 *) dst;
	const fat_uint8 *s = (const fat_uint8 *) src;

	int r = 0;

	do {
		r = *d++ - *s++;
	} while (--cnt && r == 0);

	return r;
}


int
fat_strchr (const char* str, int chr)
{
	while (*str && *str != chr) str++;

	return *str;
}
