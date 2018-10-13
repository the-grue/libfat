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

#include <fat/object-info.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/** Represents an open file from
 * a FAT file system.
 * */

struct fat_file {
	/* Object identifier (must be the 1st member to detect invalid object pointer) */
	struct fat_object_info obj;
	/* File status flags */
	BYTE flag;
	/* Abort flag (error code) */
	BYTE err;
	/* File read/write pointer (Zeroed on file open) */
	FSIZE_t fptr;
	/* Current cluster of fpter (invalid when fptr is 0) */
	DWORD clust;
	/* Sector number appearing in buf[] (0:invalid) */
	DWORD sect;
#if !FF_FS_READONLY
	DWORD dir_sect; /* Sector number containing the directory entry (not used at exFAT) */
	BYTE* dir_ptr; /* Pointer to the directory entry in the win[] (not used at exFAT) */
#endif
#if FF_USE_FASTSEEK
	/* Pointer to the cluster link map table (nulled on open, set by application) */
	DWORD* cltbl;
#endif
#if !FF_FS_TINY
	/* File private data read/write window */
	BYTE buf[FF_MAX_SS];
#endif
};

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FAT_FILE_H */
