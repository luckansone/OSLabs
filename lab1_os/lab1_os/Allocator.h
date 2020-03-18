#pragma once

struct BlockHeader {
	bool state; 
	size_t size;
	size_t prevsize;
};

class Allocator {
public:
	Allocator(const int n);
	
	void* mem_alloc(size_t size);

	void* mem_realloc(void* addr, size_t size);
	
	void mem_free(void* addr);
	
	void mem_dump();
private:
	size_t bSize; 
	int N; 
	BlockHeader* begin; 
	int* endOfMemory; 

	//all blocks must be fill the same number	
	bool checkDamage(int filler);

	BlockHeader* nextBlockHeader(BlockHeader* current);
	
	BlockHeader* previousBlockHeader(BlockHeader* current);
	
	bool isLast(BlockHeader* h);

	//next 4 functions merge 2 or 3 free blocks

	void mergeWithNext(BlockHeader* current, BlockHeader* next);
	void mergeWithPrevious(BlockHeader* previous, BlockHeader* current);
	void mergeWithPrevious(BlockHeader* previous, BlockHeader* current, BlockHeader* next);
	void mergeBoth(BlockHeader* previous, BlockHeader* current, BlockHeader* next);

	//copy data in new block (all  or part = length of new block)
	void copyData(void* from, void* to, size_t quantity);
	//return link on finded free block or NULL
	void* searchNewBlock(void* addr, size_t size);

	//next founctions merde 2 or 3 blocks (one is use), then separate them on use and free and copy data to new use

	void* expandLeft(void* addr, size_t size);
	void* expandRight(void* addr, size_t size);
	void* expandBoth(void* addr, size_t size);

	//set fields of BH selected by mask
	void initBlockHeader(BlockHeader* bh, bool state, size_t previous, size_t size, int mask);//mask 7 (binary: 111) - all
	//size - length of new use block
	void* separateOnUseAndFree(BlockHeader* current, size_t size);
	//return begin of memory block for user (after BH)
	void* getBlock(BlockHeader* h);
};

