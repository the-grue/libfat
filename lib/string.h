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

#ifndef FAT_STRING_H
#define FAT_STRING_H

#include <fat/types.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

void
fat_memcpy(void *dst,
           const void *src,
           fat_uint_least64 size);

void
fat_memset(void *dst,
           int value,
           fat_uint_least64 size);

int
fat_memcmp(const void *dst,
           const void *src,
           fat_uint_least64 size);

int
fat_strchr(const char *str, int chr);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FAT_STRING_H */
