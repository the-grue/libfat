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

#ifndef FAT_ENCODE_H
#define FAT_ENCODE_H

#include <fat/types.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

void
encode_uint16(fat_uint8 *ptr,
              fat_uint_least16 n);

void
encode_uint32(fat_uint8 *ptr,
              fat_uint_least32 n);

void
encode_uint64(fat_uint8 *ptr,
              fat_uint_least64 n);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FAT_ENCODE_H */
