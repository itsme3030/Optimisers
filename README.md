# 🔧 Optimisers

A collection of efficient probabilistic data structures and algorithms implemented in C++ for space-efficient data processing and estimation. Currently includes:

- 🌸 **Bloom Filter** — For fast membership checks with a controlled false positive rate.
- 📊 **HyperLogLog** — For cardinality (distinct count) estimation using sublinear space.

---

## 📂 Contents

### 1. Bloom Filter
A probabilistic data structure that allows testing whether an element is a member of a set, with false positives but no false negatives.

📁 File: `bloom_filter.cpp`

**Features:**
- Uses multiple hash functions to reduce false positive probability.
- Supports insertion and membership check.
- Configurable bit array size and hash count.

**Use Cases:**
- Caches
- Web crawlers
- Spell checkers
- Network packet analysis

---

### 2. HyperLogLog
A probabilistic algorithm used for estimating the number of distinct elements (cardinality) in a dataset with high accuracy and low memory usage.

📁 File: `hyper_log_log.cpp`

**Features:**
- Uses stochastic averaging and registers.
- Space complexity: O(log log n)
- Great for large-scale streaming data.

**Use Cases:**
- Analytics platforms (like counting unique visitors)
- Large-scale telemetry and logging systems