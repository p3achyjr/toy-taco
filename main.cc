#include <filesystem>
#include <fstream>
#include <string>

#include "codegen.h"
#include "grammar.h"

namespace {
using namespace ::codegen;
using namespace ::gram;
namespace fs = std::filesystem;
}  // namespace

int main(int argc, char** argv) {
  GrammarBuilder bst_builder;
  Grammar bst_grammar = bst_builder.CreateNode("bst")
                            .AddNodeField("bst", "e", ElemType{1})
                            .AddNodeField("bst", "l", ChildType{"bst", 1})
                            .AddNodeField("bst", "r", ChildType{"bst", 1})
                            .AddNodeSeq("bst", {"l", "e", "r"})
                            .build();

  std::string bst_def = EmitStructs(bst_grammar);
  fs::path out_dir = "gen";
  if (!fs::exists(out_dir)) fs::create_directories(out_dir);
  fs::path out_path = out_dir / "bst.h";
  std::ofstream out_file(out_path);
  out_file << bst_def << "\n";
  out_file.close();

  return 0;
}
