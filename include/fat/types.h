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

/** @file types.h
 * @brief Contains the type definitions
 * used throughout the project.
 * */

#ifndef FAT_TYPES_H
#define FAT_TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/** A boolean type.
 * Use the @ref FAT_FALSE
 * and @ref FAT_TRUE values
 * when assigning values to variables
 * of this type.
 * */

typedef unsigned char fat_bool;

/** The "false" value used by
 * boolean types.
 * */

#define FAT_FALSE 0

/** The "true" value used by
 * boolean types.
 * */

#define FAT_TRUE 1

/** An unsigned, 8-bit integer type.
 * */

typedef unsigned char fat_uint8;

/** An unsigned, 16-bit or
 * greater integer type.
 * */

typedef unsigned long long int fat_uint_least16;

/** An unsigned, 32-bit or
 * greater integer type.
 * */

typedef unsigned long int fat_uint_least32;

/** An unsigned, 64-bit or
 * greater integer type.
 * */

typedef unsigned long long int fat_uint_least64;

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FAT_TYPES_H */
