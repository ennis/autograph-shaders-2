#include "Module.hpp"

namespace fxc
{
	Record*  Module::addExportedRecordDecl(const clang::CXXRecordDecl* decl)
	{
		auto r = std::make_unique<Record>(decl);
		auto ptr = r.get();
		exportedRecordDecls.emplace_back(std::move(r));
		return ptr;
	}

	ProgramPipeline* Module::addProgramPipelineDecl(const clang::CXXRecordDecl* decl)
	{
		auto pp = std::make_unique<ProgramPipeline>(decl);
		auto ptr = pp.get();
		programPipelines.emplace_back(std::move(pp));
		return ptr;
	}

}