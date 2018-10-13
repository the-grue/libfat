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

#ifndef FAT_ERROR_H
#define FAT_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif

/** Enumerates the several possible
 * error codes of a file system operation.
 * */

enum fat_error {
	/* (0) Succeeded */
	FR_OK = 0,
	/* (1) A hard error occurred in the low level disk I/O layer */
	FR_DISK_ERR,
	/* (2) Assertion failed */
	FR_INT_ERR,
	/* (3) The physical drive cannot work */
	FR_NOT_READY,
	/* (4) Could not find the file */
	FR_NO_FILE,
	/* (5) Could not find the path */
	FR_NO_PATH,
	/* (6) The path name format is invalid */
	FR_INVALID_NAME,
	/* (7) Access denied due to prohibited access or directory full */
	FR_DENIED,
	/* (8) Access denied due to prohibited access */
	FR_EXIST,
	/* (9) The file/directory object is invalid */
	FR_INVALID_OBJECT,
	/* (10) The physical drive is write protected */
	FR_WRITE_PROTECTED,
	/* (11) The logical drive number is invalid */
	FR_INVALID_DRIVE,
	/* (12) The volume has no work area */
	FR_NOT_ENABLED,
	/* (13) There is no valid FAT volume */
	FR_NO_FILESYSTEM,
	/* (14) The f_mkfs() aborted due to any problem */
	FR_MKFS_ABORTED,
	/* (15) Could not get a grant to access the volume within defined period */
	FR_TIMEOUT,
	/* (16) The operation is rejected according to the file sharing policy */
	FR_LOCKED,
	/* (17) LFN working buffer could not be allocated */
	FR_NOT_ENOUGH_CORE,
	/* (18) Number of open files > FF_FS_LOCK */
	FR_TOO_MANY_OPEN_FILES,
	/* (19) Given parameter is invalid */
	FR_INVALID_PARAMETER
};

/** Returns a human readable version of an error code.
 * @param error The error code to convert to a string.
 * @returns A human readable version of the error code.
 * */

const char *
fat_strerror(enum fat_error error);

#ifdef __cplusplus
}
#endif

#endif /* FAT_ERROR_H */
