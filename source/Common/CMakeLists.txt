project(Common)

set(CMAKE_CXX_STANDARD 17)

add_library(Common
	"api/HostInterop.h"
	"common.h"
	"config.h"
	"types.h"
	"core/patch.hxx"
	"core/sync.hxx"
	"debug.h"
	"debug/assert.h"
	"debug/log.h"
	"util/crc.hxx"
	"util/deferred.hxx"
	"util/json.hxx"
	"debug/kassert.cxx"
	"memory/heap.hxx"

	# smol_json
	"vendor/smol_json.hxx"

	# EASTL
	"vendor/EABase/config/eacompiler.h"
	"vendor/EABase/config/eacompilertraits.h"
	"vendor/EABase/config/eaplatform.h"
	"vendor/EABase/eabase.h"
	"vendor/EABase/eahave.h"
	"vendor/EABase/earesult.h"
	"vendor/EABase/eastdarg.h"
	"vendor/EABase/eaunits.h"
	"vendor/EABase/int128.h"
	"vendor/EABase/nullptr.h"
	"vendor/EABase/version.h"
	"vendor/EASTL/algorithm.h"
	"vendor/EASTL/allocator.h"
	"vendor/EASTL/allocator_malloc.h"
	"vendor/EASTL/any.h"
	"vendor/EASTL/array.h"
	"vendor/EASTL/bitset.h"
	"vendor/EASTL/bitvector.h"
	"vendor/EASTL/bonus/adaptors.h"
	"vendor/EASTL/bonus/call_traits.h"
	"vendor/EASTL/bonus/compressed_pair.h"
	"vendor/EASTL/bonus/fixed_ring_buffer.h"
	"vendor/EASTL/bonus/fixed_tuple_vector.h"
	"vendor/EASTL/bonus/intrusive_sdlist.h"
	"vendor/EASTL/bonus/intrusive_slist.h"
	"vendor/EASTL/bonus/list_map.h"
	"vendor/EASTL/bonus/lru_cache.h"
	"vendor/EASTL/bonus/ring_buffer.h"
	"vendor/EASTL/bonus/sort_extra.h"
	"vendor/EASTL/bonus/sparse_matrix.h"
	"vendor/EASTL/bonus/tuple_vector.h"
	"vendor/EASTL/chrono.h"
	"vendor/EASTL/core_allocator.h"
	"vendor/EASTL/core_allocator_adapter.h"
	"vendor/EASTL/deque.h"
	"vendor/EASTL/fixed_allocator.h"
	"vendor/EASTL/fixed_function.h"
	"vendor/EASTL/fixed_hash_map.h"
	"vendor/EASTL/fixed_hash_set.h"
	"vendor/EASTL/fixed_list.h"
	"vendor/EASTL/fixed_map.h"
	"vendor/EASTL/fixed_set.h"
	"vendor/EASTL/fixed_slist.h"
	"vendor/EASTL/fixed_string.h"
	"vendor/EASTL/fixed_substring.h"
	"vendor/EASTL/fixed_vector.h"
	"vendor/EASTL/functional.h"
	"vendor/EASTL/hash_map.h"
	"vendor/EASTL/hash_set.h"
	"vendor/EASTL/heap.h"
	"vendor/EASTL/initializer_list.h"
	"vendor/EASTL/internal/allocator_traits.h"
	"vendor/EASTL/internal/allocator_traits_fwd_decls.h"
	"vendor/EASTL/internal/char_traits.h"
	"vendor/EASTL/internal/config.h"
	"vendor/EASTL/internal/copy_help.h"
	"vendor/EASTL/internal/enable_shared.h"
	"vendor/EASTL/internal/fill_help.h"
	"vendor/EASTL/internal/fixed_pool.h"
	"vendor/EASTL/internal/function.h"
	"vendor/EASTL/internal/function_detail.h"
	"vendor/EASTL/internal/function_help.h"
	"vendor/EASTL/internal/functional_base.h"
	"vendor/EASTL/internal/generic_iterator.h"
	"vendor/EASTL/internal/hashtable.h"
	"vendor/EASTL/internal/in_place_t.h"
	"vendor/EASTL/internal/integer_sequence.h"
	"vendor/EASTL/internal/intrusive_hashtable.h"
	"vendor/EASTL/internal/mem_fn.h"
	"vendor/EASTL/internal/memory_base.h"
	"vendor/EASTL/internal/meta.h"
	"vendor/EASTL/internal/move_help.h"
	"vendor/EASTL/internal/pair_fwd_decls.h"
	"vendor/EASTL/internal/piecewise_construct_t.h"
	"vendor/EASTL/internal/red_black_tree.h"
	"vendor/EASTL/internal/smart_ptr.h"
	"vendor/EASTL/internal/thread_support.h"
	"vendor/EASTL/internal/tuple_fwd_decls.h"
	"vendor/EASTL/internal/type_compound.h"
	"vendor/EASTL/internal/type_fundamental.h"
	"vendor/EASTL/internal/type_pod.h"
	"vendor/EASTL/internal/type_properties.h"
	"vendor/EASTL/internal/type_transformations.h"
	"vendor/EASTL/intrusive_hash_map.h"
	"vendor/EASTL/intrusive_hash_set.h"
	"vendor/EASTL/intrusive_list.h"
	"vendor/EASTL/intrusive_ptr.h"
	"vendor/EASTL/iterator.h"
	"vendor/EASTL/linked_array.h"
	"vendor/EASTL/linked_ptr.h"
	"vendor/EASTL/list.h"
	"vendor/EASTL/map.h"
	"vendor/EASTL/memory.h"
	"vendor/EASTL/meta.h"
	"vendor/EASTL/numeric.h"
	"vendor/EASTL/numeric_limits.h"
	"vendor/EASTL/optional.h"
	"vendor/EASTL/priority_queue.h"
	"vendor/EASTL/queue.h"
	"vendor/EASTL/random.h"
	"vendor/EASTL/ratio.h"
	"vendor/EASTL/safe_ptr.h"
	"vendor/EASTL/scoped_array.h"
	"vendor/EASTL/scoped_ptr.h"
	"vendor/EASTL/segmented_vector.h"
	"vendor/EASTL/set.h"
	"vendor/EASTL/shared_array.h"
	"vendor/EASTL/shared_ptr.h"
	"vendor/EASTL/slist.h"
	"vendor/EASTL/sort.h"
	"vendor/EASTL/span.h"
	"vendor/EASTL/stack.h"
	"vendor/EASTL/string.h"
	"vendor/EASTL/string_hash_map.h"
	"vendor/EASTL/string_map.h"
	"vendor/EASTL/string_view.h"
	"vendor/EASTL/tuple.h"
	"vendor/EASTL/type_traits.h"
	"vendor/EASTL/unique_ptr.h"
	"vendor/EASTL/unordered_map.h"
	"vendor/EASTL/unordered_set.h"
	"vendor/EASTL/utility.h"
	"vendor/EASTL/variant.h"
	"vendor/EASTL/vector.h"
	"vendor/EASTL/vector_map.h"
	"vendor/EASTL/vector_multimap.h"
	"vendor/EASTL/vector_multiset.h"
	"vendor/EASTL/vector_set.h"
	"vendor/EASTL/version.h"
	"vendor/EASTL/weak_ptr.h"

	"vendor/EASTL/allocator_eastl.cxx"
	"vendor/EASTL/assert.cxx"
	"vendor/EASTL/fixed_pool.cpp"
	"vendor/EASTL/hashtable.cpp"
	"vendor/EASTL/intrusive_list.cpp"
	"vendor/EASTL/numeric_limits.cpp"
	"vendor/EASTL/red_black_tree.cpp"
	"vendor/EASTL/string.cpp"
 "compiler/ppc.hxx" "security/Canary.hxx" "util/list.hxx")

target_include_directories(Common PUBLIC "./" "./vendor" "../")