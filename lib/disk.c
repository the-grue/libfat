/*-----------------------------------------------------------------------*/
/* Low level disk_file I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include <fatfs/disk.h>

#include <stdio.h>

#ifndef NULL
#define NULL ((void *) 0x00)
#endif /* NULL */

void
fatfs_disk_init(struct fatfs_disk *disk)
{
	disk->data = NULL;
	disk->funcs.status = NULL;
	disk->funcs.initialize = NULL;
	disk->funcs.read = NULL;
	disk->funcs.write = NULL;
	disk->funcs.ioctl = NULL;
}

FILE *disk_file = NULL;

DSTATUS
disk_status(struct fatfs_disk *disk)
{
	if (disk->funcs.status == NULL)
	{
		return STA_NOINIT;
	}

	return disk->funcs.status(disk->data);
}

DSTATUS
disk_initialize(struct fatfs_disk *disk)
{
	if (disk->funcs.initialize == NULL)
	{
		return STA_NOINIT;
	}

	return disk->funcs.initialize(disk->data);
}

DRESULT
disk_read(struct fatfs_disk *disk,
          BYTE *buff,
          DWORD sector,
          UINT count)
{
	if (disk->funcs.read == NULL)
	{
		return RES_ERROR;
	}

	struct fatfs_read_operation read_operation;
	read_operation.buffer = buff;
	read_operation.sector = sector;
	read_operation.count = count;

	return disk->funcs.read(disk->data, &read_operation);
}

DRESULT
disk_write(struct fatfs_disk *disk,
           const BYTE *buff,
           DWORD sector,
           UINT count)
{
	if (disk->funcs.read == NULL)
	{
		return RES_ERROR;
	}

	struct fatfs_write_operation write_operation;
	write_operation.buffer = buff;
	write_operation.sector = sector;
	write_operation.count = count;

	return disk->funcs.write(disk->data, &write_operation);
}

DRESULT
disk_ioctl(struct fatfs_disk *disk,
           BYTE cmd,
           void *buff)
{
	if (disk->funcs.read == NULL)
	{
		return RES_ERROR;
	}

	return disk->funcs.ioctl(disk->data, cmd, buff);
}
