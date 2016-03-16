
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"


namespace fxc
{
	// A code generation context
	struct CodeGen
	{
		clang::ASTContext& astContext;
	};


	struct CodeGenVisitor : public clang::RecursiveASTVisitor<CodeGenVisitor>
	{
	public:
		CodeGenVisitor(CodeGen& CG_) : CG(CG_)
		{}

		bool VisitCXXRecordDecl(clang::CXXRecordDecl* decl)
		{
			return true;
		}

	protected:
		CodeGen& CG;
	};
}