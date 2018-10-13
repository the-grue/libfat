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

#ifndef FAT_UTIL_FDISK_H
#define FAT_UTIL_FDISK_H

#include <fat/disk.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

struct ffutil_fdisk
{
	struct fat_disk disk;
};

void
ffutil_fdisk_init(struct ffutil_fdisk *fdisk);

void
ffutil_fdisk_done(struct ffutil_fdisk *fdisk);

int
ffutil_fdisk_open(struct ffutil_fdisk *fdisk,
                  const char *path,
                  const char *mode);

int
ffutil_fdisk_resize(struct ffutil_fdisk *fdisk,
                    long size);

#ifdef __cplusplus
/* extern "C" */
#endif /* __cplusplus */

#endif /* FAT_UTIL_FDISK_H */
