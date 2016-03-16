#include "Sema.hpp"

namespace fxc
{
	bool Sema::CheckCXXRecord(clang::CXXRecordDecl* Declaration)
	{
		auto& OS = llvm::errs();
		//OS << "CheckCXXRecord TODO\n";

		for (auto d : Declaration->fields())
		{
			// Check fields
			d->dump();
		}

		return false;
	}
}
