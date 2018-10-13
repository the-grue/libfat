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

#include <fatfs.h>
#include <fatfs/disk.h>

#include <stdio.h>
#include <stdlib.h>

int main (int argc, const char **argv)
{
	(void) argc;
	(void) argv;

	struct fatfs_disk disk;

	size_t working_buffer_size = 32 * 1024;

	void *working_buffer = malloc(working_buffer_size);

	FATFS FatFs;

	UINT clusterSize = 512;

	/* Create an FAT volume */
	f_mount(&FatFs, "", 0);

	if (f_mkfs(&disk, "", FM_FAT32, clusterSize, working_buffer, working_buffer_size)) {
		printf("Failed to create FAT volume. Adjust volume size or cluster size.\n");
		free(working_buffer);
		return EXIT_FAILURE;
	}

	free(working_buffer);

	return EXIT_SUCCESS;
}
