#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>

#include "block.h"
#include "block.private.h"
#include "block.debug.h"

int key_comparator( void *a, void *b ) {
	return strcmp( ( char * ) a, ( char * ) b );
}

char *cast( void *key ) {
	return ( char * ) key;
}

int main( int argc, char *argv[] ) {
	size_t page_size = ( size_t ) sysconf( _SC_PAGESIZE );
	void *address = malloc( page_size );
	size_t key_size = atoi( argv[1] );
	struct block_config *config = 0;
	int c = init_block( address, page_size, key_size, ( BLOCK_CONFIG * ) &config );
	//int c = init_block( address, page_size, key_size, ( BLOCK_CONFIG * ) 0 );
	char *key;
	struct block_header *head;
	
	if( c == NULL_CONFIG_POINTER ) {
		printf("NULL_CONFIG_POINTER\n");
		return NULL_CONFIG_POINTER;
	}
	else if( c == NULL_ADDRESS ) {
		printf("NULL_ADDRESS\n");
		return NULL_ADDRESS;
	}
	else if( c == INVALID_SIZE ) {
		printf("INVALID_SIZE\n");
		return INVALID_SIZE;
	}
	else if( c == INSUFFICIENT_SIZE ) {
		printf("INSUFFICIENT_SIZE\n");
		return INSUFFICIENT_SIZE;
	}
	else if( c == INVALID_KEYSIZE ) {
		printf("INVALID_KEYSIZE\n");
		return INVALID_KEYSIZE;
	}
	else {
		printf("page_size = %zd\n", page_size);
		printf("key_size = %zd\n", key_size);
		printf("capacity = %d\n", config->capacity);
		printf("esize = %d\n", config->element_size);
		printf("hsize = %lu\n", BLOCK_HEADER_SIZE);
		printf("bsize = %lu\n", BLOCK_HEADER_SIZE + config->capacity * config->element_size);
	}
	
	c = set_comparator_block( config, key_comparator );
	
	head = ( struct block_header * ) address;
	
	key = malloc( key_size );
	key = "abc";
	c = add_key_block( config, address, key, 10 );
	print_block( config, address, cast );
	
	key = "cba";
	c = add_key_block( config, address, key, 9 );
	print_block( config, address, cast );
	
	key = "aaa";
	c = add_key_block( config, address, key, 8 );
	print_block( config, address, cast );
	
	return 0;
	
}

