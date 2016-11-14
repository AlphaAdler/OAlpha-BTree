tf: block.h block.private.h block.debug.h tf.c block.c block.debug.c
	gcc -o tf tf.c block.c block.debug.c
