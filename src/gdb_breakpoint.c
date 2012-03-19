/*Copyright (c) 2012 anton.feldmann@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#define _POSIX_SOURCE_
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <bfd.h>

#if __APPLE__
  #include <sys/fcntl.h> 
  #define FD_DIR "/dev/fd/"
#else
  #define FD_DIR "/proc/self/fd/"
#endif

 //2^^64 => 20 digits
 #define FD_FILE_MAX_LEN (sizeof(FD_DIR) + 20)

#define die(msg, ...) \
  do { fprintf(stderr, msg, ## __VA_ARGS__); exit(1); } while (0)

#define errno_die(msg) \
  do { perror(msg); exit(1); } while(0)

#define bfd_die(msg) \
  do { bfd_perror(msg); exit(1); } while(0)

int main(int argc, char** argv)
{
  if (argc < 2)
   die("Usage:\t%s <additional gdb options> ... <programm> \n", argv[0]);

  // get Contents of the breakpoint section
  bfd* _bfd = bfd_openr(argv[argc-1], NULL);
  if (!_bfd)
   { bfd_die("error while constructing bfd object");}

  // load data
  if (!bfd_check_format(_bfd, bfd_object))
    {bfd_die("not bfd format"); }

   asection *sec = bfd_get_section_by_name(_bfd, "breakpoints");
    if (!sec)
        bfd_die("bfd_get_section_by_name");

    size_t contents_size = sec->size;
    char *contents = malloc(contents_size);
    if (!contents)
        die("Could not allocate contents\n");

    if (!bfd_get_section_contents(_bfd, sec, contents, 0, contents_size))
        bfd_die("bfd_get_section_contents");

    if (!bfd_close(_bfd))
        bfd_die("bfd_close");


    // Write GDB breakpoint commands to a temporary file

    FILE *temp = tmpfile();
    if (!temp)
        errno_die("tmpfile");

    for (size_t i = 0; i < contents_size; i += sizeof(void*)) {
        fprintf(temp, "break *%p\n", *( (void**) (contents+i) ));
    }

    rewind(temp);

    // Execute GDB with that script, along with original args

    char fd_file_path[FD_FILE_MAX_LEN];
    snprintf(fd_file_path, FD_FILE_MAX_LEN, "%s%d", FD_DIR, fileno(temp));

    char **gdb_args = malloc(sizeof(char*) * (argc+3));
    if (!gdb_args)
        die("Could not allocate gdb_args\n");

    gdb_args[0] = "gdb";
    gdb_args[1] = "-x";
    gdb_args[2] = fd_file_path;
    for (size_t i=1; i<argc; i++) {
        gdb_args[2+i] = argv[i];
    }
    gdb_args[2+argc] = (char*) NULL;

    execvp("gdb", gdb_args);

    // If we get here, then execvp failed.
    errno_die("execvp");
}

