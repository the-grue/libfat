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

#include <fat/error.h>

const char *
fat_strerror(enum fat_error error)
{
	switch (error)
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
