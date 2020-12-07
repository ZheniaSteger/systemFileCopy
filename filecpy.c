//==============================================================================
// Author      : Zhenia Steger
// Purpose     : Demonstrate file copying at the system level.
// =============================================================================

#include <stdio.h>  // standard IO
#include <unistd.h> // declares read() and write()
#include <fcntl.h>  // declares flags for open functions

// MAIN: Runs the program from command line.
// USAGE: filecpy.c "input file" "output file"
//
// Using only open(), close(), read() and write() system calls

int main(int argc, char *argv[])
{
  // Check that we have 3 arguments, throw error if any other amount.
  if (argc != 3) {
    fprintf(stderr, "Error. Not enough arguments.\n");
    return -1;
  }

  // File descriptors are integer values.
  // Declare values for the input file and output file to be used later in the code.
  int inputFile, outputFile;

  // Open the file to be read. Throw error if file does not exist.
  inputFile = open(argv[1], O_RDONLY);
  if (inputFile == -1) {
    fprintf(stderr, "Error. Read file does not exist.\n");
    return -1;
  }

  // Create or overwrite the file to be written to.
  // Throw error if file cannot be created.
  outputFile = open(argv[2], O_CREAT | O_WRONLY, S_IRWXU);
  if (outputFile == -1) {
    fprintf(stderr, "Error. Write file cannot be opened.\n");
    return -1;
  }

  // Create buffers and while read file has data write that data to new file.
  ssize_t readIn;
  char buf[1024];
  size_t size = 1024;
  while((readIn = read(inputFile, buf, size)) > 0) {
    write(outputFile, buf, readIn);
  }

  // Close the write file.
  close(outputFile);
  // Close the read file.
  close(inputFile);

} // END OF PROGRAM
