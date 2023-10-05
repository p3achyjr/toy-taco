#include "codegen.h"

#include <iostream>
#include <sstream>
#include <variant>

namespace codegen {
namespace {
using namespace ::gram;
}

void EmitType(std::stringstream& ss, const Type& ty) {
  if (std::holds_alternative<ElemType>(ty)) {
    ss << "std::pair<int32_t, double>";
  } else {
    // ChildType.
    const ChildType& child_ty = std::get<ChildType>(ty);
    ss << child_ty.ty_name << "*";
  }
}

void EmitMaybeSize(std::stringstream& ss, const Type& ty) {
  if (std::holds_alternative<ElemType>(ty)) {
    const ElemType& elem_ty = std::get<ElemType>(ty);
    if (elem_ty.size > 1) {
      ss << "[" << elem_ty.size << "]";
    }
  } else {
    // ChildType.
    const ChildType& child_ty = std::get<ChildType>(ty);
    if (child_ty.size > 1) {
      ss << "[" << child_ty.size << "]";
    }
  }
}

void EmitField(std::stringstream& ss, const std::string& name,
               const Field& field) {
  ss << "  ";
  EmitType(ss, field.ty);
  ss << " " << field.name;
  EmitMaybeSize(ss, field.ty);
  ss << ";\n";
}

void EmitStruct(std::stringstream& ss, const std::string& name,
                const Node& node) {
  ss << "struct " << name << " {\n";
  for (const auto& [name, field] : node.fields) {
    EmitField(ss, name, field);
  }
  ss << "};\n";
}

std::string EmitStructs(gram::Grammar g) {
  std::stringstream ss;
  // emit fdecls.
  ss << "#pragma once\n";
  ss << "#include <cstdint>\n";
  ss << "#include <utility>\n";
  for (const auto& [name, _] : g.nodes_) {
    ss << "struct " << name << ";\n";
  }

  // emit structs in arbitrary order.
  for (const auto& [name, node] : g.nodes_) {
    ss << "\n";
    EmitStruct(ss, name, node);
  }

  return ss.str();
}

// std::string EmitMappers(gram::Grammar g);

}  // namespace codegen
