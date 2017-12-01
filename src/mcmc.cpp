#include <mcaa/mcmc.h>

using namespace std; 

void MCMCRunner::run()  {
    Float currentE = computeEnergy(m_patterns, m_sampler.getSamples(), m_classes);
    
    for(int i = 0; i < m_mutationCount; i++) {
        int index = (int) (m_rng.nextFloat() / m_sampler.size());
        m_sampler.swap(index);
            
        Float proposedE = computeEnergy(m_patterns, m_sampler.getSamples(), m_classes);
        Float tmpAccept = computeGibbsBoltzmann(m_beta, 

    }
    
}
