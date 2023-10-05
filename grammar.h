#pragma once

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace gram {
struct ElemType {
  size_t size;
};

struct ChildType {
  std::string ty_name;
  size_t size;
};

using Type = std::variant<ElemType, ChildType>;

struct Field {
  std::string name;
  Type ty;
};

struct Node {
  std::string name;
  std::unordered_map<std::string, Field> fields;
  std::vector<std::string> seq;
};

struct Grammar {
  std::unordered_map<std::string, Node> nodes_;
};

class GrammarBuilder {
 public:
  GrammarBuilder() = default;
  ~GrammarBuilder() = default;

  GrammarBuilder CreateNode(std::string node_name);
  GrammarBuilder AddNodeField(std::string node_name, std::string field_name,
                              ElemType ty);
  GrammarBuilder AddNodeField(std::string node_name, std::string field_name,
                              ChildType ty);
  GrammarBuilder AddNodeSeq(std::string node_name,
                            std::vector<std::string> seq);
  Grammar build();

 private:
  Grammar grammar_;
};
};  // namespace gram
