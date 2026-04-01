#ifndef LLD_DESIGN_LRUCACHE_H
#define LLD_DESIGN_LRUCACHE_H
#include <list>
#include <optional>
#include <unordered_map>

template <typename Key, typename Value>
class LRUCache{
		using List = std::list<std::pair<Key, Value>>;
		using ListIt = List::iterator;
		using Map = std::unordered_map<Key, ListIt>;
		using MapIt = Map::iterator;
	public:
		explicit LRUCache(const std::size_t capacity)
		  : capacity_(capacity)
			{};

		[[nodiscard]] std::optional<Value> get(const Key& key) {
				if (const auto iter = cache_.find(key); iter != cache_.end()){
						values_.splice(values_.begin(), values_, iter->second);
						iter->second = values_.begin();
						return (values_.front()).second;
				}
				return std::nullopt;
		}

		void put(const Key& key, const Value& input_value)
			{
				const auto iter = cache_.find(key);
				if (iter != cache_.end()) {
						update_kv_pair(iter, input_value);
				} else {
						add_kv_pair(key, input_value);
						if (cache_.size() > capacity_)
							{
								evict_least_recently_used_item();
							}
				}
			}
	private:
		std::size_t capacity_{};
		void evict_least_recently_used_item()
			{
				const auto last_elem = std::prev(values_.end());
				cache_.erase(last_elem->first);
				values_.pop_back();
			}
		void add_kv_pair(const Key &key, const Value& input_value)
			{
				values_.emplace_front(key, input_value);
				cache_.insert_or_assign(key, values_.begin());
			}
		void update_kv_pair(const MapIt& iter, const Value &input_value)
			{
				const auto kv_pair = iter->second;
				// move the node at key to front
				values_.splice(values_.begin(), values_, kv_pair);
				// since the key exists, I just update the value.
				kv_pair->second = input_value;
			}
		Map cache_{};
		List values_{};
};

#endif //LLD_DESIGN_LRUCACHE_H