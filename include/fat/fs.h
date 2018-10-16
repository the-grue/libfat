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
#include <fat/error.h>
#include <fat/types.h>

/** This structure represents a
 * single FAT file system instance.
 * */

struct fat_fs
{
	/** Filesystem type (0:N/A) */
	fat_uint8 fs_type;
	/** Number of FATs (1 or 2) */
	fat_uint8 n_fats;
	/** win[] flag (b0:dirty) */
	fat_uint8 wflag;
	/** FSINFO flags (b7:disabled, b0:dirty) */
	fat_uint8 fsi_flag;
	/** Volume mount ID */
	fat_uint_least16 id;
	/** Number of root directory entries (FAT12/16) */
	fat_uint_least16 n_rootdir;
	/** Cluster size [sectors] */
	fat_uint_least16 csize;
#if FF_MAX_SS != FF_MIN_SS
	/** Sector size (512, 1024, 2048 or 4096) */
	fat_uint_least16 ssize;
#endif
#if FF_USE_LFN
	/** LFN working buffer */
	WCHAR* lfnbuf;
#endif
#if FF_FS_EXFAT
	/** Directory entry block scratchpad buffer for exFAT */
	fat_uint8* dirbuf;
#endif
#if FF_FS_REENTRANT
	/** Identifier of sync object */
	FF_SYNC_t sobj;
#endif
	/** Last allocated cluster */
	fat_uint_least32 last_clst;
	/** Number of free clusters */
	fat_uint_least32 free_clst;
#if FF_FS_RPATH
	/** Current directory start cluster (0:root) */
	fat_uint_least32 cdir;
#if FF_FS_EXFAT
	/** Containing directory start cluster (invalid when cdir is 0) */
	fat_uint_least32 cdc_scl;
	/** b31-b8:Size of containing directory, b7-b0: Chain status */
	fat_uint_least32 cdc_size;
	/** Offset in the containing directory (invalid when cdir is 0) */
	fat_uint_least32 cdc_ofs;
#endif
#endif
	/** Number of FAT entries (number of clusters + 2) */
	fat_uint_least32 n_fatent;
	/** Size of an FAT [sectors] */
	fat_uint_least32 fsize;
	/** Volume base sector */
	fat_uint_least32 volbase;
	/** FAT base sector */
	fat_uint_least32 fatbase;
	/** Root directory base sector/cluster */
	fat_uint_least32 dirbase;
	/** Data base sector */
	fat_uint_least32 database;
	/** Current sector appearing in the win[] */
	fat_uint_least32 winsect;
	/** Disk access window for Directory, FAT (and file data at tiny cfg) */
	fat_uint8 win[FF_MAX_SS];
	/** The disk that the file system resides on. */
	struct fat_disk *disk;
};

/** Initializes a file system structure.
 * @param fs The file system structure to initialize.
 * */

void
fat_fs_init(struct fat_fs *fs);

/** Creates a new directory.
 * This function will fail if the directory already
 * exists, or if the parent directory does not exist yet.
 * @param fs The file system to create the directory on.
 * @param path The path of the directory to create.
 * @returns See @ref fat_error for return values.
 * */

enum fat_error
fat_mkdir(struct fat_fs *fs,
          const char *path);

#ifdef __cplusplus
}
#endif

#endif /* FAT_FS_H */
