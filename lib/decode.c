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

#include "decode.h"

fat_uint_least16
decode_uint16(const fat_uint8 *ptr)
{
	fat_uint_least16 n = 0;
	n |= ((const fat_uint_least16) ptr[0]);
	n |= ((const fat_uint_least16) ptr[1]) << 8;
	return n;
}

fat_uint_least32
decode_uint32(const fat_uint8 *ptr)
{
	fat_uint_least32 n = 0;
	n |= ((const fat_uint_least32) ptr[0]);
	n |= ((const fat_uint_least32) ptr[1]) << 8;
	n |= ((const fat_uint_least32) ptr[2]) << 16;
	n |= ((const fat_uint_least32) ptr[3]) << 24;
	return n;
}

fat_uint_least64
decode_uint64(const fat_uint8 *ptr)
{
	fat_uint_least64 n = 0;
	n |= ((const fat_uint_least64) ptr[0]);
	n |= ((const fat_uint_least64) ptr[1]) << 8;
	n |= ((const fat_uint_least64) ptr[2]) << 16;
	n |= ((const fat_uint_least64) ptr[3]) << 24;
	n |= ((const fat_uint_least64) ptr[4]) << 32;
	n |= ((const fat_uint_least64) ptr[5]) << 40;
	n |= ((const fat_uint_least64) ptr[6]) << 48;
	n |= ((const fat_uint_least64) ptr[7]) << 56;
	return n;
}
