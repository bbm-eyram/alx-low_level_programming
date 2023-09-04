#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * read_textfile - Reads a text file and prints it to the POSIX standard output
 * @filename: The name of the file to read
 * @letters: The number of letters to read and print
 *
 * Return: The actual number of letters read and printed,
 *         or 0 if the file cannot be opened or read
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
	int fd, num_read, num_written;
	char *buffer;

	/* Check if the filename is NULL */
	if (filename == NULL)
		return (0);

	/* Open the file in read-only mode */
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);

	/* Allocate memory for the buffer */
	buffer = malloc(sizeof(char) * (letters + 1));
	if (buffer == NULL)
	{
		close(fd);
		return (0);
	}

	/* Read the specified number of letters from the file */
	num_read = read(fd, buffer, letters);
	if (num_read == -1)
	{
		free(buffer);
		close(fd);
		return (0);
	}

	/* Close the file descriptor */
	close(fd);

	/* Print the read letters to the standard output */
	num_written = write(STDOUT_FILENO, buffer, num_read);
	if (num_written == -1 || num_written != num_read)
	{
		free(buffer);
		return (0);
	}

	/* Free the buffer memory */
	free(buffer);

	/* Return the number of letters read and printed */
	return (num_written);
}

