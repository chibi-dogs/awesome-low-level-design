## Production-Grade LRU Cache System Design

### Problem Statement

Design and implement a production-ready, thread-safe LRU Cache that can survive in a real-world distributed system. This goes beyond a textbook implementation - you need to handle failures, observability, and operational concerns.

### Core Requirements

#### Basic LRU Operations

- `get(key)`: Return the value if key exists, otherwise return null/optional
- `put(key, value)`: Insert or update key-value pair
- `remove(key)`: Explicitly remove an entry
- All operations update the "recently used" status

#### Capacity Management

- Fixed maximum capacity with optional soft/hard limits
- Support for both item count limits AND memory size limits
- Dynamic capacity adjustment based on memory pressure

#### Thread Safety with Performance

- Multiple threads can read/write concurrently
- Use modern C++ primitives (std::shared_mutex, lock-free structures)
- Optimize for read-heavy workloads (90% reads, 10% writes)
- Minimize lock contention using sharding/partitioning

### Advanced Requirements

#### Tiered Eviction Policy

- Priority levels: CRITICAL, HIGH, NORMAL, LOW
- CRITICAL items are never evicted (pinned)
- Support pluggable eviction strategies (LRU, LFU, FIFO) via Strategy pattern

#### TTL & Expiration

- Per-entry TTL support
- Passive expiration (on access) + Active expiration (background thread)
- Graceful handling of time synchronization issues

#### Observability & Monitoring

- Prometheus-style metrics: hit_rate, miss_rate, eviction_count, latency_p99
- Structured logging with correlation IDs
- Health check endpoint
- Eviction callbacks with full context (reason, timestamp, stats)

### Real-World Engineering Constraints 🔥

#### 7. Crash Recovery & Persistence

**Scenario:** Your service crashes. How do you recover the cache state?

**Requirements:**

- Implement Write-Ahead Logging (WAL) for all mutations
- Support snapshotting at configurable intervals
- Handle partial writes and corrupted snapshots
- Implement recovery reconciliation with source of truth
- Support both synchronous and asynchronous persistence modes

**Trade-offs to discuss:**

- Performance impact of synchronous writes
- Recovery time vs snapshot frequency
- Consistency guarantees (what if snapshot is stale?)

#### 8. Memory Pressure & Adaptive Sizing

**Scenario:** System memory is running low. Your cache is consuming too much RAM.

**Requirements:**

- Monitor system memory via meminfo or similar
- Implement adaptive eviction when memory pressure is detected
- Support emergency cache draining
- Provide memory usage estimation for each entry (including overhead)
- Handle memory allocation failures gracefully

#### 9. Hot Key Problem

**Scenario:** A single key is accessed by thousands of threads causing lock contention.

**Requirements:**

- Detect hot keys using probabilistic counting (Count-Min Sketch)
- Implement thread-local caching for hot keys
- Support read replicas for critical keys
- Provide hooks to promote hot keys to upper cache tiers

#### 10. Cache Stampede Protection

**Scenario:** Cache miss on popular key causes 1000 threads to hit database simultaneously.

**Requirements:**

- Implement request coalescing (only one thread loads, others wait)
- Support probabilistic early expiration to prevent thundering herd
- Provide async refresh before expiration (refresh-ahead)
- Handle loader function failures gracefully

#### 11. Distributed Cache Coherency

**Scenario:** You have 10 instances of your service, each with local cache. How do you invalidate?

**Requirements:**

- Implement cache invalidation notifications (pub/sub pattern)
- Handle network partitions gracefully
- Support versioning to detect stale entries
- Provide eventual consistency guarantees
- Handle clock skew between nodes

#### 12. Graceful Degradation

**Scenario:** Cache is unavailable (disk full, corrupted). Service should continue working.

**Requirements:**

- Implement circuit breaker pattern for persistence layer
- Fallback to in-memory only mode if persistence fails
- Support read-only mode for diagnostics
- Provide configurable failure policies (fail-fast vs best-effort)

#### 13. Testing Challenges

**Requirements:**

- Write tests that simulate crashes mid-write
- Test concurrent access with thread sanitizer
- Benchmark with realistic workloads (Zipfian distribution)
- Test memory leak scenarios with valgrind/ASAN
- Test clock skew and time jumping scenarios

### Modern C++ Implementation Expectations

#### Design Patterns to Demonstrate

- **Strategy Pattern:** Pluggable eviction policies
- **Observer Pattern:** Eviction callbacks, metrics
- **Template Method:** Persistence layer abstraction
- **Circuit Breaker:** Fault tolerance for persistence
- **Factory Pattern:** Create cache with different configurations
- **RAII:** Lock guards, resource handles
- **Singleton (if needed):** Global cache instance

### Evaluation Criteria

#### System Design (30%)

- How well do you handle real-world failures?
- Trade-off discussions (consistency vs performance)
- Scalability considerations

#### Code Quality (30%)

- Modern C++ idioms (smart pointers, RAII, move semantics)
- SOLID principles adherence
- Error handling with exceptions vs error codes
- Const correctness and type safety

#### Concurrency (20%)

- Proper use of mutexes, atomics, memory ordering
- Deadlock prevention
- Lock-free data structures where appropriate

#### Testing & Operations (20%)

- Testability of design
- Observability hooks
- Operational runbooks consideration

### Discussion Questions

- How would you handle a corrupted WAL file during recovery?
- What's your strategy for upgrading cache schema without downtime?
- How do you prevent memory fragmentation in long-running processes?
- If persistence is 2x slower than expected, what's your mitigation?
- How would you debug a production issue where hit rate drops by 50%?
- What metrics would you alert on for this cache?
- How do you handle schema evolution (adding new fields to cached objects)?

### Expected Time: 60-75 minutes

This is a production-grade system design problem. Focus on demonstrating:

- Deep understanding of real-world engineering challenges
- Pragmatic trade-off decisions
- Clean, maintainable, observable code
- Thinking beyond the happy path
