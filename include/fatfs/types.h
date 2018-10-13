/* FatFS : A FAT file system library written in C.
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

#ifndef FATFS_TYPES_H
#define FATFS_TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

typedef unsigned char fatfs_bool;

#ifndef FATFS_FALSE
#define FATFS_FALSE 0
#endif /* FATFS_FALSE */

#ifndef FATFS_TRUE
#define FATFS_TRUE 1
#endif /* FATFS_TRUE */

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FATFS_TYPES_H */
