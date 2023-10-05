#include "grammar.h"

#include <iostream>

#define CHECK(cond)                                                   \
  if (!(cond)) {                                                      \
    std::cerr << "Check Failed: " << #cond << ", " << __FILE__ << ":" \
              << __LINE__;                                            \
  }

namespace gram {

GrammarBuilder GrammarBuilder::CreateNode(std::string node_name) {
  grammar_.nodes_[node_name] = Node{node_name, {}, {}};
  return *this;
}

GrammarBuilder GrammarBuilder::AddNodeField(std::string node_name,
                                            std::string field_name,
                                            ElemType ty) {
  grammar_.nodes_[node_name].fields[field_name] = Field{field_name, ty};
  return *this;
}

GrammarBuilder GrammarBuilder::AddNodeField(std::string node_name,
                                            std::string field_name,
                                            ChildType ty) {
  grammar_.nodes_[node_name].fields[field_name] = Field{field_name, ty};
  return *this;
}

GrammarBuilder GrammarBuilder::AddNodeSeq(std::string node_name,
                                          std::vector<std::string> seq) {
  grammar_.nodes_[node_name].seq = seq;
  return *this;
}

Grammar GrammarBuilder::build() { return grammar_; }

}  // namespace gram
