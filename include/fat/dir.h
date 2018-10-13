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

#ifndef FAT_DIR_H
#define FAT_DIR_H

#include <fat/object-info.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/** Represents a FAT file system directory.
 * */

struct fat_dir {
	/** Object information */
	struct fat_object_info obj;
	/** Current read/write offset */
	fat_uint_least32 dptr;
	/** Current cluster */
	fat_uint_least32 clust;
	/** Current sector (0:Read operation has terminated) */
	fat_uint_least32 sect;
	/** Pointer to the directory item in the win[] */
	fat_uint8* dir;
	/** SFN (in/out) {body[8],ext[3],status[1]} */
	fat_uint8 fn[12];
#if FF_USE_LFN
	/** Offset of current entry block being processed (0xFFFFFFFF:Invalid) */
	fat_uint_least32 blk_ofs;
#endif
#if FF_USE_FIND
	/** Pointer to the name matching pattern */
	const TCHAR* pat;
#endif
};

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FAT_DIR_H */
