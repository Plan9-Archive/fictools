/* malloc.c
 * A really small, simple malloc for the Z-machine.
 * (C) 2001 David Given
 * Based on my malloc.h from baZic.
 */

#include <stdlib.h>
#define DEBUG

enum {
	FREE_MAGIC = 0xFAEE,
	ALLOC_MAGIC = 0xA10C
};

typedef struct mblock {
	int magic;
	size_t size;
	struct mblock* prev;
	struct mblock* next;
} mblock;

static char* heap_bottom;
static char* heap_top;
static mblock* firstfree;

/* Initialise the heap manager to work on the given area. */

void heap_init(char* bottom, char* top)
{
	heap_top = top;
	heap_bottom = bottom;

	/* Create a free chunk spanning the length of the block. */
	
	firstfree = (mblock*) bottom;
	firstfree->magic = FREE_MAGIC;
	firstfree->size = heap_top - heap_bottom;
	firstfree->prev = NULL;
	firstfree->next = NULL;
}

/* Remove a node from the list. */

static void mem_node_remove(mblock* p)
{
	if (p == firstfree)
		firstfree = p->next;
	if (p->prev)
		p->prev->next = p->next;
	if (p->next)
		p->next->prev = p->prev;
}

/* Allocate a block. */

void* malloc(size_t size)
{
	mblock* p;

	/* Add the space required for the header. */

	size += sizeof(mblock);

	/* Iterate through the free list trying to find a free chunk large
	 * enough. */

	p = firstfree;
	while (p && (p->size < size))
		p = p->next;
	
	if (!p)
	{
		/* No sufficiently large block could be found. */
		return NULL;
	}

	/* Can we split the free block we've just found, or is there not enough
	 * room? */

	if ((p->size - size) < sizeof(mblock))
	{
		/* There's no room, so we're going to allocate the entire free
		 * block. */

		size = p->size;
		mem_node_remove(p);
	}
	else
	{
		/* There is room. We shrink the free block and put the new
		 * block in the space so formed. */

		p->size -= size;
		p = (mblock*)((char*)p + p->size);
	}

	/* Initialise the new node. */

	memset(p, 0, size);
	p->magic = ALLOC_MAGIC;
	p->size = size;
	return (void*)(p+1);
}

/* Try to free a block. */

void free(void* _p)
{
	mblock* p = (mblock*)p - 1;
	mblock* q;

#ifdef DEBUG
	/* Check the magic number. */

	if (p->magic != ALLOC_MAGIC)
	{
		printf("Trying to free invalid node %X!\n", p);
		printf("Magic was %X when it should have been %X.\n",
			p->magic, ALLOC_MAGIC);
		return;
	}
#endif

	/* Turn the alloc node into a free node. */

	p->magic = FREE_MAGIC;
	p->next = firstfree;
	p->prev = 0;
	if (firstfree)
		firstfree->prev = p;
	firstfree = p;

	/* Right. We've successfully freed the block; p points to the FB
	 * structure.
	 *
	 * Unfortunately, they way we use memory leads to lots of
	 * fragmentation, which is bad. So we need to find out if we can
	 * coalesce with the block immediately afterwards.
	 */

	q = (mblock*) ((char*)p + p->size);
	if (q->magic != FREE_MAGIC)
	{
		/* Nothing coalescable. */
		return;
	}
	
	/* Change the size of our block to encompass the next block... */

	p->size += q->size;

	/* And remove the next block from the free list. */

	mem_node_remove(q);
}

/*

	! Change the size of our block to encompass the next block...

	p-->FB_SIZE = q + (p+q)-->FB_SIZE;

	! ...and remove the next block from the free list.

	mem_node_remove(p+q);
];

! Get amount of free memory.

[ mem_countfree p size;
	size = 0;
	p = mem_firstfree;
	while (p ~= 0)
	{
		size = size + p-->FB_SIZE;
		p = p-->FB_NEXT;
	}
	return size;
];

! Get total amount of memory.

[ mem_counttotal;
	return (mem_top - mem_bottom);
];
	
! Get amount of used memory.

[ mem_countused;
	return mem_counttotal() - mem_countfree();
];

#ifdef DEBUG;
! Dump the free list.

[ mem_show_free_list p;
	print "Free list start^";
	p = mem_firstfree;
	while (p ~= 0)
	{
		print "  node ", p, " prev=", p-->FB_PREV, " next=", p-->FB_NEXT;
		print " size=", p-->FB_SIZE;
		if (p-->FB_MAGIC ~= FREE_MAGIC)
			print " invalid magic";
		print "^";
		p = p-->FB_NEXT;
	}
	print "Free list end; used=", mem_countused(), " total=", mem_counttotal(), "^";
];

#endif;
*/
