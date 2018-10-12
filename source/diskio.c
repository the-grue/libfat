/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"

#include <stdio.h>

FILE *diskFile = NULL;

DSTATUS
disk_status(BYTE driveIndex)
{
	(void) driveIndex;

	if (diskFile == NULL) {
		return STA_NOINIT;
	} else {
		return 0;
	}
}

DSTATUS
disk_initialize(BYTE driveIndex)
{
	(void) driveIndex;

	if (diskFile != NULL)
	{
		return 0;
	}

	diskFile = fopen("fat.img", "rb+");
	if (diskFile == NULL)
	{
		diskFile = fopen("fat32.img", "wb+");
		if (diskFile == NULL) {
			return STA_NOINIT;
		}
	}

	return 0;
}

DRESULT
disk_read(BYTE driveIndex,
          BYTE *buff,
          DWORD sector,
          UINT count)
{
	(void) driveIndex;

	if (diskFile == NULL) {
		return RES_ERROR;
	}

	if (fseek(diskFile, sector * 512, SEEK_SET) != 0) {
		return RES_ERROR;
	}

	if (fread(buff, 512, count, diskFile) != count) {
		return RES_ERROR;
	}

	return RES_OK;
}

DRESULT
disk_write(BYTE driveIndex,
           const BYTE *buff,
           DWORD sector,
           UINT count)
{
	(void) driveIndex;

	if (diskFile == NULL) {
		return RES_ERROR;
	}

	if (fseek(diskFile, sector * 512, SEEK_SET) != 0) {
		return RES_ERROR;
	}

	if (fwrite(buff, 512, count, diskFile) != count) {
		return RES_ERROR;
	}

	return RES_OK;
}

DRESULT
disk_ioctl(BYTE driveIndex,
           BYTE cmd,
           void *buff)
{
	(void) driveIndex;
	(void) cmd;
	(void) buff;
	return RES_PARERR;
}
