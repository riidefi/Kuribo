#pragma once

#include "common.h"
#include <stdlib.h>

// We have a shrinking frame. From memory region A to B:
// A --------- B
// We can allocate (but not free) off of either end
// A XXX----YY B
// The benefit here is that we can efficiently fill in a block of memory without
// knowing the relative sizes of X/Y. In the compiler, the two big regions will
// be
// - Per frame functions
// - Referenced, call-on-demand functions
// So our region will look as follows:
// MEMMORY_BEGIN:
// (compiled) 04...
// (compiled) 02...
// blr
// |
// V expand downward
//
// Free space
//
// ^
// | expand upward
// C0 body
// blr
// C2 body
// blr
// MEMORY_END

namespace gecko_jit {

class FrameAllocator {
public:
  FrameAllocator(u8* memory_begin, size_t size)
      : begin(memory_begin), end(memory_begin + size), up_it(begin),
        down_it(end) {}

  u8* alloc(size_t size, bool head = true) {
    if (head) {
      u8* dst = up_it;
      up_it += size;
      KURIBO_ASSERT(up_it - begin < end - begin);
      return dst;
    } else {
      down_it -= size;
      KURIBO_ASSERT(end - down_it < end - begin);
      return down_it;
    }
  }

  struct MemoryRegion {
    void* begin;
    void* end;
  };

  struct UsedRegion {
    MemoryRegion low;
    MemoryRegion high;
  };

  void printStats() const {
#ifdef KURIBO_ENABLE_LOG
    const u32 alloc_head = static_cast<u32>(up_it - begin);
    const u32 alloc_tail = static_cast<u32>(end - down_it);
    const u32 alloc_total = alloc_head + alloc_tail;
    const u32 remainder = static_cast<u32>(down_it - up_it);

    KURIBO_LOG("-----------------------\n");
    KURIBO_LOG("Computing remainder of the FrameAllocator:\n");
    KURIBO_LOG("-----------------------\n");
    KURIBO_LOG("Allocated from head: %u\n", alloc_head);
    KURIBO_LOG("Allocated from tail: %u\n", alloc_tail);
    KURIBO_LOG("-----------------------\n");
    KURIBO_LOG("Allocated total:     %u\n", alloc_total);
    KURIBO_LOG("Remaining bytes:     %u\n", remainder);
    KURIBO_LOG("-----------------------\n");
#endif
  }

  MemoryRegion computeRemainder() const {
#ifdef KURIBO_ENABLE_LOG
    printStats();
#endif

    return {up_it, down_it};
  }

  UsedRegion computeUsed() const {
#ifdef KURIBO_ENABLE_LOG
    printStats();
#endif

    return {.low = {begin, up_it}, .high = {down_it, end}};
  }

  // -1 if failed
  u32 getSaveState() const {
    const s32 delta_up = up_it - begin;
    const s32 delta_down = end - down_it;
    KURIBO_ASSERT(delta_up > 0 && delta_down > 0);
    const u16 trunc_delta_up = static_cast<u16>(delta_up);
    if (trunc_delta_up != delta_up)
      return 0xFFFF'FFFF;
    const s16 trunc_delta_down = static_cast<u16>(delta_down);
    if (trunc_delta_down != delta_down)
      return 0xFFFF'FFFF;

    return (delta_up << 16) | delta_down;
  }

  // return if successful
  bool applySaveState(u32 save) {
    if (save == 0xFFFF'FFFF)
      return false;
    const u16 delta_up = (save >> 16);
    const u16 delta_down = (save << 16) >> 16;
    up_it = begin + delta_up;
    down_it = end - delta_down;
    return true;
  }

private:
  u8* begin;
  u8* end;

  u8* up_it;
  u8* down_it;
};

} // namespace gecko_jit