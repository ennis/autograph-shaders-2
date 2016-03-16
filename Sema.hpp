#ifndef SEMA_HPP
#define SEMA_HPP

#include <clang/AST/RecursiveASTVisitor.h>
#include <clang/AST/Attr.h>
#include <clang/CodeGen/ModuleBuilder.h>

#include "GLSLTypes.hpp"

namespace fxc
{
	class Sema : public clang::RecursiveASTVisitor<Sema>
	{
	public:
		Sema() : 
			IntTy(GLSLScalarKind::Int),
			UIntTy(GLSLScalarKind::UInt),
			FloatTy(GLSLScalarKind::Float),
			DoubleTy(GLSLScalarKind::Double),
			BoolTy(GLSLScalarKind::Bool)
		{}

		bool VisitCXXMethodDecl(clang::CXXMethodDecl * MD);
		bool VisitCXXRecordDecl(clang::CXXRecordDecl* D);
		bool VisitFunctionDecl(clang::FunctionDecl* D);
		bool VisitVarDecl(clang::VarDecl* D);
		bool TraverseCXXRecordDecl(clang::CXXRecordDecl* D);

	private:
		enum class SpecialDeclKind
		{
			NotSpecial,
			ProgramPipeline,
			BuiltinType
		};

		// [SemaRecord.cpp]
		// Verify classes and structs that are not program pipelines
		bool CheckCXXRecord(clang::CXXRecordDecl* Declaration);
		
		// [SemaPipelines.cpp]
		// Verify program pipelines
		bool CheckProgramPipeline(clang::CXXRecordDecl* Declaration);
		
		// [SemaType.cpp]
		// Is it the declaration of a special type or function?
		SpecialDeclKind GetSpecialDeclKind(const clang::Decl * D, const clang::AGFXBuiltinTypeAttr*& kind);

		// list of program pipelines
		// list of declarations to export

		GLSLScalarType IntTy;
		GLSLScalarType UIntTy;
		GLSLScalarType FloatTy;
		GLSLScalarType DoubleTy;
		GLSLScalarType BoolTy;
	};
}

#endif // !SEMA_HPP
