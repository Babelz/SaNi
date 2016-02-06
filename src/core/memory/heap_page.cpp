#include "sani/core/memory/heap_page.hpp"
#include "sani/core/memory/memory.hpp"

namespace sani {

	const float32 FragmentationTreshhold = 0.10f;

	HeapPage::HeapPage(const uint32 size) : size(size),
											pagepointer(0),
											missedBytes(0),
											fragmentation(0.0f),
											bytesUsed(0) {
		memory = new char[size];
	}

	void HeapPage::joinBlocks(std::list<HeapBlock> &newReleasedBlocks, std::list<HeapBlock> &newBlocks)
	{
		auto current = blocks.begin();

		while (current != blocks.end()) {
			if (current->isReleased()) {
				// Found released blocks, look forward for more
				// released blocks.
				HeapBlock& head = *current;
				uint32 bytes = 0;

				while (current != blocks.end() && current->isReleased()) {
					bytes += current->getSize();

					current++;
				}

				const uint32 diff = bytes - head.getSize();
				head.grow(diff);

				newReleasedBlocks.push_back(head);
				newBlocks.push_back(head);
			} else {
				// Just push the block to block list, it is occupied.
				newBlocks.push_back(*current);

				current++;
			}
		}
	}
	void HeapPage::freeBlocks(std::list<HeapBlock>& newBlocks, std::list<HeapBlock>& newReleasedBlocks) {
		// Copy new blocks.
		blocks = newBlocks;

		// Check if we can join some values.
		IntPtr pageHighAddress = reinterpret_cast<IntPtr>(&memory[pagepointer]);
		std::list<HeapBlock>::reverse_iterator current = newBlocks.rbegin();

		// Start looking from the end of new blocks.
		// Use the new blocks listing, not the instance list.
		while (current != newBlocks.rend() && current->isReleased()) {
			const IntPtr blockHighAddress = reinterpret_cast<IntPtr>(current->getHandle()) + current->getSize();

			// If both are pointing to the same memory location,
			// we can join this block with the free memory region
			// of the page.
			if (blockHighAddress == pageHighAddress) {
				// Compute new high address and move page 
				// pointer back.
				pageHighAddress -= current->getSize();
				pagepointer -= current->getSize();

				// Remove from new released block listing.
				newReleasedBlocks.remove(*current);
				blocks.remove(*current);

				current++;
			} else {
				// If we can't join the first block to the free memory region,
				// there is no point going trough other blocks.
				break;
			}
		}
	}
	void HeapPage::generateNewReleasedQueue(std::list<HeapBlock>& newReleasedBlocks) {
		std::priority_queue<HeapBlock> newReleasedBlocksQueue;

		for (HeapBlock& block : newReleasedBlocks) newReleasedBlocksQueue.push(block);

		// Copy to instance field.
		releasedBlocks = newReleasedBlocksQueue;
	}

	bool HeapPage::shouldDefragment() const {
		return fragmentation >= FragmentationTreshhold && fragmented();
	}
	bool HeapPage::fragmented() const {
		return missedBytes > 0 || releasedBlocks.size() > 0;
	}
	void HeapPage::defragment() {
		if (releasedBlocks.size() == 0) return;

		// Go trough the heap starting from the beginning and
		// look for released blocks.
		std::list<HeapBlock> newReleasedBlocks;
		std::list<HeapBlock> newBlocks;

		// Join released blocks together that are aligned next
		// to each other.
		joinBlocks(newReleasedBlocks, newBlocks);

		// See if we can join some blocks to the main memory region 
		// where the page pointer is pointing to.
		freeBlocks(newBlocks, newReleasedBlocks);
		
		// Generate new released priority queue.
		generateNewReleasedQueue(newReleasedBlocks);

		fragmentation = 0.0f;
		missedBytes = 0;
	}

	uint64 HeapPage::getBytesUsed() const {
		return bytesUsed;
	}

	HeapPage::~HeapPage() {
		delete[] memory;
	}
}