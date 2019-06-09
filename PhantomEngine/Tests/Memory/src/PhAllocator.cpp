#include "PhAllocator.h"
#include <memory>

namespace Phantom {

#define Max(a,b) (((a) > (b)) ? (a) : (b))

	Allocator::Allocator
	(
		unsigned dataSize,
		unsigned pageSize,
		unsigned alignment
	)
		: m_pageList(nullptr)
		, m_freeList(nullptr)
	{
		Reset(dataSize, pageSize, alignment);
	}

	Allocator::~Allocator(void)
	{
		FreeAll();
	}

	void Allocator::Reset
	(
		unsigned dataSize,
		unsigned pageSize,
		unsigned alignment
	)
	{
		FreeAll();

		m_dataSize = dataSize;
		m_pageSize = pageSize;

		unsigned maxHeaderData =
			Max(sizeof(BlockHeader), m_dataSize); //win32 4bytes pointer

		m_alignmentSize =
			(maxHeaderData % alignment)
			? (alignment - maxHeaderData % alignment)
			: (0);

		m_blockSize =
			maxHeaderData + m_alignmentSize;

		m_blocksPerPage =
			(m_pageSize - sizeof(PageHeader)) / m_blockSize;
	}

	void *Allocator::Allocate(void)
	{
		// free list empty, create new page
		if (!m_freeList)
		{
			// allocate new page
			PageHeader *newPage =
				reinterpret_cast<PageHeader *>
				(new char[m_pageSize]);
			++m_numPages;
			m_numBlocks += m_blocksPerPage;
			m_numFreeBlocks += m_blocksPerPage;

			FillFreePage(newPage);

			// page list not empty, link new page
			if (m_pageList)
			{
				newPage->Next = m_pageList;
			}

			// push new page
			m_pageList = newPage;

			// link new free blocks
			BlockHeader *currBlock = newPage->Blocks();
			for (unsigned i = 0; i < m_blocksPerPage - 1; ++i)
			{
				currBlock->Next = NextBlock(currBlock);
				currBlock = NextBlock(currBlock);
			}
			currBlock->Next = nullptr; // last block

			// push new blocks
			m_freeList = newPage->Blocks();
		}

		// pop free block
		BlockHeader *freeBlock = m_freeList;
		m_freeList = m_freeList->Next;
		--m_numFreeBlocks;

		FillAllocatedBlock(freeBlock);

		return freeBlock;
	}

	void Allocator::Free(void *p)
	{
		// retrieve block header
		BlockHeader *block =
			reinterpret_cast<BlockHeader *>(p);

		FillFreeBlock(block);

		// push block
		block->Next = m_freeList;
		m_freeList = block;
		++m_numFreeBlocks;
	}

	void Allocator::FreeAll(void)
	{
		// free all pages
		PageHeader *pageWalker = m_pageList;
		while (pageWalker)
		{
			PageHeader *currPage = pageWalker;
			pageWalker = pageWalker->Next;

			delete[] reinterpret_cast<char *>(currPage);
		}

		// release pointers
		m_pageList = nullptr;
		m_freeList = nullptr;

		// re-init stats
		m_numPages = 0;
		m_numBlocks = 0;
		m_numFreeBlocks = 0;
	}


	void Allocator::FillFreePage(PageHeader *p)
	{
		// page header
		p->Next = nullptr;

		// blocks
		BlockHeader *currBlock = p->Blocks();
		for (unsigned i = 0; i < m_blocksPerPage; ++i)
		{
			FillFreeBlock(currBlock);
			currBlock = NextBlock(currBlock);
		}
	}

	void Allocator::FillFreeBlock(BlockHeader *p)
	{
		// block header + data
		std::memset
		(
			p,
			PATTERN_FREE,
			m_blockSize - m_alignmentSize
		);

		// alignment
		std::memset
		(
			reinterpret_cast<char *>(p)
			+ m_blockSize - m_alignmentSize,
			PATTERN_ALIGN,
			m_alignmentSize
		);
	}

	void Allocator::FillAllocatedBlock(BlockHeader *p)
	{
		// block header + data
		std::memset
		(
			p,
			PATTERN_ALLOC,
			m_blockSize - m_alignmentSize
		);

		// alignment
		std::memset
		(
			reinterpret_cast<char *>(p)
			+ m_blockSize - m_alignmentSize,
			PATTERN_ALIGN,
			m_alignmentSize
		);
	}

	Allocator::BlockHeader *
		Allocator::NextBlock
		(BlockHeader *p)
	{
		return
			reinterpret_cast<BlockHeader *>
			(reinterpret_cast<char *>(p) + m_blockSize);
	}
}
