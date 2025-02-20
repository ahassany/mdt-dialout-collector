// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: cisco_dialout.proto

#include "cisco_dialout.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace mdt_dialout {
constexpr MdtDialoutArgs::MdtDialoutArgs(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : data_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , errors_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , reqid_(int64_t{0}){}
struct MdtDialoutArgsDefaultTypeInternal {
  constexpr MdtDialoutArgsDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~MdtDialoutArgsDefaultTypeInternal() {}
  union {
    MdtDialoutArgs _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT MdtDialoutArgsDefaultTypeInternal _MdtDialoutArgs_default_instance_;
}  // namespace mdt_dialout
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_cisco_5fdialout_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_cisco_5fdialout_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_cisco_5fdialout_2eproto = nullptr;

const uint32_t TableStruct_cisco_5fdialout_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::mdt_dialout::MdtDialoutArgs, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::mdt_dialout::MdtDialoutArgs, reqid_),
  PROTOBUF_FIELD_OFFSET(::mdt_dialout::MdtDialoutArgs, data_),
  PROTOBUF_FIELD_OFFSET(::mdt_dialout::MdtDialoutArgs, errors_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::mdt_dialout::MdtDialoutArgs)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::mdt_dialout::_MdtDialoutArgs_default_instance_),
};

const char descriptor_table_protodef_cisco_5fdialout_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\023cisco_dialout.proto\022\013mdt_dialout\"=\n\016Md"
  "tDialoutArgs\022\r\n\005ReqId\030\001 \001(\003\022\014\n\004data\030\002 \001("
  "\014\022\016\n\006errors\030\003 \001(\t2^\n\016gRPCMdtDialout\022L\n\nM"
  "dtDialout\022\033.mdt_dialout.MdtDialoutArgs\032\033"
  ".mdt_dialout.MdtDialoutArgs\"\000(\0010\001b\006proto"
  "3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_cisco_5fdialout_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_cisco_5fdialout_2eproto = {
  false, false, 201, descriptor_table_protodef_cisco_5fdialout_2eproto, "cisco_dialout.proto", 
  &descriptor_table_cisco_5fdialout_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_cisco_5fdialout_2eproto::offsets,
  file_level_metadata_cisco_5fdialout_2eproto, file_level_enum_descriptors_cisco_5fdialout_2eproto, file_level_service_descriptors_cisco_5fdialout_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_cisco_5fdialout_2eproto_getter() {
  return &descriptor_table_cisco_5fdialout_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_cisco_5fdialout_2eproto(&descriptor_table_cisco_5fdialout_2eproto);
namespace mdt_dialout {

// ===================================================================

class MdtDialoutArgs::_Internal {
 public:
};

MdtDialoutArgs::MdtDialoutArgs(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:mdt_dialout.MdtDialoutArgs)
}
MdtDialoutArgs::MdtDialoutArgs(const MdtDialoutArgs& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  data_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    data_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_data().empty()) {
    data_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_data(), 
      GetArenaForAllocation());
  }
  errors_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    errors_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_errors().empty()) {
    errors_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_errors(), 
      GetArenaForAllocation());
  }
  reqid_ = from.reqid_;
  // @@protoc_insertion_point(copy_constructor:mdt_dialout.MdtDialoutArgs)
}

inline void MdtDialoutArgs::SharedCtor() {
data_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  data_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
errors_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  errors_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
reqid_ = int64_t{0};
}

MdtDialoutArgs::~MdtDialoutArgs() {
  // @@protoc_insertion_point(destructor:mdt_dialout.MdtDialoutArgs)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void MdtDialoutArgs::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  data_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  errors_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void MdtDialoutArgs::ArenaDtor(void* object) {
  MdtDialoutArgs* _this = reinterpret_cast< MdtDialoutArgs* >(object);
  (void)_this;
}
void MdtDialoutArgs::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void MdtDialoutArgs::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void MdtDialoutArgs::Clear() {
// @@protoc_insertion_point(message_clear_start:mdt_dialout.MdtDialoutArgs)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  data_.ClearToEmpty();
  errors_.ClearToEmpty();
  reqid_ = int64_t{0};
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* MdtDialoutArgs::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int64 ReqId = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          reqid_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // bytes data = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_data();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // string errors = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_errors();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "mdt_dialout.MdtDialoutArgs.errors"));
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* MdtDialoutArgs::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:mdt_dialout.MdtDialoutArgs)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int64 ReqId = 1;
  if (this->_internal_reqid() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(1, this->_internal_reqid(), target);
  }

  // bytes data = 2;
  if (!this->_internal_data().empty()) {
    target = stream->WriteBytesMaybeAliased(
        2, this->_internal_data(), target);
  }

  // string errors = 3;
  if (!this->_internal_errors().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_errors().data(), static_cast<int>(this->_internal_errors().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "mdt_dialout.MdtDialoutArgs.errors");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_errors(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:mdt_dialout.MdtDialoutArgs)
  return target;
}

size_t MdtDialoutArgs::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:mdt_dialout.MdtDialoutArgs)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes data = 2;
  if (!this->_internal_data().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_data());
  }

  // string errors = 3;
  if (!this->_internal_errors().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_errors());
  }

  // int64 ReqId = 1;
  if (this->_internal_reqid() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64SizePlusOne(this->_internal_reqid());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData MdtDialoutArgs::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    MdtDialoutArgs::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*MdtDialoutArgs::GetClassData() const { return &_class_data_; }

void MdtDialoutArgs::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<MdtDialoutArgs *>(to)->MergeFrom(
      static_cast<const MdtDialoutArgs &>(from));
}


void MdtDialoutArgs::MergeFrom(const MdtDialoutArgs& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:mdt_dialout.MdtDialoutArgs)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_data().empty()) {
    _internal_set_data(from._internal_data());
  }
  if (!from._internal_errors().empty()) {
    _internal_set_errors(from._internal_errors());
  }
  if (from._internal_reqid() != 0) {
    _internal_set_reqid(from._internal_reqid());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void MdtDialoutArgs::CopyFrom(const MdtDialoutArgs& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:mdt_dialout.MdtDialoutArgs)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MdtDialoutArgs::IsInitialized() const {
  return true;
}

void MdtDialoutArgs::InternalSwap(MdtDialoutArgs* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &data_, lhs_arena,
      &other->data_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      &errors_, lhs_arena,
      &other->errors_, rhs_arena
  );
  swap(reqid_, other->reqid_);
}

::PROTOBUF_NAMESPACE_ID::Metadata MdtDialoutArgs::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_cisco_5fdialout_2eproto_getter, &descriptor_table_cisco_5fdialout_2eproto_once,
      file_level_metadata_cisco_5fdialout_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace mdt_dialout
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::mdt_dialout::MdtDialoutArgs* Arena::CreateMaybeMessage< ::mdt_dialout::MdtDialoutArgs >(Arena* arena) {
  return Arena::CreateMessageInternal< ::mdt_dialout::MdtDialoutArgs >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
