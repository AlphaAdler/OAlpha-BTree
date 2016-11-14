#ifndef TREE_BLOCK_H
#define TREE_BLOCK_H

typedef void *BLOCK_CONFIG;

typedef void *BLOCK;

typedef void *ELEMENT;

typedef int (*COMPARATOR)( void *a, void *b );

extern int NULL_CONFIG_POINTER;

extern int NULL_ADDRESS;

extern int INVALID_SIZE;

extern int INSUFFICIENT_SIZE;

extern int INVALID_KEYSIZE;

extern int CAPACITY_REACHED;

int set_comparator_block( BLOCK_CONFIG config_ptr, COMPARATOR comparator );

int init_block( void *address, size_t size, size_t key_size, BLOCK_CONFIG *config );

int add_key_block( BLOCK_CONFIG config, void *address, void *key, int child );

int remove_at_block( BLOCK_CONFIG config, void *address, int index, void **key, int *child );

int remove_key_block( BLOCK_CONFIG config, void *address, void *key, int *child );

int transfer_block( BLOCK_CONFIG config, void *parent, void *source, void *dest, int index, int n );

int tribute_block( BLOCK_CONFIG config, void *parent, void *child, int index, int *at, void *siblings );

int multiply_block( BLOCK_CONFIG config, void *address, int *at, void *children );

#endif // TREE_BLOCK_H

