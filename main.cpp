#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/ArgumentsAdjusters.h"

#include "llvm/Support/CommandLine.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/CodeGen/ModuleBuilder.h"
#include "clang/CodeGen/CodeGenAction.h"
#include "clang/Serialization/ASTReader.h"

#include <fstream>
#include <iostream>

#include "Driver.hpp"
#include "Module.hpp"

using namespace clang;
using namespace clang::ast_matchers;
using namespace clang::tooling;

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("agfxc options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static llvm::cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static llvm::cl::extrahelp MoreHelp("\nMore help text...");

/*
enum class ShaderStage
{
	VertexShader,
	FragmentShader,
	GeometryShader,
	TessEvalShader,
	TessControlShader,
	ComputeShader
};
*/

//////////////////// Main frontend action
class FXCDriverFrontendAction : public clang::ASTFrontendAction
{
public:
	virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(
		clang::CompilerInstance &Compiler, llvm::StringRef InFile) 
	{
		return std::unique_ptr<clang::ASTConsumer>(new fxc::Driver(Compiler.getASTContext(), Compiler.getDiagnostics()));
	}
};


//////////////////// Main 
int main(int argc, const char **argv) {
	CommonOptionsParser OptionsParser(argc, argv, MyToolCategory);
	ClangTool Tool(OptionsParser.getCompilations(),
					OptionsParser.getSourcePathList());
	Tool.appendArgumentsAdjuster(clang::tooling::getInsertArgumentAdjuster("-fmodules"));
   
	return Tool.run(newFrontendActionFactory<FXCDriverFrontendAction>().get());
}