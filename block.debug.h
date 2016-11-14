#ifndef TREE_BLOCK_DEBUG_H
#define TREE_BLOCK_DEBUG_H

typedef char *(*KEY_STRINGIFIER)( void * );

void print_block_i( struct block_config *config, void *address, char *indent, KEY_STRINGIFIER ks );

void print_block( struct block_config *config, void *address, KEY_STRINGIFIER ks );

#endif // TREE_BLOCK_DEBUG_H

