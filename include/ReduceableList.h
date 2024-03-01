#pragma once

namespace Barta {
    template<typename List, typename T>
    concept ListConcept = 
        requires (List list, T t) {
            { list.push_back(t) } -> std::same_as<void>;
            { list.push_back(std::move(t)) } -> std::same_as<void>;
            { List::iterator };
            { list.begin() } -> std::forward_iterator;
            { list.end() } -> std::forward_iterator;
        };
        
    template<typename List, typename T>
    concept ReducableListConcept = 
        ListConcept<List, T> && 
        requires (List list, T t) {
            { list.reduce() };
        };

	template<typename List>
	class ReducibleList:public List {
		public:
		void reduce() {
			auto i = this->begin();
			while (i != this->end()) {
				if ((*i)->isToBeDeleted()) {
					i = this->erase(i);
					continue;
				}

				i++;
			}
		}
	};

}