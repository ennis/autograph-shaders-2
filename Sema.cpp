#include "Sema.hpp"
#include "clang/CodeGen/CodeGenAction.h"

namespace fxc
{
	namespace
	{

	}

	bool Sema::VisitCXXRecordDecl(clang::CXXRecordDecl* D)
	{
		// We only care about definitions
		if (!D->isCompleteDefinition())
			return true;

		const clang::AGFXBuiltinTypeAttr* attr = nullptr;
		auto specDeclKind = GetSpecialDeclKind(D, attr);
		if (specDeclKind == SpecialDeclKind::ProgramPipeline) {
			CheckProgramPipeline(D);
		}
		else if (specDeclKind == SpecialDeclKind::BuiltinType) {
			// TODO consistency check for builtin types?
		}
		else {
			// Not a special type
			CheckCXXRecord(D);
		}

		llvm::errs() << "CXXRecordDecl " << D->getQualifiedNameAsString() << "\n";
		return true;
	}

	bool Sema::VisitCXXMethodDecl(clang::CXXMethodDecl * MD)
	{
		
	}

	bool Sema::VisitFunctionDecl(clang::FunctionDecl * D)
	{
		llvm::errs() << "FunctionDecl " << D->getQualifiedNameAsString() << "\n";
		return true;
	}

	bool Sema::VisitVarDecl(clang::VarDecl * D)
	{
		llvm::errs() << "VarDecl " << D->getQualifiedNameAsString() << "\n";
		return true;
	}

	bool Sema::TraverseCXXRecordDecl(clang::CXXRecordDecl * D)
	{
		VisitCXXRecordDecl(D);
		return true;
	}
}