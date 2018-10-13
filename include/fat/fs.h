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

#ifndef FAT_FS_H
#define FAT_FS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <fat/integer.h>
#include <fat/config.h>

/** This structure represents a
 * single FAT file system instance.
 * */

struct fat_fs
{
	/* Filesystem type (0:N/A) */
	BYTE fs_type;
	/* Number of FATs (1 or 2) */
	BYTE n_fats;
	/* win[] flag (b0:dirty) */
	BYTE wflag;
	/* FSINFO flags (b7:disabled, b0:dirty) */
	BYTE fsi_flag;
	/* Volume mount ID */
	WORD id;
	/* Number of root directory entries (FAT12/16) */
	WORD n_rootdir;
	/* Cluster size [sectors] */
	WORD csize;
#if FF_MAX_SS != FF_MIN_SS
	/* Sector size (512, 1024, 2048 or 4096) */
	WORD ssize;
#endif
#if FF_USE_LFN
	/* LFN working buffer */
	WCHAR* lfnbuf;
#endif
#if FF_FS_EXFAT
	/* Directory entry block scratchpad buffer for exFAT */
	BYTE* dirbuf;
#endif
#if FF_FS_REENTRANT
	/* Identifier of sync object */
	FF_SYNC_t sobj;
#endif
#if !FF_FS_READONLY
	/* Last allocated cluster */
	DWORD last_clst;
	/* Number of free clusters */
	DWORD free_clst;
#endif
#if FF_FS_RPATH
	/* Current directory start cluster (0:root) */
	DWORD cdir;
#if FF_FS_EXFAT
	/* Containing directory start cluster (invalid when cdir is 0) */
	DWORD cdc_scl;
	/* b31-b8:Size of containing directory, b7-b0: Chain status */
	DWORD cdc_size;
	/* Offset in the containing directory (invalid when cdir is 0) */
	DWORD cdc_ofs;
#endif
#endif
	/* Number of FAT entries (number of clusters + 2) */
	DWORD n_fatent;
	/* Size of an FAT [sectors] */
	DWORD fsize;
	/* Volume base sector */
	DWORD volbase;
	/* FAT base sector */
	DWORD fatbase;
	/* Root directory base sector/cluster */
	DWORD dirbase;
	/* Data base sector */
	DWORD database;
	/* Current sector appearing in the win[] */
	DWORD winsect;
	/* Disk access window for Directory, FAT (and file data at tiny cfg) */
	/** The disk that the file system is contained in. */
	BYTE win[FF_MAX_SS];
	/** The disk that the file system resides on. */
	struct fat_disk *disk;
};

#ifdef __cplusplus
}
#endif

#endif /* FAT_FS_H */
