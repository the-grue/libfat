#include <fatfs.h>

#include <stdio.h>
#include <stdlib.h>

int main (int argc, const char **argv)
{
	(void) argc;
	(void) argv;

	size_t working_buffer_size = 32 * 1024;

	void *working_buffer = malloc(working_buffer_size);

	FATFS FatFs;

	UINT clusterSize = 512;

	/* Create an FAT volume */
	f_mount(&FatFs, "", 0);

	if (f_mkfs("", FM_FAT32, clusterSize, working_buffer, working_buffer_size)) {
		printf("Failed to create FAT volume. Adjust volume size or cluster size.\n");
		free(working_buffer);
		return EXIT_FAILURE;
	}

	free(working_buffer);

	return EXIT_SUCCESS;
}
