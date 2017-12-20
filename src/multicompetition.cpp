#include <thread>
#include <mcaa/multicompetition.h>

using namespace std; 

void MultiCompetitionRunner::runJobs(int index) {
    int currentIndex = index;
    while (currentIndex < m_jobsCount) {
        (m_runners[currentIndex])->run();
        currentIndex += m_workerCount; 
    }
}

void MultiCompetitionRunner::runAll() {
    vector<std::thread> workers;
    workers.reserve(m_workerCount);

    for (int i = 0; i < m_workerCount; i++) {
        workers.push_back(thread(&MultiCompetitionRunner::runJobs, this, i));
    }

    for (int i = 0; i < m_workerCount; i++) {
        workers[i].join();
    }
}
