#ifndef MODULE_HPP
#define MODULE_HPP

#include <unordered_map>

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"


namespace fxc
{
	class Record
	{
	public:
		Record(const clang::CXXRecordDecl* decl) : clangDecl(decl)
		{}

		const clang::CXXRecordDecl* getClangDecl() const {
			return clangDecl;
		}

	private:
		const clang::CXXRecordDecl* clangDecl;
	};

	class ProgramPipeline
	{
	public:
		ProgramPipeline(const clang::CXXRecordDecl* decl) : clangDecl(decl)
		{}

		const clang::CXXRecordDecl* getClangDecl() const {
			return clangDecl;
		}
	private:
		const clang::CXXRecordDecl* clangDecl;
	};


	class Module
	{
	public:
		Record* addExportedRecordDecl(const clang::CXXRecordDecl* decl);
		ProgramPipeline* addProgramPipelineDecl(const clang::CXXRecordDecl* decl);

	private:
		clang::Module* clangModule;
		// List of exported record declarations
		std::vector<std::unique_ptr<Record> > exportedRecordDecls;
		std::vector<std::unique_ptr<ProgramPipeline> > programPipelines;
	};
}

#endif // !MODULE_HPP
