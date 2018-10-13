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

#ifndef FATFS_DISK_H
#define FATFS_DISK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <fatfs/integer.h>

/** Enumerates the several possible
 * disk status codes.
 * */

typedef enum {
	/** The drive is in a normal
	 * working state. */
	STA_NORMAL = 0x00,
	/** Drive not initialized */
	STA_NOINIT = 0x01,
	/** No medium in the drive */
	STA_NODISK = 0x02,
	/** Write protected */
	STA_PROTECT = 0x04
} DSTATUS;

/* Enumerates the possible results
 * of a disk function.
 * */

typedef enum {
	/* 0: Successful */
	RES_OK = 0,
	/* 1: R/W Error */
	RES_ERROR,
	/* 2: Write Protected */
	RES_WRPRT,
	/* 3: Not Ready */
	RES_NOTRDY,
	/* 4: Invalid Parameter */
	RES_PARERR
} DRESULT;

struct fatfs_disk_data;

/** Encapsulates a read operation.
 * */

struct fatfs_read_operation {
	/** The buffer to put the data into. */
	void *buffer;
	/** The index of the sector to start
	 * reading from. */
	DWORD sector;
	/** The number of sectors to read. */
	UINT count;
};

/** Encapsulates a disk operation.
 * */

struct fatfs_write_operation {
	/** The buffer to write the data from. */
	const void *buffer;
	/** The sector to start writing the data at. */
	DWORD sector;
	/** The number of sectors to write. */
	UINT count;
};

/** Contains the functions that make up
 * the disk interface.
 * */

struct fatfs_disk_funcs {
	/** Gets the status of the disk. */
	DSTATUS (*status)(struct fatfs_disk_data *data);
	/** Initializes the disk. */
	DSTATUS (*initialize)(struct fatfs_disk_data *data);
	/** Reads from the disk. */
	DRESULT (*read)(struct fatfs_disk_data *data,
	                struct fatfs_read_operation *read_operation);
	/** Writes to the disk. */
	DRESULT (*write)(struct fatfs_disk_data *data,
	                 struct fatfs_write_operation *write_operation);
	/** Mimics an ioctl function for the disk. */
	DRESULT (*ioctl)(struct fatfs_disk_data *data,
	                 BYTE cmd,
	                 void *buffer);
};

/** Contains a disk instance.
 * */

struct fatfs_disk {
	/** The disk implementation data. */
	struct fatfs_disk_data *data;
	/** The functions defined
	 * by the disk. */
	struct fatfs_disk_funcs funcs;
};

/** Initializes a disk structure.
 * @param disk The disk structure to initialize.
 * */

void
fatfs_disk_init(struct fatfs_disk *disk);

/** Initializes a disk for reading and writing.
 * @returns See @ref DSTATUS for a list
 * of possible return values.
 * */

DSTATUS
disk_initialize(struct fatfs_disk *disk);

/** Queries the status of a disk.
 * @returns See @ref DSTATUS for a list
 * of possible return values.
 * */

DSTATUS
disk_status(struct fatfs_disk *disk);

/** Reads data from a disk.
 * @param buff The buffer to put the data into.
 * @param sector The index of the sector to start
 * the read operation at.
 * @param count The number of sectors to read.
 * @returns See @ref DSTATUS for a list
 * of possible return values.
 * */

DRESULT
disk_read(struct fatfs_disk *disk,
          BYTE* buff,
          DWORD sector,
          UINT count);

/** Writes data to a disk.
 * @param buff The buffer to get the data from.
 * @param sector The index of the sector to start
 * the write operation at.
 * @param count The number of sectors to write.
 * @returns See @ref DSTATUS for a list
 * of possible return values.
 * */

DRESULT
disk_write(struct fatfs_disk *disk,
           const BYTE* buff,
           DWORD sector,
           UINT count);

/** Mimics an ioctl call to the disk.
 * @param disk An initialized disk instance.
 * @param cmd The ioctl command.
 * @param buffer The buffer to put the data into.
 * @returns See @ref DSTATUS for a list
 * of possible return values.
 * */

DRESULT
disk_ioctl(struct fatfs_disk *disk,
           BYTE cmd,
           void *buffer);

/* Command code for disk_ioctrl fucntion */

/* Generic command (Used by FatFs) */
#define CTRL_SYNC			0	/* Complete pending write process (needed at FF_FS_READONLY == 0) */
#define GET_SECTOR_COUNT	1	/* Get media size (needed at FF_USE_MKFS == 1) */
#define GET_SECTOR_SIZE		2	/* Get sector size (needed at FF_MAX_SS != FF_MIN_SS) */
#define GET_BLOCK_SIZE		3	/* Get erase block size (needed at FF_USE_MKFS == 1) */
#define CTRL_TRIM			4	/* Inform device that the data on the block of sectors is no longer used (needed at FF_USE_TRIM == 1) */

/* Generic command (Not used by FatFs) */
#define CTRL_POWER			5	/* Get/Set power status */
#define CTRL_LOCK			6	/* Lock/Unlock media removal */
#define CTRL_EJECT			7	/* Eject media */
#define CTRL_FORMAT			8	/* Create physical format on the media */

/* MMC/SDC specific ioctl command */
#define MMC_GET_TYPE		10	/* Get card type */
#define MMC_GET_CSD			11	/* Get CSD */
#define MMC_GET_CID			12	/* Get CID */
#define MMC_GET_OCR			13	/* Get OCR */
#define MMC_GET_SDSTAT		14	/* Get SD status */
#define ISDIO_READ			55	/* Read data form SD iSDIO register */
#define ISDIO_WRITE			56	/* Write data to SD iSDIO register */
#define ISDIO_MRITE			57	/* Masked write data to SD iSDIO register */

/* ATA/CF specific ioctl command */
#define ATA_GET_REV			20	/* Get F/W revision */
#define ATA_GET_MODEL		21	/* Get model name */
#define ATA_GET_SN			22	/* Get serial number */

#ifdef __cplusplus
}
#endif

#endif /* FATFS_DISK_H */
