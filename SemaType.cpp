#include "Sema.hpp"

#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang;
using namespace clang::ast_matchers;

namespace fxc
{
	namespace
	{
		static DeclarationMatcher ProgramPipelineDeclMatcher =
			cxxRecordDecl(
				isDefinition(),
				isDerivedFrom(
					cxxRecordDecl(
						hasName("::ag::ProgramPipeline")))).bind("0");

		static DeclarationMatcher BuiltinTypeMatcher =
			decl(hasAttr(clang::attr::AGFXBuiltinType)).bind("0");

		struct CheckSpecialTypeCallback : public MatchFinder::MatchCallback
		{
			void run(const MatchFinder::MatchResult& result) override
			{
				match = true;
			}

			bool match = false;
		};
	}

	Sema::SpecialDeclKind Sema::GetSpecialDeclKind(const clang::Decl* D, const AGFXBuiltinTypeAttr*& attr)
	{
		MatchFinder MF;
		CheckSpecialTypeCallback CSTC_BuiltinTypeDecl;
		CheckSpecialTypeCallback CSTC_ProgPipelineDecl;
		MF.addMatcher(BuiltinTypeMatcher, &CSTC_BuiltinTypeDecl);
		MF.addMatcher(ProgramPipelineDeclMatcher, &CSTC_ProgPipelineDecl);
		MF.match(*D, D->getASTContext());
		if (CSTC_ProgPipelineDecl.match && CSTC_BuiltinTypeDecl.match) {
			// this is an internal error
			llvm::report_fatal_error("Inconsistent builtin types");
		}
		if (CSTC_ProgPipelineDecl.match) return SpecialDeclKind::ProgramPipeline;
		if (CSTC_BuiltinTypeDecl.match) {
			attr = D->getAttr<AGFXBuiltinTypeAttr>();
			return SpecialDeclKind::BuiltinType;
		}
		return SpecialDeclKind::NotSpecial;
	}
}