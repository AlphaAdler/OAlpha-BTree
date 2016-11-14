#include <stdlib.h>

#include "block.h"
#include "block.private.h"

int NULL_CONFIG_POINTER = -5;

int NULL_ADDRESS = -1;

int INVALID_SIZE = -2;

int INSUFFICIENT_SIZE = -3;

int INVALID_KEYSIZE = -4;

int CAPACITY_REACHED = -6;

int set_comparator_block( void *config_ptr, COMPARATOR comparator ) {
	
	struct block_config *config;
	
	void *array;
	
	if( !config_ptr )
		return NULL_CONFIG_POINTER;
	config = ( struct block_config * ) config_ptr;
	
	config->comparator = comparator;
	
	return 0;
	
}

int init_block( void *address, size_t size, size_t key_size, void **config_ptr ) {
	
	void *array;
	
	struct block_header *head;
	struct block_element *cur;
	
	struct block_config *config;
	
	int i;
	
	if( !config_ptr )
		return NULL_CONFIG_POINTER;
	
	if( ! *config_ptr )
		*config_ptr = config = malloc( sizeof( struct block_config ) );
	else
		config = ( struct block_config * ) *config_ptr;
	
	config->key_size = key_size;
	
	if( !address )
		return NULL_ADDRESS;
	
	if( size < 1 )
		return INVALID_SIZE;
	
	if( key_size < 1 )
		return INVALID_KEYSIZE;
	
	if( size < ( BLOCK_HEADER_SIZE + ELEMENT_HEADER_SIZE + key_size ) )
		return INSUFFICIENT_SIZE;
	
	array = address + BLOCK_HEADER_SIZE;
	config->element_size = ELEMENT_HEADER_SIZE + key_size;
	config->capacity = ( size - BLOCK_HEADER_SIZE ) / config->element_size;
	
	head = ( struct block_header * ) address;
	head->size = 0;
	head->last = -1;
	
	for( i = 0; i < config->capacity; i++ ) {
		cur = ELEMENT_AT( config, array, i );
		cur->next = i + 1;
		cur->child = -1;
	}
	
	return 0;
	
}

int add_key_block( void *config_ptr, void *address, void *key, int child ) {
	
	struct block_config *config;
	struct block_header *head;
	struct block_element *cur;
	struct block_element *prev;
	struct block_element *last;
	struct block_element *next;
	int t;
	
	void *array;
	int i;
	
	if( !config_ptr )
		return NULL_CONFIG_POINTER;
	config = ( struct block_config * ) config_ptr;
	
	if( !address )
		return NULL_ADDRESS;
	head = ( struct block_header * ) address;
	
	array = address + BLOCK_HEADER_SIZE;
	
	cur = ( struct block_element * ) array;
	if( head->size == config->capacity )
		return CAPACITY_REACHED;
	else if( head->size == 0 ) {
		cur->child = child;
		for( i = 0; i < config->key_size; i++ )
			( ( char * ) ( ( void * ) cur + ELEMENT_HEADER_SIZE ) )[i] = ( ( char * ) key )[i];
		head->size = 1;
		head->last = 0;
	}
	else if( config->comparator( key, ( ( void * ) cur + ELEMENT_HEADER_SIZE ) ) < 0 ) {
		last = ELEMENT_AT( config, array, head->last );
		next = ELEMENT_AT( config, array, last->next );
		
		next->child = cur->child;
		for( i = 0; i < config->key_size; i++ )
			( ( char * ) ( ( void * ) next + ELEMENT_HEADER_SIZE ) )[i] = ( ( char * ) ( ( void * ) cur + ELEMENT_HEADER_SIZE ) )[i];
		t = next->next;
		next->next = cur->next;
		
		cur->child = child;
		for( i = 0; i < config->key_size; i++ )
			( ( char * ) ( ( void * ) cur + ELEMENT_HEADER_SIZE ) )[i] = ( ( char * ) key )[i];
		cur->next = last->next;
		
		last->next = t;
		
		head->size = head->size + 1;
	}
	else {
		last = ELEMENT_AT( config, array, head->last );
		next = ELEMENT_AT( config, array, last->next );
		
		for( i = 0; i < head->size && config->comparator( key, ( ( void * ) cur + ELEMENT_HEADER_SIZE ) ) > 0; i++ ) {
			prev = cur;
			cur = ELEMENT_AT( config, array, cur->next );
		}
		
		if( i < head->size ) {
			next->child = child;
			for( i = 0; i < config->key_size; i++ )
				( ( char * ) ( ( void * ) next + ELEMENT_HEADER_SIZE ) )[i] = ( ( char * ) key )[i];
			t = next->next;
			next->next = prev->next;
			
			prev->next = last->next;
			
			last->next = t;
		}
		else {
			next->child = child;
			for( i = 0; i < config->key_size; i++ )
				( ( char * ) ( ( void * ) next + ELEMENT_HEADER_SIZE ) )[i] = ( ( char * ) key )[i];
			head->last = last->next;
		}
		
		head->size = head->size + 1;
	}
	
	return 0;
	
}

int remove_at_block( void *config_ptr, void *address, int index, void **key, int *child ) {
	
	struct block_config *config;
	struct block_header *head;
	struct block_element *cur;
	
	void *array;
	
	if( !config_ptr )
		return NULL_CONFIG_POINTER;
	config = ( struct block_config * ) config_ptr;
	
	if( !address )
		return NULL_ADDRESS;
	head = ( struct block_header * ) address;
	
	array = address + BLOCK_HEADER_SIZE;
	
	return 0;
	
}

int remove_key_block( void *config_ptr, void *address, void *key, int *child ) {
	
	struct block_config *config;
	struct block_header *head;
	struct block_element *cur;
	
	void *array;
	
	if( !config_ptr )
		return NULL_CONFIG_POINTER;
	config = ( struct block_config * ) config_ptr;
	
	if( !address )
		return NULL_ADDRESS;
	head = ( struct block_header * ) address;
	
	array = address + BLOCK_HEADER_SIZE;
	
	return 0;
	
}

int transfer_block( BLOCK_CONFIG config, void *addr1, void *addr2, int n );

int tribute_block( BLOCK_CONFIG config, void *parent, void *child, int index, int *at, void *siblings );

int multiply_block( BLOCK_CONFIG config, void *address, int *at, void *children );

