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

#ifndef FAT_HOST_H
#define FAT_HOST_H

#include <fat/types.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

struct fat_host_data;

/** Used to provide an interface from the
 * host system to the library.
 * */

struct fat_host
{
	/** Initializes a host data instance. */
	struct fat_host_data *(*init)(void);
	/** Releases memory allocated by the host data. */
	void (*done)(struct fat_host_data *host_data);
	/** Allocates memory from the host. */
	void *(*malloc)(struct fat_host_data *host_data,
	             fat_size size);
	/** Releases memory allocated by the host. */
	void (*free)(struct fat_host_data *host_data,
	          void *addr);
};

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FAT_HOST_H */
