#include <stdlib.h>
#include <stdio.h>

#include "block.h"
#include "block.private.h"
#include "block.debug.h"

void print_block_i( struct block_config *config, void *address, char *indent, KEY_STRINGIFIER ks ) {
    
    void *array = address + BLOCK_HEADER_SIZE;
    struct block_header *head = ( struct block_header * ) address;
    struct block_element *cur;
    int i, index;
    
    printf( "%sblock = {\n%s\tsize: %2d,\n%s\tlast: %2d,\n%s\tchild: %2d,\n%s\telements: [\n", indent, indent, head->size, indent, head->last, indent, head->child, indent );
    
    index = 0;
    cur = ( struct block_element * ) array;
    for( i = 0; i < head->size; i++ ) {
        printf( "%s\t\t%2d(%2d): { next: %2d, child: %2d, key: %s }\n", indent, i, index, cur->next, cur->child, ks( ( void * ) cur + ELEMENT_HEADER_SIZE ) );
        if( head->size - i > 1 ) {
            index = cur->next;
            cur = ELEMENT_AT( config, array, index );
        }
    }
    
    printf( "%s\t]\n%s}\n", indent, indent );
    
}

void print_block( struct block_config *config, void *address, KEY_STRINGIFIER ks ) {
    
    char *indent = malloc( 1 );
    
    indent[0] = 0;
    print_block_i( config, address, indent, ks );
    
}
