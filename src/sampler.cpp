#include <mcaa/sampler.h>

using namespace std;

Sampler::Sample::Sample(int N) {
}

Sampler::Sampler(int N, uint32_t seed) : m_X(N) { 
    m_rng.seed(seed);
}

void Sampler::accept(int index) {
}

void Sampler::reject(int index) {
}

void Sampler::swap(int index) {
    m_currentIndex = index;
}
