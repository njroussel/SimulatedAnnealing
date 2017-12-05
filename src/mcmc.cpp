#include <mcaa/mcmc.h>

using namespace std; 

void MCMCRunner::run()  {
    Float currentE = computeEnergy(m_patterns, m_sampler.getSamples(), m_classes);

    for(int i = 0; i < m_mutationCount; i++) {
        int index = (int) (m_rng.nextFloat() * m_sampler.size());
        m_sampler.swap(index);

        Float proposedE = computeEnergy(m_patterns, m_sampler.getSamples(), m_classes);

        Float tmpAccept = computeGibbsBoltzmann(m_beta, currentE, proposedE);
        Float accept = 1.0 < tmpAccept ? 1.0 : tmpAccept;

        if (m_rng.nextFloat() < accept) {
            m_sampler.accept(index);
            currentE = proposedE;
        } else {
            m_sampler.reject(index);
        }

        if (i % m_measureStep == 0) {
            int measureIndex = i / m_measureStep; 
            m_EMeasures(measureIndex) = currentE;
        }
    }
}
