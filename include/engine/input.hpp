#ifndef __INPUT_H__
#define __INPUT_H__

#include <vector>
class Input
{
	public:
		static Input* instance()
		{
			static Input inputInstance;
			return &inputInstance;
		}
		void AddKey(int key, int action)
		{
			keys_.emplace_back(key, action);
		}
		void Clear()
		{
			keys_.clear();
		}
		std::vector<std::pair<int, int>>& GetKeys()
		{
			return keys_;
		}
	private:
		//Constructor
		Input() = default;
		//Destructor??? 
		~Input() = default;

		Input(const Input&) = default;
		Input(Input&&) = default;
		Input& operator = (const Input&) = default;
		Input& operator = (Input&&) = default;
		std::vector<std::pair<int, int>> keys_;

};

#endif // !__WINDOW_H__
