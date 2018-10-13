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

#include "mkdir.h"

#include "arg-iterator.h"
#include "common-opts.h"
#include "fdisk.h"

#include <fat/fat.h>
#include <fat/disk.h>
#include <fat/types.h>

#include <stdio.h>
#include <stdlib.h>

int
ffutil_mkdir(const struct common_opts *common_opts,
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
	FRESULT result = f_mount(&fs, "", 1);
	if (result != FR_OK)
	{
		fprintf(stderr, "Failed to mount FAT volume: %s\n", fat_strerror(result));
		ffutil_fdisk_done(&fdisk);
		return EXIT_FAILURE;
	}

	arg_iterator_next(iterator);

	if (arg_iterator_at_end(iterator))
	{
		fprintf(stderr, "Missing at least one directory path.\n");
		ffutil_fdisk_done(&fdisk);
		return EXIT_FAILURE;
	}

	while (!arg_iterator_at_end(iterator))
	{
		const char *path = arg_iterator_get_current(iterator);
		if (path == NULL)
		{
			break;
		}

		result = fat_mkdir(&fs, path);
		if (result != FR_OK)
		{
			fprintf(stderr, "Failed to create '%s': %s.\n", path, fat_strerror(result));
			break;
		}

		arg_iterator_next(iterator);
	}

	ffutil_fdisk_done(&fdisk);

	if (result == FR_OK)
	{
		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}
