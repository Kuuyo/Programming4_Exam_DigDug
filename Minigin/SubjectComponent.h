#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace dae
{
	class SubjectComponent final : public BaseComponent, public Subject
	{
	public:
		SubjectComponent(std::string &&subjectName);

		SubjectComponent(const SubjectComponent&) = delete;
		SubjectComponent(SubjectComponent&&) = delete;
		SubjectComponent& operator= (const SubjectComponent&) = delete;
		SubjectComponent& operator= (const SubjectComponent&&) = delete;

		void Notify(int nrArgs, ...);

	protected:
		void Initialize(const SceneContext &) override {}
		void Update(const SceneContext &) override {}
		void LateUpdate(const SceneContext &) override {}

		~SubjectComponent() = default;
	};
}