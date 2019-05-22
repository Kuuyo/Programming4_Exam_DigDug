#include "MiniginPCH.h"
#include "SubjectComponent.h"

namespace dae
{
	SubjectComponent::SubjectComponent(std::string &&subjectName)
		: Subject(std::move(subjectName))
	{}

	void SubjectComponent::Notify(int nrArgs, ...)
	{
		va_list ap;
		va_start(ap, nrArgs);
		Subject::Notify(this, ap, nrArgs);
		va_end(ap);
	}
}