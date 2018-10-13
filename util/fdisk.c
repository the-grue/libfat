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

#include "fdisk.h"

#include <fat/types.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

struct fat_disk_data
{
	FILE *file;
};

static void
free_disk_data(struct fat_disk_data *disk_data)
{
	if (disk_data->file != NULL)
	{
		fclose(disk_data->file);
		disk_data->file = NULL;
	}
}

static fat_bool
fdisk_is_open(const struct fat_disk_data *disk_data)
{
	if ((disk_data == NULL)
	 || (disk_data->file == NULL)) {
		return FAT_FALSE;
	}

	return FAT_TRUE;
}

static DSTATUS
fdisk_status(struct fat_disk_data *disk_data)
{
	if (!fdisk_is_open(disk_data))
	{
		return STA_NOINIT;
	}

	return STA_NORMAL;
}

static DSTATUS
fdisk_initialize(struct fat_disk_data *disk_data)
{
	if (!fdisk_is_open(disk_data))
	{
		return STA_NOINIT;
	}

	if (fseek(disk_data->file, 0L, SEEK_SET) != 0)
	{
		return STA_NOINIT;
	}

	return STA_NORMAL;
}

static DRESULT
fdisk_read(struct fat_disk_data *disk_data,
           struct fat_read_operation *read_operation)
{
	if (!fdisk_is_open(disk_data))
	{
		return RES_ERROR;
	}

	if (fseek(disk_data->file, read_operation->sector, SEEK_SET) != 0)
	{
		return RES_ERROR;
	}

	size_t read_count = fread(read_operation->buffer, 512, read_operation->count, disk_data->file);
	if (read_count != read_operation->count)
	{
		return RES_ERROR;
	}

	return RES_OK;
}

static DRESULT
fdisk_write(struct fat_disk_data *disk_data,
            struct fat_write_operation *write_operation)
{
	if (!fdisk_is_open(disk_data))
	{
		return RES_ERROR;
	}

	if (fseek(disk_data->file, write_operation->sector, SEEK_SET) != 0)
	{
		return RES_ERROR;
	}

	size_t write_count = fwrite(write_operation->buffer, 512, write_operation->count, disk_data->file);
	if (write_count != write_operation->count)
	{
		return RES_ERROR;
	}

	return RES_OK;
}

static DRESULT
fdisk_get_sector_count(struct fat_disk_data *disk_data,
                       DWORD *sector_count)
{
	if (fseek(disk_data->file, 0L, SEEK_END) != 0)
	{
		return RES_ERROR;
	}

	long size = ftell(disk_data->file);
	if (size == -1L)
	{
		return RES_ERROR;
	}

	if (sector_count != NULL)
	{
		*sector_count = (DWORD)(((unsigned long int) size) / 512UL);
	}

	return RES_OK;
}

static DRESULT
fdisk_get_sector_size(DWORD *sector_size)
{
	if (sector_size != NULL)
	{
		*sector_size = 512;
	}

	return RES_OK;
}

static DRESULT
fdisk_get_block_size(DWORD *block_size)
{
	if (block_size != NULL)
	{
		/* A block size of one means
		 * that this is a non-flash media. */
		*block_size = 1;
	}

	return RES_OK;
}

static DRESULT
fdisk_ioctl(struct fat_disk_data *disk_data,
            BYTE cmd,
            void *buffer)
{
	switch (cmd)
	{
	case GET_SECTOR_COUNT:
		return fdisk_get_sector_count(disk_data, (DWORD *) buffer);
	case GET_SECTOR_SIZE:
		return fdisk_get_sector_size((DWORD *) buffer);
	case GET_BLOCK_SIZE:
		return fdisk_get_block_size((DWORD *) buffer);
	case CTRL_SYNC:
	case CTRL_TRIM:
		break;
	default:
		return RES_PARERR;
	}

	return RES_OK;
}

void
ffutil_fdisk_init(struct ffutil_fdisk *fdisk)
{
	fat_disk_init(&fdisk->disk);
	fdisk->disk.funcs.status = fdisk_status;
	fdisk->disk.funcs.initialize = fdisk_initialize;
	fdisk->disk.funcs.read = fdisk_read;
	fdisk->disk.funcs.write = fdisk_write;
	fdisk->disk.funcs.ioctl = fdisk_ioctl;
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
		fdisk->disk.data = malloc(sizeof(struct fat_disk_data));
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
