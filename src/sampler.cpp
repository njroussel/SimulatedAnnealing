#include <mcaa/sampler.h>
#include <mcaa/helpers.h>

using namespace std;

Sampler::Sampler(int N, uint32_t seed) { 
    m_rng.seed(seed);
    m_X.reserve(N);

    for(int i = 0; i < N; i++) {
        int value = signFloat(m_rng.nextFloat());
        m_X.push_back(Sample(value, value));
    }
}

void Sampler::accept(int index) {
}

void Sampler::reject(int index) {
    Sample &sample = m_X[index];
    sample.restore();
}

void Sampler::swap(int index) {
    Sample &sample = m_X[index];
    sample.backup();
    sample.value = -1 * sample.value;
}
