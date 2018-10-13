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

#include "list.h"

#include "arg-iterator.h"
#include "common-opts.h"
#include "fdisk.h"

#include <fat/fat.h>
#include <fat/disk.h>
#include <fat/types.h>

#include <stdio.h>
#include <stdlib.h>

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

static int
ffutil_list_path(struct fat_fs *fs,
                 const char *path)
{
	(void) fs;

	struct fat_dir dir;

	FRESULT result = f_opendir(&dir, path);
	if (result != FR_OK)
	{
		fprintf(stderr, "Failed to open '%s'\n", path);
		return EXIT_FAILURE;
	}

	struct fat_file_info file_info;

	while (result == FR_OK)
	{
		result = f_readdir(&dir, &file_info);
		if (result != FR_OK)
		{
			break;
		}
		else if (file_info.fname[0] == 0)
		{
			break;
		}

		printf("%s\n", file_info.fname);
	}

	f_closedir(&dir);

	return EXIT_SUCCESS;
}

int
ffutil_list(const struct common_opts *common_opts,
            struct arg_iterator *iterator)
{
	struct ffutil_fdisk fdisk;

	ffutil_fdisk_init(&fdisk);

	int err = ffutil_fdisk_open(&fdisk, common_opts->disk_path, "rb+");
	if (err != 0)
	{
		fprintf(stderr, "Failed to open '%s' for writing.\n", common_opts->disk_path);
		ffutil_fdisk_done(&fdisk);
		return EXIT_FAILURE;
	}

	struct fat_fs fs;

	fs.disk = &fdisk.disk;

	/* Create an FAT volume */
	FRESULT result = f_mount(&fs, "", 0);
	if (result != FR_OK)
	{
		fprintf(stderr, "Failed to mount FAT volume: %s\n", fatfs_strerror(result));

		ffutil_fdisk_done(&fdisk);

		return EXIT_FAILURE;
	}

	arg_iterator_next(iterator);

	int exit_code = EXIT_SUCCESS;

	if (arg_iterator_at_end(iterator))
	{
		exit_code = ffutil_list_path(&fs, "/");
	}

	while (!arg_iterator_at_end(iterator))
	{
		const char *path = arg_iterator_get_current(iterator);
		if (path == NULL)
		{
			break;
		}

		exit_code = ffutil_list_path(&fs, path);
		if (exit_code != EXIT_SUCCESS)
		{
			break;
		}

		arg_iterator_next(iterator);
	}

	ffutil_fdisk_done(&fdisk);

	return exit_code;
}
