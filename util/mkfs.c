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

#include "mkfs.h"

#include "arg-iterator.h"
#include "common-opts.h"
#include "fdisk.h"

#include <fat/fat.h>
#include <fat/disk.h>
#include <fat/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct mkfs_opts
{
	unsigned long long int volume_size;
	unsigned long long int cluster_size;
};

static void
mkfs_opts_init(struct mkfs_opts *opts)
{
	opts->volume_size = 64 * 1024 * 1024;
	opts->cluster_size = 512;
}

static fat_bool
is_nonopt(const struct arg_iterator *iterator)
{
	if (arg_iterator_at_end(iterator))
	{
		return FAT_FALSE;
	}

	const char *nonopt = arg_iterator_get_current(iterator);

	if (nonopt[0] == '-')
	{
		return FAT_FALSE;
	}

	return FAT_TRUE;
}

static int
parse_volume_size(struct mkfs_opts *opts,
                  struct arg_iterator *iterator)
{
	const char *key = arg_iterator_get_current(iterator);
	if (key == NULL)
	{
		return -1;
	}

	if (strcmp(key, "--volume-size") != 0)
	{
		return 0;
	}

	arg_iterator_next(iterator);

	if (arg_iterator_at_end(iterator))
	{
		fprintf(stderr, "The '%s' option requires a volume size afterwards.\n", key);
		return -1;
	}

	const char *value = arg_iterator_get_current(iterator);

	if (sscanf(value, "%llu", &opts->volume_size) != 1)
	{
		fprintf(stderr, "Failed to convert volume size '%s' to an integer.\n", value);
		return -1;
	}

	/* convert to bytes */
	opts->volume_size *= 1024 * 1024;

	arg_iterator_next(iterator);

	return 1;
}

static int
parse_cluster_size(struct mkfs_opts *opts,
                  struct arg_iterator *iterator)
{
	const char *key = arg_iterator_get_current(iterator);
	if (key == NULL)
	{
		return -1;
	}

	if (strcmp(key, "--cluster-size") != 0)
	{
		return 0;
	}

	arg_iterator_next(iterator);

	if (arg_iterator_at_end(iterator))
	{
		fprintf(stderr, "The '%s' option requires a cluster size afterwards.\n", key);
		return -1;
	}

	const char *value = arg_iterator_get_current(iterator);

	if (sscanf(value, "%llu", &opts->cluster_size) != 1)
	{
		fprintf(stderr, "Failed to convert cluster size '%s' to an integer.\n", value);
		return -1;
	}

	arg_iterator_next(iterator);

	return 1;
}

static void
print_help(void)
{
	printf("Usage: ffutil mkfs [options]\n");
	printf("\n");
	printf("Options:\n");
	printf("	-h, --help          : Print this help content.\n");
	printf("	--cluster-size SIZE : Specify the cluster size (in bytes)\n");
	printf("	--volume-size  SIZE : Specify the volume size (in MiB)\n");
}

static int
parse_help(struct arg_iterator *iterator)
{
	const char *opt = arg_iterator_get_current(iterator);
	if ((strcmp(opt, "-h") == 0)
	 || (strcmp(opt, "--help") == 0))
	{
		print_help();
		return -1;
	}

	return 0;
}

static int
unknown_option(const struct arg_iterator *iterator)
{
	const char *opt = arg_iterator_get_current(iterator);
	fprintf(stderr, "Unknown option '%s'.\n", opt);
	fprintf(stderr, "\n");
	fprintf(stderr, "See -h or --help for assistance.\n");
	return EXIT_FAILURE;
}

static int
mkfs_opts_parse(struct mkfs_opts *opts,
                struct arg_iterator *iterator)
{
	int result = 0;

	while (!arg_iterator_at_end(iterator)) {

		result = parse_volume_size(opts, iterator);
		if (result < 0)
		{
			return EXIT_FAILURE;
		}
		else if (result > 0)
		{
			continue;
		}

		result = parse_cluster_size(opts, iterator);
		if (result < 0)
		{
			return EXIT_FAILURE;
		}
		else if (result > 0)
		{
			continue;
		}

		result = parse_help(iterator);
		if (result < 0)
		{
			return EXIT_FAILURE;
		}

		if (is_nonopt(iterator))
		{
			break;
		}
		else
		{
			return unknown_option(iterator);
		}
	}

	return EXIT_SUCCESS;
}

int
ffutil_mkfs(const struct common_opts *common_opts,
            struct arg_iterator *iterator)
{
	arg_iterator_next(iterator);

	struct mkfs_opts mkfs_opts;

	mkfs_opts_init(&mkfs_opts);

	int err = mkfs_opts_parse(&mkfs_opts, iterator);
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

	err = ffutil_fdisk_resize(&fdisk, mkfs_opts.volume_size);
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

	struct fat_fs fs;

	fs.disk = &fdisk.disk;

	/* Create an FAT volume */
	FRESULT result = f_mount(&fs, "", 0);
	if (result != FR_OK)
	{
		fprintf(stderr, "Failed to mount FAT volume: %s\n", fat_strerror(result));
		free(working_buffer);
		ffutil_fdisk_done(&fdisk);
		return EXIT_FAILURE;
	}

	result = f_mkfs(&fdisk.disk, "", FM_FAT32 | FM_SFD, mkfs_opts.cluster_size, working_buffer, working_buffer_size);
	if (result != FR_OK) {
		fprintf(stderr, "Failed to create FAT volume: %s.\n", fat_strerror(result));
		free(working_buffer);
		ffutil_fdisk_done(&fdisk);
		return EXIT_FAILURE;
	}

	free(working_buffer);

	ffutil_fdisk_done(&fdisk);

	return EXIT_SUCCESS;
}
