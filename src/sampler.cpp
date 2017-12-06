#include <mcaa/sampler.h>
#include <mcaa/helpers.h>

using namespace std;

Sampler::Sample::Sample(int N, uint32_t seed) : values(N) {
    pcg32 rng;
    rng.seed(seed);

    for (int i = 0; i < N; i++) {
        values(i) = signFloat(rng.nextFloat() - 0.5);
    }
}

Sampler::Sampler(int N, uint32_t seed) : m_sample(N, seed), m_currentIndex(0) { 
}

void Sampler::accept() {
}

void Sampler::reject() {
    m_sample.swap(m_currentIndex);
}

void Sampler::mutate(int index) {
    m_currentIndex = index;
    m_sample.swap(index);
}
