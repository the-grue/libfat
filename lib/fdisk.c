
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

#include "fdisk.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

struct fatfs_disk_data
{
	FILE *file;
};

static void
free_disk_data(struct fatfs_disk_data *disk_data)
{
	if (disk_data->file != NULL)
	{
		fclose(disk_data->file);
		disk_data->file = NULL;
	}
}

static fatfs_bool
fdisk_is_open(const struct fatfs_disk *disk)
{
	if ((disk->data == NULL)
	 || (disk->data->file == NULL))
	{
		return FATFS_FALSE;
	}

	return FATFS_TRUE;
}

static DSTATUS
fdisk_status(struct fatfs_disk *disk)
{
	if (disk->data->file == NULL) {
		return STA_NOINIT;
	} else {
		return 0;
	}
}

static DSTATUS
fdisk_initialize(struct fatfs_disk *disk)
{
	if (!fdisk_is_open(disk))
	{
		return STA_NOINIT;
	}

	if (fseek(disk->data->file, 0L, SEEK_SET) != 0)
	{
		return STA_NOINIT;
	}

	return 0;
}

static DRESULT
fdisk_read(struct fatfs_disk *disk,
           BYTE *buff,
           DWORD sector,
           UINT count)
{
	if (!fdisk_is_open(disk))
	{
		return RES_ERROR;
	}

	if (fseek(disk->data->file, sector * 512, SEEK_SET) != 0) {
		return RES_ERROR;
	}

	if (fread(buff, 512, count, disk->data->file) != count) {
		return RES_ERROR;
	}

	return RES_OK;
}

static DRESULT
fdisk_write(struct fatfs_disk *disk,
            const BYTE *buff,
            DWORD sector,
            UINT count)
{
	if (!fdisk_is_open(disk))
	{
		return RES_ERROR;
	}

	if (disk->data->file == NULL) {
		return RES_ERROR;
	}

	if (fseek(disk->data->file, sector * 512, SEEK_SET) != 0) {
		return RES_ERROR;
	}

	if (fwrite(buff, 512, count, disk->data->file) != count) {
		return RES_ERROR;
	}

	return RES_OK;
}

static DRESULT
get_sector_count(struct fatfs_disk *disk,
                 DWORD *sector_count)
{
	if (fseek(disk->data->file, 0L, SEEK_END) != 0) {
		return RES_ERROR;
	}

	long size = ftell(disk->data->file);
	if (size == -1L) {
		return RES_ERROR;
	}

	*sector_count = (DWORD) size;

	return RES_OK;
}

static DRESULT
get_block_size(struct fatfs_disk *disk,
               DWORD *block_size)
{
	(void) disk;

	*block_size = 512;

	return RES_OK;
}

DRESULT
fdisk_ioctl(struct fatfs_disk *disk,
            BYTE cmd,
            void *buff)
{
	if (!fdisk_is_open(disk))
	{
		return RES_ERROR;
	}

	switch (cmd) {
	case CTRL_SYNC:
		break;
	case GET_SECTOR_COUNT:
		return get_sector_count(disk, (DWORD *) buff);
	case GET_BLOCK_SIZE:
		return get_block_size(disk, (DWORD *) buff);
	default:
		return RES_PARERR;
	}

	return RES_OK;
}
void
ffutil_fdisk_init(struct ffutil_fdisk *fdisk)
{
	fatfs_disk_init(&fdisk->disk);
}

void
ffutil_fdisk_done(struct ffutil_fdisk *fdisk)
{
	if (fdisk->disk.data != NULL)
	{
		free_disk_data(fdisk->disk.data);
		free(fdisk->disk.data);
		fdisk->disk.data = NULL;
	}
}

int
ffutil_fdisk_open(struct ffutil_fdisk *fdisk,
                  const char *path,
                  const char *mode)
{
	if (fdisk->disk.data == NULL)
	{
		fdisk->disk.data = malloc(sizeof(struct fatfs_disk_data));
		if (fdisk->disk.data == NULL)
		{
			return -errno;
		}
	}

	fdisk->disk.data->file = fopen(path, mode);
	if (fdisk->disk.data->file == NULL)
	{
		return -errno;
	}

	return 0;
}

int
ffutil_fdisk_resize(struct ffutil_fdisk *fdisk,
                    long size)
{
	if (size <= 0)
	{
		return -EINVAL;
	}

	if (fseek(fdisk->disk.data->file, size - 1, SEEK_SET) != 0)
	{
		return -errno;
	}

	unsigned char null_byte = 0;

	fwrite(&null_byte, 1, 1, fdisk->disk.data->file);

	return 0;
}

