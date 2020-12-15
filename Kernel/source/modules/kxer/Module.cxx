#include "modules/Project.hxx"
#include "modules/kxer/Loader.hxx"

namespace kuribo {

struct KuriboModule final : public IModule {
  KuriboModule(const u8* buf, const u32 size) {
#ifdef _WIN32
    return;
#endif

    KURIBO_SCOPED_LOG("Loading Kuribo binary!");

    auto succ = kxer::Load(kxer::LoadParam{
        eastl::string_view((const char*)buf, size),
        &mem::GetHeap(mem::GlobalHeapType::MEM2), (void**)&mPrologue, &mData});

    if (succ != kxer::LoadResult::Success) {
      KURIBO_LOG("Failed to load Kuribo binary: ");

      switch (succ) {
      case kxer::LoadResult::MalformedRequest:
        KURIBO_LOG("Malformed Request -- Caller supplied invalid arguments.\n");
        break;
      case kxer::LoadResult::InvalidFileType:
        KURIBO_LOG("Invalid File -- This is not a Kuribo binary.\n");
        break;
      case kxer::LoadResult::InvalidVersion:
        KURIBO_LOG("Invalid Version -- Only V0 are supported.\n");
        break;
      case kxer::LoadResult::BadAlloc:
        KURIBO_LOG("Out of Memory -- File is too large.\n");
        break;
      case kxer::LoadResult::BadReloc:
        KURIBO_LOG("Bad relocation\n");
        break;
      default:
        KURIBO_LOG("Unknown error.\n");
        break;
      }
      mData.reset();
      return;
    }
    KURIBO_ASSERT(succ == kxer::LoadResult::Success);
    KURIBO_ASSERT(mData);
    KURIBO_ASSERT(mPrologue);
  }

  int prologue(int type, __kuribo_module_ctx_t* interop) override final {
    if (mPrologue == nullptr)
      return KURIBO_EXIT_FAILURE;

    KURIBO_SCOPED_LOG("KURIBO Module: Prologue call");
    KURIBO_LOG("Type: %u, interop: %p\n", (u32)type, interop);
    KURIBO_PRINTF("PROLOGUE: %p\n", mPrologue);

    return mPrologue(type, interop);
  }
  eastl::unique_ptr<u8[]> mData;
  kuribo_module_prologue mPrologue = nullptr;
};

eastl::unique_ptr<IModule> makeKuriboModule(const u8* data, u32 size) {
  return eastl::make_unique<KuriboModule>(data, size);
}

} // namespace kuribo