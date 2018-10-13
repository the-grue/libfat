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

FILE *disk_file = NULL;

DSTATUS
disk_status(struct fatfs_disk *disk)
{
	(void) disk;

	if (disk_file == NULL) {
		return STA_NOINIT;
	} else {
		return 0;
	}
}

DSTATUS
disk_initialize(struct fatfs_disk *disk)
{
	(void) disk;

	if (disk_file != NULL)
	{
		return 0;
	}

	disk_file = fopen("fat.img", "rb+");
	if (disk_file == NULL)
	{
		disk_file = fopen("fat.img", "wb+");
		if (disk_file == NULL) {
			return STA_NOINIT;
		}
	}

	return 0;
}

DRESULT
disk_read(struct fatfs_disk *disk,
          BYTE *buff,
          DWORD sector,
          UINT count)
{
	(void) disk;

	if (disk_file == NULL) {
		return RES_ERROR;
	}

	if (fseek(disk_file, sector * 512, SEEK_SET) != 0) {
		return RES_ERROR;
	}

	if (fread(buff, 512, count, disk_file) != count) {
		return RES_ERROR;
	}

	return RES_OK;
}

DRESULT
disk_write(struct fatfs_disk *disk,
           const BYTE *buff,
           DWORD sector,
           UINT count)
{
	(void) disk;

	if (disk_file == NULL) {
		return RES_ERROR;
	}

	if (fseek(disk_file, sector * 512, SEEK_SET) != 0) {
		return RES_ERROR;
	}

	if (fwrite(buff, 512, count, disk_file) != count) {
		return RES_ERROR;
	}

	return RES_OK;
}

static DRESULT
get_sector_count(DWORD *sector_count)
{
	if (disk_file == NULL) {
		return RES_ERROR;
	}

	if (fseek(disk_file, 0L, SEEK_END) != 0) {
		return RES_ERROR;
	}

	long size = ftell(disk_file);
	if (size == -1L) {
		return RES_ERROR;
	}

	*sector_count = (DWORD) size;

	return RES_OK;
}

static DRESULT
get_block_size(DWORD *block_size)
{
	*block_size = 512;

	return RES_OK;
}

DRESULT
disk_ioctl(struct fatfs_disk *disk,
           BYTE cmd,
           void *buff)
{
	(void) disk;

	switch (cmd) {
	case CTRL_SYNC:
		break;
	case GET_SECTOR_COUNT:
		return get_sector_count((DWORD *) buff);
	case GET_BLOCK_SIZE:
		return get_block_size((DWORD *) buff);
	default:
		return RES_PARERR;
	}

	return RES_OK;
}
