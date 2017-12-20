#include <iostream>
#include <mcaa/competition.h>
#include <mcaa/helpers.h>

using namespace std; 

void CompetitionRunner::run()  {
    Float currentE = computeEnergy(m_patterns, m_sampler.getSamples(), m_classes);

    if (m_measureStep != 0) {
        m_EMeasures(0) = currentE;
    }

    for(int i = 0; i < m_mutationCount; i++) {
        int index = (int) (m_rng.nextFloat() * m_sampler.size());
        m_sampler.mutate(index);

        Float proposedE = computeEnergy(m_patterns, m_sampler.getSamples(), m_classes);

        Float tmpAccept = computeGibbsBoltzmann(m_schedule.computeNextTemp(), currentE, proposedE);
        Float accept = 1.0 < tmpAccept ? 1.0 : tmpAccept;

        if (m_rng.nextFloat() < accept) {
            m_sampler.accept();
            currentE = proposedE;
        } else {
            m_sampler.reject();
        }

        if (currentE == 0) {
            if (m_measureStep == 0) {
                m_EMeasures(0) = currentE;
            } else {
                m_EMeasures(m_EMeasures.size() - 1) = currentE;
            }
            cout << "DONE !!!" << endl;
            return;
        }

        if (m_measureStep != 0 && i % m_measureStep == 0) {
            int measureIndex =  1 + i / m_measureStep; 
            m_EMeasures(measureIndex) = currentE;
        }
    }

    if (m_measureStep == 0) {
        m_EMeasures(0) = currentE;
    } else {
        m_EMeasures(m_EMeasures.size() - 1) = currentE;
    }
}
