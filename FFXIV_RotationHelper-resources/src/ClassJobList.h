#pragma once

namespace FFXIV_RotationHelper_resources
{
	class ClassJob;
	class WebReader;

	constexpr int ClassJobCount = 19;

	class ClassJobList
	{
	public:
		struct Iterator
		{
			ClassJob* i;

			Iterator(ClassJob* _i);

			bool operator==(const Iterator& other) const;

			bool operator!=(const Iterator& other) const;

			Iterator& operator++();

			const ClassJob& operator*() const;
		};

	public:
		ClassJobList(const WebReader& webReader);

		~ClassJobList();

		Iterator begin() const;

		Iterator end() const;

	private:
		ClassJob* jobs;
	};
}