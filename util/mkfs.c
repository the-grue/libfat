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

#include "mkfs.h"

#include "arg-iterator.h"
#include "common-opts.h"
#include "fdisk.h"

#include <fatfs.h>
#include <fatfs/disk.h>
#include <fatfs/types.h>

#include <stdio.h>
#include <stdlib.h>

struct mkfs_opts
{
	size_t volumn_size;
};

static int
parse_opts(struct mkfs_opts *opts,
           struct arg_iterator *iterator)
{
	(void) opts;

	while (!arg_iterator_at_end(iterator)) {

		arg_iterator_next(iterator);
	}

	return EXIT_SUCCESS;
}

static const char *
fatfs_strerror(FRESULT fresult)
{
	switch (fresult)
	{
	case FR_OK:
		return "success";
	case FR_DISK_ERR:
		return "a hardware error occurred on disk";
	case FR_INT_ERR:
		return "an assertion failed";
	case FR_NOT_READY:
		return "the physical drive does not work";
	case FR_NO_FILE:
		return "could not find the specified file";
	case FR_NO_PATH:
		return "could not find the specified path";
	case FR_INVALID_NAME:
		return "the path name format is invalid";
	case FR_DENIED:
		return "access denied";
	case FR_EXIST:
		return "file or directory already exists";
	case FR_INVALID_OBJECT:
		return "the file or directory object is invalid";
	case FR_WRITE_PROTECTED:
		return "the physical drive is write protected";
	case FR_INVALID_DRIVE:
		return "the logical drive number is invalid";
	case FR_NOT_ENABLED:
		return "the volumn has no work area";
	case FR_NO_FILESYSTEM:
		return "no valid FAT volume was found";
	case FR_MKFS_ABORTED:
		return "an unknown file system creation error occurred";
	case FR_TIMEOUT:
		return "could not get a grant to access the volume within the defined time period";
	case FR_LOCKED:
		return "the operation was aborted due to file sharing policy";
	case FR_NOT_ENOUGH_CORE:
		return "working buffer could not be allocated";
	case FR_TOO_MANY_OPEN_FILES:
		return "too many files are open";
	case FR_INVALID_PARAMETER:
		return "an invalid parameter was passed";
	}

	return "";
}

int
ffutil_mkfs(const struct common_opts *common_opts,
            struct arg_iterator *iterator)
{
	struct mkfs_opts opts;

	(void) common_opts;

	int err = parse_opts(&opts, iterator);
	if (err != 0)
	{
		return EXIT_FAILURE;
	}

	struct ffutil_fdisk fdisk;

	ffutil_fdisk_init(&fdisk);

	err = ffutil_fdisk_open(&fdisk, common_opts->disk_path, "wb+");
	if (err != 0)
	{
		fprintf(stderr, "Failed to open '%s' for writing.\n", common_opts->disk_path);
		ffutil_fdisk_done(&fdisk);
		return EXIT_FAILURE;
	}

	err = ffutil_fdisk_resize(&fdisk, 64 * 1024 * 1024);
	if (err != 0)
	{
		fprintf(stderr, "Failed to resize '%s'.\n", common_opts->disk_path);
		ffutil_fdisk_done(&fdisk);
		return EXIT_FAILURE;
	}

	size_t working_buffer_size = 32 * 1024;

	void *working_buffer = malloc(working_buffer_size);
	if (working_buffer == NULL)
	{
		fprintf(stderr, "Failed to allocate working buffer.\n");
		ffutil_fdisk_done(&fdisk);
		return EXIT_FAILURE;
	}

	FATFS FatFs;
	UINT clusterSize = 512;

	/* Create an FAT volume */
	FRESULT result = f_mount(&FatFs, "", 0);
	if (result != FR_OK)
	{
		fprintf(stderr, "Failed to mount FAT volume: %s\n", fatfs_strerror(result));
		free(working_buffer);
		ffutil_fdisk_done(&fdisk);
		return EXIT_FAILURE;
	}

	result = f_mkfs(&fdisk.disk, "", FM_FAT32, clusterSize, working_buffer, working_buffer_size);
	if (result != FR_OK) {
		fprintf(stderr, "Failed to create FAT volume: %s.\n", fatfs_strerror(result));
		free(working_buffer);
		ffutil_fdisk_done(&fdisk);
		return EXIT_FAILURE;
	}

	free(working_buffer);

	ffutil_fdisk_done(&fdisk);

	return EXIT_SUCCESS;
}
