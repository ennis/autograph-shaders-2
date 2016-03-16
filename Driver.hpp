#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <vector>
#include <memory>
#include <unordered_map>

#include "Module.hpp"
#include "clang/AST/ASTConsumer.h"

namespace fxc
{
	class Driver : public clang::ASTConsumer
	{
	public:
		Driver(clang::ASTContext& astContext_, clang::DiagnosticsEngine& DE_) :
			astContext(astContext_),
			DE(DE_)
		{}

		void HandleTranslationUnit(clang::ASTContext &context) override;
		
	private:
		clang::ASTContext& astContext;
		clang::DiagnosticsEngine& DE;
		//std::unordered_map<std::string, std::unique_ptr<Module> > moduleMap;
	};
}

#endif // !DRIVER_HPP
