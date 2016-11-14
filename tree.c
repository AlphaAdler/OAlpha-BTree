#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

/**
 * void *mmap(void *address, size_t length, int protect, int flags, int filedes, off_t offset);
 * void *munmap(void *addr, size_t length);
 * void *mremap(void *address, size_t length, size_t new_length, int flag);
 */

struct tree {
	
};

int init_tree() {
	size_t page_size = ( size_t ) sysconf( _SC_PAGESIZE );
}

