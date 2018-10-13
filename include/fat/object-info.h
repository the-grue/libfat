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

#ifndef FAT_OBJECT_INFO_H
#define FAT_OBJECT_INFO_H

#include <fat/types.h>
#include <fat/integer.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/** Contains information about
 * a file system object.
 * */

struct fat_object_info
{
	/* Pointer to the hosting volume of this object */
	struct fat_fs* fs;
	/* Hosting volume mount ID */
	fat_uint_least16 id;
	/* Object attribute */
	fat_uint8 attr;
	/* Object chain status (b1-0: =0:not contiguous, =2:contiguous, =3:flagmented in this session, b2:sub-directory stretched) */
	fat_uint8 stat;
	/* Object data start cluster (0:no cluster or root directory) */
	fat_uint_least32 sclust;
	/* Object size (valid when sclust != 0) */
	FSIZE_t objsize;
#if FF_FS_EXFAT
	/* Size of first fragment - 1 (valid when stat == 3) */
	fat_uint_least32 n_cont;
	/* Size of last fragment needs to be written to FAT (valid when not zero) */
	fat_uint_least32 n_frag;
	/* Containing directory start cluster (valid when sclust != 0) */
	fat_uint_least32 c_scl;
	/* b31-b8:Size of containing directory, b7-b0: Chain status (valid when c_scl != 0) */
	fat_uint_least32 c_size;
	/* Offset in the containing directory (valid when file object and sclust != 0) */
	fat_uint_least32 c_ofs;
#endif
#if FF_FS_LOCK
	/* File lock ID origin from 1 (index of file semaphore table Files[]) */
	UINT lockid;
#endif
};

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FAT_OBJECT_INFO_H */
