#include "Driver.hpp"

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/CodeGen/ModuleBuilder.h"
#include "clang/CodeGen/CodeGenAction.h"
#include "clang/Serialization/ASTReader.h"

#include "Sema.hpp"

namespace fxc
{
	void Driver::HandleTranslationUnit(clang::ASTContext& context)
	{
		Sema sema;
		sema.TraverseDecl(context.getTranslationUnitDecl());
	}
}