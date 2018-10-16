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

#ifndef FAT_SUPERBLOCK_H
#define FAT_SUPERBLOCK_H

#include <fat/types.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/** Contains information about the on-disk file system.
 * */

struct fat_superblock
{
	/** The number of bytes per logical sector. */
	fat_uint_least16 bytes_per_sector;
	/** The number of sectors per cluster. */
	fat_uint8 sectors_per_cluster;
	/** The number of sectors reserved
	 * before the first FAT. */
	fat_uint_least16 reserved_sector_count;
	/** The number of FATs in the file system. */
	fat_uint8 fat_count;
	/** The maximum number of entries in the
	 * root directory for FAT16. */
	fat_uint_least16 root_dir_entry_max;
	/** The number of sectors in the file system.
	 * If this is set to zero, then @ref sector_count32
	 * should be set as well. */
	fat_uint_least16 sector_count_16bit;
	/** The media descriptor.
	 * Always set to 0xf8 (fixed disk.) */
	fat_uint8 media_descriptor;
	/** The number of sectors per FAT. */
	fat_uint_least16 sectors_per_fat_16bit;
	/** The number of sectors in a single track. */
	fat_uint_least16 sectors_per_track;
	/** The number of heads on the disk. */
	fat_uint_least16 head_count;
	/** The number of hidden sectors preceding
	 * the partition that contains the FAT volume.
	 * This is not used by this library. */
	fat_uint_least32 hidden_sector_count;
	/** The number of sectors on the file system,
	 * in 32-bit format. */
	fat_uint_least32 sector_count_32bit;
	/** The number of sectors per FAT, in 32-bit format. */
	fat_uint_least32 sectors_per_fat_32bit;
	/** A bitwise description of the drive
	 * that contains this file system. */
	fat_uint_least16 drive_description;
	/** The version of this file system. */
	fat_uint_least16 version;
	/** The cluster index of the root directory. */
	fat_uint_least32 root_directory_cluster;
	/** The index of the sector containing the
	 * file system information. */
	fat_uint_least16 information_sector;
	/** The starting sector of the copies
	 * of the three FAT boot sectors. */
	fat_uint_least16 copy_sector;
	/** Reserved. */
	fat_uint8[12] reserved;
	/** Physical drive number. */
	fat_uint8 physical_drive_number;
	/** TODO : name this variable,
	 * perhaps in a union with multiple
	 * names since it has multiple uses. */
	fat_uint8 name_this_variable;
	/** Extended boot signature. */
	fat_uint8 extended_boot_signature;
	/** The volume ID. */
	fat_uint8[4] volume_id;
	/** The volume label. */
	fat_uint8[11] volume_label;
	/** The file system type, padded
	 * with spaces. */
	fat_uint8[8] fs_type;
};

/** Initializes the FAT superblock with default values.
 * @param superblock The superblock to initialize.
 * */

void
fat_superblock_init(struct fat_superblock *superblock);

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FAT_SUPERBLOCK_H */
