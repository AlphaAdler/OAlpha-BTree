#ifndef TREE_BLOCK_PRIVATE_H
#define TREE_BLOCK_PRIVATE_H

#define BLOCK_HEADER_SIZE (sizeof(struct block_header))

#define ELEMENT_HEADER_SIZE (sizeof(struct block_element))

#define ELEMENT_AT( config, array, i ) ( ( struct block_element * ) ( ( array ) + ( i ) * ( config )->element_size ) )

struct block_config {
	int capacity;
	int key_size;
	int element_size;
	COMPARATOR comparator;
};

struct block_header {
	int  size;
	int  last;
	int child;
};

struct block_element {
	int  next;
	int child;
};

#endif // TREE_BLOCK_PRIVATE_H

