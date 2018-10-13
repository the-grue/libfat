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

#include "encode.h"

void
encode_uint16(fat_uint8 *ptr,
              fat_uint_least16 n)
{
	ptr[0] = (n >> 0) & 0xff;
	ptr[1] = (n >> 8) & 0xff;
}

void
encode_uint32(fat_uint8 *ptr,
              fat_uint_least32 n)
{
	ptr[0] = (n >> 0) & 0xff;
	ptr[1] = (n >> 8) & 0xff;
	ptr[2] = (n >> 16) & 0xff;
	ptr[3] = (n >> 24) & 0xff;
}

void
encode_uint64(fat_uint8 *ptr,
              fat_uint_least64 n)
{
	ptr[0] = (n >> 0) & 0xff;
	ptr[1] = (n >> 8) & 0xff;
	ptr[2] = (n >> 16) & 0xff;
	ptr[3] = (n >> 24) & 0xff;
	ptr[4] = (n >> 32) & 0xff;
	ptr[5] = (n >> 40) & 0xff;
	ptr[6] = (n >> 48) & 0xff;
	ptr[7] = (n >> 56) & 0xff;
}
