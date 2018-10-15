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

#ifndef FAT_FILE_H
#define FAT_FILE_H

#include <fat/config.h>
#include <fat/object-info.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/** Represents an open file from
 * a FAT file system.
 * */

struct fat_file {
	/** Object identifier (must be the 1st member to detect invalid object pointer) */
	struct fat_object_info obj;
	/** File status flags */
	fat_uint8 flag;
	/** Abort flag (error code) */
	fat_uint8 err;
	/** File read/write pointer (Zeroed on file open) */
	FSIZE_t fptr;
	/** Current cluster of fpter (invalid when fptr is 0) */
	fat_uint_least32 clust;
	/** Sector number appearing in buf[] (0:invalid) */
	fat_uint_least32 sect;
#if !FF_FS_READONLY
	/** Sector number containing the directory entry (not used at exFAT) */
	fat_uint_least32 dir_sect;
	/** Pointer to the directory entry in the win[] (not used at exFAT) */
	fat_uint8* dir_ptr;
#endif
#if FF_USE_FASTSEEK
	/** Pointer to the cluster link map table (nulled on open, set by application) */
	fat_uint_least32* cltbl;
#endif
#if !FF_FS_TINY
	/** File private data read/write window */
	fat_uint8 buf[FF_MAX_SS];
#endif
};

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FAT_FILE_H */
